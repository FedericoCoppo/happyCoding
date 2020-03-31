/*******************************************************************************
	File        : List.cpp
	Date        : 16/03/2020
	Author      : Federico Coppo
	Description : List and node classes implementation
*******************************************************************************/

/*******************************************************************************
	Includes
*******************************************************************************/
#include <stdio.h>
#include "List.h"

/*******************************************************************************
	Node Methods implementation
*******************************************************************************/

// Const
Node::Node(void)
{
	p_prev = p_next = NULL;
	p_list = NULL;
}

// Dest
Node::~Node(void)
{
	if (p_list != NULL)
	{
		p_list->Remove(this);
	}
}

// Insert a node between two node
void Node::insertBetween(Node* p_previousNode, Node* p_nextNode, NodeList* p_list)
{
	if (p_previousNode != NULL)
	{
		p_previousNode->p_next = this;
	}

	if (p_nextNode != NULL)
	{
		p_nextNode->p_prev = this;
	}

	this->p_prev = p_previousNode;
	this->p_next = p_nextNode;
	this->p_list = p_list;
}

// Autoref
void Node::selfReference(NodeList* p_list)
{
	this->p_prev = this;
	this->p_next = this;
	this->p_list = p_list;
}

// Detach node from list
void Node::detach()
{
	if (p_list != NULL)
	{
		p_prev->p_next = p_next;
		p_next->p_prev = p_prev;
		p_prev = p_next = NULL;
		p_list = NULL;
	}
}

/*******************************************************************************
	NodeList Methods implementation
*******************************************************************************/

// Const
NodeList::NodeList(void)
{
	p_first = NULL;
	count = 0;
}

// Dist .
NodeList::~NodeList(void)
{
	// Clean list
	Clear();
}

// Add node after specific node
bool NodeList::AddAfter(Node* p_node, Node* p_newNode)
{
	if (p_node != NULL && p_newNode != NULL)
	{
		if (p_node->p_list == this && p_newNode->p_list == NULL)
		{
			// Insert the node
			p_newNode->insertBetween(p_node, p_node->p_next, this);

			// Increase node counter
			count++;
			return true;
		}
	}

	return false;
}

// Add node before specific node
bool NodeList::AddBefore(Node* p_node, Node* p_newNode)
{
	if ( (p_node != NULL) && (p_newNode != NULL) )
	{
		if ( (p_node->p_list == this) && (p_newNode->p_list == NULL) )
		{
			// Insert the node
			p_newNode->insertBetween(p_node->p_prev, p_node, this);

			// Increase node counter
			count++;

			if (p_node == p_first)
			{
				p_first = p_newNode;
			}

			return true;
		}
	}

	return false;
}

// Add node in the list head
bool NodeList::AddFirst(Node* p_newNode)
{
	if (p_newNode != NULL)
	{
		if (p_newNode->p_list == NULL)
		{
			if (p_first == NULL)
			{
				p_newNode->selfReference(this);
			}
			else
			{
				p_newNode->insertBetween(p_first->p_prev, p_first, this);
			}

			// Increase node counter
			count++;

			p_first = p_newNode;

			return true;
		}
	}

	return false;
}

// Add node in the list end
bool NodeList::AddLast(Node* p_newNode)
{
	if (p_newNode != NULL)
	{
		if (p_newNode->p_list == NULL)
		{
			if (p_first == NULL)
			{
				p_newNode->selfReference(this);
				p_first = p_newNode;
			}
			else
			{
				p_newNode->insertBetween(p_first->p_prev, p_first, this);
			}

			// Increase node counter
			count++;

			return true;
		}
	}

	return false;
}

// Remove specific node of the list
bool NodeList::Remove(Node* p_node)
{
	if (p_node != NULL)
	{
		if (p_node->p_list == this)
		{
			// Decrease the counter
			count--;

			if (count == 0)
			{
				p_first = NULL;
			}

			if (p_first == p_node)
			{
				p_first = p_first->p_next;
			}

			// Detach node from list
			p_node->detach();

			return true;
		}
	}

	return false;
}

// Remove first node of the list
bool NodeList::RemoveFirst()
{
	if (p_first != NULL)
	{
		return Remove(p_first);
	}

	return false;
}

// Remove last node of the list
bool NodeList::RemoveLast()
{
	if (p_first != NULL)
	{
		return Remove(p_first->p_prev);
	}

	return false;
}

// Clear list
void NodeList::Clear()
{
	while (p_first != NULL)
	{
		Remove(p_first);
	}
}

// Check if node is present in the list
bool NodeList::Contains(Node* p_node)
{
	if (p_node != NULL)
	{
		if (p_node->p_list == this)
		{
			return true;
		}
	}

	return false;
}

// Insert node in queue
bool NodeList::Enqueue(Node* p_newNode)
{
	return AddLast(p_newNode);
}

// Estract node from head
Node* NodeList::Dequeue()
{
	Node* p_node = p_first;

	if (p_first != NULL)
	{
		Remove(p_first);
	}

	return p_node;
}

// Operator to access node list
Node* NodeList::operator[](uint16_t index) const
{
	Node* p_current = NULL;

	if (index < count)
	{
		p_current = p_first;

		for (uint16_t i = 0; p_current != NULL && i < index; i++)
		{
			p_current = p_current->Next();
		}
	}

	return p_current;
}
