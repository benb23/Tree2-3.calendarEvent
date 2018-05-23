#pragma once
#include <ctime>
#include "CalendarEvent.h"
#include <iostream>

using namespace std;

class CalendarTree
{
	friend class Node;
	Node * m_Root;
	void printSortedAuxiliary(Node * root);
	void fixCaseBrotherHas3Children(Node *i_node);
	void fixCaseBrotherHas2Children(Node *i_node);

public:
	CalendarTree();
	~CalendarTree();
	void fixMinToRoot(Node *i_node);
	CalendarEvent * eventAt(time_t eventTime);
	Node * eventAtAuxiliary(time_t i_EventTime, Node * i_CurrNode);
	CalendarEvent * eventAfter(time_t i_eventTime);
	Node * eventAfterAuxiliary(Node *i_node, time_t i_eventTime);
	CalendarEvent * insert(CalendarEvent * i_eventTime);	// pointer to Event or Node?
	Node * findInsertStartNode(CalendarEvent * i_Event);
	CalendarEvent * deleteFirst();
	void printSorted();
	int numBefore(time_t i_currentTime);	// bonus function
	void fixTreeAfterDelete(Node *i_node);
	bool isCrossingWithNodeEvents2(CalendarEvent * i_Event);
};



