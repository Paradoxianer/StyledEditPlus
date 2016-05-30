
#include <View.h>
#include <Window.h>
#include "ToolBar.h"


ToolBar::ToolBar(BRect r) : BView(r,"ToolBar", B_FOLLOW_LEFT_RIGHT | B_FOLLOW_TOP , B_WILL_DRAW)
{

	currentVerticalLimit = B_MARGIN;
	currentHorizontalLimit = B_MARGIN;
	
	bottomLimit = 9999;

}

ToolBar::ToolBar(BPoint p) : BView( BRect(p,p),"ToolBar", B_FOLLOW_LEFT_RIGHT | B_FOLLOW_TOP , B_WILL_DRAW)
{

	currentVerticalLimit = B_MARGIN;
	currentHorizontalLimit = B_MARGIN;
	
	bottomLimit = 9999;

	if ( ! Parent() )
		ResizeTo( Window()->Bounds().Width() , Window()->Bounds().bottom );
	else
		ResizeTo( Parent()->Bounds().right , Parent()->Bounds().bottom );
	
}

void ToolBar::Draw(BRect urect) 
{
	float location = Bounds().right - 5;
	
	BeginLineArray((2* Bounds().Height())/ 3);

	rgb_color darkc= { 128, 128, 128 };
	for(int i=2; i< Bounds().Height()- 1; i+= 3)
		AddLine(BPoint(location + 2, i), BPoint( location + 2, i), darkc);

	rgb_color brightc= { 239, 239, 239 };
	for(int i= 3; i< Bounds().Height(); i+= 3)
		AddLine(BPoint( location + 3, i), BPoint(location + 3, i), brightc);

	EndLineArray();
	
	BeginLineArray((2* Bounds().Height())/ 3);

//	rgb_color darkc= { 128, 128, 128 };
	for(int i=2; i< Bounds().Height()- 1; i+= 3)
		AddLine(BPoint(2, i), BPoint(2, i), darkc);

//	brightc= { 239, 239, 239 };
	for(int i= 3; i< Bounds().Height(); i+= 3)
		AddLine(BPoint(3, i), BPoint(3, i), brightc);
		
	AddLine(BPoint(5, Bounds().Height() -2 ), 
	        BPoint(Bounds().right - 5 , Bounds().Height() -2), darkc);
	        
	EndLineArray();

	BView::Draw(urect);	
}
