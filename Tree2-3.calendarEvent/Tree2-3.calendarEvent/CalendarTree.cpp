#include "CalendarTree.h"
#include "Node.h"


CalendarTree::CalendarTree()
{
}

CalendarTree::~CalendarTree()
{
}

CalendarEvent * CalendarTree::eventAt(time_t i_EventTime)
{
	Node * res = eventAtAuxiliary(i_EventTime, m_Root);
	return res->m_Key;
}

Node * CalendarTree::eventAtAuxiliary(time_t i_EventTime, Node * i_CurrNode)
{
	if (i_CurrNode->isLeaf())
	{
		if (i_CurrNode->m_Key->IsTimeInEventRage(i_EventTime))
		{
			return i_CurrNode;
		}
		return nullptr;
	}
	else
	{
		if (i_CurrNode->m_Left != nullptr && i_EventTime < i_CurrNode->m_Min2)
		{
			eventAtAuxiliary(i_EventTime, i_CurrNode->m_Left);

		}
		else if (i_CurrNode->m_Mid != nullptr && i_CurrNode->m_Min2 <= i_EventTime && i_EventTime < i_CurrNode->m_Min3)
		{
			eventAtAuxiliary(i_EventTime, i_CurrNode->m_Mid);
		}
		else
		{
			eventAtAuxiliary(i_EventTime, i_CurrNode->m_Right);
		}
	}
}

CalendarEvent * CalendarTree::eventAfter(time_t eventTime)
{
	return nullptr;
}

CalendarEvent * CalendarTree::insert(CalendarEvent * eventTime)
{
	return nullptr;
}

CalendarEvent * CalendarTree::deleteFirst()
{
	Node * currentNode = m_Root;
	CalendarEvent * firstEvent;

	while (!currentNode->isLeaf())
	{
		currentNode = currentNode->m_Left;
	}

	firstEvent = currentNode->m_Key;
	currentNode->Delete(*currentNode->m_Key);
	return firstEvent;
}

void CalendarTree::printSorted()
{
}



// bonus function
int CalendarTree::numBefore(time_t currentTime)
{
	return 0;
}

