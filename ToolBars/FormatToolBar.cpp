
#include "FormatToolBar.h"
#include "ColorPicker.h"
#include "ColorMenuItem.h"
#include "FontMenuItem.h"
#include "ColorButton.h"
#include "Misc/Colors.h"
#include "Misc/Messages.h"

#include "clsWidgetBlock.h"

int sizes[] = { 8,10,12,14,16,18,24,36,72 };

FormatToolBar::FormatToolBar(BPoint point) : ToolBar( point)
{

	_styles = NULL;
	_colorb = new ColorButton(BRect(5,5,50,30),"Color","Color", new BMessage('ccol'));
	
	/* FONTS */
	_fonts = new BPopUpMenu("Font");
	BMessage* fontMessage;
	
    BFont font;
    font.SetSize(12);
  	int32 numFamilies = count_font_families();
	for (int32 i = 0; i < numFamilies; i++) {

		font_family family;
		get_font_family(i, &family);		
		font.SetFamilyAndStyle(family, NULL);

		fontMessage = new BMessage(MESSAGE_FONT_SELECTED);
//**		fontMessage->AddData("font", B_FONT_TYPE, &family, B_FONT_FAMILY_LENGTH + 1 );
		_fonts->AddItem(new FontMenuItem(family, fontMessage, &font));
	}

	_fonts->SetRadioMode(true);
    /* nFONTS */
    
    /* SIZE */
    BString str;
	_size = new BPopUpMenu("Size");
	for (int32 i = 0 ; i < sizeof(sizes) / sizeof(int) ; i++)
	{
		str	<< sizes[i];
		_size->AddItem(new BMenuItem(str.String(),NULL));
		str = "";
	}
    /* nSIZE */    
   
}
FormatToolBar::FormatToolBar(BRect r) : ToolBar( r)
{

	_styles = NULL;
	_colorb = new ColorButton(BRect(5,5,50,30),"Color","Color", new BMessage('ccol'));
	
	/* FONTS */
	_fonts = new BPopUpMenu("Font");
	BMessage* Message;
	
    BFont font;
    font.SetSize(12);
  	int32 numFamilies = count_font_families();
	for (int32 i = 0; i < numFamilies; i++) {

		font_family family;
		get_font_family(i, &family);		
		font.SetFamilyAndStyle(family, NULL);

		Message = new BMessage(MESSAGE_FONT_SELECTED);
//**		Message->AddData("font", B_FONT_TYPE, &family, B_FONT_FAMILY_LENGTH + 1 );
		_fonts->AddItem(new FontMenuItem(family, Message, &font));
	}

	_fonts->SetRadioMode(true);
    /* nFONTS */
    
    /* SIZE */
    BString str;
	_size = new BPopUpMenu("Size");
	for (int32 i = 0 ; i < sizeof(sizes) / sizeof(int) ; i++)
	{
		str	<< sizes[i];
		Message = new BMessage(MESSAGE_SIZE_SELECTED);
		Message->AddInt32("size", sizes[i] );
		
		_size->AddItem(new BMenuItem(str.String(),Message));
		str = "";
	}
    /* nSIZE */    

}

void FormatToolBar::AttachedToWindow()
{
	BMenuField* menu;

	_colorb->SetTarget( this );
    AddChild( _colorb );
      
    menu = new BMenuField(BRect(55, 8, 100, 20), "Fonts", NULL, _fonts);
	AddChild(menu);
    menu->MoveBy(0,3);    	
	_fonts->SetTargetForItems( this );
	//_fonts->ItemAt(0)->Invoke();

    menu = new BMenuField(BRect(155, 8, 200, 20), "Fonts", NULL, _size);
	AddChild(menu);
    menu->MoveBy(0,3);
	_size->SetTargetForItems( this );
	//_size->ItemAt(0)->Invoke();
   
}

void FormatToolBar::MessageReceived(BMessage *message)
{
	BMessage* 	fmMessage;
	BFont 		font;
		    
    long l;
								
	switch(message->what) {
	
		case MESSAGE_FONT_SELECTED:	

		    /* FONTS */
			int32		numStyles;
		    font_family* family;
		    
		    if ( ! _styles )
		    {
				BMenuField* menu;
				_styles = new BPopUpMenu("Style");				
				menu = new BMenuField(BRect(200, 8, 250, 20), "Styles", NULL, _styles);		    
				AddChild( menu );
				menu->MoveBy(0,3);
	    	}
	    	else
	    	{
	    		while (_styles->CountItems() > 0 )
	    		{
	    			delete (_styles->RemoveItem((int32)0));
	    		}
	    		
	    	}
	    	
		    font.SetSize(12);
//**			message->FindData("font", B_FONT_TYPE, (const void **)&family, &l);
			//printf("%s %d\n",*family,l);

			numStyles = count_font_styles(*family);
			for (int32 j = 0; j < numStyles; j++) {
				font_style style;
				get_font_style(*family, j, &style);
				
				font.SetFamilyAndStyle(*family, style);
				fmMessage = new BMessage(MESSAGE_STYLE_SELECTED);
		//**		fmMessage->AddData("style", B_FONT_TYPE, &style, B_FONT_STYLE_LENGTH + 1 );
		//**		fmMessage->AddData("font", B_FONT_TYPE, family, B_FONT_FAMILY_LENGTH + 1 );
				_styles->AddItem(new FontMenuItem(style, fmMessage, &font));
			}

			_styles->SetRadioMode(true);
			_styles->SetTargetForItems(this);
			/* Set a default value */
//			_styles->ItemAt(0)->Invoke();


		break;	
	
		case MESSAGE_STYLE_SELECTED:
		case MESSAGE_SIZE_SELECTED:
					
             Window()->PostMessage(message);   

		break;

		case MESSAGE_DEFAULT_COLOR_PICKER_DROP_COLOR:

			rgb_color *c;
	
			if (message && message->FindData("color", B_RGB_COLOR_TYPE, (const void **)&c, &l) == B_NO_ERROR)
			{
                 _colorb->SetBGColor((const rgb_color &)*c);
                 Window()->PostMessage(message);
			}
		
		break;
		
		case MESSAGE_COLOR_PICKER:
  			
  			_cpicker = new CColorPicker( BRect(50,50,600,600), "colorpicker");
	    	_cpicker->ResizeTo(390, 170);
	    	_cpicker->MoveTo( _cpicker->NicePosition().left, _cpicker->NicePosition().top );
  		    
  		    fmMessage = new BMessage(MESSAGE_DEFAULT_COLOR_PICKER_DROP_COLOR);
  		    fmMessage->AddData("color", B_RGB_COLOR_TYPE, &_colorb->BGColor(), sizeof(rgb_color));
  		    
		    _cpicker->Connect( fmMessage, this );
		    		
		break;

	}
	
}
