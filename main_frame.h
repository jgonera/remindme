#ifndef __main_frame__
#define __main_frame__

/**
@file
Subclass of MainFrameBase, which is generated by wxFormBuilder.
*/

#include <wx/timer.h>
#include <wx/msgdlg.h>
#include <wx/taskbar.h>
#include <wx/menu.h>
#include <wx/sound.h>
#include "gui.h"
#include "event_frame.h"
#include "popup_dialog.h"
#include "icalendar/icalendar.h"
#include "icalendar/wxwrapper.h"

enum { SHOW_ALL=0, SHOW_TODAYS, SHOW_UPCOMING, SHOW_SPECIFIC };
enum { COLUMN_SUMMARY=0, COLUMN_START, COLUMN_END, COLUMN_CATEGORIES, COLUMN_ALARM, COLUMN_RECURRENCE };
enum { ICON_EVENT=0, ICON_RECURRENT, ICON_ALARM };
enum { TASKBAR_RESTORE=wxID_HIGHEST+1, TASKBAR_NEW, TASKBAR_QUIT };

struct SortOptionsT {
	bool Descending;
	int Column;
};

/** Implementing MainFrameBase */
class MainFrame: public MainFrameBase {
	protected:
		void Closed(wxCloseEvent& event);
		void Iconized(wxIconizeEvent& event);
		void CalendarCtrlChanged(wxCalendarEvent& event);
		void ShowChanged(wxCommandEvent& event);
		void FromDateChanged(wxDateEvent& event);
		void ToDateChanged(wxDateEvent& event);
		void QueryChanged(wxCommandEvent& event);
		void EventsSelected(wxListEvent& event);
		void EventsDeselected(wxListEvent& event);
		void ColumnClicked(wxListEvent& event);
		void DeleteKeyDown(wxListEvent& event);
		void NewClicked(wxCommandEvent& event);
		void DeleteClicked(wxCommandEvent& event);
		void EditClicked(wxCommandEvent& event);
		void QuitClicked(wxCommandEvent& event);
		void ListDClick(wxMouseEvent& event);
		
		void CheckAlarms(wxTimerEvent& event);
		void NewEvent();
		
		class TaskBarIcon;
		
		ICalendar::Query *ViewQuery, *AlarmsQuery;
		wxTimer *AlarmsTimer;
		wxImageList *EventsImages;
		wxSound *Sound;
		MainFrame::TaskBarIcon *Icon;
		SortOptionsT SortOptions;
		
	public:
		MainFrame(wxWindow* parent);
		~MainFrame();

		void UpdateEvents();
		void UpdateMonthEvents();
		void EditEvent(Event *EditedEvent);

		ICalendar *Calendar;
		bool Quit;
};

class MainFrame::TaskBarIcon: public wxTaskBarIcon {
public:
	TaskBarIcon(MainFrame *Main);
	void IconDClick(wxTaskBarIconEvent &event);
	void RestoreClicked(wxCommandEvent& event);
	void NewClicked(wxCommandEvent &event);
	void QuitClicked(wxCommandEvent& event);
	
	wxMenu *CreatePopupMenu();
	void NormalIcon();
	void AlarmIcon(Event *AlarmEvent);

private:
	MainFrame *Main;
	Event *CurrentEvent;
};

int wxCALLBACK CompareEvents(long Item1, long Item2, long SortInfo);

#endif // __main_frame__
