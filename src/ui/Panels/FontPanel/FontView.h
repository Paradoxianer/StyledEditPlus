#ifndef FONT_VIEW_H_
#define FONT_VIEW_H_

#include <Font.h>
#include <InterfaceDefs.h>
#include <ListView.h>
#include <ListItem.h>
#include <String.h>

#define	PREVIEW_STR "AaBbCcDdEeFfGg!?1234567890"
const uint32	M_FONT_SELECTED		= 'mfsl';
const float		kMarginTopBottom	= 2.0;
const float		kMarginLeftRight	= 4.0;

class FontView : public BListView
{
public:
				FontView(void);
				~FontView(void);
	
	void		AttachedToWindow(void);
	void		MessageReceived(BMessage *msg);

	void		SetFontSize(uint16 size);
	void		SetUnderline(bool underline);
	void		SetStrikeout(bool strkeout);
	void		SetItalic(bool italic);
	void		SetOutlined(int32 outline);

	void		SelectFont(BFont &font);
	void		SelectFont(font_family family, font_style style, float size);

	void		SetFilter(char *newFilter);
	void		ResetFilter(void);
	void		SetDividerPosition(float pos){fDivider = pos;}
	float		DividerPosition(void){return fDivider;}
	
private:	
	void		RescanForFonts(void);
	void		DeleteAll(void);
	
	float		fDivider;
	BString		filterString;
	BString		fDrawString;
	

	
};

class FontItem : public BListItem
{
public:
					FontItem(font_family myFamily);
	
	virtual void	DrawItem(BView *owner,
    		        BRect frame,
            		bool complete = false);
            char*	GetFamily(void){return family;};
            void	SetSize(float size){font.SetSize(size);};
			void	SetShear(float shear){font.SetShear(shear);};
			void	SetRotation(float rotation){font.SetRotation(rotation);};
			void	SetFalseBoldWidth(float width){font.SetFalseBoldWidth(width);};
			void	SetSpacing(uint8 spacing){font.SetSpacing(spacing);};
			void	SetEncoding(uint8 encoding){font.SetEncoding(encoding);};
			void	SetFace(uint16 face){font.SetFace(face);};
			void	SetFlags(uint32 flags){font.SetFlags(flags);};

			void	Update( BView *owner, const BFont *fFont);

private:
		font_family	family;
		BFont		font;		
};


#endif
