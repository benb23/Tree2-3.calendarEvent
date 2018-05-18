
#pragma once
#include "CalendarEvent.h"
#include <ctime>
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
		Node *m_Left, *m_Mid, *m_Right;
		time_t m_Min2, m_Min3;
		CalendarEvent m_Key;
	public:
		Node();
		~Node();
		Node * Find(CalendarEvent i_EventToFind);
		void Insert(CalendarEvent i_EventToInsert);
		void Delete(CalendarEvent i_EventToDelete);
		bool IsLeaf();
};