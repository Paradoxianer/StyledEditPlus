/*
	FontPanel.cpp: A general-purpose font selection class
	Written by DarkWyrm <darkwyrm@earthlink.net>, Copyright 2007
	Released under the MIT license.
*/

#include "FontPanel.h"
#include "Spinner.h"
#include "FontView.h"
#include "FontWindow.h"

#include <Application.h>
#include <Invoker.h>
#include <String.h>
#include <stdio.h>

// TODO: Add Escape key as a shortcut for cancelling


class FontPreview : public BView
{
public:
					FontPreview(const BRect frame);
			
	void			SetPreviewText(const char *text);
	const char *	PreviewText(void) const;
			
	void			Draw(BRect r);
	
private:
	BString	fPreviewText;
};


FontPreview::FontPreview(const BRect frame)
 :	BView(frame,"fontpreview",B_FOLLOW_LEFT_RIGHT | B_FOLLOW_TOP, B_WILL_DRAW),
 	fPreviewText(PREVIEW_STR)
{
}


void
FontPreview::SetPreviewText(const char *text)
{
	fPreviewText = text ? text : PREVIEW_STR;
}


const char *
FontPreview::PreviewText(void) const
{
	return fPreviewText.String();
} 


void
FontPreview::Draw(BRect r)
{
	BFont font;
	GetFont(&font);
	int32 width = (int32)font.StringWidth(fPreviewText.String());
	
	BPoint drawpt;
	if (width < Bounds().IntegerWidth())
		drawpt.x = (Bounds().IntegerWidth() - width) / 2;
	else
		drawpt.x = 10;
	
	font_height fheight;
	font.GetHeight(&fheight);
	int32 size = (int32)(fheight.ascent + fheight.descent + fheight.leading);
	
	if (size < Bounds().IntegerHeight() - 10)
		drawpt.y = (Bounds().IntegerHeight() + fheight.ascent) / 2;
	else
		drawpt.y = Bounds().bottom - 10;
	DrawString(fPreviewText.String(), drawpt);
}



FontPanel::FontPanel(BMessenger *target,BMessage *msg, float size, bool modal,
					bool hide_when_done)
{
	fWindow = new FontWindow(BRect(200,200,600,500),size);
	
	if (target)
		fWindow->fView->SetTarget(*target);
	
	if (msg)
		fWindow->fView->SetMessage(msg);
	
	if (modal)
		fWindow->SetFeel(B_MODAL_APP_WINDOW_FEEL);
	
	
	fWindow->fView->SetFontSize(size);
//	fWindow->fView->SetHideWhenDone(hide_when_done);
}


FontPanel::~FontPanel(void)
{
	fWindow->ReallyQuit();
	fWindow->PostMessage(B_QUIT_REQUESTED);
}


void
FontPanel::SelectFont(const BFont &font)
{
	fWindow->fView->SelectFont(&font);
}


void
FontPanel::SelectFont(font_family family, font_style style, float size)
{
	fWindow->fView->SelectFont(family,style,size);
}


void
FontPanel::Show()
{
	fWindow->Show();
}


void
FontPanel::Hide()
{
	fWindow->Hide();
}


bool
FontPanel::IsShowing(void) const
{
	return !fWindow->IsHidden();
}


BWindow *
FontPanel::Window(void) const
{
	return fWindow;
}


void
FontPanel::SetTarget(BMessenger msgr)
{
	fWindow->fView->SetTarget(msgr);
}


void
FontPanel::SetMessage(BMessage *msg)
{
	fWindow->fView->SetMessage(msg);
}


void
FontPanel::SetHideWhenDone(bool value)
{
	//fWindow->fView->SetHideWhenDone(value);
}


bool
FontPanel::HideWhenDone(void) const
{
//	return fWindow->fView->HideWhenDone();
}


void
FontPanel::SetFontSize(uint16 size)
{
	fWindow->fView->SetFontSize(size);
}
