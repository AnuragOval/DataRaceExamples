#pragma once
#include<Windows.h>

class AutoCriticalSection
{
private:
	CRITICAL_SECTION& m_cs; // Using it as a reference.
public:
	AutoCriticalSection(const AutoCriticalSection&) = delete;
	AutoCriticalSection& operator=(const AutoCriticalSection&) = delete;
	AutoCriticalSection(AutoCriticalSection&&) = default;
	AutoCriticalSection& operator=(AutoCriticalSection&&) = default;
	AutoCriticalSection(CRITICAL_SECTION& cs) :m_cs(cs)
	{
		EnterCriticalSection(&m_cs);
	}
	~AutoCriticalSection()
	{
		LeaveCriticalSection(&m_cs);
	}
	
};