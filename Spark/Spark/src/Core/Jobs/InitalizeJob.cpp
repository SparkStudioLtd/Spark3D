#include "InitalizeJob.h"

void InitalizeJob::setup()
{
	this->m_DebugName = "Initalize";
	this->m_executeType = ONCE;
	this->m_syncType = SYNC;
}

void InitalizeJob::execute(Event* event)
{
	AssetManager::loadFromFolder();

	Asset* asset = new Asset();
	asset->m_Path = "C:\\Users\\xpiot\\Documents\\test.shader";
	asset->save();

	this->log("Initalizing engine");
}

void InitalizeJob::clean() {
	
}
