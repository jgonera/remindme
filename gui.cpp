///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 16 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "gui.h"

///////////////////////////////////////////////////////////////////////////

MainFrameBase::MainFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxDefaultSize );
	
	wxBoxSizer* MainSizer;
	MainSizer = new wxBoxSizer( wxHORIZONTAL );
	
	SidePanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxTAB_TRAVERSAL );
	wxBoxSizer* SidePanelSizer;
	SidePanelSizer = new wxBoxSizer( wxVERTICAL );
	
	CalendarCtrl = new wxCalendarCtrl( SidePanel, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxSize( -1,-1 ), 0|wxSTATIC_BORDER );
	SidePanelSizer->Add( CalendarCtrl, 0, wxEXPAND|wxALL, 10 );
	
	wxBoxSizer* ShowSizer;
	ShowSizer = new wxBoxSizer( wxHORIZONTAL );
	
	ShowLabel = new wxStaticText( SidePanel, wxID_ANY, _("Show:"), wxDefaultPosition, wxDefaultSize, 0 );
	ShowLabel->Wrap( -1 );
	ShowSizer->Add( ShowLabel, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString ShowChoiceChoices[] = { _("All events"), _("Today's events"), _("Upcoming week"), _("Specific period") };
	int ShowChoiceNChoices = sizeof( ShowChoiceChoices ) / sizeof( wxString );
	ShowChoice = new wxChoice( SidePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, ShowChoiceNChoices, ShowChoiceChoices, 0 );
	ShowChoice->SetSelection( 1 );
	ShowSizer->Add( ShowChoice, 1, wxEXPAND|wxLEFT, 8 );
	
	SidePanelSizer->Add( ShowSizer, 0, wxEXPAND|wxRIGHT|wxLEFT, 10 );
	
	PeriodPanel = new wxPanel( SidePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* PeriodPanelSizer;
	PeriodPanelSizer = new wxBoxSizer( wxVERTICAL );
	
	m_staticline1 = new wxStaticLine( PeriodPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	PeriodPanelSizer->Add( m_staticline1, 0, wxEXPAND|wxTOP|wxBOTTOM, 10 );
	
	wxFlexGridSizer* PeriodSizer;
	PeriodSizer = new wxFlexGridSizer( 2, 2, 10, 5 );
	PeriodSizer->AddGrowableCol( 1 );
	PeriodSizer->SetFlexibleDirection( wxBOTH );
	PeriodSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	FromLabel = new wxStaticText( PeriodPanel, wxID_ANY, _("From:"), wxDefaultPosition, wxDefaultSize, 0 );
	FromLabel->Wrap( -1 );
	PeriodSizer->Add( FromLabel, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	FromDatePicker = new wxDatePickerCtrl( PeriodPanel, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DROPDOWN );
	PeriodSizer->Add( FromDatePicker, 0, wxEXPAND, 5 );
	
	ToLabel = new wxStaticText( PeriodPanel, wxID_ANY, _("To:"), wxDefaultPosition, wxDefaultSize, 0 );
	ToLabel->Wrap( -1 );
	PeriodSizer->Add( ToLabel, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	ToDatePicker = new wxDatePickerCtrl( PeriodPanel, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DROPDOWN );
	PeriodSizer->Add( ToDatePicker, 0, wxEXPAND, 5 );
	
	PeriodPanelSizer->Add( PeriodSizer, 1, wxEXPAND, 5 );
	
	PeriodPanel->SetSizer( PeriodPanelSizer );
	PeriodPanel->Layout();
	PeriodPanelSizer->Fit( PeriodPanel );
	SidePanelSizer->Add( PeriodPanel, 0, wxEXPAND|wxRIGHT|wxLEFT, 10 );
	
	
	SidePanelSizer->Add( 0, 0, 1, wxEXPAND, 5 );
	
	wxBoxSizer* QueryPanel;
	QueryPanel = new wxBoxSizer( wxVERTICAL );
	
	CategoriesLabel = new wxStaticText( SidePanel, wxID_ANY, _("Categories contain:"), wxDefaultPosition, wxDefaultSize, 0 );
	CategoriesLabel->Wrap( -1 );
	QueryPanel->Add( CategoriesLabel, 0, wxTOP|wxBOTTOM, 5 );
	
	CategoriesText = new wxTextCtrl( SidePanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	QueryPanel->Add( CategoriesText, 0, wxEXPAND, 5 );
	
	SummaryLabel = new wxStaticText( SidePanel, wxID_ANY, _("Summary contains:"), wxDefaultPosition, wxDefaultSize, 0 );
	SummaryLabel->Wrap( -1 );
	QueryPanel->Add( SummaryLabel, 0, wxTOP|wxBOTTOM, 5 );
	
	SearchText = new wxTextCtrl( SidePanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	QueryPanel->Add( SearchText, 0, wxEXPAND, 10 );
	
	SidePanelSizer->Add( QueryPanel, 0, wxEXPAND|wxALL, 10 );
	
	SidePanel->SetSizer( SidePanelSizer );
	SidePanel->Layout();
	SidePanelSizer->Fit( SidePanel );
	MainSizer->Add( SidePanel, 0, wxEXPAND, 5 );
	
	EventsList = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT );
	MainSizer->Add( EventsList, 1, wxEXPAND, 5 );
	
	this->SetSizer( MainSizer );
	this->Layout();
	ToolBar = this->CreateToolBar( wxTB_FLAT|wxTB_HORIZONTAL|wxTB_HORZ_TEXT, wxID_ANY );
	ToolBar->SetToolBitmapSize( wxSize( 16,16 ) );
	ToolBar->AddTool( wxID_NEW, _("Add"), wxBitmap( wxT("icons/add.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, _("Add Event"), wxEmptyString );
	ToolBar->AddTool( wxID_DELETE, _("Delete"), wxBitmap( wxT("icons/delete.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, _("Delete Event"), wxEmptyString );
	ToolBar->AddTool( wxID_PROPERTIES, _("Edit"), wxBitmap( wxT("icons/edit.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, _("Edit Event"), wxEmptyString );
	ToolBar->AddSeparator();
	ToolBar->AddTool( wxID_EXIT, _("Quit"), wxBitmap( wxT("icons/quit.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, _("Quit program"), wxEmptyString );
	ToolBar->Realize();
	
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrameBase::Closed ) );
	CalendarCtrl->Connect( wxEVT_CALENDAR_SEL_CHANGED, wxCalendarEventHandler( MainFrameBase::CalendarCtrlChanged ), NULL, this );
	ShowChoice->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrameBase::ShowChanged ), NULL, this );
	FromDatePicker->Connect( wxEVT_DATE_CHANGED, wxDateEventHandler( MainFrameBase::FromDateChanged ), NULL, this );
	ToDatePicker->Connect( wxEVT_DATE_CHANGED, wxDateEventHandler( MainFrameBase::ToDateChanged ), NULL, this );
	CategoriesText->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrameBase::QueryChanged ), NULL, this );
	SearchText->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrameBase::QueryChanged ), NULL, this );
	EventsList->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( MainFrameBase::ListDClick ), NULL, this );
	EventsList->Connect( wxEVT_COMMAND_LIST_COL_CLICK, wxListEventHandler( MainFrameBase::ColumnClicked ), NULL, this );
	EventsList->Connect( wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxListEventHandler( MainFrameBase::EventsDeselected ), NULL, this );
	EventsList->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( MainFrameBase::EventsSelected ), NULL, this );
	EventsList->Connect( wxEVT_COMMAND_LIST_KEY_DOWN, wxListEventHandler( MainFrameBase::DeleteKeyDown ), NULL, this );
	this->Connect( wxID_NEW, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrameBase::NewClicked ) );
	this->Connect( wxID_DELETE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrameBase::DeleteClicked ) );
	this->Connect( wxID_PROPERTIES, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrameBase::EditClicked ) );
	this->Connect( wxID_EXIT, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrameBase::QuitClicked ) );
}

MainFrameBase::~MainFrameBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrameBase::Closed ) );
	CalendarCtrl->Disconnect( wxEVT_CALENDAR_SEL_CHANGED, wxCalendarEventHandler( MainFrameBase::CalendarCtrlChanged ), NULL, this );
	ShowChoice->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrameBase::ShowChanged ), NULL, this );
	FromDatePicker->Disconnect( wxEVT_DATE_CHANGED, wxDateEventHandler( MainFrameBase::FromDateChanged ), NULL, this );
	ToDatePicker->Disconnect( wxEVT_DATE_CHANGED, wxDateEventHandler( MainFrameBase::ToDateChanged ), NULL, this );
	CategoriesText->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrameBase::QueryChanged ), NULL, this );
	SearchText->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrameBase::QueryChanged ), NULL, this );
	EventsList->Disconnect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( MainFrameBase::ListDClick ), NULL, this );
	EventsList->Disconnect( wxEVT_COMMAND_LIST_COL_CLICK, wxListEventHandler( MainFrameBase::ColumnClicked ), NULL, this );
	EventsList->Disconnect( wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxListEventHandler( MainFrameBase::EventsDeselected ), NULL, this );
	EventsList->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( MainFrameBase::EventsSelected ), NULL, this );
	EventsList->Disconnect( wxEVT_COMMAND_LIST_KEY_DOWN, wxListEventHandler( MainFrameBase::DeleteKeyDown ), NULL, this );
	this->Disconnect( wxID_NEW, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrameBase::NewClicked ) );
	this->Disconnect( wxID_DELETE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrameBase::DeleteClicked ) );
	this->Disconnect( wxID_PROPERTIES, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrameBase::EditClicked ) );
	this->Disconnect( wxID_EXIT, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrameBase::QuitClicked ) );
}

EventFrameBase::EventFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxSize( -1,-1 ) );
	
	wxBoxSizer* MainSizer;
	MainSizer = new wxBoxSizer( wxVERTICAL );
	
	MainPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* MainPanelSizer;
	MainPanelSizer = new wxBoxSizer( wxVERTICAL );
	
	Notebook = new wxNotebook( MainPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	GeneralPanel = new wxPanel( Notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* GeneralPanelSizer;
	GeneralPanelSizer = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* GeneralSizer;
	GeneralSizer = new wxFlexGridSizer( 6, 2, 8, 8 );
	GeneralSizer->AddGrowableCol( 1 );
	GeneralSizer->AddGrowableRow( 5 );
	GeneralSizer->SetFlexibleDirection( wxBOTH );
	GeneralSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	SummaryLabel = new wxStaticText( GeneralPanel, wxID_ANY, _("Summary:"), wxDefaultPosition, wxDefaultSize, 0 );
	SummaryLabel->Wrap( -1 );
	GeneralSizer->Add( SummaryLabel, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	SummaryText = new wxTextCtrl( GeneralPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	GeneralSizer->Add( SummaryText, 1, wxEXPAND, 5 );
	
	CategoriesLabel = new wxStaticText( GeneralPanel, wxID_ANY, _("Categories:"), wxDefaultPosition, wxDefaultSize, 0 );
	CategoriesLabel->Wrap( -1 );
	GeneralSizer->Add( CategoriesLabel, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	CategoriesText = new wxTextCtrl( GeneralPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	GeneralSizer->Add( CategoriesText, 0, wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	StartLabel = new wxStaticText( GeneralPanel, wxID_ANY, _("Start:"), wxDefaultPosition, wxDefaultSize, 0 );
	StartLabel->Wrap( -1 );
	GeneralSizer->Add( StartLabel, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	wxBoxSizer* StartSizer;
	StartSizer = new wxBoxSizer( wxHORIZONTAL );
	
	StartDatePicker = new wxDatePickerCtrl( GeneralPanel, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxSize( 130,-1 ), wxDP_DROPDOWN );
	StartSizer->Add( StartDatePicker, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	StartHourSpinCtrl = new wxSpinCtrl( GeneralPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 45,-1 ), wxSP_ARROW_KEYS|wxSP_WRAP, 0, 23, 0 );
	StartHourSpinCtrl->Enable( false );
	
	StartSizer->Add( StartHourSpinCtrl, 0, wxLEFT|wxALIGN_CENTER_VERTICAL, 8 );
	
	StartMinuteSpinCtrl = new wxSpinCtrl( GeneralPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 45,-1 ), wxSP_ARROW_KEYS|wxSP_WRAP, 0, 59, 0 );
	StartMinuteSpinCtrl->Enable( false );
	
	StartSizer->Add( StartMinuteSpinCtrl, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	
	StartSizer->Add( 0, 0, 1, wxEXPAND, 5 );
	
	SpecificTimeCheckBox = new wxCheckBox( GeneralPanel, wxID_ANY, _("Specific time"), wxDefaultPosition, wxDefaultSize, 0 );
	
	StartSizer->Add( SpecificTimeCheckBox, 0, wxALIGN_CENTER_VERTICAL, 8 );
	
	GeneralSizer->Add( StartSizer, 1, wxEXPAND, 5 );
	
	EndDateCheckBox = new wxCheckBox( GeneralPanel, wxID_ANY, _("End:"), wxDefaultPosition, wxDefaultSize, 0 );
	
	GeneralSizer->Add( EndDateCheckBox, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	wxBoxSizer* EndSizer;
	EndSizer = new wxBoxSizer( wxHORIZONTAL );
	
	EndDatePicker = new wxDatePickerCtrl( GeneralPanel, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxSize( 130,-1 ), wxDP_DROPDOWN );
	EndDatePicker->Enable( false );
	
	EndSizer->Add( EndDatePicker, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	EndHourSpinCtrl = new wxSpinCtrl( GeneralPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 45,-1 ), wxSP_ARROW_KEYS|wxSP_WRAP, 0, 23, 0 );
	EndHourSpinCtrl->Enable( false );
	
	EndSizer->Add( EndHourSpinCtrl, 0, wxLEFT|wxALIGN_CENTER_VERTICAL, 8 );
	
	EndMinuteSpinCtrl = new wxSpinCtrl( GeneralPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 45,-1 ), wxSP_ARROW_KEYS|wxSP_WRAP, 0, 59, 0 );
	EndMinuteSpinCtrl->Enable( false );
	
	EndSizer->Add( EndMinuteSpinCtrl, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	GeneralSizer->Add( EndSizer, 1, wxEXPAND, 5 );
	
	RecurrenceLabel = new wxStaticText( GeneralPanel, wxID_ANY, _("Recurrence:"), wxDefaultPosition, wxDefaultSize, 0 );
	RecurrenceLabel->Wrap( -1 );
	GeneralSizer->Add( RecurrenceLabel, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	wxBoxSizer* RecurrenceSizer;
	RecurrenceSizer = new wxBoxSizer( wxHORIZONTAL );
	
	RepeatCheckBox = new wxCheckBox( GeneralPanel, wxID_ANY, _("Repeat every"), wxDefaultPosition, wxDefaultSize, 0 );
	
	RecurrenceSizer->Add( RepeatCheckBox, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT, 5 );
	
	IntervalSpinCtrl = new wxSpinCtrl( GeneralPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 45,-1 ), wxSP_ARROW_KEYS, 0, 999, 1 );
	IntervalSpinCtrl->Enable( false );
	
	RecurrenceSizer->Add( IntervalSpinCtrl, 0, wxALIGN_CENTER_VERTICAL, 8 );
	
	wxString FrequencyChoiceChoices[] = { _("year(s)"), _("month(s)"), _("week(s)"), _("day(s)"), _("hour(s)"), _("minute(s)") };
	int FrequencyChoiceNChoices = sizeof( FrequencyChoiceChoices ) / sizeof( wxString );
	FrequencyChoice = new wxChoice( GeneralPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, FrequencyChoiceNChoices, FrequencyChoiceChoices, 0 );
	FrequencyChoice->SetSelection( 0 );
	FrequencyChoice->Enable( false );
	
	RecurrenceSizer->Add( FrequencyChoice, 0, wxRIGHT|wxLEFT|wxALIGN_CENTER_VERTICAL, 8 );
	
	
	RecurrenceSizer->Add( 0, 0, 1, wxEXPAND, 5 );
	
	UntilCheckBox = new wxCheckBox( GeneralPanel, wxID_ANY, _("Until"), wxDefaultPosition, wxDefaultSize, 0 );
	
	UntilCheckBox->Enable( false );
	
	RecurrenceSizer->Add( UntilCheckBox, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	UntilDatePicker = new wxDatePickerCtrl( GeneralPanel, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxSize( 130,-1 ), wxDP_DROPDOWN );
	UntilDatePicker->Enable( false );
	
	RecurrenceSizer->Add( UntilDatePicker, 0, wxLEFT|wxALIGN_CENTER_VERTICAL, 5 );
	
	GeneralSizer->Add( RecurrenceSizer, 1, wxEXPAND, 5 );
	
	DesciptionLabel = new wxStaticText( GeneralPanel, wxID_ANY, _("Description:"), wxDefaultPosition, wxDefaultSize, 0 );
	DesciptionLabel->Wrap( -1 );
	GeneralSizer->Add( DesciptionLabel, 0, 0, 5 );
	
	DescriptionText = new wxTextCtrl( GeneralPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	GeneralSizer->Add( DescriptionText, 1, wxEXPAND, 5 );
	
	GeneralPanelSizer->Add( GeneralSizer, 1, wxALL|wxEXPAND, 12 );
	
	GeneralPanel->SetSizer( GeneralPanelSizer );
	GeneralPanel->Layout();
	GeneralPanelSizer->Fit( GeneralPanel );
	Notebook->AddPage( GeneralPanel, _("General"), true );
	AlarmsPanel = new wxPanel( Notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* GeneralAlarmsSizer;
	GeneralAlarmsSizer = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* AlarmsListSizer;
	AlarmsListSizer = new wxBoxSizer( wxVERTICAL );
	
	AlarmsList = new wxListCtrl( AlarmsPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_NO_HEADER|wxLC_REPORT|wxLC_SINGLE_SEL|wxSUNKEN_BORDER );
	AlarmsListSizer->Add( AlarmsList, 1, wxBOTTOM|wxEXPAND, 8 );
	
	wxBoxSizer* AlarmsButtonsSizer;
	AlarmsButtonsSizer = new wxBoxSizer( wxHORIZONTAL );
	
	AddAlarmButton = new wxButton( AlarmsPanel, wxID_ANY, _("&Add"), wxDefaultPosition, wxDefaultSize, 0 );
	AlarmsButtonsSizer->Add( AddAlarmButton, 0, 0, 5 );
	
	DeleteAlaramButton = new wxButton( AlarmsPanel, wxID_ANY, _("&Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	DeleteAlaramButton->Enable( false );
	
	AlarmsButtonsSizer->Add( DeleteAlaramButton, 0, wxLEFT, 5 );
	
	AlarmsListSizer->Add( AlarmsButtonsSizer, 0, wxEXPAND, 5 );
	
	GeneralAlarmsSizer->Add( AlarmsListSizer, 0, wxALL|wxEXPAND, 12 );
	
	AlarmPropertiesPanel = new wxPanel( AlarmsPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* AlarmPropertiesSizer;
	AlarmPropertiesSizer = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* AlarmPropertiesSubSizer;
	AlarmPropertiesSubSizer = new wxFlexGridSizer( 2, 2, 8, 8 );
	AlarmPropertiesSubSizer->AddGrowableCol( 1 );
	AlarmPropertiesSubSizer->SetFlexibleDirection( wxBOTH );
	AlarmPropertiesSubSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	AlarmTypeLabel = new wxStaticText( AlarmPropertiesPanel, wxID_ANY, _("Type:"), wxDefaultPosition, wxDefaultSize, 0 );
	AlarmTypeLabel->Wrap( -1 );
	AlarmPropertiesSubSizer->Add( AlarmTypeLabel, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString AlarmTypeChoiceChoices[] = { _("Pop-up window"), _("Taskbar icon"), _("Sound") };
	int AlarmTypeChoiceNChoices = sizeof( AlarmTypeChoiceChoices ) / sizeof( wxString );
	AlarmTypeChoice = new wxChoice( AlarmPropertiesPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, AlarmTypeChoiceNChoices, AlarmTypeChoiceChoices, 0 );
	AlarmTypeChoice->SetSelection( 0 );
	AlarmPropertiesSubSizer->Add( AlarmTypeChoice, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	AlarmTriggerLabel = new wxStaticText( AlarmPropertiesPanel, wxID_ANY, _("Trigger:"), wxDefaultPosition, wxDefaultSize, 0 );
	AlarmTriggerLabel->Wrap( -1 );
	AlarmPropertiesSubSizer->Add( AlarmTriggerLabel, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	wxBoxSizer* AlarmTriggerSizer;
	AlarmTriggerSizer = new wxBoxSizer( wxHORIZONTAL );
	
	AlarmTriggerSpinCtrl = new wxSpinCtrl( AlarmPropertiesPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, 0, 999, 0 );
	AlarmTriggerSizer->Add( AlarmTriggerSpinCtrl, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString AlarmTriggerUnitChoiceChoices[] = { _("minute(s)"), _("hour(s)"), _("day(s)"), _("week(s)") };
	int AlarmTriggerUnitChoiceNChoices = sizeof( AlarmTriggerUnitChoiceChoices ) / sizeof( wxString );
	AlarmTriggerUnitChoice = new wxChoice( AlarmPropertiesPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, AlarmTriggerUnitChoiceNChoices, AlarmTriggerUnitChoiceChoices, 0 );
	AlarmTriggerUnitChoice->SetSelection( 0 );
	AlarmTriggerSizer->Add( AlarmTriggerUnitChoice, 0, wxRIGHT|wxLEFT|wxALIGN_CENTER_VERTICAL, 8 );
	
	wxString AlarmBeforeAfterChoiceChoices[] = { _("before"), _("after") };
	int AlarmBeforeAfterChoiceNChoices = sizeof( AlarmBeforeAfterChoiceChoices ) / sizeof( wxString );
	AlarmBeforeAfterChoice = new wxChoice( AlarmPropertiesPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, AlarmBeforeAfterChoiceNChoices, AlarmBeforeAfterChoiceChoices, 0 );
	AlarmBeforeAfterChoice->SetSelection( 0 );
	AlarmTriggerSizer->Add( AlarmBeforeAfterChoice, 0, wxRIGHT|wxALIGN_CENTER_VERTICAL, 8 );
	
	AlarmTriggerLabel2 = new wxStaticText( AlarmPropertiesPanel, wxID_ANY, _("the start"), wxDefaultPosition, wxDefaultSize, 0 );
	AlarmTriggerLabel2->Wrap( -1 );
	AlarmTriggerSizer->Add( AlarmTriggerLabel2, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	AlarmPropertiesSubSizer->Add( AlarmTriggerSizer, 0, wxEXPAND, 5 );
	
	AlarmPropertiesSizer->Add( AlarmPropertiesSubSizer, 0, wxEXPAND|wxBOTTOM, 12 );
	
	AlarmDescriptionLabel = new wxStaticText( AlarmPropertiesPanel, wxID_ANY, _("Additional alarm description:"), wxDefaultPosition, wxDefaultSize, 0 );
	AlarmDescriptionLabel->Wrap( -1 );
	AlarmPropertiesSizer->Add( AlarmDescriptionLabel, 0, wxBOTTOM, 5 );
	
	AlarmDescriptionText = new wxTextCtrl( AlarmPropertiesPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	AlarmPropertiesSizer->Add( AlarmDescriptionText, 1, wxEXPAND, 12 );
	
	AlarmPropertiesPanel->SetSizer( AlarmPropertiesSizer );
	AlarmPropertiesPanel->Layout();
	AlarmPropertiesSizer->Fit( AlarmPropertiesPanel );
	GeneralAlarmsSizer->Add( AlarmPropertiesPanel, 1, wxTOP|wxBOTTOM|wxRIGHT|wxEXPAND, 12 );
	
	AlarmsPanel->SetSizer( GeneralAlarmsSizer );
	AlarmsPanel->Layout();
	GeneralAlarmsSizer->Fit( AlarmsPanel );
	Notebook->AddPage( AlarmsPanel, _("Alarms"), false );
	
	MainPanelSizer->Add( Notebook, 1, wxALL|wxEXPAND, 8 );
	
	ButtonsSizer = new wxStdDialogButtonSizer();
	ButtonsSizerOK = new wxButton( MainPanel, wxID_OK );
	ButtonsSizer->AddButton( ButtonsSizerOK );
	ButtonsSizerCancel = new wxButton( MainPanel, wxID_CANCEL );
	ButtonsSizer->AddButton( ButtonsSizerCancel );
	ButtonsSizer->Realize();
	MainPanelSizer->Add( ButtonsSizer, 0, wxBOTTOM|wxRIGHT|wxEXPAND, 8 );
	
	MainPanel->SetSizer( MainPanelSizer );
	MainPanel->Layout();
	MainPanelSizer->Fit( MainPanel );
	MainSizer->Add( MainPanel, 1, wxEXPAND, 5 );
	
	this->SetSizer( MainSizer );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( EventFrameBase::Closed ) );
	SpecificTimeCheckBox->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( EventFrameBase::SpecificTimeCheckBoxClicked ), NULL, this );
	EndDateCheckBox->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( EventFrameBase::EndDateCheckBoxClicked ), NULL, this );
	RepeatCheckBox->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( EventFrameBase::RepeatCheckBoxClicked ), NULL, this );
	UntilCheckBox->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( EventFrameBase::UntilCheckBoxClicked ), NULL, this );
	AlarmsList->Connect( wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxListEventHandler( EventFrameBase::AlarmDeselected ), NULL, this );
	AlarmsList->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( EventFrameBase::AlarmSelected ), NULL, this );
	AddAlarmButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EventFrameBase::AddAlarmClicked ), NULL, this );
	DeleteAlaramButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EventFrameBase::DeleteAlarmClicked ), NULL, this );
	AlarmTypeChoice->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( EventFrameBase::AlarmTypeChanged ), NULL, this );
	AlarmTriggerSpinCtrl->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( EventFrameBase::AlarmTriggerChanged ), NULL, this );
	AlarmTriggerUnitChoice->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( EventFrameBase::AlarmTriggerUnitChanged ), NULL, this );
	AlarmBeforeAfterChoice->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( EventFrameBase::AlarmBeforeAfterChanged ), NULL, this );
	ButtonsSizerCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EventFrameBase::CancelClicked ), NULL, this );
	ButtonsSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EventFrameBase::OKClicked ), NULL, this );
}

EventFrameBase::~EventFrameBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( EventFrameBase::Closed ) );
	SpecificTimeCheckBox->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( EventFrameBase::SpecificTimeCheckBoxClicked ), NULL, this );
	EndDateCheckBox->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( EventFrameBase::EndDateCheckBoxClicked ), NULL, this );
	RepeatCheckBox->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( EventFrameBase::RepeatCheckBoxClicked ), NULL, this );
	UntilCheckBox->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( EventFrameBase::UntilCheckBoxClicked ), NULL, this );
	AlarmsList->Disconnect( wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxListEventHandler( EventFrameBase::AlarmDeselected ), NULL, this );
	AlarmsList->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( EventFrameBase::AlarmSelected ), NULL, this );
	AddAlarmButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EventFrameBase::AddAlarmClicked ), NULL, this );
	DeleteAlaramButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EventFrameBase::DeleteAlarmClicked ), NULL, this );
	AlarmTypeChoice->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( EventFrameBase::AlarmTypeChanged ), NULL, this );
	AlarmTriggerSpinCtrl->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( EventFrameBase::AlarmTriggerChanged ), NULL, this );
	AlarmTriggerUnitChoice->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( EventFrameBase::AlarmTriggerUnitChanged ), NULL, this );
	AlarmBeforeAfterChoice->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( EventFrameBase::AlarmBeforeAfterChanged ), NULL, this );
	ButtonsSizerCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EventFrameBase::CancelClicked ), NULL, this );
	ButtonsSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EventFrameBase::OKClicked ), NULL, this );
}

PopupDialogBase::PopupDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* MainSizer;
	MainSizer = new wxBoxSizer( wxVERTICAL );
	
	Panel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* PanelSizer;
	PanelSizer = new wxBoxSizer( wxVERTICAL );
	
	SummaryLabel = new wxStaticText( Panel, wxID_ANY, _("Summary"), wxDefaultPosition, wxDefaultSize, 0 );
	SummaryLabel->Wrap( -1 );
	SummaryLabel->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	PanelSizer->Add( SummaryLabel, 0, 0, 5 );
	
	DateLabel = new wxStaticText( Panel, wxID_ANY, _("Date"), wxDefaultPosition, wxDefaultSize, 0 );
	DateLabel->Wrap( -1 );
	PanelSizer->Add( DateLabel, 0, wxBOTTOM, 8 );
	
	DescriptionText = new wxTextCtrl( Panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	PanelSizer->Add( DescriptionText, 1, wxEXPAND, 5 );
	
	wxBoxSizer* ButtonsSizer;
	ButtonsSizer = new wxBoxSizer( wxHORIZONTAL );
	
	DetailsButton = new wxButton( Panel, wxID_ANY, _("Event's details"), wxDefaultPosition, wxDefaultSize, 0 );
	ButtonsSizer->Add( DetailsButton, 0, 0, 5 );
	
	OKSizer = new wxStdDialogButtonSizer();
	OKSizerOK = new wxButton( Panel, wxID_OK );
	OKSizer->AddButton( OKSizerOK );
	OKSizer->Realize();
	ButtonsSizer->Add( OKSizer, 0, 0, 5 );
	
	PanelSizer->Add( ButtonsSizer, 0, wxALIGN_RIGHT|wxTOP, 12 );
	
	Panel->SetSizer( PanelSizer );
	Panel->Layout();
	PanelSizer->Fit( Panel );
	MainSizer->Add( Panel, 1, wxEXPAND | wxALL, 8 );
	
	this->SetSizer( MainSizer );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( PopupDialogBase::Closed ) );
	DetailsButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PopupDialogBase::DetailsButtonClicked ), NULL, this );
}

PopupDialogBase::~PopupDialogBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( PopupDialogBase::Closed ) );
	DetailsButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PopupDialogBase::DetailsButtonClicked ), NULL, this );
}
