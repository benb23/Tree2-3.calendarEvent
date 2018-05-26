#pragma once
#include "CalendarEvent.h"
#include <ctime>
#include "CalendarTree.h"

using namespace std;

#define THREE_CHILDREN	3
#define TWO_CHILDREN	2
#define ONE_CHILD		1

class Node
{
	private:
		friend class CalendarTree;
		Node *m_Father, *m_Left, *m_Mid, *m_Right;
		time_t m_Min1, m_Min2, m_Min3;				
		CalendarEvent * m_Key;
		void insert(CalendarEvent * i_EventToInsert);
		void addEventTo2ChildrenNode(Node * i_NewNode);
		void addEventTo3ChildrenNode(Node * i_NewNode);
		void addEventTo1ChildrenNode(Node * i_NewNode);
		void updateMinToRoot();
		int getNumOfChildrens();
		bool isLeaf();
		bool brotherHas3children();
		bool isCrossingWithNodeEvents(CalendarEvent * i_Event);
		Node * findAuxiliary(CalendarEvent i_EventToFind, Node * i_CurrentNode);

	public:
		Node();
		~Node();
		Node * find(CalendarEvent i_EventToFind);
};