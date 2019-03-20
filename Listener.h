#pragma once
#include "GameMessage.h"

class Listener
{
public:
	virtual void onNotify(GameMessage* msg) = 0;
};