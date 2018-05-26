#pragma once
#include <ctime>
#include "CalendarEvent.h"
#include <iostream>

using namespace std;

#define MIN_NULL_VAL 0

class Node;			// foward declaration

class CalendarTree
{
	Node * m_Root;
	void printSortedAuxiliary(Node * root);
	void fixCaseBrotherHas3Children(Node *i_node);
	void fixCaseBrotherHas2Children(Node *i_node);
	void fixTreeAfterDelete(Node *i_node);
	Node * eventAtAuxiliary(time_t i_EventTime, Node * i_CurrNode);
	Node * eventAfterAuxiliary(Node *i_node, time_t i_eventTime);
	Node * findInsertStartNode(CalendarEvent * i_Event);
	void numBeforeAuxiliary(Node * node, time_t currentTime, int& numOfEvents);

public:
	CalendarTree();
	CalendarEvent * eventAt(time_t eventTime);
	CalendarEvent * eventAfter(time_t i_eventTime);
	CalendarEvent * insert(CalendarEvent * i_eventTime);
	CalendarEvent * deleteFirst();
	void printSorted();
	int numBefore(time_t i_currentTime);
};



