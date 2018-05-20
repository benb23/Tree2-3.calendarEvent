#include "CalendarTree.h"
#include "Node.h"


CalendarTree::CalendarTree()
{
	m_Root = nullptr;
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

CalendarEvent * CalendarTree::eventAfter(time_t i_eventTime)
{
	return nullptr;
}

CalendarEvent * CalendarTree::insert(CalendarEvent * i_eventTime)
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
	currentNode->m_Left = null;
	fixTree();
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

void CalendarTree::fixTreeAfterDelete(Node *i_node)
{
	if (i_node->getNumOfChildrens() == TWO_CHILDREN)
	{
			i_node->m_Father->m_Left = i_node->m_Father->m_Mid;
			i_node->m_Father->m_Min1 = i_node->m_Father->m_Left->m_Key->getStartTime();
			i_node->m_Father->m_Mid = i_node-> m_Father->m_Right;
			i_node->m_Min2 = i_node->m_Min3;
			i_node->m_Min3 = NULL;
	}
	else
	{
		if (i_node->brotherHas3children())
		{
			fixCaseBrotherHas3Children(i_node->m_Father);
		}
		else
		{
			fixCaseBrotherHas2Children(i_node->m_Father);
		}
	}
}

void CalendarTree::fixCaseBrotherHas3Children(Node *i_node)
{
			i_node->m_Mid->m_Left = i_node->m_Father->m_Mid->m_Mid;
			i_node->m_Mid->m_Min1 = i_node->m_Father->m_Mid->m_Min2;
			i_node->m_Mid->m_Min2 = i_node->m_Father->m_Mid->m_Min3;
			i_node->m_Mid->m_Mid = i_node->m_Father->m_Mid->m_Right;
			i_node->m_Mid->m_Min3 = NULL;
			i_node->m_Mid->m_Right = nullptr;
			fixMin2Min3ToRoot(i_node->m_Father);
}

void CalendarTree::fixCaseBrotherHas2Children(Node *i_node)
{
		i_node->m_Mid->m_Right = i_node->m_Mid->m_Mid;
		i_node->m_Mid->m_Min3 = i_node->m_Mid->m_Min2;
		i_node->m_Mid->m_Mid = i_node->m_Mid->m_Left;
		i_node->m_Mid->m_Min2 = i_node->m_Mid->m_Min1;
		i_node->m_Mid->m_Left = i_node->m_Left->m_Left;
		i_node->m_Mid->m_Min1 = i_node->m_Left->m_Min2;
		i_node->m_Left->m_Left = nullptr;
		deleteFirst();//??
}

void CalendarTree::fixMin2Min3ToRoot(Node *i_node)
{
	if (this == m_Root)
	{
		return;
	}
	else
	{
		fixMin2Min3ToRoot(i_node->m_Father);
	}
	i_node->m_Min1 = i_node-> m_Left->m_Min1;
	i_node->m_Min2 = i_node->m_Mid->m_Min1;
	if (i_node->m_Right != nullptr)
	{
		i_node->m_Min3 = i_node->m_Right->m_Min1;
	}
}


