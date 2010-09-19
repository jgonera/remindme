///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 16 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __gui__
#define __gui__

#include <wx/intl.h>

#include <wx/calctrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/datectrl.h>
#include <wx/dateevt.h>
#include <wx/panel.h>
#include <wx/textctrl.h>
#include <wx/listctrl.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/toolbar.h>
#include <wx/frame.h>
#include <wx/spinctrl.h>
#include <wx/checkbox.h>
#include <wx/button.h>
#include <wx/notebook.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainFrameBase
///////////////////////////////////////////////////////////////////////////////
class MainFrameBase : public wxFrame 
{
	private:
	
	protected:
		wxPanel* SidePanel;
		wxCalendarCtrl* CalendarCtrl;
		wxStaticText* ShowLabel;
		wxChoice* ShowChoice;
		wxPanel* PeriodPanel;
		wxStaticLine* m_staticline1;
		wxStaticText* FromLabel;
		wxDatePickerCtrl* FromDatePicker;
		wxStaticText* ToLabel;
		wxDatePickerCtrl* ToDatePicker;
		
		wxStaticText* CategoriesLabel;
		wxTextCtrl* CategoriesText;
		wxStaticText* SummaryLabel;
		wxTextCtrl* SearchText;
		wxListCtrl* EventsList;
		wxToolBar* ToolBar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void Closed( wxCloseEvent& event ){ event.Skip(); }
		virtual void CalendarCtrlChanged( wxCalendarEvent& event ){ event.Skip(); }
		virtual void ShowChanged( wxCommandEvent& event ){ event.Skip(); }
		virtual void FromDateChanged( wxDateEvent& event ){ event.Skip(); }
		virtual void ToDateChanged( wxDateEvent& event ){ event.Skip(); }
		virtual void QueryChanged( wxCommandEvent& event ){ event.Skip(); }
		virtual void ListDClick( wxMouseEvent& event ){ event.Skip(); }
		virtual void ColumnClicked( wxListEvent& event ){ event.Skip(); }
		virtual void EventsDeselected( wxListEvent& event ){ event.Skip(); }
		virtual void EventsSelected( wxListEvent& event ){ event.Skip(); }
		virtual void DeleteKeyDown( wxListEvent& event ){ event.Skip(); }
		virtual void NewClicked( wxCommandEvent& event ){ event.Skip(); }
		virtual void DeleteClicked( wxCommandEvent& event ){ event.Skip(); }
		virtual void EditClicked( wxCommandEvent& event ){ event.Skip(); }
		virtual void QuitClicked( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		MainFrameBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("remind.me"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 932,565 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~MainFrameBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class EventFrameBase
///////////////////////////////////////////////////////////////////////////////
class EventFrameBase : public wxFrame 
{
	private:
	
	protected:
		wxPanel* MainPanel;
		wxNotebook* Notebook;
		wxPanel* GeneralPanel;
		wxStaticText* SummaryLabel;
		wxTextCtrl* SummaryText;
		wxStaticText* CategoriesLabel;
		wxTextCtrl* CategoriesText;
		wxStaticText* StartLabel;
		wxDatePickerCtrl* StartDatePicker;
		wxSpinCtrl* StartHourSpinCtrl;
		wxSpinCtrl* StartMinuteSpinCtrl;
		
		wxCheckBox* SpecificTimeCheckBox;
		wxCheckBox* EndDateCheckBox;
		wxDatePickerCtrl* EndDatePicker;
		wxSpinCtrl* EndHourSpinCtrl;
		wxSpinCtrl* EndMinuteSpinCtrl;
		wxStaticText* RecurrenceLabel;
		wxCheckBox* RepeatCheckBox;
		wxSpinCtrl* IntervalSpinCtrl;
		wxChoice* FrequencyChoice;
		
		wxCheckBox* UntilCheckBox;
		wxDatePickerCtrl* UntilDatePicker;
		wxStaticText* DesciptionLabel;
		wxTextCtrl* DescriptionText;
		wxPanel* AlarmsPanel;
		wxListCtrl* AlarmsList;
		wxButton* AddAlarmButton;
		wxButton* DeleteAlaramButton;
		wxPanel* AlarmPropertiesPanel;
		wxStaticText* AlarmTypeLabel;
		wxChoice* AlarmTypeChoice;
		wxStaticText* AlarmTriggerLabel;
		wxSpinCtrl* AlarmTriggerSpinCtrl;
		wxChoice* AlarmTriggerUnitChoice;
		wxChoice* AlarmBeforeAfterChoice;
		wxStaticText* AlarmTriggerLabel2;
		wxStaticText* AlarmDescriptionLabel;
		wxTextCtrl* AlarmDescriptionText;
		wxStdDialogButtonSizer* ButtonsSizer;
		wxButton* ButtonsSizerOK;
		wxButton* ButtonsSizerCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void Closed( wxCloseEvent& event ){ event.Skip(); }
		virtual void SpecificTimeCheckBoxClicked( wxCommandEvent& event ){ event.Skip(); }
		virtual void EndDateCheckBoxClicked( wxCommandEvent& event ){ event.Skip(); }
		virtual void RepeatCheckBoxClicked( wxCommandEvent& event ){ event.Skip(); }
		virtual void UntilCheckBoxClicked( wxCommandEvent& event ){ event.Skip(); }
		virtual void AlarmDeselected( wxListEvent& event ){ event.Skip(); }
		virtual void AlarmSelected( wxListEvent& event ){ event.Skip(); }
		virtual void AddAlarmClicked( wxCommandEvent& event ){ event.Skip(); }
		virtual void DeleteAlarmClicked( wxCommandEvent& event ){ event.Skip(); }
		virtual void AlarmTypeChanged( wxCommandEvent& event ){ event.Skip(); }
		virtual void AlarmTriggerChanged( wxSpinEvent& event ){ event.Skip(); }
		virtual void AlarmTriggerUnitChanged( wxCommandEvent& event ){ event.Skip(); }
		virtual void AlarmBeforeAfterChanged( wxCommandEvent& event ){ event.Skip(); }
		virtual void CancelClicked( wxCommandEvent& event ){ event.Skip(); }
		virtual void OKClicked( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		EventFrameBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Event"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 610,400 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~EventFrameBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class PopupDialogBase
///////////////////////////////////////////////////////////////////////////////
class PopupDialogBase : public wxDialog 
{
	private:
	
	protected:
		wxPanel* Panel;
		wxStaticText* SummaryLabel;
		wxStaticText* DateLabel;
		wxTextCtrl* DescriptionText;
		wxButton* DetailsButton;
		wxStdDialogButtonSizer* OKSizer;
		wxButton* OKSizerOK;
		
		// Virtual event handlers, overide them in your derived class
		virtual void Closed( wxCloseEvent& event ){ event.Skip(); }
		virtual void DetailsButtonClicked( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		PopupDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Remember"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 364,227 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		~PopupDialogBase();
	
};

#endif //__gui__
