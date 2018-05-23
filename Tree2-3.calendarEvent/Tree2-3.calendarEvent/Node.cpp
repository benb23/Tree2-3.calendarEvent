#include "Node.h"
#include <cmath>

Node::Node()
{
	m_Father = m_Left = m_Mid = m_Right = nullptr;
	m_Min1 = m_Min2 = m_Min3 = NULL;
	m_Key = nullptr;
}

Node::~Node()
{

}

Node * Node::Find(CalendarEvent i_EventToFind)
{
	Node *currentNode = this;
	return FindAuxiliary(i_EventToFind, currentNode);
}

Node * Node::FindAuxiliary(CalendarEvent i_EventToFind, Node * i_CurrentNode)
{
	if (i_CurrentNode->isLeaf())
	{
		if (*i_CurrentNode->m_Key == i_EventToFind)
		{
			return i_CurrentNode;
		}
		else
		{
			i_CurrentNode = nullptr;
		}
	}
	else
	{
		if (i_CurrentNode->m_Left != nullptr && i_EventToFind.getEndTime() < i_CurrentNode->m_Min2)
		{
			FindAuxiliary(i_EventToFind, i_CurrentNode->m_Left);

		}
		else if (i_CurrentNode->m_Mid != nullptr && i_EventToFind.getStartTime() >= i_CurrentNode->m_Min3)
		{
			FindAuxiliary(i_EventToFind, i_CurrentNode->m_Right);
		}
		else
		{
			FindAuxiliary(i_EventToFind, i_CurrentNode->m_Mid);
		}
	}
	return i_CurrentNode;
}

//TODO: Continue
void Node::Insert(CalendarEvent * i_EventToInsert)
{
	Node * newNode = new Node();
	newNode->m_Key = i_EventToInsert;

	if (m_Mid == nullptr)
	{
		AddEventTo1ChildrenNode(newNode);
	}
	else if (m_Right == nullptr)
	{
		AddEventTo2ChildrenNode(newNode);
	}
	else
	{
		AddEventTo3ChildrenNode(newNode);
	}
}



void Node::AddEventTo1ChildrenNode(Node * i_NewNode)
{
	time_t newKeyStart = i_NewNode->m_Key->getStartTime();

	if (newKeyStart < m_Min1)
	{
		// newNode place is in the left
		m_Min2 = m_Min1;
		m_Min1 = newKeyStart;

		// shift children
		m_Mid = m_Left;
		m_Left = i_NewNode;
	}
	else
	{
		m_Mid = i_NewNode;
	}
}

void Node::AddEventTo2ChildrenNode(Node * i_NewNode)
{
	time_t newKeyStart = i_NewNode->m_Key->getStartTime();
	time_t newKeyEnd = i_NewNode->m_Key->getEndTime();

	if (newKeyEnd < m_Min2)
	{
		// newNode place is in the left
		m_Min3 = m_Min2;
		m_Min2 = m_Min1;
		m_Min1 = newKeyStart;

		// shift children
		m_Right = m_Mid;
		m_Mid = m_Left;
		m_Left = i_NewNode;
	}
	else if (newKeyStart >= m_Min2 && newKeyEnd <= m_Min3)
	{
		// newNode place is in the middle
		m_Min3 = m_Mid->m_Key->getStartTime();
		m_Min2 = newKeyStart;

		m_Right = m_Mid;
		m_Mid = i_NewNode;
	}
	else
	{
		// newNode place is in the right
		m_Right = i_NewNode;
		m_Min3 = newKeyStart;
	}

	//fixMinToRoot(this);//TODO
}

void Node::AddEventTo3ChildrenNode(Node * i_NewNode)
{
	time_t newNodeKey = i_NewNode->m_Key->getStartTime();

	Node * newSplitNodeLeft = new Node();
	Node * newRoot = nullptr;


	/*
	
			father
			/     \
		   /       \
  newSplitNode     This

	
	*/

	if (m_Father == nullptr)
	{	
		newRoot = new Node();
		newRoot->m_Left = newSplitNodeLeft;
		newRoot->m_Mid = this;
		newSplitNodeLeft->m_Father = newRoot;
		m_Father = newRoot;
	}
	else
	{
		newSplitNodeLeft->m_Father = m_Father;
	}

	if (newNodeKey < m_Min2 )
	{
		// newLeaf is in the left Node (newSplitNode)
		newSplitNodeLeft->m_Min1 = (time_t)fmin(newNodeKey, m_Min1);
		newSplitNodeLeft->m_Min2 = (time_t)fmax(newNodeKey, m_Min1);
		m_Min1 = m_Min2;
		m_Min2 = m_Min3;
		m_Min3 = NULL;

		if (newNodeKey < m_Min1)
		{
			newSplitNodeLeft->m_Left = i_NewNode;
			newSplitNodeLeft->m_Mid = m_Left;
		}
		else
		{
			newSplitNodeLeft->m_Left = m_Left;
			newSplitNodeLeft->m_Mid = i_NewNode;
		}
		m_Left = m_Mid;
		m_Mid = m_Right;
		m_Right = nullptr;
	}
	else
	{
		// newLeaf is in the right Node (this)

		newSplitNodeLeft->m_Left = m_Left;
		newSplitNodeLeft->m_Mid = m_Mid;
		newSplitNodeLeft->m_Min1 = m_Min1;
		newSplitNodeLeft->m_Min2 = m_Min2;

		if (newNodeKey < m_Min3)
		{
			m_Left = i_NewNode;
			m_Min1 = newNodeKey;
			m_Mid = m_Right;
			m_Min2 = m_Mid->m_Key->getStartTime();
			
		}
		else
		{
			m_Left = m_Right;
			m_Min1 = m_Right->m_Key->getStartTime();
			m_Mid = i_NewNode;
			m_Min2 = newNodeKey;
		}
		m_Min3 = NULL;
		m_Right = nullptr;
	}
	
	if (newRoot != nullptr)
	{
		//updateNewRoot()
		Node * temp = this;
	


		newRoot->m_Min1 = newSplitNodeLeft->m_Min1;
		newRoot->m_Min2 = this->m_Min1;
	}
	else
	{
		updateMinToRoot(this);
	}
	
}

//void Node::updateNewRoot()
//{
//
//}

//TODO: to check if working
void Node::updateMinToRoot(Node * i_Node)
{
	Node * nodeFather = i_Node->m_Father;
	while (i_Node != nullptr)
	{
		if (i_Node->m_Left != nullptr)
		{
			nodeFather->m_Min1 = i_Node->m_Left->m_Min1;
		}

		if (i_Node->m_Mid != nullptr)
		{
			nodeFather->m_Min2 = i_Node->m_Mid->m_Min1;
		}
		if (i_Node->m_Right != nullptr)
		{
			nodeFather->m_Min3 = i_Node->m_Right->m_Min1;
		}
	}
}


bool Node::isLeaf()
{
	return m_Left == nullptr && m_Right == nullptr && m_Mid == nullptr;
}

bool Node::brotherHas3children()
{
	if (m_Father->m_Left == this || m_Father->m_Right == this)
	{
		if (m_Father->m_Mid->getNumOfChildrens() == THREE_CHILDREN)
		{
			return true;
		}
	}
	else //case current node is mid child
	{
		if (m_Father->m_Right->getNumOfChildrens() == THREE_CHILDREN
			|| m_Father->m_Left->getNumOfChildrens() == THREE_CHILDREN)
		{
			return true;
		}
	}

	return false;
}

int Node::getNumOfChildrens()
{

	if (this->m_Left != nullptr && this->m_Mid != nullptr && this->m_Right != nullptr)
	{
		return THREE_CHILDREN;
	}
	else if (this->m_Left != nullptr && this->m_Mid != nullptr
		|| this->m_Left != nullptr && this->m_Right != nullptr
		|| this->m_Mid != nullptr && this->m_Right != nullptr)
	{
		return TWO_CHILDREN;
	}
	else
	{
		return ONE_CHILD;
	}
}


bool Node::isCrossingWithNodeEvents(CalendarEvent * i_Event)
{
	int numOfChildren = this->getNumOfChildrens();
	time_t startTime = i_Event->getStartTime();
	time_t endTime = i_Event->getEndTime();



	if (numOfChildren == THREE_CHILDREN)
	{
		return m_Left->m_Key->IsTimeInEventRage(startTime) || m_Left->m_Key->IsTimeInEventRage(endTime - 1) ||
			m_Mid->m_Key->IsTimeInEventRage(startTime) || m_Mid->m_Key->IsTimeInEventRage(endTime - 1) ||
			m_Right->m_Key->IsTimeInEventRage(startTime) || m_Right->m_Key->IsTimeInEventRage(endTime - 1);

	}
	else if (numOfChildren == TWO_CHILDREN)
	{
		return m_Left->m_Key->IsTimeInEventRage(startTime) || m_Left->m_Key->IsTimeInEventRage(endTime) ||
			m_Mid->m_Key->IsTimeInEventRage(startTime) || m_Mid->m_Key->IsTimeInEventRage(endTime);
	}
	else
	{
		return m_Left->m_Key->IsTimeInEventRage(startTime) || m_Left->m_Key->IsTimeInEventRage(endTime);
	} 


}
