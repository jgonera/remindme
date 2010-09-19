#include "main_frame.h"

MainFrame::MainFrame(wxWindow* parent): MainFrameBase(parent) {
	Quit = false;

	// it seems the default width of CalendarCtrl under GTK is a bit too small
#if defined(__WXGTK__)
	wxSize NewSize = CalendarCtrl->GetSize() + wxSize(10, 0);
	NewSize.SetHeight(-1);
	CalendarCtrl->SetMinSize(NewSize);
	SidePanel->Fit();
#endif

	// making calendar header less ugly
	CalendarCtrl->SetHeaderColours(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNTEXT), wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));

	// events list preparation
	EventsImages = new wxImageList(16, 16);
	EventsImages->Add(wxBitmap(wxT("icons/event.png"), wxBITMAP_TYPE_PNG));
	EventsImages->Add(wxBitmap(wxT("icons/recurrent.png"), wxBITMAP_TYPE_PNG));
	EventsImages->Add(wxBitmap(wxT("icons/alarm.png"), wxBITMAP_TYPE_PNG));
	EventsList->AssignImageList(EventsImages, wxIMAGE_LIST_SMALL);

	EventsList->InsertColumn(COLUMN_SUMMARY, _("Summary"), wxLIST_FORMAT_LEFT, 190);
	EventsList->InsertColumn(COLUMN_START, _("Start"), wxLIST_FORMAT_LEFT, 135);
	EventsList->InsertColumn(COLUMN_END, _("End"), wxLIST_FORMAT_LEFT, 135);
	EventsList->InsertColumn(COLUMN_CATEGORIES, _("Categories"), wxLIST_FORMAT_LEFT, 100);
	EventsList->InsertColumn(COLUMN_ALARM, _("A"), wxLIST_FORMAT_LEFT, 25);
	EventsList->InsertColumn(COLUMN_RECURRENCE, _("R"), wxLIST_FORMAT_LEFT, 45);

	PeriodPanel->Hide();

	ToolBar->EnableTool(wxID_DELETE, false);
	ToolBar->EnableTool(wxID_PROPERTIES, false);

	SortOptions.Descending = false;
	SortOptions.Column = COLUMN_START;

	Calendar = new ICalendar("calendar.ics");
	ViewQuery = new ICalendar::Query(Calendar);
	AlarmsQuery = new ICalendar::Query(Calendar);
	UpdateMonthEvents();
	UpdateEvents();

	Sound = new wxSound();

	Connect(wxEVT_TIMER, wxTimerEventHandler(MainFrame::CheckAlarms));
	AlarmsTimer = new wxTimer(this);
	AlarmsTimer->Start(60000);

	Icon = new MainFrame::TaskBarIcon(this);
	Icon->NormalIcon();
}

MainFrame::~MainFrame() {
	AlarmsTimer->Stop();
	delete AlarmsTimer;
	delete Sound;
	delete Calendar;
	delete Icon;
}

void MainFrame::Closed(wxCloseEvent& event) {
	if (Quit == false) {
		if (IsShown())
			Hide();

		event.Veto();
	} else
		event.Skip();
}

void MainFrame::UpdateEvents() {
	Event *CurrentEvent;
	int Index;

	ViewQuery->Criteria.From << FromDatePicker->GetValue();
	ViewQuery->Criteria.To << ToDatePicker->GetValue();
	ViewQuery->Criteria.To[HOUR] = 23;
	ViewQuery->Criteria.To[MINUTE] = 59;
	ViewQuery->Criteria.To[SECOND] = 59;

  EventsList->DeleteAllItems();

	ViewQuery->ResetPosition();
	while ((CurrentEvent = ViewQuery->GetNextEvent()) != NULL) {
		wxString Summary(CurrentEvent->Summary.c_str(), wxConvUTF8);
		wxString Categories(CurrentEvent->Categories.c_str(), wxConvUTF8);
		if (
		(SearchText->GetValue().IsEmpty() || Summary.Lower().Contains(SearchText->GetValue().Lower())) &&
		(CategoriesText->GetValue().IsEmpty() || Categories.Lower().Contains(CategoriesText->GetValue().Lower()))
		) {
			Index = EventsList->InsertItem(COLUMN_SUMMARY, Summary, ICON_EVENT);

			EventsList->SetItem(Index, COLUMN_START, wxString(CurrentEvent->DtStart.Format().c_str(), wxConvLibc));
			if (!CurrentEvent->DtEnd.IsEmpty())
				EventsList->SetItem(Index, COLUMN_END, wxString(CurrentEvent->DtEnd.Format().c_str(), wxConvLibc));
			else
				EventsList->SetItem(Index, COLUMN_END, wxT(""));
			EventsList->SetItem(Index, COLUMN_CATEGORIES, Categories);
			EventsList->SetItem(Index, COLUMN_ALARM, wxT(""), CurrentEvent->Alarms->empty() ? -1 : ICON_ALARM);
			if (CurrentEvent->RecurrenceNo > 0)
				EventsList->SetItem(Index, COLUMN_RECURRENCE, wxString::Format(wxT("%d"), CurrentEvent->RecurrenceNo), ICON_RECURRENT);
			else if (!CurrentEvent->RRule.IsEmpty())
				EventsList->SetItem(Index, COLUMN_RECURRENCE, wxT(""), ICON_RECURRENT);

			EventsList->SetItemPtrData(Index, (wxUIntPtr)CurrentEvent);
		}
	}

	ToolBar->EnableTool(wxID_DELETE, false);
	ToolBar->EnableTool(wxID_PROPERTIES, false);

	EventsList->SortItems(CompareEvents, (long)&SortOptions);
}

void MainFrame::UpdateMonthEvents() {
	Event *CurrentEvent;
	short DaysInMonth;
	wxCalendarDateAttr *Attr;

	ViewQuery->Criteria.From << CalendarCtrl->GetDate();
	ViewQuery->Criteria.From[DAY] = 1;
	ViewQuery->Criteria.To << CalendarCtrl->GetDate();
	DaysInMonth = ViewQuery->Criteria.To.DaysInMonth();
	ViewQuery->Criteria.To[DAY] = DaysInMonth;
	ViewQuery->Criteria.To[HOUR] = 23;
	ViewQuery->Criteria.To[MINUTE] = 59;
	ViewQuery->Criteria.To[SECOND] = 59;

	for (short i=1; i<=DaysInMonth; ++i)
		CalendarCtrl->ResetAttr(i);

	wxFont AttrFont(wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT));
	AttrFont.SetWeight(wxFONTWEIGHT_BOLD);

	ViewQuery->ResetPosition();
	while ((CurrentEvent = ViewQuery->GetNextEvent()) != NULL) {
		Attr = new wxCalendarDateAttr();
		Attr->SetFont(AttrFont);

		CalendarCtrl->SetAttr(CurrentEvent->DtStart[DAY], Attr);
	}

	CalendarCtrl->Refresh();
}

void MainFrame::NewEvent() {
	EventFrame *NewEventFrame = new EventFrame(this);
	NewEventFrame->Show();
}

void MainFrame::EditEvent(Event *EditedEvent = NULL) {
	EventFrame *EditedEventFrame = new EventFrame(this);

	if (EditedEvent == NULL && EventsList->GetSelectedItemCount() == 1)
		EditedEventFrame->LoadEvent(((Event *)EventsList->GetItemData(EventsList->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)))->BaseEvent);
	else
		EditedEventFrame->LoadEvent(EditedEvent);

	EditedEventFrame->Show();
}

void MainFrame::CheckAlarms(wxTimerEvent& event) {
	Event *CurrentEvent;
	PopupDialog *NewPopupDialog;

	AlarmsQuery->Criteria.From.SetToNow();
	AlarmsQuery->Criteria.To = AlarmsQuery->Criteria.From;
	AlarmsQuery->Criteria.To[SECOND] += 59;

	AlarmsQuery->ResetPosition();
	while ((CurrentEvent = AlarmsQuery->GetNextEvent(true)) != NULL) {
		for (list<Alarm>::iterator AlarmsIterator = CurrentEvent->Alarms->begin(); AlarmsIterator != CurrentEvent->Alarms->end(); ++AlarmsIterator) {
			if (AlarmsIterator->Active) {
				switch (AlarmsIterator->Action) {
					case DISPLAY:
						NewPopupDialog = new PopupDialog(this, CurrentEvent, *AlarmsIterator);
						NewPopupDialog->Show();
						NewPopupDialog->Raise();
						break;

					case AUDIO:
						Sound->Play(wxT("sound.wav"));
						break;

					case PROCEDURE:
					default:
						Icon->AlarmIcon(CurrentEvent);
						break;
				}
			}
		}
	}
}

/// SidePanel's children related

void MainFrame::CalendarCtrlChanged(wxCalendarEvent& event) {
	FromDatePicker->SetValue(CalendarCtrl->GetDate());
	ToDatePicker->SetValue(CalendarCtrl->GetDate());

	if (CalendarCtrl->GetDate().IsSameDate(wxDateTime::Today())) {
		PeriodPanel->Hide();
		ShowChoice->SetSelection(SHOW_TODAYS);
	} else {
		PeriodPanel->Show();
		ShowChoice->SetSelection(SHOW_SPECIFIC);
	}

	ViewQuery->Criteria.AllEvents = false;

	UpdateMonthEvents();
	UpdateEvents();
}

void MainFrame::ShowChanged(wxCommandEvent& event) {
	if (ShowChoice->GetSelection() == SHOW_SPECIFIC) {
		PeriodPanel->Show();
		ViewQuery->Criteria.AllEvents = false;
	} else {
		PeriodPanel->Hide();

		if (ShowChoice->GetSelection() == SHOW_TODAYS || ShowChoice->GetSelection() == SHOW_UPCOMING) {
			CalendarCtrl->SetDate(wxDateTime::Today());
			FromDatePicker->SetValue(wxDateTime::Today());

			if (ShowChoice->GetSelection() == SHOW_TODAYS)
				ToDatePicker->SetValue(wxDateTime::Today());
			else
				ToDatePicker->SetValue(wxDateTime::Today().Add(wxDateSpan(0, 0, 0, 7)));

			ViewQuery->Criteria.AllEvents = false;

			UpdateMonthEvents();
		} else if (ShowChoice->GetSelection() == SHOW_ALL) {
			ViewQuery->Criteria.AllEvents = true;
		}
	}

	UpdateEvents();
}

void MainFrame::FromDateChanged(wxDateEvent& event) {
	CalendarCtrl->SetDate(FromDatePicker->GetValue());
	if (FromDatePicker->GetValue() > ToDatePicker->GetValue())
		ToDatePicker->SetValue(FromDatePicker->GetValue());

	UpdateMonthEvents();
	UpdateEvents();
}

void MainFrame::ToDateChanged(wxDateEvent& event) {
	if (ToDatePicker->GetValue() < FromDatePicker->GetValue())
		FromDatePicker->SetValue(ToDatePicker->GetValue());

	UpdateEvents();
}

void MainFrame::QueryChanged(wxCommandEvent& event) {
	UpdateEvents();
}

/// EventsList related

void MainFrame::EventsSelected(wxListEvent& event) {
	ToolBar->EnableTool(wxID_DELETE, true);
	if (EventsList->GetSelectedItemCount() == 1)
		ToolBar->EnableTool(wxID_PROPERTIES, true);
	else
		ToolBar->EnableTool(wxID_PROPERTIES, false);
}

void MainFrame::EventsDeselected(wxListEvent& event) {
	if (EventsList->GetSelectedItemCount() == 0)
		ToolBar->EnableTool(wxID_DELETE, false);
	if (EventsList->GetSelectedItemCount() == 1)
		ToolBar->EnableTool(wxID_PROPERTIES, true);
	else
		ToolBar->EnableTool(wxID_PROPERTIES, false);
}

void MainFrame::ColumnClicked(wxListEvent& event) {
	if (SortOptions.Column == event.GetColumn()) {
		SortOptions.Descending = !SortOptions.Descending;
	} else {
		SortOptions.Column = event.GetColumn();
		SortOptions.Descending = false;
	}

	EventsList->SortItems(CompareEvents, (long)&SortOptions);
}

void MainFrame::ListDClick(wxMouseEvent& event) {
	EditEvent();
}

void MainFrame::DeleteKeyDown(wxListEvent& event) {
	if (event.GetKeyCode() == WXK_DELETE)
		DeleteClicked(event);
}

int wxCALLBACK CompareEvents(long Item1, long Item2, long SortInfo) {
	static wxString String1, String2;

	SortOptionsT *SortOptions = (SortOptionsT *)SortInfo;

	if (SortOptions->Column == COLUMN_RECURRENCE) {
		if (((Event *)Item1)->RecurrenceNo < ((Event *)Item2)->RecurrenceNo)
			return SortOptions->Descending ? 1 : -1;

		if (((Event *)Item1)->RecurrenceNo > ((Event *)Item2)->RecurrenceNo)
			return SortOptions->Descending ? -1 : 1;

		return 0;
	}

	switch (SortOptions->Column) {
		case COLUMN_SUMMARY:
			String1 = wxString::FromUTF8(((Event *)Item1)->Summary.c_str());
			String2 = wxString::FromUTF8(((Event *)Item2)->Summary.c_str());
			break;
		case COLUMN_START:
			String1 = wxString::FromUTF8(((Event *)Item1)->DtStart.Format().c_str());
			String2 = wxString::FromUTF8(((Event *)Item2)->DtStart.Format().c_str());
			break;
		case COLUMN_END:
			String1 = wxString::FromUTF8(((Event *)Item1)->DtEnd.Format().c_str());
			String2 = wxString::FromUTF8(((Event *)Item2)->DtEnd.Format().c_str());
			break;
		case COLUMN_CATEGORIES:
			String1 = wxString::FromUTF8(((Event *)Item1)->Categories.c_str());
			String2 = wxString::FromUTF8(((Event *)Item2)->Categories.c_str());
			break;
	}

	return SortOptions->Descending ? -String1.CmpNoCase(String2) : String1.CmpNoCase(String2);
}

/// ToolBar related

void MainFrame::NewClicked(wxCommandEvent& event) {
	NewEvent();
}

void MainFrame::DeleteClicked(wxCommandEvent& event) {
	if (EventsList->GetSelectedItemCount() > 0 &&
	wxMessageBox(
	wxString::Format(_("Are you sure you want to delete %d item(s)?"), EventsList->GetSelectedItemCount()),
	_("Confirmation"),
	wxYES_NO
	) == wxYES) {
		long Item = -1;

		while ((Item = EventsList->GetNextItem(Item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != -1) {
			Calendar->DeleteEvent(((Event *)EventsList->GetItemData(Item))->BaseEvent);
		}

		UpdateMonthEvents();
		UpdateEvents();
	}
}

void MainFrame::EditClicked(wxCommandEvent& event) {
	EditEvent();
}

void MainFrame::QuitClicked(wxCommandEvent& event) {
	Quit = true;
	Close();
}

/// TaskBar Icon related

MainFrame::TaskBarIcon::TaskBarIcon(MainFrame *Main): Main(Main), CurrentEvent(NULL) {
	Connect(wxEVT_TASKBAR_LEFT_DCLICK, wxTaskBarIconEventHandler(MainFrame::TaskBarIcon::IconDClick));
	Connect(TASKBAR_RESTORE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::TaskBarIcon::RestoreClicked));
	Connect(TASKBAR_NEW, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::TaskBarIcon::NewClicked));
	Connect(TASKBAR_QUIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::TaskBarIcon::QuitClicked));
}

void MainFrame::TaskBarIcon::IconDClick(wxTaskBarIconEvent &event) {
	if (CurrentEvent == NULL) {
		if (Main->IsShown())
			Main->Hide();
		else {
			Main->Show();
			Main->Raise();
		}
	} else {
		Main->EditEvent(CurrentEvent);
		NormalIcon();
		CurrentEvent = NULL;
	}
}

void MainFrame::TaskBarIcon::RestoreClicked(wxCommandEvent& event) {
	if (!Main->IsShown()) {
		Main->Show();
		Main->Raise();
	}
}

void MainFrame::TaskBarIcon::NewClicked(wxCommandEvent& event) {
	Main->NewEvent();
}

void MainFrame::TaskBarIcon::QuitClicked(wxCommandEvent& event) {
	Main->Quit = true;
	Main->Close();
}

wxMenu *MainFrame::TaskBarIcon::CreatePopupMenu() {
	wxMenu *Menu = new wxMenu;
	Menu->Append(TASKBAR_RESTORE, _("&Restore"));
	Menu->Append(TASKBAR_NEW, _("&New Event"));
	Menu->AppendSeparator();
	Menu->Append(TASKBAR_QUIT, _("&Quit"));

	return Menu;
}

void MainFrame::TaskBarIcon::NormalIcon() {
	SetIcon(wxIcon(wxT("icons/main.png"), wxBITMAP_TYPE_PNG), _("remind.me"));
}

void MainFrame::TaskBarIcon::AlarmIcon(Event *AlarmEvent) {
	CurrentEvent = AlarmEvent;
	SetIcon(wxIcon(wxT("icons/alarm.png"), wxBITMAP_TYPE_PNG), wxString(CurrentEvent->Summary.c_str(), wxConvUTF8));
}
