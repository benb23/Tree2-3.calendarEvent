#include "CalendarEvent.h"

CalendarEvent::CalendarEvent(time_t i_StartTime, time_t i_Duration, string i_Description)
{
	m_StartTime = i_StartTime;
	m_Duration = i_Duration;
	m_Description = i_Description;
}


