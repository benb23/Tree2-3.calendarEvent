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
	Node *node = eventAfterAuxiliary(m_Root, i_eventTime);
	return node->m_Key;
}

Node * CalendarTree::eventAfterAuxiliary(Node * i_node, time_t i_eventTime)
{
	if (i_node->isLeaf())
	{
		if (i_node->m_Left->m_Key->getStartTime() > i_eventTime)
		{
			return i_node->m_Left;
		}
		else if (i_node->m_Mid->m_Key->getStartTime() > i_eventTime)
		{
			return i_node->m_Mid;
		}
		else if(i_node->m_Right->m_Key->getEndTime()>i_eventTime)
		{
			if (i_node->m_Right != nullptr)
			{
				if (i_node->m_Right->m_Key->getStartTime() > i_eventTime)
				{
					return i_node->m_Right;
				}
			}
		}
		else
		{
			return nullptr;
		}
	}
	else
	{
		if (i_node->m_Min1 > i_eventTime)
		{
			eventAfterAuxiliary(i_node->m_Left, i_eventTime);
		}
		else if(i_node->m_Min2 > i_eventTime)
		{
			eventAfterAuxiliary(i_node->m_Mid, i_eventTime);
		}
		else
		{
			eventAfterAuxiliary(i_node->m_Right, i_eventTime);
		}
	}
}

CalendarEvent * CalendarTree::insert(CalendarEvent * i_Event)
{
	time_t eventStartTime = i_Event->getStartTime();

	Node * nodeToInsert = new Node();
	nodeToInsert->m_Key = i_Event;

	Node * currNode = m_Root;

	// If there is no root --> crate new root
	if (m_Root == nullptr)
	{
		m_Root = nodeToInsert;
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
			currNode->Insert(*i_Event);
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
		Node *newRoot = new Node();
		newRoot->m_Left = m_Root;
		newRoot->m_Min1 = m_Root->m_Key->getStartTime();
		m_Root = newRoot;
		return m_Root;
	}

	Node * i_CurrNode = m_Root;

	while (!i_CurrNode->isLeaf())
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



