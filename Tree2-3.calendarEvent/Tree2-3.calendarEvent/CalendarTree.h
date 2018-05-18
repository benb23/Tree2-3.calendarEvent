#pragma once
#include <ctime>
#include "CalendarEvent.h"



class CalendarTree
{
	Node * m_Root;
public:
	CalendarTree();
	~CalendarTree();
	CalendarEvent * eventAt(time_t eventTime);
	Node * eventAtAuxiliary(time_t i_EventTime, Node * i_CurrNode);
	CalendarEvent * eventAfter(time_t eventTime);
	CalendarEvent * insert(CalendarEvent * eventTime);	// pointer to Event or Node?
	CalendarEvent * deleteFirst();
	void printSorted();
	int numBefore(time_t currentTime);	// bonus function
};



