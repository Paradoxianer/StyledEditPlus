#ifndef _SCROLLTAB_H_
#define _SCROLLTAB_H_

#include <View.h>
#include <Window.h>
#include <TabView.h>

#include "Messages.h"

#define SCROLL_BAR_FIX 2
#define MESSAGE_TAB_SELECTED    'sBrM'
#define MESSAGE_TAB_DESELECTED  'dBrM'

class ScrollTab : public BTab 
{
   public:
   ScrollTab(BView* tabView = NULL) : BTab(tabView)
   {

   }
      
   virtual void Select(BView *owner)
   {
   		BTab::Select(owner);
   		
//		BRect r = _tabview->Bounds();
  		BRect r = owner->Bounds();
//		r.bottom += _tabview->TabHeight() + B_H_SCROLL_BAR_HEIGHT + 2; 
//	    r.right  += B_V_SCROLL_BAR_WIDTH + 2;

		r.bottom += SCROLL_BAR_FIX;
	    r.right  += SCROLL_BAR_FIX;

		View()->ResizeTo( r.Width(), r.Height() );

		owner->Window()->PostMessage(new BMessage(MESSAGE_TAB_SELECTED));

   }
   virtual void Deselect(void)
   {
   		BTab::Deselect();   	
   		
   		/* TODO : Check why it does not work */
   		View()->Window()->PostMessage(new BMessage(MESSAGE_TAB_DESELECTED));
   
   }

};

#endif
