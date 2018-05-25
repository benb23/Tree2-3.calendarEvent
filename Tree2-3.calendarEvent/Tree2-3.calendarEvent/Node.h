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
		void AddEventTo2ChildrenNode(Node * i_NewNode);
		void AddEventTo3ChildrenNode(Node * i_NewNode);
		void AddEventTo1ChildrenNode(Node * i_NewNode);
		bool isLeaf();
		bool brotherHas3children();
		int getNumOfChildrens();
		bool isCrossingWithNodeEvents(CalendarEvent * i_Event);
		void updateMinToRoot(Node * i_Node);
		Node * FindAuxiliary(CalendarEvent i_EventToFind, Node * i_CurrentNode);
	public:
		Node();
		~Node();
		Node * Find(CalendarEvent i_EventToFind);
		void Insert(CalendarEvent * i_EventToInsert);
};