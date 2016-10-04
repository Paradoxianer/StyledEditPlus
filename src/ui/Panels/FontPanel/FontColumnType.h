#ifndef FONT_COLUMN_TYPES_H
#define FONT_COLUMN_TYPES_H

#include <Font.h>

class BFontField : public BField
{
public:
								BStringField(const char* string);

			void				SetString(const char* string);
			const char*			String() const;
			void				SetClippedString(const char* string);
			bool				HasClippedString() const;
			const char*			ClippedString();
			void				SetWidth(float);
			float				Width();
			void				SetFont(BFont *font);
			BFont*				Font(void);

private:
			float				fWidth;
			BString				fString;
			BString				fClippedString;
			BFont				fFont;
};


//--------------------------------------------------------------------

class BFontColumn : public BTitledColumn
{
public:
								BFontColumn(const char* title, float width,
									float minWidth, float maxWidth, uint32 truncate,
									alignment align = B_ALIGN_LEFT);
	virtual	void				DrawField(BField* field, BRect rect, BView* parent);
	virtual	int					CompareFields(BField* field1, BField* field2);
	virtual	float				GetPreferredWidth(BField* field, BView* parent) const;
	virtual	bool				AcceptsField(const BField* field) const;

private:
			uint32				fTruncate;
};



#endif	// FONT_COLUMN_TYPES_H
