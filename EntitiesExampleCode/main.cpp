/*******************************************************************************
	File        : main.cpp
	Date        : 16/03/2020
	Author      : Federico Coppo
	Description : Main function used to test Store class
*******************************************************************************/

/*******************************************************************************
	Includes
*******************************************************************************/
#include <stdio.h>
#include "List.h"
#include "Entities.h"

/*******************************************************************************
	Static variable
*******************************************************************************/

// label used for debug
static 	double tsrange[2] = { 0.4, 14 };
static const uint16_t sizeMax = 100;
static int64_t queryArray[sizeMax] = { 0 };

int main()
{
	/*********** Assignment Part 1 – A Basic Store ***************/

	// Istantiate list (Store) of node (toDo Entities)
	Store* p_store = new Store("STORE");
	Entities* node_pt = new Entities(1, "Buy Milk", "made of almonds!", 0.1);

	// Head  insertion
	p_store->AddFirst(node_pt);			

	//  Queue insertion
	node_pt = new Entities(3, "Buy Chocolate", "made of milk!", 0.5); 
	p_store->AddLast(node_pt);			  
	node_pt = new Entities(4, "Buy Pasta", "good with sauce!", 0.7);
	p_store->AddLast(node_pt);
	node_pt = new Entities(5, "Buy Cake", "made of cream!", 10);
	p_store->AddLast(node_pt);
	node_pt = new Entities(2133, "Buy Milk", "made of almonds!", 12);
	p_store->AddLast(node_pt);
	node_pt = new Entities(15, "Buy Cake", "made of fruits!", 20);
	p_store->AddLast(node_pt);
	node_pt = new Entities(17, "Buy Cake", "made of chocolate!", 22);
	p_store->AddLast(node_pt);

	// Insertion before a node (with a specific ID)
	node_pt = new Entities(2, "Buy Cake", "not made of almonds!", 13.33);
	Entities* node_pt_before = p_store->SearchbyId(1);

	if (node_pt_before != NULL)
	{
		p_store->AddBefore(node_pt_before, node_pt); 
	}

	// Update only specified property
	p_store->Update(4, "title", "Buy biscuit");
	p_store->Update(4, "description", "Good with milk");
	p_store->Update(4, "title", "BUY BISCUIT" , "description", "GOOD WITH MILK");
	p_store->Update(4, "title", "BUY BISCUIT", "description", "GOOD WITH MILK", "timestamp", 10.1);
	p_store->Update(4, "title", "BUY biscuit", "timestamp", 10.2);
	p_store->Update(4, "timestamp", 11);
	p_store->Update(4, "description", "bad with water","timestamp", 13);

	// Debug new store
	p_store->Print();

	// Retrieve properties of an entity with given id
	std::cout << "\n\nSEARCH ENTITIES (UID = 2133):\n";
	p_store->GetDataById(2133);

	// Remove an entity with given id
	std::cout << "\nREMOVING ENTITIES:\n";
	p_store->RemovebyId(500);   // wrong id
	p_store->RemovebyId(5);		// good id

	/*********** Assignment Part 2 – Query ***************/

	p_store->Print();

	// returns a set of ids where the value of the "title" property is equal to "Buy Cake"
	uint16_t idArraySizeOut = p_store->Query("title", "Buy Cake", queryArray, sizeMax);
	std::cout << "\nQUERY |Title| = 'Buy Cake' IDs:\n";
	p_store->PrintSeriesID(queryArray, idArraySizeOut);

	// Same API to query by time stamp
	idArraySizeOut = p_store->Query("timestamp", tsrange, queryArray, sizeMax);
	std::cout << "\nQUERY |TimeStamp| in range [" << tsrange[0] << " : " << tsrange[1] << "] IDs:\n";
	p_store->PrintSeriesID(queryArray, idArraySizeOut);

	// Same API to query by description
	idArraySizeOut = p_store->Query("description", "made of almonds!", queryArray, sizeMax);
	std::cout << "\nQUERY |Description| = 'made of almonds!' IDs:\n";
	p_store->PrintSeriesID(queryArray, idArraySizeOut);

	/*********** Assignment Part 3 – Child Stores (see end of file for design consideration) ***************/

	// 1. Create a child store (a new list is created)
	Store* p_child = new Store("CHILD STORE");		// create a new list
	p_child->CloneById(p_store, 2133);				// clone entities from store list with ID = 2133
	p_child->Print();								// print child list before update

	// 2. Use it to insert, get, update, delete, and query entities
	p_child->Update(2133, "title", "Buy Cream");	// update the cloned node of child list

	std::cout << "\nCOMPARE CHILD AND STORE ENTITIES:\n";
	p_child->SearchbyId(2133)->printEntities();		// print clone entitites
	p_store->SearchbyId(2133)->printEntities();		// compare with original entities

	// Query child list of title
	std::cout << "\nQUERY (CHILD) |Title| = 'Buy Cream' IDs:\n";
	idArraySizeOut = p_child->Query("title", "Buy Cream", queryArray, sizeMax);
	p_child->PrintSeriesID(queryArray, idArraySizeOut);

	// 3. Remove the child store and commit its changes to the parent
	p_child->Committ(p_store);						// Committ the change of all node
	p_store->Print();
	// NOTE: To Committ only the change of a specific node use: p_child->Committ(p_store, 2133)
	
	// delete child node
	p_child->DeleteAll();
	delete p_child;
	p_child = NULL;
	// NOTE: to to delete a specific node use: p_child->DeleteEntities((Entities *) p_child->First())

	/*********** Assignment Part 4 – Performance Consideration ***************/
	/*< Consideration on this part is contained into README.txt file or at the end of the file >*/
	
	/*********** Free all other resources ***************/
	p_store->DeleteAll();
	delete p_store;
	p_store = NULL;
	node_pt = NULL;
	p_store->Print();
	std:: cout << "Goodbye Test ";
}


/*
Assignment Part 3 – Child Stores Design Consideration:
 
In a first design approach it has been choosen to use the same Class both for "Store and "Child" obj in order to have two separated equal linked list that can Clone and Committ nodes each other;
In this way, different Store can Clone from other Store/Child and viceversa.
In case some constrain is needed between Store and Child (i.e. Store is not allowed to clone and committ from another Store or from a Child) or in case Child obj need additional property, a better
implementation should be design "Child" as sub-class of "Store" and move Committ and Clone method under the "Child" new sub-class.

Assignment Part 3 – Mutual Committ Consideration:

What would happen in a situation where the main store has two children (i.e. siblings), both of which contain pending changes to the same entity, and one of them is committed to the parent store. What, in your opinion, are good ways to deal with this situation?
This situation is similar to what happen on GIT version system once two branches are merged generating a conflict. 
The fast solution (actually implemented) should be keeping valid only the last child committ: any new child committ on Store overwrite previous one (so you loose "in between" modifications)
The better solution, to avoid lossing in between committ, instead could be the following:
	-> every child, when copy an Entities, mantains a copy of the original Store's Entities
	-> when a child committ his own modification, it check if the actual Store Entities data is different from the original Child copy:
		--> if no difference are found committ can be done
		--> in case of differences (that means in between committ happened) the child should decide what to do (for example committ only specific data that himself manipulated and don't touch other modifications)
 
Assignment Part 4 – Performance Consideration:

Please brainstorm in a comment in your code how you could improve the performance of your `range_query` implementation. 
-1 To improve performance, using a TimeStamp-Ordered Array (instead of the list) a dichotomous research for min and max range_query can be done.

You should take child stores from Part 3 into account:
If you use a list:
- suppose Store list as ordered (increasing) for time stamp
- create, using a Child list, a chunk of Store list with cloned equidistant node (i.e. Store node = 25, Child node = 4)
- each clone node have a pointer to original node
- using child node is possible to perform dichotomous research only in defined piece of store list (Chunk) 
Using an algo with child sub-list the iteration (in means) deacrease.
For an example please see MY_README.md file.

*/
