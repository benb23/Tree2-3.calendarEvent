#pragma once
#include <ctime>
#include "CalendarEvent.h"



class CalendarTree
{
	Node * m_Root;
	//Node * firstLeaf;
	friend class Node;

public:
	
	CalendarTree();
	~CalendarTree();
	CalendarEvent * eventAt(time_t eventTime);
	Node * eventAtAuxiliary(time_t i_EventTime, Node * i_CurrNode);
	CalendarEvent * eventAfter(time_t i_eventTime);
	CalendarEvent * insert(CalendarEvent * i_eventTime);	// pointer to Event or Node?
	CalendarEvent * deleteFirst();
	void printSorted();
	int numBefore(time_t i_currentTime);	// bonus function
	void fixTreeAfterDelete(Node *i_node);
	void fixCaseBrotherHas3Children(Node *i_node);
	void fixCaseBrotherHas2Children(Node *i_node);
	void fixMin2Min3ToRoot(Node *i_node);
};



