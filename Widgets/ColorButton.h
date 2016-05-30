//
// ColorButton
//

#ifndef _ColorButton_H
#define _ColorButton_H

#include <Button.h>
#include <Locale.h>
#include <PopUpMenu.h>
#include "ColorMenuItem.h"

#include "Misc/Colors.h"

class CColorPicker;

class ColorButton: public BButton {

typedef BButton inherited;

public:
	ColorButton(
		BRect frame
	, const char *name
	, const char *label
	, BMessage *message
	, uint32 resizemode = B_FOLLOW_LEFT | B_FOLLOW_TOP
	, uint32 flags = B_WILL_DRAW | B_NAVIGABLE);
	
	void SetBGColor(const rgb_color &clr) { m_BGColor = clr; Invalidate(); }
	rgb_color BGColor(void) const { return m_BGColor; }
	
	virtual void Draw(BRect updateRect);
	virtual void MouseDown(BPoint point);
  void SetTarget(BHandler* h);
	
private:

	rgb_color 	m_BGColor;
	BPopUpMenu *_colors;
	CColorPicker	*_cpicker;	
};


#endif // _ColorButton_H
