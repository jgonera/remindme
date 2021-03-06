#ifndef __popup_dialog__
#define __popup_dialog__

/**
@file
Subclass of PopupDialogBase, which is generated by wxFormBuilder.
*/

#include "gui.h"
#include "main_frame.h"
#include "icalendar/types.h"

/** Implementing PopupDialogBase */
class PopupDialog : public PopupDialogBase
{
protected:
	void Closed(wxCloseEvent& event);
	void DetailsButtonClicked(wxCommandEvent& event);
	
public:
	PopupDialog(wxWindow* parent, Event *CurrentEvent, Alarm &CurrentAlarm);
	
	Event *CurrentEvent;
};

#endif // __popup_dialog__
