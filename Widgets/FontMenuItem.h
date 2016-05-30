/*************************************************************
*   FontMenuItem
*
*   FontMenuItem is a usefull UI component.
*
**************************************************************/

#ifndef __FontMenuItem_H__
#define __FontMenuItem_H__

#include <MenuItem.h>

class FontMenuItem :public BMenuItem {
public:
					FontMenuItem(const char* label
								,BMessage *message
								,BFont *font
								,char shortcut = 0
								,uint32 modifiers = 0
								,BBitmap *bitmap = NULL
								,bool copyBitmap = true
								,bool deleteInputBitmap = true);
		virtual		~FontMenuItem();

protected:
	virtual	void	DrawContent();
private:

		BFont		*_font;
};
#endif
