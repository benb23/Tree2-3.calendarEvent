#pragma once

#include <ctime>
#include <string.h>
#include <iostream>

using namespace std;

class CalendarEvent
{
	time_t m_StartTime;	// time_t is defined in the header file <ctime>
	time_t m_Duration;	// duration of the event, in seconds
	string m_Description; // should not contain special characters or newline
public:
	CalendarEvent(time_t startTime, time_t duration, string description); // constructor, destructor, other methods as needed
	void print();		// "print" the event to cout
	bool IsTimeInEventRage(time_t i_Time);
	bool operator==(const CalendarEvent& i_Event) const;
	time_t getEndTime();
	time_t getStartTime();
};