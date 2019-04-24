#pragma once

#include "Events.h"

class Listener
{
public:
	virtual void onNotify(Event* evt) = 0;
};