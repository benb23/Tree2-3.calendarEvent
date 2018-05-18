#pragma once
#include <ctime>
#include "CalendarEvent.h"

class CalendarTree
{


public:
	CalendarTree();
	~CalendarTree();
	
	CalendarEvent * eventAt(time_t eventTime);
	CalendarEvent * eventAfter(time_t eventTime);
	CalendarEvent * insert(CalendarEvent * eventTime);	// pointer to Event or Node?
	CalendarEvent * deleteFitrst();
	void printSorted();
	int numBefore(time_t currentTime);	// bonus function
};



