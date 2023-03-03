#include "InitalizeJob.h"

void InitalizeJob::setup()
{
	this->m_DebugName = "Initalize";
	this->m_executeType = EVENTHANDLER;
	this->m_syncType = SYNC;
}

void InitalizeJob::execute(Event* event)
{
	this->log("Initalizing engine");
}

void InitalizeJob::clean() {
	
}
