#pragma once
#include "log.h"


class enum EventType { INPUT_UPDATE = 0, BULLET_DELETE = 1, PLAYER_DELETE = 2 };

class Event
{
	Event(EventType type) {}
};