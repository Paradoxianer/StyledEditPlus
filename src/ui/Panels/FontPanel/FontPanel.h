#ifndef FONTPANEL_H_
#define FONTPANEL_H_

#include <View.h>
#include <Window.h>
#include <Button.h>
#include <ListView.h>
#include <ListItem.h>
#include <Font.h>
#include <Message.h>
#include <Messenger.h>
#include <Catalog.h>

#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "FontPanel"

class FontWindow;

enum
{
	M_FONT_SELECTED='mfsl'
};

enum
{
	M_OK = 'm_ok',
	M_CANCEL,
	M_SIZE_CHANGED,
	M_FAMILY_SELECTED,
	M_STYLE_SELECTED,
	M_HIDE_WINDOW
};


#define	PREVIEW_STR "AaBbCcDdEeFfGg!?1234567890"
const float		kMarginTopBottom	= 2.0;
const float		kMarginLeftRight	= 4.0;


class FontPanel
{
public:
						FontPanel(BMessenger *target = NULL,
									BMessage *message = NULL,
									float size = 12,
									bool modal = false,
									bool hide_when_done = true);
	virtual				~FontPanel(void);
			void		SelectFont(const BFont &font);
			void		SelectFont(font_family family, font_style style,
									float size = 12);
			void		Show();
			void		Hide();
			bool		IsShowing(void) const;
			void		SetTarget(BMessenger msgr);
			void		SetMessage(BMessage *msg);
			BWindow *	Window(void) const;
			void		SetHideWhenDone(bool value);
			bool		HideWhenDone(void) const;
			void		SetFontSize(uint16 size);
private:
		FontWindow		*fWindow;
	
};

#endif
