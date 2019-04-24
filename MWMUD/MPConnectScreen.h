#pragma once

#include <list>

#include "Screen.h"
#include "UI_LabeledTextInput.h"
#include "Listener.h"

class MPConnectScreen : public Screen, public Listener
{
	friend std::function<void()>;

private:
	std::list<Focusable*> focusableElements;
	std::list<Focusable*>::iterator focusedElement;
	UI_LabeledTextInput ipInput;
	UI_MenuOption connectButton;
	UI_Text connectionNotification;

public:
	MPConnectScreen();
	~MPConnectScreen();
	//static std::wstring ip; // static so that lambda can capture it

	std::wstring getIpFromInput();

	void handleKeypress(wchar_t key) override;
	void onNotify(GameEvent* gevt) override;
	void draw(ID2D1HwndRenderTarget* pRT) override;
};

