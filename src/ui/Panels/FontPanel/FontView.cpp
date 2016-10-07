
#include "FontView.h"
#include <string.h>
#include <math.h>

FontView::FontView(void)
 : BListView("font_view"),
   fDivider(140.0),
   filterString("")
{
	SetSelectionMessage(new BMessage(M_FONT_SELECTED));
	//first find the normal font then use it to construck the 
	//fonts for the fontitems
}


FontView::~FontView(void)
{

}


void
FontView::AttachedToWindow(void)
{
	RescanForFonts();
}


void
FontView::SetFontSize(uint16 size)
{
}


void
FontView::SelectFont(font_family family, font_style style, float size)
{
}


void
FontView::SelectFont(BFont &font)
{
}


void
FontView::MessageReceived(BMessage *msg)
{
	switch (msg->what) {
/*		case '': {
			break;
		}*/
		default: {
			BView::MessageReceived(msg);
			break;
		}
	}
}

void
FontView::RescanForFonts(void)
{	
	DeleteAll();
	int32 numFamilies = count_font_families();
	for ( int32 i = 0; i < numFamilies; i++ )
	{
		font_family localfamily;
		if ( get_font_family ( i, &localfamily ) == B_OK )
		{
			if (strcasestr(localfamily,filterString) != NULL)
				AddItem(new FontItem(localfamily));
		}
	}
}

void FontView::SetFilter(char *newFilter)
{
	filterString=newFilter;
	int32		count	= CountItems();
	RescanForFonts();
}

void
FontView::DeleteAll(void)
{	
	MakeEmpty();
}

FontItem::FontItem(font_family myFamily): BListItem()
{
	memcpy(family,myFamily,B_FONT_FAMILY_LENGTH + 1);
	font	= BFont();
	font.SetFamilyAndFace(family,B_REGULAR_FACE);	
}

void  FontItem::DrawItem(BView *owner, BRect frame, bool complete)
{
	FontView *fView = static_cast<FontView *>(owner);
	font_height			m_fontHeight;
	rgb_color			color;
	fView->SetDrawingMode(B_OP_OVER);
	
	if (IsSelected())
		color = ui_color(B_LIST_SELECTED_BACKGROUND_COLOR);
	else
		color = ui_color(B_LIST_BACKGROUND_COLOR);
	
	fView->SetHighColor(color);
	fView->FillRect(frame);
	if (IsSelected()) 
		color = ui_color(B_LIST_SELECTED_ITEM_TEXT_COLOR);
	else
		color = ui_color(B_LIST_ITEM_TEXT_COLOR);
	
	fView->GetFontHeight(&m_fontHeight);
	fView->SetHighColor(color);
	fView->MovePenTo(frame.left+kMarginLeftRight, frame.bottom-abs(m_fontHeight.descent));
   	fView->DrawString(family);
	//save the BView font
	
	BFont tmpFont;
	owner->GetFont(&tmpFont);
	owner->SetFont(&font);
	fView->GetFontHeight(&m_fontHeight);
	fView->MovePenTo(frame.left+kMarginLeftRight+fView->DividerPosition(), frame.bottom-abs(m_fontHeight.descent));
	//draw the PreviewString
	owner->DrawString(PREVIEW_STR);
	//and restore the default BView Font
	owner->SetFont(&tmpFont);
}



void
FontItem::Update( BView *owner, const BFont *fFont)
{
	BListItem::Update(owner, fFont);
	FontView *fView = static_cast<FontView *>(owner);
	if ((fFont->StringWidth(family)+2*kMarginLeftRight)>fView->DividerPosition())
		fView->SetDividerPosition(fFont->StringWidth(family)+2*kMarginLeftRight);
	SetWidth(font.StringWidth(PREVIEW_STR) + fView->DividerPosition()+(2*kMarginLeftRight));
	font_height			m_fontHeight;
	font.GetHeight(&m_fontHeight);
	float newHeight = abs(m_fontHeight.ascent) + abs(m_fontHeight.descent) + abs(m_fontHeight.leading)+(kMarginTopBottom);
	fFont->GetHeight(&m_fontHeight);
	float newHeight2 = abs(m_fontHeight.ascent) + abs(m_fontHeight.descent) + abs(m_fontHeight.leading)+(kMarginTopBottom);
	if (newHeight > newHeight2)
		SetHeight(newHeight);
	else
		SetHeight(newHeight2);
}
