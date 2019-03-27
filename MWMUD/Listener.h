#pragma once
#include "GameEvent.h"

class Listener
{
public:
	virtual void onNotify(GameEvent* evt) = 0;
};