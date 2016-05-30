//Title: WidgetBlock Class
//Platform: BeOS 5
//Version: 2001.12.12
//Description:
//	A Simple BView-derived class that draws a "widget block".
//	Useful for occupying small, empty, square spaces in windows.

//Copyright (C) 2001, 2002 Kevin H. Patterson
//Available for use under the terms of the BSD license agreement:
//See the associated file "License.txt" for details.

#include "clsWidgetBlock.h"

clsWidgetBlock::clsWidgetBlock
(
	BRect frame,
	uint32 resizingMode,
	uint32 flags
)
:
	BView
	(
		frame,
		NULL,
		resizingMode,
		flags | B_WILL_DRAW
	)
{
	BackColor = ui_color(B_PANEL_BACKGROUND_COLOR);
	Color_H1 = tint_color(BackColor, B_LIGHTEN_1_TINT);
	Color_H2 = tint_color(BackColor, B_LIGHTEN_2_TINT);
	Color_D1 = tint_color(BackColor, B_DARKEN_1_TINT);
	Color_D2 = tint_color(BackColor, B_DARKEN_2_TINT);
}

clsWidgetBlock::~clsWidgetBlock()
{
}

void clsWidgetBlock::AttachedToWindow()
{
	BView::AttachedToWindow();
	BView::SetViewColor(B_TRANSPARENT_COLOR);
}

void clsWidgetBlock::Draw(BRect UpdateRect)
{
	static float left;
	static float top;
	static float right;
	static float bottom;
	left = BView::Bounds().left + 1.0;
	top = BView::Bounds().top + 1.0;
	right = BView::Bounds().right - 1.0;
	bottom = BView::Bounds().bottom - 1.0;
	BView::SetPenSize(1.0);
	BView::SetHighColor(BackColor);
	BView::FillRect(BRect(left + 1.0, top + 1.0, right - 1.0, bottom - 1.0));
	BView::SetHighColor(Color_D2);
	BView::StrokeRect(BView::Bounds());
	BView::BeginLineArray(6);
	BView::AddLine(BPoint(left, top), BPoint(right, top), Color_H2);
	BView::AddLine(BPoint(left + 1.0, top + 1.0), BPoint(right - 1.0, top + 1.0), Color_H1);
	BView::AddLine(BPoint(left, top), BPoint(left, bottom), Color_H2);
	BView::AddLine(BPoint(left + 1.0, top + 1.0), BPoint(left + 1.0, bottom - 1.0), Color_H1);
	BView::AddLine(BPoint(right, top + 1.0), BPoint(right, bottom), Color_D1);
	BView::AddLine(BPoint(left + 1.0, bottom), BPoint(right, bottom), Color_D1);
	BView::EndLineArray();
}
