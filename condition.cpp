#include "condition.h"

Condition::Condition(Mutex & mutex) : m_mutex(mutex)
{
	pthread_cond_init(&m_cond, NULL);
}

Condition::~Condition()
{
	pthread_cond_destroy(&m_cond);
}

void Condition::Wait()
{
	pthread_cond_wait(&m_cond, m_mutex.GetMutex());
}

bool Condition::WaitForSeconds(double seconds)
{
	struct timespec stExpireTime;
	struct timeval now;
	gettimeofday(&now, NULL);
	
	stExpireTime.tv_sec = static_cast<time_t>(now.tv_sec) + static_cast<time_t>(seconds);
	stExpireTime.tv_nsec = static_cast<long>(now.tv_usec * 1000);
	return ETIMEDOUT == pthread_cond_timedwait(&m_cond, m_mutex.GetMutex(), &stExpireTime);
}

void Condition::Notify()
{
	pthread_cond_signal(&m_cond);
}

void Condition::NotifyAll()
{
	pthread_cond_broadcast(&m_cond);
}
