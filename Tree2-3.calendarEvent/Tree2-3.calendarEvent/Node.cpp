#include "Node.h"



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
			return nullptr;
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
}


//TODO: Continue
void Node::Insert(CalendarEvent i_EventToInsert)
{
	Node * newNode = new Node();
	newNode->m_Key = &i_EventToInsert;

	if (m_Mid == nullptr || m_Right == nullptr)
	{
		AddEventToNode();
	}
	else
	{
		SplitNodeAndAddEvent();
	}

}

void Node::Delete(CalendarEvent i_EventToDelete)
{
	Node *node;

	if (*m_Key == i_EventToDelete)
	{
		node = this;
	}
	else
	{
		node = Find(i_EventToDelete);
	}
		if (node->m_Father->m_Left == this)
		{
			delete m_Father->m_Left;
			m_Father->m_Left = nullptr;
		}
		else if (m_Father->m_Mid == this)
		{
			delete m_Father->m_Mid;
			m_Father->m_Mid = nullptr;
		}
		else
		{
			delete m_Father->m_Right;
			m_Father->m_Right = nullptr;
		}

		fixTree();
}

bool Node::isLeaf()
{
	return this->m_Left == nullptr && this->m_Right == nullptr && this->m_Mid == nullptr;
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

bool Node::isNotCrossingWithNodeEvents(CalendarEvent * i_Event)
{
	int numOfChildren = this->getNumOfChildrens();
	time_t startTime = i_Event->getStartTime();
	time_t endTime = i_Event->getEndTime();

	if (numOfChildren == THREE_CHILDREN)
	{
		return startTime >= m_Min1 && endTime <= m_Min2 ||
			startTime >= m_Min2 && endTime <= m_Min3 ||
			startTime >= m_Min3;
	}
	else if (numOfChildren == TWO_CHILDREN)
	{
		return startTime >= m_Min1 && endTime <= m_Min2 || startTime >= m_Min2;
	}
	else
	{
		return startTime >= m_Min1 && endTime <= m_Min2;
	} 
}
