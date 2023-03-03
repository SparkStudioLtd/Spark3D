#include "pch.h"

#include "Core/JobSystem.h"
#include "Core/AssetManager.h"

class InitalizeJob : public Job {
public:
	void setup();
	void execute(Event* event);
	void clean();
};