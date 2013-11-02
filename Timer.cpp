#include "Timer.h"

Timer::Timer(void)
{
	QueryPerformanceFrequency((LARGE_INTEGER*) &m_lFrequency);
	Reset();
}

void Timer::Reset(void)
{
	QueryPerformanceCounter((LARGE_INTEGER*) &m_lStartTime);
}

double Timer::Duration(void) const
{
	LONGLONG m_lEndTime;
	QueryPerformanceCounter((LARGE_INTEGER*) &m_lEndTime);
	return ((double)(m_lEndTime - m_lStartTime)/m_lFrequency);
}