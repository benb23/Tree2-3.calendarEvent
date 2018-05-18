#include "Node.h"

Node::Node()
{
}

Node::~Node()
{
}

Node * Node::Find(CalendarEvent i_EventToFind)
{
	return nullptr;
}

void Node::Insert(CalendarEvent i_EventToInsert)
{
}

void Node::Delete(CalendarEvent i_EventToDelete)
{
}

bool Node::IsLeaf()
{
	return this->m_Left == nullptr && this->m_Right == nullptr && this->m_Mid == nullptr;
}

