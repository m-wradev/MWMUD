#pragma once

class Focusable
{
protected:
	bool focused = false;

public:
	virtual bool hasFocus() = 0;
	virtual void setFocus(bool) = 0;
};