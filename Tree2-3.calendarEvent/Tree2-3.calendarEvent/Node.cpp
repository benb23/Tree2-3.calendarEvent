#include "Node.h"
#include <cmath>

Node::Node()
{
	m_Father = m_Left = m_Mid = m_Right = nullptr;
	m_Min1 = m_Min2 = m_Min3 = MIN_NULL_VAL;
	m_Key = nullptr;
}

Node::~Node()
{

}

Node * Node::find(CalendarEvent i_EventToFind)
{
	Node * currentNode = this;
	return findAuxiliary(i_EventToFind, currentNode);
}

Node * Node::findAuxiliary(CalendarEvent i_EventToFind, Node * i_CurrentNode)
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
			findAuxiliary(i_EventToFind, i_CurrentNode->m_Left);

		}
		else if (i_CurrentNode->m_Mid != nullptr && i_EventToFind.getStartTime() >= i_CurrentNode->m_Min3)
		{
			findAuxiliary(i_EventToFind, i_CurrentNode->m_Right);
		}
		else
		{
			findAuxiliary(i_EventToFind, i_CurrentNode->m_Mid);
		}
	}
	return i_CurrentNode;
}

void Node::insert(CalendarEvent * i_EventToInsert)
{
	Node * newNode = new Node();
	newNode->m_Key = i_EventToInsert;
	newNode->m_Father = this;

	if (m_Mid == nullptr)
	{
		addEventTo1ChildrenNode(newNode);
	}
	else if (m_Right == nullptr)
	{
		addEventTo2ChildrenNode(newNode);
	}
	else
	{
		addEventTo3ChildrenNode(newNode);
	}
}

void Node::addEventTo1ChildrenNode(Node * i_NewNode)
{
	time_t newKeyStart = i_NewNode->m_Key->getStartTime();

	if (newKeyStart < m_Min1)
	{
		// newNode place is in the left
		m_Min2 = m_Min1;
		m_Min1 = newKeyStart;

		// shift children to the right
		m_Mid = m_Left;
		m_Left = i_NewNode;
	}
	else
	{
		m_Mid = i_NewNode;
		m_Min2 = newKeyStart;
	}
}

void Node::addEventTo2ChildrenNode(Node * i_NewNode)
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
}

void Node::addEventTo3ChildrenNode(Node * i_NewNode)
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
		/*
		 if father has 2 childern
		where is this place


		//TODO: UPADATE a pointer from the father to the child
		*/
	}

	if (newNodeKey < m_Min2 )
	{
		// newLeaf is in the left Node (newSplitNode)
		newSplitNodeLeft->m_Min1 = (time_t)fmin(newNodeKey, m_Min1);
		newSplitNodeLeft->m_Min2 = (time_t)fmax(newNodeKey, m_Min1);
		m_Min1 = m_Min2;
		m_Min2 = m_Min3;
		m_Min3 = MIN_NULL_VAL;

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
		m_Min3 = MIN_NULL_VAL;
		m_Right = nullptr;
	}
	

	// FATHER UPDATE --> FUNCTION
	if (newRoot == nullptr)
	{
		if (m_Father->getNumOfChildrens() == TWO_CHILDREN)
		{
			if (m_Father->m_Left == this)
			{ 
				// left side
				m_Father->m_Left = newSplitNodeLeft;
				m_Father->m_Min1 = newSplitNodeLeft->m_Min1;
				m_Father->m_Right = m_Father->m_Mid;
				m_Father->m_Min3 = m_Father->m_Min2;
				m_Father->m_Min2 = m_Min1;
				m_Father->m_Mid = this;
				//TODO: check if min123 updated
			}
			else if (m_Father->m_Mid == this)
			{ 
				// right side
				m_Father->m_Min1 = m_Father->m_Min2;
				m_Father->m_Right = m_Father->m_Mid;
				m_Father->m_Mid = newSplitNodeLeft;
				m_Father->m_Min3 = m_Min1;
				m_Father->m_Min2 = newSplitNodeLeft->m_Min1;
			}
		}
		else //(m_Father->getNumOfChildrens() == THREE_CHILDREN)
		 // 3 childern
		{
			Node * fatherSplitNode = new Node();
			fatherSplitNode->m_Father = this->m_Father;
			fatherSplitNode->m_Min1 = newSplitNodeLeft->m_Min1;
			fatherSplitNode->m_Left = newSplitNodeLeft;
			fatherSplitNode->m_Min2 = this->m_Min1;
			fatherSplitNode->m_Mid = this;
			newSplitNodeLeft->m_Father = fatherSplitNode;

			if (m_Father->m_Left == this)
			{
				m_Father->m_Left = fatherSplitNode;
			}
			else if (m_Father->m_Mid == this)
			{
				m_Father->m_Mid = fatherSplitNode;
			}
			else
			{
				m_Father->m_Right = fatherSplitNode;
			}

			this->m_Father = fatherSplitNode;
		}
	}

	if (newRoot != nullptr)
	{
		Node * temp = this;
	
		newRoot->m_Min1 = newSplitNodeLeft->m_Min1;
		newRoot->m_Min2 = this->m_Min1;
	}
	else
	{
		updateMinToRoot();
	}
}

// The method is updating all the Min1, Min2, Min3 values up to the root
// from the input Node
void Node::updateMinToRoot()
{
	Node * nodeFather = m_Father;
	while (nodeFather != nullptr)
	{
		if (nodeFather->m_Left != nullptr)
		{
			nodeFather->m_Min1 = nodeFather->m_Left->m_Min1;
		}

		if (nodeFather->m_Mid != nullptr)
		{
			nodeFather->m_Min2 = nodeFather->m_Mid->m_Min1;
		}
		if (nodeFather->m_Right != nullptr)
		{
			nodeFather->m_Min3 = nodeFather->m_Right->m_Min1;
		}
		nodeFather = nodeFather->m_Father;
	}
}

bool Node::isLeaf()
{
	return m_Left == nullptr && m_Right == nullptr && m_Mid == nullptr;
}

bool Node::brotherHas3children()
{
	if (m_Father->m_Left == this) 
	{
		if (m_Father->m_Mid->getNumOfChildrens() == THREE_CHILDREN)
		{
			return true;
		}
	}
	else if (m_Father->m_Right != nullptr && m_Father->m_Right == this)
	{
			if (m_Father->m_Mid->getNumOfChildrens() == THREE_CHILDREN)
			{
				return true;
			}
	}
	else if(m_Father->m_Mid == this)
	{
		if (m_Father->m_Right != nullptr)
		{
			if (m_Father->m_Right->getNumOfChildrens() == THREE_CHILDREN
				|| m_Father->m_Left->getNumOfChildrens() == THREE_CHILDREN)
			{
				return true;
			}
		}
		else if (m_Father->m_Left->getNumOfChildrens() == THREE_CHILDREN)
		{
			return true;
		}
		else
		{
			return false;
		}
		
	}
	else
	{
		return false;
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
		return m_Left->m_Key->isTimeInEventRage(startTime + 1) || m_Left->m_Key->isTimeInEventRage(endTime - 1) ||
			m_Mid->m_Key->isTimeInEventRage(startTime + 1) || m_Mid->m_Key->isTimeInEventRage(endTime - 1) ||
			m_Right->m_Key->isTimeInEventRage(startTime + 1) || m_Right->m_Key->isTimeInEventRage(endTime - 1);

	}
	else if (numOfChildren == TWO_CHILDREN)
	{
		return m_Left->m_Key->isTimeInEventRage(startTime + 1) || m_Left->m_Key->isTimeInEventRage(endTime - 1) ||
			m_Mid->m_Key->isTimeInEventRage(startTime + 1) || m_Mid->m_Key->isTimeInEventRage(endTime - 1);
	}
	else
	{
		return m_Left->m_Key->isTimeInEventRage(startTime + 1) || m_Left->m_Key->isTimeInEventRage(endTime - 1);
	} 
}
