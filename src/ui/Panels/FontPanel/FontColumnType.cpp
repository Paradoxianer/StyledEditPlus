// #pragma mark - BFontField


BFontField::BFontField(const char* string)
	:
	fWidth(0),
	fString(string),
	fClippedString(string)
{
}


void
BFontField::SetString(const char* val)
{
	fString = val;
	fClippedString = "";
	fWidth = 0;
}


const char*
BFontField::String() const
{
	return fString.String();
}


void
BFontField::SetWidth(float width)
{
	fWidth = width;
}


float
BFontField::Width()
{
	return fWidth;
}


void
BFontField::SetClippedString(const char* val)
{
	fClippedString = val;
}


bool
BFontField::HasClippedString() const
{
	return !fClippedString.IsEmpty();
}


const char*
BFontField::ClippedString()
{
	return fClippedString.String();
}


// #pragma mark - BStringColumn


BStringColumn::BStringColumn(const char* title, float width, float minWidth,
	float maxWidth, uint32 truncate, alignment align)
	:
	BTitledColumn(title, width, minWidth, maxWidth, align),
	fTruncate(truncate)
{
}


void
BStringColumn::DrawField(BField* _field, BRect rect, BView* parent)
{
	float width = rect.Width() - (2 * kTEXT_MARGIN);
	BFontField* field = static_cast<BFontField*>(_field);
	float fieldWidth = field->Width();
	bool updateNeeded = width != fieldWidth;

	if (updateNeeded) {
		BString out_string(field->String());
		float preferredWidth = parent->StringWidth(out_string.String());
		if (width < preferredWidth) {
			parent->TruncateString(&out_string, fTruncate, width + 2);
			field->SetClippedString(out_string.String());
		} else
			field->SetClippedString("");
		field->SetWidth(width);
	}

	DrawString(field->HasClippedString()
		? field->ClippedString()
		: field->String(), parent, rect);
}


float
BStringColumn::GetPreferredWidth(BField *_field, BView* parent) const
{
	BFontField* field = static_cast<BFontField*>(_field);
	return parent->StringWidth(field->String()) + 2 * kTEXT_MARGIN;
}


int
BStringColumn::CompareFields(BField* field1, BField* field2)
{
	return ICompare(((BFontField*)field1)->String(),
		(((BFontField*)field2)->String()));
}


bool
BStringColumn::AcceptsField(const BField *field) const
{
	return static_cast<bool>(dynamic_cast<const BFontField*>(field));
}
