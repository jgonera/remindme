#include "popup_dialog.h"

PopupDialog::PopupDialog(wxWindow* parent, Event *CurrentEvent, Alarm &CurrentAlarm):
	PopupDialogBase(parent), CurrentEvent(CurrentEvent)
{
	SummaryLabel->SetLabel(wxString(CurrentEvent->Summary.c_str(), wxConvUTF8));
	DateLabel->SetLabel(wxString(CurrentEvent->DtStart.Format().c_str(), wxConvLibc));
	
	if (CurrentAlarm.Description.empty()) {
		DescriptionText->Hide();
		Fit();
	} else {
		DescriptionText->SetValue(wxString(CurrentAlarm.Description.c_str(), wxConvUTF8));
	}
}

void PopupDialog::Closed(wxCloseEvent& event) {
	Destroy();
}

void PopupDialog::DetailsButtonClicked(wxCommandEvent& event) {
	MainFrame *Main = static_cast<MainFrame *>(GetParent());
	Main->EditEvent(CurrentEvent);
}
