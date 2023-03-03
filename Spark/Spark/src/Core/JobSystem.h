#pragma once
#include "pch.h"

#include "Event.h"

enum JobExecuteType {
	ONCE,
	EVENTHANDLER
};

enum JobSyncType {
	ASYNC,
	SYNC
};

class Job {
public:
	std::string m_DebugName;
	JobExecuteType m_executeType;
	JobSyncType m_syncType;
	virtual void setup();
	virtual void execute(Event* event);
	virtual void clean();
	void log(std::string content);
};

class JobSystem {
public:
	static void AddJob(Job* job);
	static std::vector<Job*> m_Jobs;
	static void update();
	static void clean();
};