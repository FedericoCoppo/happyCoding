/*******************************************************************************
	File        : Entities.cpp
	Date        : 16/03/2020
	Author      : Federico Coppo
	Description : Entities class interface class implementation
*******************************************************************************/

/*******************************************************************************
	Includes
*******************************************************************************/
#include "List.h"
#include "Entities.h"
#include  <iomanip>

/*******************************************************************************
	Entities Class Methods implementation
*******************************************************************************/

// Const
Entities::Entities(int64_t id, std::string title, std::string description, double timestamp)
{
	this->id = id;
	this->title = title;
	this->description = description;
	this->timestamp = timestamp;

	// NOTE : a check on unique id shoud be added
}

// Dest
Entities::~Entities()
{
	// nothing
}

// Update time stamp
bool Entities::UpdateTimestamp(double val)
{
	bool res = false;

	if (val > 0)
	{
		this->timestamp = val;
		res = true;
	}

	return res;
}

// Update title
bool Entities::UpdateTitle(std::string title)
{
	bool res = false;

	if (title != "")
	{
		this->title = title;
		res = true;
	}

	return res;
}

// Update description 
bool Entities::UpdateDescription(std::string description)
{
	bool res = false;

	if (description != "")
	{
		this->description = description;
		res = true;
	}

	return res;
}

// Print the entitie
void Entities::printEntities(void)
{
	std::cout << "|ID|: " << std::setw(4) << this->id << "  |TITLE|:  " << std::setw(14) << this->title << "  |DESC|:  ";
	std::cout  << std::setw(20) << this->description << "  |TM STAMP|:  " << std::setw(6) << this->timestamp << "\n";
	//std::cout << "|ID|: " << std::setw(9) <<  this->id << "  |TITLE|:  ";
}


/*******************************************************************************
	Store Class Methods implementation
*******************************************************************************/

// Const
Store::Store(const char* p_name)
{
	this->p_name = p_name;
}

// Dest
Store::~Store()
{
	// nothing
}

// Search in the store list the Entities by id
Entities* Store::SearchbyId(int64_t id)
{
	bool found = false;
	uint16_t cnt = 0;

	// keep the head
	Entities* pt = (Entities*) this->First();
	Entities* pt_ret = NULL;

	while ( (cnt++ < this->Count()) && (pt != NULL) )
	{
		if (pt->id == id)
		{
			found = true;
			break;
		}
		else
		{
			pt = (Entities*) pt->Next();
		}
	}

	if (found)
	{
		pt_ret = pt;
	}

	return pt_ret;
}


// 	Remove node by id
void Store::RemovebyId(int64_t id)
{
	Entities* node_pt = this->SearchbyId(id);

	if (node_pt != NULL)
	{
		std::cout << "\nremoved entities from list:" << this->p_name << "\n";
		node_pt->printEntities();
		this->Remove(node_pt);		// node extraction
		delete node_pt;				// node delete
	}
	else
	{
		std::cout << "entities id = " << id << " not found!:\n";
	}
}

// Get data by ID
void Store::GetDataById(uint64_t id)
{
	Entities*  node_pt = this->SearchbyId(id);

	if (node_pt != NULL)
	{
		node_pt->printEntities();
	}
	else
	{
		std::cout << "entities not found!\n";
	}
}

// print all the entities in the store
void Store::Print(void)
{
	uint16_t cnt = 0;

	if (this != NULL)
	{
		// keep the head
		Entities* pt = (Entities*)this->First();

		std::cout << "\nPRINT " << this->p_name << ":\n";

		while (cnt++ < this->Count())
		{
			pt->printEntities();
			pt = (Entities*)pt->Next();
		}
	}
	else
	{
		std::cout << "list is empty!\n";
	}
}

// Print an ID series
void Store::PrintSeriesID(int64_t* queryArray, uint16_t idArraySizeOut)
{
	for (int i = 0; i < idArraySizeOut; i++)
	{
		std::cout << queryArray[i] << "\n";
	}
}

// Query generic (title, description or time stamp)
uint16_t Store::Query(std::string key, std::string val, double* range, int64_t* pt_idArray, uint16_t size)
{
	uint16_t cnt = 0;
	uint16_t cntFounded = 0;
	Entities* pt = (Entities*)this->First();

	while ((cnt++ < this->Count()) && (pt != NULL))
	{
		if (cntFounded < size)							// limited size of array
		{
			if (key == "title")
			{
				if (val == pt->title)
				{
					pt_idArray[cntFounded++] = pt->id; // keep the id for title equal requested
				}
			}
			else if (key == "description")
			{
				if (val == pt->description)
				{
					pt_idArray[cntFounded++] = pt->id; // keep the id for description equal requested
				}
			}
			else if (key == "timestamp")
			{
				if ((pt->timestamp > range[0]) && (pt->timestamp < range[1]))
				{
					pt_idArray[cntFounded++] = pt->id; // keep the id for time stamp in range
				}
			}
		}

		pt = (Entities*)pt->Next();
	}

	return cntFounded;
}

// Query for title or description
uint16_t Store::Query(std::string key, std::string val, int64_t* pt_idArray, uint16_t size)
{
	double dummyArray[2] = { 0, 0 };
	return this->Query(key, val, dummyArray, pt_idArray, size);
}

// Qury for timestamp
uint16_t Store::Query(std::string key, double* range, int64_t* pt_idArray, uint16_t size)
{
	std::string dummy = "";
	return this->Query(key, dummy, range, pt_idArray, size);
}

// only time stamp
void Store::Update(int64_t id, std::string key, double param)
{
	Entities* node_pt = this->SearchbyId(id);

	if (node_pt != NULL)
	{
		this->update(node_pt, key, param);
	}
}

// title or description or both
void Store::Update(int64_t id, std::string key, std::string param, std::string key2, std::string param2)
{
	Entities* node_pt = this->SearchbyId(id);

	if (node_pt != NULL)
	{
		if (key != key2)
		{
			this->update(node_pt, key, param);
			this->update(node_pt, key2, param2);
		}
	}
}

// title or description + timestamp
void Store::Update(int64_t id, std::string key, std::string param, std::string key3, double param3)
{
	Entities* node_pt = this->SearchbyId(id);

	if (node_pt != NULL)
	{
		if (key != key3)
		{
			this->update(node_pt, key, param);
			this->update(node_pt, key3, param3);
		}
	}
}

// Update all element
void Store::Update(int64_t id, std::string key1, std::string param1, std::string key2, std::string param2, std::string key3, double param3)
{
	Entities* node_pt = this->SearchbyId(id);

	if (node_pt != NULL)
	{
		if (key1 != key2)
		{
			if (key2 != key3)
			{
				if (key1 != key3)
				{
					this->update(node_pt, key1, param1);
					this->update(node_pt, key2, param2);
					this->update(node_pt, key3, param3);
				}
			}
		}
	}
}

// Used to clone a node from another list
bool Store::CloneById(Store* sourceList, int64_t idToBeCloned)
{
	bool res = false;
	Entities * node = sourceList->SearchbyId(idToBeCloned);

	if (node != NULL)
	{
		// node has been founded
		res = true;	   
		Entities* clone = new Entities(idToBeCloned, node->title, node->description, node->timestamp);
		this->AddFirst(clone);
	}

	return res;
}

// Committ all list to another list
void Store::Committ(Store* destinationList)
{
	uint16_t cnt = 0;
	Entities* pt_source = (Entities*)this->First();								// keep the head of source 

	// for all node contained by source
	while ((cnt++ < this->Count()) && (pt_source != NULL))
	{
		Entities* pt_destination = destinationList->SearchbyId(pt_source->id);  // search the dest copy

		// if copy node has been founded
		if (pt_destination != NULL)
		{
			pt_destination->title = pt_source->title;
			pt_destination->description = pt_source->description;
			pt_destination->timestamp = pt_source->timestamp;
		}

		pt_source = (Entities*) pt_source->Next();
	}
}

// Committ a single node of the list to another list
void Store::Committ(Store* destinationList, int64_t idCommitt)
{
	Entities* pt_destination = destinationList->SearchbyId(idCommitt);
	Entities* pt_source = this->SearchbyId(idCommitt);

	if ((pt_destination != NULL) && (pt_source != NULL))
	{
		pt_destination->title = pt_source->title;
		pt_destination->description = pt_source->description;
		pt_destination->timestamp = pt_source->timestamp;
	}
}

// Delete specific node
void Store::DeleteEntities(Entities* pt)
{
	std::cout << "\nremoved entities from list:" << this->p_name << "\n";
	pt->printEntities();
	this->Remove(pt);			// node extraction 
	delete pt;					// node delete
}

// Delete all list node
void Store::DeleteAll(void)
{
	uint16_t cnt = 0;
	Entities* pt = (Entities *) this->First();		// keep the head of source and destination list
	Entities* pt_next = NULL;
	uint16_t EntitiesCnt = this->Count();

	// for all node contained by source
	while ( (cnt++ < EntitiesCnt) && (pt != NULL))
	{
		pt_next = (Entities *) pt->Next();
		this->DeleteEntities(pt);
		pt = (Entities *) pt_next;
	}
}

// update string
void Store::update(Entities* node_pt, std::string key, std::string param)
{
	if (key== "title")
	{
		node_pt->title = param;
	}
	else if (key == "description")
	{
		node_pt->description = param;
	}
}

// update double
void Store:: update(Entities* node_pt, std::string key, double param)
{
	if (key == "timestamp")
	{
		node_pt->timestamp = param;
	}
}
