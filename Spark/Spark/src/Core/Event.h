#include "pch.h"

enum EventType {
	UPDATE,
	MOUSE,
	KEYBOARD
};

class Event {
public:
	EventType m_EventType;
};