#ifndef _TOOLBAR_H_
#define _TOOLBAR_H_

#define B_DEFAULT_HIGH_TOOLBAR 35

/* Styles */
#define B_HORIZONTAL_TOOLBAR   (1<<0)
#define B_VERTICAL_TOOLBAR     (1<<1)
#define B_MOVABLE_TOOLBAR      (1<<2)
#define B_CONFIGURABLE_TOOLBAR (1<<3)

#define B_MARGIN 5

#include <View.h>

class ToolBar : public BView 
{
   public:
      ToolBar(BRect r);
      
      /* SelfSizabe */
      ToolBar(BPoint p);
   
      virtual void AddChild(BView* view) {

                  view->ResizeToPreferred();
                  view->MoveTo( currentVerticalLimit, currentHorizontalLimit );
                  
                  currentVerticalLimit += view->Bounds().Width() + B_MARGIN;
                  
                  BView::AddChild(view);
                  /*
				  if (bottomLimit > view->Bounds().bottom + 2*B_MARGIN) 
				  {
				  	bottomLimit = view->Bounds().Width() + 2*B_MARGIN;
				  	ResizeTo(Bounds().Height(), view->Bounds().Width() + 2*B_MARGIN );
				  }
				  */
              }
              
		virtual void Draw(BRect urect);
                void AddHiddenChild(BView* view);
                void SetStyle();
              
   private:

      int32 style;
      float currentVerticalLimit;
      /* For a case of multilines or Horizontal toolBar */
      float currentHorizontalLimit;
      
      float bottomLimit;

};

#endif
