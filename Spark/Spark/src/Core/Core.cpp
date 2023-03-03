#include "Spark.h"

void Spark::CreateCore() {

}

void Spark::RegisterApplicationSpecification(ApplicationSpecification app) {

}

bool Spark::m_ApplicationRunning = true;
void Spark::EnterLoop() {

	JobSystem::AddJob(new InitalizeJob());
	while (m_ApplicationRunning) {
		JobSystem::update();
	}
	JobSystem::clean();
}

void Spark::Shutdown() {

}