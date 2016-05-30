#include "FontMenu.h"
#include <MenuItem.h>

/***********************************************************
 * Constructor.
 ***********************************************************/
FontMenu::FontMenu(const char *name,
   					         BFont* font,
                             menu_layout layout = B_ITEMS_IN_COLUMN ) :BMenu(name,layout)
{
    _font = new BFont(font);
}

/***********************************************************
 * Destructor.
 ***********************************************************/
FontMenu::~FontMenu()
{

}

/***********************************************************
 * Draw menu icon.
 ***********************************************************/
void
FontMenu::Draw( BRect updateRect )
{
    BMenu::Draw(updateRect);
    
	BRect r;

	r = Bounds();
		
	Supermenu()->SetFont(_font);
	Supermenu()->DrawString(Name(),BPoint(r.left + 5 , r.bottom - 5 ));
    Supermenu()->StrokeLine(BPoint(updateRect.left, updateRect.top ) , BPoint( updateRect.right , updateRect.bottom), B_MIXED_COLORS);


}
