#ifndef FormatToolBar_H
#define FormatToolBar_H

#include <View.h>
#include "ToolBar.h"

class CColorPicker;
class ColorButton;
class BPopUpMenu;

class FormatToolBar : public ToolBar {

	public:
		FormatToolBar(BPoint point);
		FormatToolBar(BRect  rect);

		virtual void MessageReceived(BMessage *message);
		virtual void AttachedToWindow();
		
//		SetFamilyFont();
//		FamilyFont();
		
//		SetStyleFont();
//		StyleFont();

//		SetColor();
//		Color();

	private:

		CColorPicker    *_cpicker;
		ColorButton     *_colorb;  
		BPopUpMenu      *_styles;
		BPopUpMenu      *_fonts;
		BPopUpMenu      *_size;
  	    
  	    // Values
		rgb_color		color;
		font_family		font;
		font_style 	    style;		
};

#endif
