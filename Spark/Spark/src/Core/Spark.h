#include "pch.h"

#include "ApplicationSpecification.h"
#include "Core/JobSystem.h"
#include "Core/Jobs/InitalizeJob.h"

class Spark {
public:
	static bool m_ApplicationRunning;

	static void CreateCore();
	static void RegisterApplicationSpecification(ApplicationSpecification appSpec);
	static void EnterLoop();
	static void Shutdown();
};