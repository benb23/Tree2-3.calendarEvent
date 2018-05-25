#include "CalendarEvent.h"


CalendarEvent::CalendarEvent(const CalendarEvent & i_Event)
{
	m_StartTime = i_Event.m_StartTime;
	m_Duration = i_Event.m_Duration;
	m_Description = i_Event.m_Description;
}

CalendarEvent::CalendarEvent(time_t i_StartTime, time_t i_Duration, string i_Description)
{
	m_StartTime = i_StartTime;
	m_Duration = i_Duration;
	m_Description = i_Description;
}

void CalendarEvent::print()
{
	cout << m_StartTime <<" "<< m_Duration << m_Description << "\n";
}

bool CalendarEvent::isTimeInEventRage(time_t i_Time)
{
	time_t endTime = m_StartTime + m_Duration;
	return i_Time >= m_StartTime && i_Time <= endTime;
}

bool CalendarEvent::operator==(const CalendarEvent& i_Event) const
{
	return m_StartTime == i_Event.m_StartTime && m_Duration == i_Event.m_Duration && m_Description == i_Event.m_Description;
}

time_t CalendarEvent::getEndTime()
{
	return m_StartTime + m_Duration;
}

time_t CalendarEvent::getStartTime()
{
	return	m_StartTime;
}


