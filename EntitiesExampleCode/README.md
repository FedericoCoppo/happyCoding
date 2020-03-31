## Assignment Part 1 – A Basic Store

Implement a `Store` component which is able to take care of entities identified by a unique `int64_t id` and represented as a map of properties. Here’s an API sketch in pseudo language:

```

  Store store;

  // Insert a new entity
  store.insert(id = 2133, properties = { "title" => "Buy Milk", 
                                         "description" => "made of almonds!", 
                                         "timestamp" => 2392348.12233 })

  // Update only specified properties
  store.update(id = 2133, properties = { "title" => "Buy Chocolate" })

  // Retrieve properties of an entity
  store.get(id = 2133)
  // returns { "title" => "Buy Chocolate",
               "description" => "made of almonds!",
               "timestamp" => 2392348.12233 }

  // Remove an entity with given id
  store.remove(id = 2133)

```

Make sure your implementation correctly and efficiently handles multiple consecutive inserts, updates, and removals.

## Assignment Part 2 – Queries

To make our `Store` more useful, we’re going to support two simple kinds of queries:

```

  store.query("title" => "Buy Milk")
  // returns a set of ids where the value of the "title" property is equal to "Buy Milk"

  store.range_query("timestamp" => (1000, 1300))
  // returns a set of ids where the value of the "timestamp" property is in the given range

```

## Assignment Part 3 – Child Stores
Sometimes it’s very useful to have nested transactions – so we can commit (or throw away) changes in bulk. Let’s support this. We are going to represent such pending transactions by using a “child store” concept. Here’s how it could work:

```

  Store store;
  store.insert(id = 2133, properties = { "title" => "Buy Milk", 
                                         "description" => "made of almonds!" })

  // 1. Create a child store

  Store child = store.create_child();


  // 2. Use it to insert, get, update, delete, and query entities

  child.get(id = 2133) // returns { "title" => "Buy Milk", "description" => "made of almonds!" }

  child.update(id = 2133, { "title" => "Buy Cream" })

  child.get(id = 2133) // returns { "title" => "Buy Cream", "description" => "made of almonds!" }

  store.get(id = 2133) // returns { "title" => "Buy Milk", "description" => "made of almonds!" }

  child.query("title" => "Buy Cream") // returns { 2133 }


  // 3. Remove the child store and commit its changes to the parent

  child.commit()

  store.get(id = 2133) // returns { "title" => "Buy Cream", "description" => "made of almonds!" }

```

The design space for the implementation of child stores is large, and the decisions you make might also affect your implementation of Assigments 1 and 2. Please comment on these decisions in your code.

Please also elaborate in a comment in your code what would happen in a situation where the main store has two children (i.e. siblings), both of which contain pending changes to the same entity, and one of them is committed to the parent store. What, in your opinion, are good ways to deal with this situation?


## Consideration
- The project has been written in C++.
- In the Makefile provided it has been modified only in the following line: [CXXFLAGS = -std=c++17 -Wall List.cpp Entities.cpp]
  (to compile the two additional file added to the main.cpp file)
	
## Solution Description
- List.cpp/h: this module contains the "Node" class and the "NodeList" class that is a generic list that can process the nodes (friend class)
- Entities.cpp/h: this module contains "Entities" class (inherited  by Node class) and "Store" class (inherited by "NodeList" class)
- main.cpp: this module contains code to test the classes 
- The data structure used is a linked-link structure with basic list and nodes methods (AddFirst, AddLast, Remove ..)
- The implementation try to show basic C++ principle (encapsulation, inheritance, overload, friend class..)

## Assignment Part 1 – A Basic Store
- A Store list is created and filled with consecutive Entities node (List's head/queue insertion and in between insertion)
- Using "Update" API is possible to update specific member of a specific entities
- Retrieve properties of an entity with given id is possible using "GetDataById" API
- Specific Entities removing is possibile using "RemovebyId" API that remove node linkage with list and delete the single node memory
- to print all the Store's entities is provided "Print" method

NOTE: 
The control on unique ID identifier is missed (user can create more node with same ID). 
To avoid this situation a logic check shoud be implemented once the node is created (constructor) or when a new node is added to the list.

## Assignment Part 2 – Queries
- The overloaded method "Query" of Store class allow to query for title, description and time stamp range.

## Assignment Part 3 – Child Stores
- To support pending transaction as been allocated the "Child" class 
- Using "Clone" method is possible to copy a specific node of the Store into the Child list object
- To update specific Entities of child should be used "Update" method (the same API used to update entities of Store object)
- To commit a specific Entities or all Entities from Child to Store is available the "Committ" method

NOTE: 
In a first design approach it has been choosen to use the same Class both for "Store and "Child" obj in order to have two separated equal linked list that can Clone and Committ nodes each other;
In this way, different Store can Clone from other Store/Child and viceversa.
In case some constrain is needed between Store and Child (i.e. Store is not allowed to clone and committ from another Store or from a Child) or in case Child obj need additional property, a better
implementation should be design "Child" as sub-class of "Store" and move Committ and Clone method under the "Child" new sub-class.

## Question
What would happen in a situation where the main store has two children (i.e. siblings), both of which contain pending changes to the same entity, and one of them is committed to the parent store. What, in your opinion, are good ways to deal with this situation?
This situation is similar to what happen on GIT version system once two branches are merged generating a conflict. 
The fast solution (actually implemented) should be keeping valid only the last child committ: any new child committ on Store overwrite previous one (so you loose "in between" modifications)
The better solution, to avoid lossing in between committ, instead could be the following:
	-> every child, when copy an Entities, mantains a copy of the original Store's Entities
	-> when a child committ his own modification, it check if the actual Store Entities data is different from the original Child copy:
		--> if no difference are found committ can be done
		--> in case of differences (that means in between committ happened) the child should decide what to do (for example committ only specific data that himself manipulated and don't touch other modifications)
 
## Assignment Part 4 – Performance Considerations


## Run program
The output of the program is the following:

federico@federico-VirtualBox:~/Desktop/ML/LAST$ make
g++  -std=c++17 -Wall List.cpp Entities.cpp -o main main.cpp
federico@federico-VirtualBox:~/Desktop/ML/LAST$ ./main

PRINT STORE:
|ID|:    2  |TITLE|:        Buy Cake  |DESC|:  not made of almonds!  |TM STAMP|:   13.33
|ID|:    1  |TITLE|:        Buy Milk  |DESC|:      made of almonds!  |TM STAMP|:     0.1
|ID|:    3  |TITLE|:   Buy Chocolate  |DESC|:         made of milk!  |TM STAMP|:     0.5
|ID|:    4  |TITLE|:     BUY biscuit  |DESC|:        bad with water  |TM STAMP|:      13
|ID|:    5  |TITLE|:        Buy Cake  |DESC|:        made of cream!  |TM STAMP|:      10
|ID|: 2133  |TITLE|:        Buy Milk  |DESC|:      made of almonds!  |TM STAMP|:      12
|ID|:   15  |TITLE|:        Buy Cake  |DESC|:       made of fruits!  |TM STAMP|:      20
|ID|:   17  |TITLE|:        Buy Cake  |DESC|:    made of chocolate!  |TM STAMP|:      22


SEARCH ENTITIES (UID = 2133):
|ID|: 2133  |TITLE|:        Buy Milk  |DESC|:      made of almonds!  |TM STAMP|:      12

REMOVING ENTITIES:
entities id = 500 not found!:

removed entities from list:STORE
|ID|:    5  |TITLE|:        Buy Cake  |DESC|:        made of cream!  |TM STAMP|:      10

PRINT STORE:
|ID|:    2  |TITLE|:        Buy Cake  |DESC|:  not made of almonds!  |TM STAMP|:   13.33
|ID|:    1  |TITLE|:        Buy Milk  |DESC|:      made of almonds!  |TM STAMP|:     0.1
|ID|:    3  |TITLE|:   Buy Chocolate  |DESC|:         made of milk!  |TM STAMP|:     0.5
|ID|:    4  |TITLE|:     BUY biscuit  |DESC|:        bad with water  |TM STAMP|:      13
|ID|: 2133  |TITLE|:        Buy Milk  |DESC|:      made of almonds!  |TM STAMP|:      12
|ID|:   15  |TITLE|:        Buy Cake  |DESC|:       made of fruits!  |TM STAMP|:      20
|ID|:   17  |TITLE|:        Buy Cake  |DESC|:    made of chocolate!  |TM STAMP|:      22

QUERY |Title| = 'Buy Cake' IDs:
2
15
17

QUERY |TimeStamp| in range [0.4 : 14] IDs:
2
3
4
2133

QUERY |Description| = 'made of almonds!' IDs:
1
2133

PRINT CHILD STORE:
|ID|: 2133  |TITLE|:        Buy Milk  |DESC|:      made of almonds!  |TM STAMP|:      12

COMPARE CHILD AND STORE ENTITIES:
|ID|: 2133  |TITLE|:       Buy Cream  |DESC|:      made of almonds!  |TM STAMP|:      12
|ID|: 2133  |TITLE|:        Buy Milk  |DESC|:      made of almonds!  |TM STAMP|:      12

QUERY (CHILD) |Title| = 'Buy Cream' IDs:
2133

PRINT STORE:
|ID|:    2  |TITLE|:        Buy Cake  |DESC|:  not made of almonds!  |TM STAMP|:   13.33
|ID|:    1  |TITLE|:        Buy Milk  |DESC|:      made of almonds!  |TM STAMP|:     0.1
|ID|:    3  |TITLE|:   Buy Chocolate  |DESC|:         made of milk!  |TM STAMP|:     0.5
|ID|:    4  |TITLE|:     BUY biscuit  |DESC|:        bad with water  |TM STAMP|:      13
|ID|: 2133  |TITLE|:       Buy Cream  |DESC|:      made of almonds!  |TM STAMP|:      12
|ID|:   15  |TITLE|:        Buy Cake  |DESC|:       made of fruits!  |TM STAMP|:      20
|ID|:   17  |TITLE|:        Buy Cake  |DESC|:    made of chocolate!  |TM STAMP|:      22

removed entities from list:CHILD STORE
|ID|: 2133  |TITLE|:       Buy Cream  |DESC|:      made of almonds!  |TM STAMP|:      12

removed entities from list:STORE
|ID|:    2  |TITLE|:        Buy Cake  |DESC|:  not made of almonds!  |TM STAMP|:   13.33

removed entities from list:STORE
|ID|:    1  |TITLE|:        Buy Milk  |DESC|:      made of almonds!  |TM STAMP|:     0.1

removed entities from list:STORE
|ID|:    3  |TITLE|:   Buy Chocolate  |DESC|:         made of milk!  |TM STAMP|:     0.5

removed entities from list:STORE
|ID|:    4  |TITLE|:     BUY biscuit  |DESC|:        bad with water  |TM STAMP|:      13

removed entities from list:STORE
|ID|: 2133  |TITLE|:       Buy Cream  |DESC|:      made of almonds!  |TM STAMP|:      12

removed entities from list:STORE
|ID|:   15  |TITLE|:        Buy Cake  |DESC|:       made of fruits!  |TM STAMP|:      20

removed entities from list:STORE
|ID|:   17  |TITLE|:        Buy Cake  |DESC|:    made of chocolate!  |TM STAMP|:      22
list is empty!


