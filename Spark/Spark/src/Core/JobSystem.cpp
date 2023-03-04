#include "JobSystem.h"

std::vector<Job*> JobSystem::m_Jobs;
void JobSystem::AddJob(Job* job)
{
	job->setup();
	m_Jobs.push_back(job);
}

int getIndex(std::vector<Job*> v, Job* K)
{
    auto it = find(v.begin(), v.end(), K);
    if (it != v.end())
    {
        int index = it - v.begin();
        return index;
    }
    else {
        return -1;
    }
}

void JobSystem::update()
{
	for (Job* job : m_Jobs) {
        Event* event = new Event();
        event->m_EventType = UPDATE;
		job->execute(event);
        delete event;

		if (job->m_executeType == ONCE) {
            job->clean();
            m_Jobs.erase(m_Jobs.begin() + getIndex(m_Jobs,job));
		}
	}
}

void JobSystem::clean()
{
    for (Job* job : m_Jobs) {
        job->clean();
        m_Jobs.erase(m_Jobs.begin() + getIndex(m_Jobs, job));
    }
}

void Job::setup()
{
}

void Job::execute(Event* event)
{
}

void Job::clean()
{

}

void Job::log(std::string content)
{
    std::cout << "\u001b[31m[Spark]\u001b[0m " << "[" + m_DebugName + "] " << content << std::endl;
}
