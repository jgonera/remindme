#ifndef _REMINDME_H
#define _REMINDME_H

#include <wx/wx.h>
#include <wx/snglinst.h>
#include "main_frame.h"

class RemindMe: public wxApp {
	public:
		RemindMe() {};
		~RemindMe() {};
		bool OnInit();
		int OnExit();
		
	private:
		void OnQueryEndSession(wxCloseEvent &event);
		
		MainFrame *MainWindow;
		wxSingleInstanceChecker *InstanceChecker;
};

DECLARE_APP(RemindMe)

#endif
