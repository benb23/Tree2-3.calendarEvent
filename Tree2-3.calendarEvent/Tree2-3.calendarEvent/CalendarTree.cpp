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
	if (res != nullptr)
		return res->m_Key;
	else
		return nullptr;
}

Node * CalendarTree::eventAtAuxiliary(time_t i_EventTime, Node * i_CurrNode)
{
	if (i_CurrNode->isLeaf())
	{
		if (i_CurrNode->m_Key->IsTimeInEventRage(i_EventTime))
		{
			return i_CurrNode;
		}
		i_CurrNode =  nullptr;
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
	return i_CurrNode;
}

CalendarEvent * CalendarTree::eventAfter(time_t i_eventTime)
{
	return nullptr;
}

CalendarEvent * CalendarTree::insert(CalendarEvent * i_Event)
{
	time_t eventStartTime = i_Event->getStartTime();
	CalendarEvent * newEvent = new CalendarEvent(*i_Event);

	Node * currNode = m_Root;

	// If there is no root --> crate new root
	if (m_Root == nullptr)
	{
		m_Root = new Node();
		m_Root->m_Key =  i_Event;
		m_Root->m_Father = nullptr;
	}
	else
	{
		//  = find the place to insert	--> currNode = the place father
		//			1.	if not found return null
		//			2.	if not in range return null
		//			3.	else insert with insertNode

		currNode = findInsertStartNode(i_Event);
		if (currNode != nullptr)
		{
			currNode->Insert(newEvent);
		}
		else
		{
			return nullptr;
		}
	}

	return i_Event;
}

Node * CalendarTree::findInsertStartNode(CalendarEvent * i_Event)
{
	if (m_Root->isLeaf())
	{
		Node * newLeaf = new Node();
		newLeaf->m_Key = m_Root->m_Key;
		m_Root->m_Key = nullptr;
		m_Root->m_Left = newLeaf;
		m_Root->m_Min1 = newLeaf->m_Key->getStartTime();

		return m_Root;
	}

	Node * i_CurrNode = m_Root;


	while (!(i_CurrNode->m_Left->isLeaf() || i_CurrNode->m_Mid->isLeaf() || i_CurrNode->m_Right->isLeaf()))
	{
		if (i_CurrNode->m_Right != nullptr && i_Event->getStartTime() >= i_CurrNode->m_Min3)
		{
			i_CurrNode = i_CurrNode->m_Right;
		}
		else if (i_CurrNode->m_Mid != nullptr && i_Event->getStartTime() >= i_CurrNode->m_Min2)
		{
			i_CurrNode = i_CurrNode->m_Mid;
		}
		else
		{
			i_CurrNode = i_CurrNode->m_Left;
		}
	}

	if (i_CurrNode->isNotCrossingWithNodeEvents(i_Event))
	{
		return i_CurrNode;
	}

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
	currentNode->m_Left = nullptr;
	fixTreeAfterDelete(currentNode);
	return firstEvent;
}

void CalendarTree::printSorted()
{
	printSortedAuxiliary(m_Root);
}

void CalendarTree::printSortedAuxiliary(Node * node)
{
	if (node->m_Left->isLeaf())
	{
		node->m_Left->m_Key->print();
		node->m_Mid->m_Key->print();
		if (node->m_Right != nullptr)
		{
			node->m_Right->m_Key->print();
		}
		return;
	}
	else
	{
		printSortedAuxiliary(node->m_Left);
		printSortedAuxiliary(node->m_Mid);
		if (node->m_Left != nullptr)
		{
			printSortedAuxiliary(node->m_Left);

		}
	}
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
			fixMinToRoot(i_node->m_Father);
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

void CalendarTree::fixMinToRoot(Node *i_node)
{
	if (i_node == m_Root)
	{
		return;
	}
	else
	{
		fixMinToRoot(i_node->m_Father);
	}
	i_node->m_Min1 = i_node->m_Left->m_Min1;
	i_node->m_Min2 = i_node->m_Mid->m_Min1;
	if (i_node->m_Right != nullptr)
	{
		i_node->m_Min3 = i_node->m_Right->m_Min1;
	}
}



