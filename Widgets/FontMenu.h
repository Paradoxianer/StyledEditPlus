/*************************************************************
*   FontMenuItem
*
*   FontMenuItem is a usefull UI component.
*
**************************************************************/

#ifndef __FontMenu_H__
#define __FontMenu_H__

#include <Menu.h>

class FontMenu :public BMenu {
public:
                    FontMenu(const char *name,
                             BFont* font,
                             menu_layout layout = B_ITEMS_IN_COLUMN );
							 
		virtual		~FontMenu();

protected:
	virtual	void	Draw( BRect updateRect );
private:

		BFont		*_font;
};
#endif
