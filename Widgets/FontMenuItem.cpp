#include "FontMenuItem.h"

#include <Bitmap.h>

/***********************************************************
 * Constructor.
 ***********************************************************/
FontMenuItem::FontMenuItem(const char* label,BMessage *message,BFont *font,char shortcut,uint32 modifiers,BBitmap *bitmap,bool copy,bool free)
	:BMenuItem(label,message,shortcut,modifiers)
{
    _font = new BFont(font);
}

/***********************************************************
 * Destructor.
 ***********************************************************/
FontMenuItem::~FontMenuItem()
{

}

/***********************************************************
 * Draw menu icon.
 ***********************************************************/
void
FontMenuItem::DrawContent()
{
	BRect r;

	r = Frame();
		
	Menu()->SetFont(_font);
	Menu()->DrawString(Label(),BPoint(r.left + 13 , r.bottom - 3 ));
//	Menu()->StrokeLine(BPoint(r.left, r.top ) , BPoint( r.right , r.bottom), B_MIXED_COLORS);
}
