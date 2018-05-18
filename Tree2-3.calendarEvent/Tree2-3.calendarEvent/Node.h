
#pragma once
#include "CalendarEvent.h"
#include <ctime>
#include "CalendarTree.h"

using namespace std;


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
		time_t m_Min2, m_Min3;				// CalendarEvent?
		CalendarEvent * m_Key;
	public:
		Node();
		~Node();
		Node * Find(CalendarEvent i_EventToFind);
		Node * FindAuxiliary(CalendarEvent i_EventToFind, Node * i_CurrentNode);
		void Insert(CalendarEvent i_EventToInsert);
		void Delete(CalendarEvent i_EventToDelete);
		bool isLeaf();//test
		void fixTree();

};