#include "MPConnectScreen.h"

#include "GameScreen.h"
#include "Dispatcher.h"
#include "Util.h"

//std::wstring MPConnectScreen::ip = L"";

MPConnectScreen::MPConnectScreen()
{
	ipInput.init(L"Server IP:", 24, DWRITE_PARAGRAPH_ALIGNMENT_NEAR, DWRITE_FONT_WEIGHT_NORMAL,
		960 / 3 + 20, 540 / 2 - 50, 150, 250);

	connectButton.setText(L"Join", 24, DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER,
		DWRITE_FONT_WEIGHT_NORMAL);
	connectButton.setBounds(0, ipInput.getBottom(), 960, ipInput.getBottom() + 40);
	connectButton.setCallback(std::function<void()>([this]()
	{
		std::string ip = Util::convert_wstring_to_string(this->getIpFromInput());
		Dispatcher::enqueueEvent(new NetworkEvent(EVENT_TYPE::GEVT_NETWORK_CLIENT_ATTEMPTCONNECT, ip));
	}));

	connectionNotification.setText(L"", 24, DWRITE_TEXT_ALIGNMENT_CENTER,
		DWRITE_PARAGRAPH_ALIGNMENT_CENTER, DWRITE_FONT_WEIGHT_NORMAL);
	connectionNotification.setBounds(0, connectButton.getBounds().bottom + 50, 960, connectButton.getBounds().bottom + 100);

	// Pushing focusable elements in order of appearance on screen.
	focusableElements.push_back(&ipInput);
	focusableElements.push_back(&connectButton);
	focusedElement = focusableElements.begin();
	(*focusedElement)->setFocus(true);

	Dispatcher::subscribe(EVENT_TYPE::GEVT_NETWORK_CLIENT_CONNECTIONSUCCESS, this);
	Dispatcher::subscribe(EVENT_TYPE::GEVT_NETWORK_CLIENT_CONNECTIONFAIL, this);
}

MPConnectScreen::~MPConnectScreen()
{
	Dispatcher::unsubscribe(EVENT_TYPE::GEVT_NETWORK_CLIENT_CONNECTIONFAIL, this);
	Dispatcher::unsubscribe(EVENT_TYPE::GEVT_NETWORK_CLIENT_CONNECTIONSUCCESS, this);
}

std::wstring MPConnectScreen::getIpFromInput()
{
	return ipInput.getInputText();
}

void MPConnectScreen::handleKeypress(wchar_t key)
{
	if (key == VK_RETURN)
	{
		static_cast<UI_MenuOption*>(*focusedElement)->select();
	}
	else if (key == VK_ESCAPE)
	{
		Dispatcher::enqueueEvent (new ScreenEvent(EVENT_TYPE::GEVT_SCREEN_RETURN));
	}
	else if (key == VK_UP)
	{
		// perform validation to ensure that we're not going to move behind the beginning of the list
		if (focusedElement != focusableElements.begin())
		{
			(*focusedElement)->setFocus(false);
			focusedElement--;
			(*focusedElement)->setFocus(true);
		}
	}
	else if (key == VK_DOWN)
	{
		// perform validation to ensure that we're not going to dereference end of list
		if (focusedElement != --focusableElements.end())
		{
			(*focusedElement)->setFocus(false);
			focusedElement++;
			(*focusedElement)->setFocus(true);
		}
	}
	else if (key == VK_BACK || key >= ' ' && key <= '~')
	{
		UI_LabeledTextInput* lti = static_cast<UI_LabeledTextInput*>(*focusedElement);
		if (lti != nullptr) lti->charIn(key);
	}
}

void MPConnectScreen::onNotify(GameEvent* gevt)
{
	if (gevt->eventType == EVENT_TYPE::GEVT_NETWORK_CLIENT_CONNECTIONSUCCESS)
	{
		Dispatcher::enqueueEvent (new ScreenEvent(EVENT_TYPE::GEVT_SCREEN_CLEARANDSET, new GameScreen()));
	}
	else if (gevt->eventType == EVENT_TYPE::GEVT_NETWORK_CLIENT_CONNECTIONFAIL)
	{
		std::wstring message = Util::convert_string_to_wstring(static_cast<NetworkEvent*>(gevt)->message);
		connectionNotification.changeText(message);
	}
}

void MPConnectScreen::draw(ID2D1HwndRenderTarget* pRT)
{
	ipInput.draw(pRT);
	connectButton.draw(pRT);
	connectionNotification.draw(pRT);
}
