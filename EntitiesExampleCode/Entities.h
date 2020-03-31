/*******************************************************************************
	File        : Entities.h
	Date        : 16/03/2020
	Author      : Federico Coppo
	Description : Entities class interface
*******************************************************************************/

#ifndef TODO_H_
#define TODO_H_

/*******************************************************************************
	Includes
*******************************************************************************/
#include <string>
#include <iostream>
#include "List.h"

/*******************************************************************************
	Classes declaration
*******************************************************************************/

// Class Entities
class Entities : public Node
{
public:

	// Const
	Entities(int64_t id, std::string title, std::string description, double timestamp);

	// Dest
	virtual ~Entities();

	// Single element update
	bool UpdateTimestamp(double val);
	bool UpdateTitle(std::string title);
	bool UpdateDescription(std::string description);

	// Print entities content
	void printEntities(void);

	friend class Store;

private:
	int64_t id;
	std::string title;
	std::string description;
	double timestamp;
};

// Class Store
class Store : public NodeList
{
public:

	// Const
	Store(const char* p_name);

	// Dest
	virtual ~Store();
	
	// Search in the store list the Entities by id
	Entities* SearchbyId(int64_t id);

	// Remove node by id
	void RemovebyId(int64_t id);

	// Get data by ID
	void GetDataById(uint64_t id);

	// Print all the entities in the store
	void Print(void);

	// Print an ID series
	void PrintSeriesID(int64_t* queryArray, uint16_t idArraySizeOut);

	// Query by title description or time stamp
	uint16_t Query(std::string key, std::string val, double* range, int64_t* pt_idArray,  uint16_t size);
	uint16_t Query(std::string key, std::string val, int64_t* pt_idArray, uint16_t size);
	uint16_t Query(std::string key, double* range, int64_t* pt_idArray, uint16_t size);

	// Generic update (key-value)

	// only time stamp
	void Update(int64_t id, std::string key, double param);

	// title or description or both
	void Update(int64_t id, std::string key, std::string param, std::string key2 = "", std::string param2 = ""); 

	// title or description + timestamp
	void Update(int64_t id, std::string key, std::string param, std::string key3, double param3);

	// Update all element
	void Update(int64_t id, std::string key1, std::string param1, std::string key2, std::string param2, std::string key3, double param3);

	// Used to clone a node from another list
	bool CloneById(Store* sourceList, int64_t idToBeCloned);

	// Committ all list to another list
	void Committ(Store* destinationList);

	// Committ a single node of the list to another list
	void Committ(Store* destinationList, int64_t idCommitt);

	// delete specific node
	void DeleteEntities(Entities* pt);

	// delete all list node
	void DeleteAll(void);

private:

	// update string
	void update(Entities* node_pt, std::string key, std::string param);

	// update double
	void update(Entities* node_pt, std::string key, double param);

	const char* p_name;
};

#endif /* TODO_H_ */
