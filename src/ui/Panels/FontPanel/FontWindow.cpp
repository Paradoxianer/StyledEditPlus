#include <ScrollView.h>
#include <ScrollBar.h>
#include <CheckBox.h>
#include <Spinner.h>
#include <DecimalSpinner.h>
#include <PopUpMenu.h>
#include <GroupLayout.h>
#include <GroupLayoutBuilder.h>
#include <GridLayout.h>
#include <GridLayoutBuilder.h>


#include "FontWindow.h"
#include "FontPanel.h"




FontWindow::FontWindow(const BRect frame, float fontsize)
 :	BWindow(frame,"Choose a Font", B_TITLED_WINDOW_LOOK, B_NORMAL_WINDOW_FEEL,0),
 	fView()
{
	
	RemoveShortcut('w',B_COMMAND_KEY);
	AddShortcut('w',B_COMMAND_KEY,new BMessage(M_HIDE_WINDOW));
	SetSizeLimits(400,2400,300,2400);
	fReallyQuit = false;

 	SetLayout(BGroupLayoutBuilder(B_HORIZONTAL)
 		.Add(&fView)
 		.Add(BGridLayoutBuilder(2,3)
 			.Add(new BCheckBox("Bold"),0,0)
 			.Add(new BCheckBox("Italic"),0,1)
 			.Add(new BCheckBox("Strike Out"),1,0)
 		)
 		
 	);
 	
	
	;
}


FontWindow::~FontWindow(void)
{
}


bool
FontWindow::QuitRequested(void)
{
	if (!fReallyQuit)
		PostMessage(M_HIDE_WINDOW);
	
	return fReallyQuit;
}

 
void
FontWindow::MessageReceived(BMessage *msg)
{
	if (msg->what == M_HIDE_WINDOW)
		Hide();
	else
		BWindow::MessageReceived(msg);
}
