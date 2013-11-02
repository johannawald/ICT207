#pragma once

#include <Windows.h>

class Timer {
public:
	Timer(void);
	void Reset(void);
	double Duration(void) const;
private:
	LONGLONG m_lStartTime;   //start time
	LONGLONG m_lFrequency;   //frequency
};

