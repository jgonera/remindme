#ifndef __event_frame__
#define __event_frame__

/**
@file
Subclass of EventFrameBase, which is generated by wxFormBuilder.
*/

#include <wx/imaglist.h>
#include "gui.h"
#include "main_frame.h"
#include "icalendar/types.h"
#include "icalendar/wxwrapper.h"

enum { YEARLY=0, MONTHLY, WEEKLY, DAILY, HOURLY, MINUTELY };
enum { MINUTES=0, HOURS, DAYS, WEEKS };

/** Implementing EventFrameBase */
class EventFrame: public EventFrameBase
{
protected:
	void Closed(wxCloseEvent& event);
	void CancelClicked(wxCommandEvent& event);
	void OKClicked(wxCommandEvent& event);
	void EndDateCheckBoxClicked(wxCommandEvent& event);
	void SpecificTimeCheckBoxClicked(wxCommandEvent& event);
	void RepeatCheckBoxClicked(wxCommandEvent& event);
	void UntilCheckBoxClicked(wxCommandEvent& event);
	void AlarmSelected(wxListEvent& event);
	void AlarmDeselected(wxListEvent& event);
	void AddAlarmClicked(wxCommandEvent& event);
	void DeleteAlarmClicked(wxCommandEvent& event);
	void AlarmTypeChanged(wxCommandEvent& event);
	void AlarmTriggerChanged(wxSpinEvent& event);
	void AlarmTriggerUnitChanged(wxCommandEvent& event);
	void AlarmBeforeAfterChanged(wxCommandEvent& event);
	
	void EnableEndDate(bool Enable);
	void EnableSpecificTime(bool Enable);
	void EnableRecurrence(bool Enable);
	void LoadAlarms();
	void UpdateAlarm();
	void LoadAlarm(Alarm *AlarmPointer);
	
	wxImageList *AlarmsImages;
	bool New;
	list<Alarm> *Alarms;
	Alarm *CurrentAlarm;
	
public:
	EventFrame(wxWindow* parent);
	void LoadEvent(Event *EventPointer);
	
	Event *EditedEvent;
};

#endif // __event_frame__
