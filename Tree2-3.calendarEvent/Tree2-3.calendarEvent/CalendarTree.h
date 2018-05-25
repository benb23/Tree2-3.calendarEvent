#pragma once
#include <ctime>
#include "CalendarEvent.h"
#include <iostream>

using namespace std;

#define MIN_NULL_VAL 0

class Node;

class CalendarTree
{
	Node * m_Root;
	void printSortedAuxiliary(Node * root);
	void fixCaseBrotherHas3Children(Node *i_node);
	void fixCaseBrotherHas2Children(Node *i_node);
	void fixMinToRoot(Node *i_node);
	Node * eventAtAuxiliary(time_t i_EventTime, Node * i_CurrNode);
	Node * eventAfterAuxiliary(Node *i_node, time_t i_eventTime);
	Node * findInsertStartNode(CalendarEvent * i_Event);
	void deleteFirstAuxiliary();
	void fixTreeAfterDelete(Node *i_node);
	bool isCrossingWithNodeEvents2(CalendarEvent * i_Event);


public:
	CalendarTree();
	~CalendarTree();
	CalendarEvent * eventAt(time_t eventTime);
	CalendarEvent * eventAfter(time_t i_eventTime);
	CalendarEvent * insert(CalendarEvent * i_eventTime);	// pointer to Event or Node?
	CalendarEvent * deleteFirst();
	void printSorted();
	int numBefore(time_t i_currentTime);	// bonus function
};



