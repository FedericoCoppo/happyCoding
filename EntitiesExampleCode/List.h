/*******************************************************************************
	File        : List.h
	Date        : 16/03/2020
	Author      : Federico Coppo
	Description : List class interface: it contains node and list classes
*******************************************************************************/

#ifndef LIST_H_
#define LIST_H_

/*******************************************************************************
	Includes
*******************************************************************************/
#include <stdint.h>
#include <cstddef>

/*******************************************************************************
	Classes declaration
*******************************************************************************/

// Class that implement a node of a list
class Node
{
public:

	// Costr
	Node(void);

	// Dest
	virtual ~Node(void);

	// Return list of the node
	class NodeList* List() { return p_list; }

	// Return next node of the list
	Node* Next() { return p_next; }

	// Return previous node if the list
	Node* Prev() { return p_prev; }
 
private:

	// list pointer
	NodeList* p_list;

	// next node pointer
	Node* p_next;

	// previous node pointer
	Node* p_prev;

	// Insert a node between two nodes
	void insertBetween(Node* p_previousNode, Node* p_nextNode, NodeList* p_list);

	// Autoref
	void selfReference(NodeList* p_list);

	// Detach node from list
	void detach();

	// friend class
	friend class NodeList;
};

// Class that implements a list
class NodeList
{
public:

	// Const
	NodeList();

	// Dest
	virtual ~NodeList();

	// Add node after specific node
	bool AddAfter(Node* p_node, Node* p_newNode);

	// Add node before specific node
	bool AddBefore(Node* p_node, Node* p_newNode);

	// Add node in the list head
	bool AddFirst(Node* p_newNode);

	// Add node in the list end
	bool AddLast(Node* p_newNode);

	// Remove specific node of the list
	bool Remove(Node* p_node);

	// Remove first node of the list
	bool RemoveFirst();

	// Remove last node of the list
	bool RemoveLast();

	// Clear list
	void Clear();

	// Check if node is present in the list
	bool Contains(Node* p_node);

	// Insert node in queue
	bool Enqueue(Node* p_newNode);
	
	// Estract node from head
	Node* Dequeue();

	// Return node numbers
	uint16_t Count() { return count; }

	// Return first list node
	Node* First() { return p_first; }

	// Return last list node
	Node* Last() { return (p_first != NULL) ? p_first->p_prev : NULL; }

	// Operator to access node list
	Node* operator[](uint16_t index) const;
	
private:

	// Fist node pointer (HEAD)
	Node* p_first;

	// node counter
	uint16_t count;
};

#endif /* LIST_H_ */
