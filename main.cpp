#include "main.h"

IMPLEMENT_APP(RemindMe)

bool RemindMe::OnInit() {
	InstanceChecker = new wxSingleInstanceChecker(wxString::Format(wxT("remind.me-%s"), wxGetUserId().c_str()));
	if (InstanceChecker->IsAnotherRunning()) {
		wxMessageBox(_("The program is already running."));
		return false;
	}
	
	// initialize random number generator for UIDs
	srand(time(NULL));
		
	// add PNG support for icons
	wxImage::AddHandler(new wxPNGHandler);
	
	MainWindow = new MainFrame((wxWindow*)NULL);
	//MainWindow->Show();
	SetTopWindow(MainWindow);
	
	Connect(wxEVT_QUERY_END_SESSION, wxCloseEventHandler(RemindMe::OnQueryEndSession));
	
	return true;
}

int RemindMe::OnExit() {
	delete InstanceChecker;
	
	return 0;
}

void RemindMe::OnQueryEndSession(wxCloseEvent &event) {
	MainWindow->Quit = true;
	event.Skip();
}
