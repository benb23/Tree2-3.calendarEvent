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

void Node::Insert(CalendarEvent i_EventToInsert)
{
	Node * resNode = new Node();
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