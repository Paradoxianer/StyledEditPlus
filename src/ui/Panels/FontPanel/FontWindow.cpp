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
#include <Button.h>

#include "FontWindow.h"
#include "FontPanel.h"




FontWindow::FontWindow(const BRect frame, float fontsize)
 :	BWindow(frame,B_TRANSLATE("Choose a Font"), B_TITLED_WINDOW_LOOK, B_NORMAL_WINDOW_FEEL,0)
{
	
	RemoveShortcut('w',B_COMMAND_KEY);
	AddShortcut('w',B_COMMAND_KEY,new BMessage(M_HIDE_WINDOW));
	SetSizeLimits(400,2400,300,2400);
	fReallyQuit = false;
	fView = new FontView();
	SetLayout(new BGroupLayout(B_VERTICAL));

 	AddChild(BGroupLayoutBuilder(B_VERTICAL)
 		.Add(fView)
 		.Add(BGridLayoutBuilder()
 			.Add(new BCheckBox(B_TRANSLATE("Bold")),0,0)
 			.Add(new BCheckBox(B_TRANSLATE("Italic")),0,1)
 			.Add(new BCheckBox(B_TRANSLATE("Strike Out")),1,0)
 		)	
		.Add(BGroupLayoutBuilder(B_HORIZONTAL)
			.AddGlue()
			.Add(new BButton("cancel",B_TRANSLATE("Cancel"),new BMessage(M_CANCEL)))
			.Add(new BButton("ok",B_TRANSLATE("OK"),new BMessage(M_OK)))		
		)
 	);
}


FontWindow::~FontWindow(void)
{
	ReallyQuit();
	PostMessage(B_QUIT_REQUESTED);
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
	msg->PrintToStream();
	if (msg->what == M_HIDE_WINDOW)
		Hide();
	else
		BWindow::MessageReceived(msg);
}
