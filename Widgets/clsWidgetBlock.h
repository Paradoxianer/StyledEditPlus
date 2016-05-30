//Title: WidgetBlock Class
//Platform: BeOS 5
//Version: 2001.12.12
//Description:
//	A Simple BView-derived class that draws a "widget block".
//	Useful for occupying small, empty, square spaces in windows.

//Copyright (C) 2001, 2002 Kevin H. Patterson
//Available for use under the terms of the BSD license agreement:
//See the associated file "License.txt" for details.

#ifndef _clsWidgetBlock_h
#define _clsWidgetBlock_h

	#include <Application.h>
	#include <View.h>
	
	class clsWidgetBlock
	:
		public BView
	{
	public:
		clsWidgetBlock
		(
			BRect frame,
			uint32 resizingMode,
			uint32 flags
		);
		~clsWidgetBlock();
		virtual void AttachedToWindow(void);
		virtual void Draw(BRect UpdateRect);
	private:
		rgb_color BackColor;
		rgb_color Color_H1;
		rgb_color Color_H2;
		rgb_color Color_D1;
		rgb_color Color_D2;
	};

#endif
