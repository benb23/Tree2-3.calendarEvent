#include "Node.h"

Node::Node()
{
	m_Father = m_Left = m_Mid = m_Right = nullptr;
	m_Min2 = m_Min3 = NULL;
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

void Node::fixTree()
{

}

