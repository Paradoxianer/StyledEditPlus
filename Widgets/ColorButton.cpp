//
// ColorButton implementation
//

#include "ColorButton.h"
#include "ColorPicker.h"

#include <MenuItem.h>

ColorButton::ColorButton(
		BRect frame
	, const char *name
	, const char *label
	, BMessage *message
	, uint32 resizemode = B_FOLLOW_LEFT | B_FOLLOW_TOP
	, uint32 flags = B_WILL_DRAW | B_NAVIGABLE)
	: BButton(frame, name, label, message, resizemode, flags)
{
		_colors = new BPopUpMenu(_T("Color"));

  	for (int i = 0 ; i < (sizeof(rgbColors) / sizeof(t_rgbColor)) ; i++ )
		    _colors->AddItem(new CColorMenuItem(rgbColors[i].colorString, 
		                                        rgbColors[i].color,
		                                        new BMessage(MESSAGE_DEFAULT_COLOR_PICKER_DROP_COLOR)
		                                       ));

    _colors->AddItem(new BMenuItem("Others ...", new BMessage(MESSAGE_COLOR_PICKER) ));
  	_colors->SetRadioMode(true);

}
void ColorButton::SetTarget(BHandler* h)
{
	_colors->SetTargetForItems(h);
	//BButton::SetTarget(h);
}

void ColorButton::Draw(BRect updateRect)
{
	inherited::Draw(updateRect);
	
	rgb_color saveColor;
			
	BRect r = Bounds();
	r.InsetBy( 5, 5);

	SetHighColor(kBlack);
  StrokeRect(r);	
	r.InsetBy(1, 1);
	SetHighColor(m_BGColor);
  FillRect(r);

}

void ColorButton::MouseDown(BPoint point) {

     BMenuItem *selected;
//   BMessage *copy; 

     ConvertToScreen(&point);
     selected = _colors ->Go (point);
		 BButton::MouseDown(point);
		 
		 if ( selected ) 
		 {
				BLooper *looper;
        BHandler *target = selected->Target(&looper);
        looper->PostMessage(selected->Message(), target);
        //Window()->PostMessage(selected->Message(), target);
     }
}
