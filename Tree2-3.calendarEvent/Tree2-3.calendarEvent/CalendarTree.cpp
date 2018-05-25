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
	if (m_Root == nullptr)
	{
		return nullptr;
	}
	else
	{
		Node * res = eventAtAuxiliary(i_EventTime, m_Root);
		if (res != nullptr)
		{
			return res->m_Key;
		}
		else
		{
			return nullptr;
		}
	}
}

Node * CalendarTree::eventAtAuxiliary(time_t i_EventTime, Node * i_CurrNode)
{
	if (i_CurrNode->isLeaf())
	{
		if (i_CurrNode->m_Key->isTimeInEventRage(i_EventTime))
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
		else if (i_CurrNode->m_Right == nullptr || i_EventTime < i_CurrNode->m_Min3)
		{
			eventAtAuxiliary(i_EventTime, i_CurrNode->m_Mid);
		}
		else
		{
			eventAtAuxiliary(i_EventTime, i_CurrNode->m_Right);
		}
	}
}

CalendarEvent * CalendarTree::eventAfter(time_t i_EventTime)
{
	if (m_Root == nullptr)
	{
		return nullptr;
	}
	else
	{
		Node *node = eventAfterAuxiliary(m_Root, i_EventTime);
		if (node != nullptr)
		{
			return node->m_Key;
		}
		else
		{ 
			return nullptr;
		}
	}
}

Node * CalendarTree::eventAfterAuxiliary(Node * i_Node, time_t i_EventTime)
{
	if (i_Node->m_Left->isLeaf())
	{
		if (i_Node->m_Left->m_Key->getStartTime() >= i_EventTime)
		{
			return i_Node->m_Left;
		}
		else if (i_Node->m_Mid->m_Key->getStartTime() >= i_EventTime)
		{
			return i_Node->m_Mid;
		}
		else if(i_Node->m_Right!=nullptr && i_Node->m_Right->m_Key->getEndTime() >= i_EventTime)
		{
			if (i_Node->m_Right != nullptr)
			{
				if (i_Node->m_Right->m_Key->getStartTime() > i_EventTime)
				{
					return i_Node->m_Right;
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
		if (i_Node->m_Left->m_Right != nullptr && i_Node->m_Left->m_Min3 >= i_EventTime)
		{
				eventAfterAuxiliary(i_Node->m_Left, i_EventTime);
		}
		else if(i_Node->m_Left->m_Min2 >= i_EventTime)
		{
				eventAfterAuxiliary(i_Node->m_Left, i_EventTime);
		}
		else if (i_Node->m_Mid->m_Right != nullptr && i_Node->m_Mid->m_Min3 >= i_EventTime)
		{
				eventAfterAuxiliary(i_Node->m_Mid, i_EventTime);
		}
		else if (i_Node->m_Mid->m_Min2 >= i_EventTime)
		{
				eventAfterAuxiliary(i_Node->m_Mid, i_EventTime);
		}
		else if(i_Node->m_Right != nullptr)
		{
				eventAfterAuxiliary(i_Node->m_Right, i_EventTime);
		}
	}
}

// The method is findind the currect node for an event to insert and return it (else return nullptr)
// and check if the input event is not crossing with the event thats already in the tree. 
Node * CalendarTree::findInsertStartNode(CalendarEvent * i_Event)
{
	if (m_Root->isLeaf())
	{
		Node *newRoot = new Node();
		newRoot->m_Left = m_Root;
		newRoot->m_Min1 = m_Root->m_Key->getStartTime();
		m_Root = newRoot;
	}

	if (m_Root->getNumOfChildrens() == ONE_CHILD && !m_Root->isCrossingWithNodeEvents(i_Event))
	{
		return m_Root;
	}

	Node * i_CurrNode = m_Root;

	while (!isNodeLeavesFather(i_CurrNode))
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

	if (!(i_CurrNode->isCrossingWithNodeEvents(i_Event)))
	{
		return i_CurrNode;
	}

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
		Node * nodeToInsert = new Node();
		nodeToInsert->m_Key = newEvent;
		m_Root = nodeToInsert;
		m_Root->m_Father = nullptr;
	}
	else
	{
		//  = find the place to insert	--> currNode = the place father
		//			1.	if not found return null
		//			2.	if not in range return null
		//			3.	else insert with insertNode

		currNode = findInsertStartNode(newEvent);
		if (currNode != nullptr)
		{
			if (currNode == m_Root && m_Root->getNumOfChildrens() == THREE_CHILDREN)
			{
				currNode->insert(newEvent);
				m_Root = currNode->m_Father;
			}
			else
			{
				currNode->insert(newEvent);
			}
		}
		else
		{
			return nullptr;
		}
	}

	return i_Event;
}

CalendarEvent * CalendarTree::deleteFirst()
{
	Node * currentNode = m_Root;
	CalendarEvent * firstEvent;
	if (currentNode->isLeaf())
	{
		firstEvent = currentNode->m_Key;
		m_Root = nullptr;
	}
	else
	{
		while (!currentNode->m_Left->isLeaf())
		{
			currentNode = currentNode->m_Left;
		}

		firstEvent = currentNode->m_Left->m_Key;
		deleteFirstAuxiliary();
	}
	return firstEvent;
}

void CalendarTree::deleteFirstAuxiliary()
{
	Node * currentNode = m_Root;
	CalendarEvent * firstEvent;

	while (!currentNode->m_Left->isLeaf())
	{
		currentNode = currentNode->m_Left;
	}

	currentNode->m_Left = nullptr;
	fixTreeAfterDelete(currentNode);
}

// The method returns TRUE if the node is "leaves father"
bool CalendarTree::isNodeLeavesFather(Node * i_CurrNode)
{
	return ((i_CurrNode->m_Left != nullptr && i_CurrNode->m_Left->isLeaf()) ||
		(i_CurrNode->m_Mid != nullptr && i_CurrNode->m_Mid->isLeaf()) ||
		(i_CurrNode->m_Right != nullptr && i_CurrNode->m_Right->isLeaf()));
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
		if (node->m_Right != nullptr)
		{
			printSortedAuxiliary(node->m_Right);
		}
	}
}

int CalendarTree::numBefore(time_t currentTime)
{
	return 0;
}

void CalendarTree::fixTreeAfterDelete(Node *i_node)
{
	if (i_node->getNumOfChildrens() == TWO_CHILDREN)
	{
			i_node->m_Left = i_node->m_Mid;
			i_node->m_Min1 = i_node->m_Min2;
			i_node->m_Mid = i_node->m_Right;
			i_node->m_Right = nullptr;
			i_node->m_Min2 = i_node->m_Min3;
			i_node->m_Min3 = MIN_NULL_VAL;
	}
	else
	{
		if (i_node == m_Root)
		{
				i_node->m_Father = nullptr;
				m_Root = i_node->m_Mid;
		}
		else if (i_node->brotherHas3children())
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
			i_node->m_Mid->m_Min3 = MIN_NULL_VAL;
			i_node->m_Mid->m_Right = nullptr;
			fixMinToRoot(i_node->m_Father);
}

void CalendarTree::fixCaseBrotherHas2Children(Node *i_node)
{
		i_node->m_Mid->m_Right = i_node->m_Mid->m_Mid;
		i_node->m_Mid->m_Min3 = i_node->m_Mid->m_Min2;
		i_node->m_Mid->m_Mid = i_node->m_Mid->m_Left;
		i_node->m_Mid->m_Min2 = i_node->m_Mid->m_Min1;
		i_node->m_Mid->m_Left = i_node->m_Left->m_Mid;
		i_node->m_Mid->m_Min1 = i_node->m_Left->m_Min2;
		i_node->m_Left->m_Left = nullptr;
		i_node->m_Left->m_Mid= nullptr;
		deleteFirstAuxiliary();
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



