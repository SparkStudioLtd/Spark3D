#include "pch.h"

#include "Core/JobSystem.h"

class InitalizeJob : public Job {
public:
	void setup();
	void execute(Event* event);
	void clean();
};