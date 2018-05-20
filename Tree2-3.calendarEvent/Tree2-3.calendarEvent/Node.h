
#pragma once
#include "CalendarEvent.h"
#include <ctime>
#include "CalendarTree.h"

using namespace std;

#define THREE_CHILDREN	3
#define TWO_CHILDREN	2
#define ONE_CHILD		1

//TODO: Delete
enum eChildDirection
{
	leftChild = 0,
	midChild,
	rightChild
};

class Node
{
	
	private:
		friend class CalendarTree;
		Node *m_Father, *m_Left, *m_Mid, *m_Right;
		time_t m_Min1, m_Min2, m_Min3;				
		CalendarEvent * m_Key;
		eChildDirection m_Direction;		//TODO: Delete
	public:
		Node();
		~Node();
		Node * Find(CalendarEvent i_EventToFind);
		Node * FindAuxiliary(CalendarEvent i_EventToFind, Node * i_CurrentNode);
		void Insert(CalendarEvent i_EventToInsert);
		void AddEventToNode(Node * i_NewNode);
		void Delete(CalendarEvent i_EventToDelete);
		bool isLeaf();
		bool brotherHas3children();
		int getNumOfChildrens();
		bool isNotCrossingWithNodeEvents(CalendarEvent * i_Event);

};