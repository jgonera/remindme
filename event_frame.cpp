#include "event_frame.h"

EventFrame::EventFrame(wxWindow* parent): EventFrameBase(parent) {
	EditedEvent = NULL;
	New = true;
	Alarms = NULL;
	CurrentAlarm = NULL;
	
	AlarmsImages = new wxImageList(16, 16);
	
	AlarmsImages->Add(wxBitmap(wxT("icons/popup.png"), wxBITMAP_TYPE_PNG));
	AlarmsImages->Add(wxBitmap(wxT("icons/clock.png"), wxBITMAP_TYPE_PNG));
	AlarmsImages->Add(wxBitmap(wxT("icons/sound.png"), wxBITMAP_TYPE_PNG));
	AlarmsList->AssignImageList(AlarmsImages, wxIMAGE_LIST_SMALL);
	
	AlarmsList->InsertColumn(0, _("Alarm"), wxLIST_FORMAT_LEFT, AlarmsList->GetClientSize().GetWidth() - wxSystemSettings::GetMetric(wxSYS_VSCROLL_X));
	
	AlarmPropertiesPanel->Hide();
	AlarmDescriptionLabel->Hide();
	AlarmDescriptionText->Hide();
}

void EventFrame::Closed(wxCloseEvent& event) {
	Destroy();
}

void EventFrame::CancelClicked(wxCommandEvent& event) {
	if (EditedEvent == NULL)
		delete Alarms;
	Close();
}

void EventFrame::OKClicked(wxCommandEvent& event) {
	if (SummaryText->GetValue().Len() == 0) {
		wxMessageBox(_("The summary cannot be empty."));
		return;
	}
	
	if (EditedEvent == NULL)
		EditedEvent = new Event;
	
	EditedEvent->Summary = SummaryText->GetValue().ToUTF8();
	EditedEvent->Description = DescriptionText->GetValue().ToUTF8();
	EditedEvent->Categories = CategoriesText->GetValue().ToUTF8();
	
	EditedEvent->DtStart << StartDatePicker->GetValue();
	if (SpecificTimeCheckBox->GetValue() == true) {
		EditedEvent->DtStart[HOUR] = StartHourSpinCtrl->GetValue();
		EditedEvent->DtStart[MINUTE] = StartMinuteSpinCtrl->GetValue();
		EditedEvent->DtStart.WithTime = true;
	} else
		EditedEvent->DtStart.Clear(true);
	
	if (EndDateCheckBox->GetValue() == true) {
		EditedEvent->DtEnd << EndDatePicker->GetValue();
		if (SpecificTimeCheckBox->GetValue() == true) {
			EditedEvent->DtEnd[HOUR] = EndHourSpinCtrl->GetValue();
			EditedEvent->DtEnd[MINUTE] = EndMinuteSpinCtrl->GetValue();
			EditedEvent->DtEnd.WithTime = true;
		} else
			EditedEvent->DtEnd.Clear(true);
	} else
		EditedEvent->DtEnd.Clear();
	
	if (RepeatCheckBox->GetValue() == true) {
		EditedEvent->RRule.Interval = IntervalSpinCtrl->GetValue();
		switch (FrequencyChoice->GetCurrentSelection()) {
			case YEARLY: EditedEvent->RRule.Freq = YEAR; break;
			case MONTHLY: EditedEvent->RRule.Freq = MONTH; break;
			case WEEKLY: EditedEvent->RRule.Freq = WEEK; break;
			case DAILY: EditedEvent->RRule.Freq = DAY; break;
			case HOURLY: EditedEvent->RRule.Freq = HOUR; break;
			case MINUTELY: EditedEvent->RRule.Freq = MINUTE; break;
		}
		
		if (UntilCheckBox->GetValue() == true)
			EditedEvent->RRule.Until << UntilDatePicker->GetValue();
		else
			EditedEvent->RRule.Until.Clear();
	} else
		EditedEvent->RRule.Clear();
	
	UpdateAlarm();
	if (Alarms != NULL) {
		delete EditedEvent->Alarms;
		EditedEvent->Alarms = Alarms;
	}
	
	MainFrame *Main = static_cast<MainFrame *>(GetParent());
	if (New)
		Main->Calendar->AddEvent(EditedEvent);
	else
		Main->Calendar->ModifyEvent(EditedEvent);
		
	Main->UpdateMonthEvents();
	Main->UpdateEvents();
	
	Close();
}

void EventFrame::LoadEvent(Event *EventPointer) {
	EditedEvent = EventPointer;
	Alarms = new list<Alarm>(*(EventPointer->Alarms));
	New = false;
	
	SummaryText->SetValue(wxString(EditedEvent->Summary.c_str(), wxConvUTF8));
	CategoriesText->SetValue(wxString(EditedEvent->Categories.c_str(), wxConvUTF8));
	DescriptionText->SetValue(wxString(EditedEvent->Description.c_str(), wxConvUTF8));
	
	StartDatePicker->SetValue(CreateWxDateTime(EditedEvent->DtStart));
	if (EditedEvent->DtStart.WithTime == true) {
		StartHourSpinCtrl->SetValue(EditedEvent->DtStart[HOUR]);
		StartMinuteSpinCtrl->SetValue(EditedEvent->DtStart[MINUTE]);
		SpecificTimeCheckBox->SetValue(true);
		EnableSpecificTime(true);
	}
	
	if (!EditedEvent->DtEnd.IsEmpty()) {
		EndDatePicker->SetValue(CreateWxDateTime(EditedEvent->DtEnd));
		EndDateCheckBox->SetValue(true);
		EnableEndDate(true);
		if (EditedEvent->DtEnd.WithTime == true) {
			EndHourSpinCtrl->SetValue(EditedEvent->DtEnd[HOUR]);
			EndMinuteSpinCtrl->SetValue(EditedEvent->DtEnd[MINUTE]);
			SpecificTimeCheckBox->SetValue(true);
			EnableSpecificTime(true);
		}
	}
	
	if (!EditedEvent->RRule.IsEmpty()) {
		RepeatCheckBox->SetValue(true);
		EnableRecurrence(true);
		IntervalSpinCtrl->SetValue(EditedEvent->RRule.Interval);
		
		switch (EditedEvent->RRule.Freq) {
			case YEAR: FrequencyChoice->Select(YEARLY); break;
			case MONTH: FrequencyChoice->Select(MONTHLY); break;
			case WEEK: FrequencyChoice->Select(WEEKLY); break;
			case DAY: FrequencyChoice->Select(DAILY); break;
			case HOUR: FrequencyChoice->Select(HOURLY); break;
			default: FrequencyChoice->Select(MINUTELY); break;
		}
		
		if (!EditedEvent->RRule.Until.IsEmpty()) {
			UntilDatePicker->SetValue(CreateWxDateTime(EditedEvent->RRule.Until));
			UntilCheckBox->SetValue(true);
			UntilDatePicker->Enable();
		}
	}
	
	LoadAlarms();
}

/// General page

void EventFrame::EndDateCheckBoxClicked(wxCommandEvent& event) {
	EnableEndDate(EndDateCheckBox->GetValue());
}

void EventFrame::SpecificTimeCheckBoxClicked(wxCommandEvent& event) {
	EnableSpecificTime(SpecificTimeCheckBox->GetValue());
}

void EventFrame::RepeatCheckBoxClicked(wxCommandEvent& event) {
	EnableRecurrence(RepeatCheckBox->GetValue());
}

void EventFrame::UntilCheckBoxClicked(wxCommandEvent& event) {
	UntilDatePicker->Enable(UntilCheckBox->GetValue());
}

void EventFrame::EnableEndDate(bool Enable) {
	EndDatePicker->Enable(Enable);

	if (Enable && SpecificTimeCheckBox->GetValue() == true) {
		EndHourSpinCtrl->Enable();
		EndMinuteSpinCtrl->Enable();
	} else {
		EndHourSpinCtrl->Disable();
		EndMinuteSpinCtrl->Disable();
	}
}

void EventFrame::EnableSpecificTime(bool Enable) {
	StartHourSpinCtrl->Enable(Enable);
	StartMinuteSpinCtrl->Enable(Enable);

	if (Enable && EndDateCheckBox->GetValue() == true) {
		EndHourSpinCtrl->Enable();
		EndMinuteSpinCtrl->Enable();
	} else {
		EndHourSpinCtrl->Disable();
		EndMinuteSpinCtrl->Disable();
	}
}

void EventFrame::EnableRecurrence(bool Enable) {
	IntervalSpinCtrl->Enable(Enable);
	FrequencyChoice->Enable(Enable);
	UntilCheckBox->Enable(Enable);
	UntilDatePicker->Enable(Enable && UntilCheckBox->GetValue() == true);
}

/// Alarms page

void EventFrame::LoadAlarms() {
	AlarmsList->DeleteAllItems();
	
	if (!Alarms->empty()) {
		int Index;
		wxString AlarmName;
		
		for (list<Alarm>::iterator AlarmsIterator = Alarms->begin(); AlarmsIterator != Alarms->end(); ++AlarmsIterator) {
			if ((*AlarmsIterator).Trigger.Value == 0) {
				AlarmName = _("At the start");
			} else {
				AlarmName = wxString::Format(wxT("%d "), (*AlarmsIterator).Trigger.Value);
				switch	((*AlarmsIterator).Trigger.Unit) {
					case HOUR: AlarmName += _("hour(s)"); break;
					case DAY: AlarmName += _("day(s)"); break;
					case WEEK: AlarmName += _("week(s)"); break;
					default: AlarmName += _("minute(s)"); break;
				}
				AlarmName += wxT(' ');
				if ((*AlarmsIterator).Trigger.Before)
					AlarmName += _("before");
				else
					AlarmName += _("after");
			}
			
			Index = AlarmsList->InsertItem(0, AlarmName);
			AlarmsList->SetItemImage(Index, (*AlarmsIterator).Action);
			AlarmsList->SetItemPtrData(Index, (wxUIntPtr)&(*AlarmsIterator));
			if (CurrentAlarm == &(*AlarmsIterator))
				AlarmsList->SetItemState(Index, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
		}
		
		if (CurrentAlarm == NULL)
			AlarmsList->SetItemState(0, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
	}
}

void EventFrame::UpdateAlarm() {
	if (CurrentAlarm != NULL) {
		CurrentAlarm->Action = (AlarmAction)AlarmTypeChoice->GetCurrentSelection();
		CurrentAlarm->Trigger.Value = AlarmTriggerSpinCtrl->GetValue();
		switch (AlarmTriggerUnitChoice->GetCurrentSelection()) {
			case HOURS: CurrentAlarm->Trigger.Unit = HOUR; break;
			case DAYS: CurrentAlarm->Trigger.Unit = DAY; break;
			case WEEKS: CurrentAlarm->Trigger.Unit = WEEK; break;
			default: CurrentAlarm->Trigger.Unit = MINUTE; break; 
		}
		CurrentAlarm->Trigger.Before = !AlarmBeforeAfterChoice->GetCurrentSelection();
		
		if (CurrentAlarm->Action == DISPLAY)
			CurrentAlarm->Description = AlarmDescriptionText->GetValue().ToUTF8();
	}
}

void EventFrame::LoadAlarm(Alarm *AlarmPointer) {
	CurrentAlarm = AlarmPointer;
	
	AlarmTypeChoice->Select(CurrentAlarm->Action);
	AlarmTriggerSpinCtrl->SetValue(CurrentAlarm->Trigger.Value);
	switch (CurrentAlarm->Trigger.Unit) {
		case HOUR: AlarmTriggerUnitChoice->Select(HOURS); break;
		case DAY: AlarmTriggerUnitChoice->Select(DAYS); break;
		case WEEK: AlarmTriggerUnitChoice->Select(WEEKS); break;
		default: AlarmTriggerUnitChoice->Select(MINUTES); break; 
	}
	AlarmBeforeAfterChoice->Select(!CurrentAlarm->Trigger.Before);
	if (CurrentAlarm->Action == DISPLAY) {
		AlarmDescriptionText->SetValue(wxString(CurrentAlarm->Description.c_str(), wxConvUTF8));
		
		AlarmDescriptionLabel->Show();
		AlarmDescriptionText->Show();
	} else {
		AlarmDescriptionLabel->Hide();
		AlarmDescriptionText->Hide();
	}
	
	AlarmPropertiesPanel->Show();
}

void EventFrame::AlarmSelected(wxListEvent& event) {
	// to prevent double UpdateAlarm() and unnecessary LoadAlarm() when the item
	// is selected by LoadAlarms() and not by the user
	if ((Alarm *)event.GetData() != CurrentAlarm) {
		UpdateAlarm();
		LoadAlarm((Alarm *)event.GetData());
	}
	DeleteAlaramButton->Enable();
}

void EventFrame::AlarmDeselected(wxListEvent& event) {
	UpdateAlarm();
	CurrentAlarm = NULL;
	DeleteAlaramButton->Disable();
	AlarmPropertiesPanel->Hide();
}

void EventFrame::AddAlarmClicked(wxCommandEvent& event) {
	if (Alarms == NULL)
		Alarms = new list<Alarm>;
	
	Alarms->push_back(Alarm());
	LoadAlarm(&Alarms->back());
	LoadAlarms();
}

void EventFrame::DeleteAlarmClicked(wxCommandEvent& event) {
	if (CurrentAlarm != NULL) {
		for (list<Alarm>::iterator Iterator = Alarms->begin(); Iterator != Alarms->end();) {
			if (&*Iterator == CurrentAlarm)
				Alarms->erase(Iterator++);
			else
				++Iterator;
		}
		
		CurrentAlarm = NULL;
		AlarmPropertiesPanel->Hide();
		LoadAlarms();
	}
}

void EventFrame::AlarmTypeChanged(wxCommandEvent& event) {
	if (AlarmTypeChoice->GetSelection() == DISPLAY) {
		AlarmDescriptionLabel->Show();
		AlarmDescriptionText->Show();
	} else {
		AlarmDescriptionLabel->Hide();
		AlarmDescriptionText->Hide();
	}
	
	UpdateAlarm();
	LoadAlarms();
}

void EventFrame::AlarmTriggerChanged(wxSpinEvent& event) {
	UpdateAlarm();
	LoadAlarms();
}

void EventFrame::AlarmTriggerUnitChanged(wxCommandEvent& event) {
	UpdateAlarm();
	LoadAlarms();
}

void EventFrame::AlarmBeforeAfterChanged(wxCommandEvent& event) {
	UpdateAlarm();
	LoadAlarms();
}
