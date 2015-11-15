#ifndef HASH_H
#define HASH_H

#include "Hash.h"

class heap {

public:

	// The constructor allocates space for the nodes of the heap
	// and the mapping (hash table) based on the specified capacity
	heap(int cap);

	// Insert a node with the specified id string, key,
	// and optionally a pointer. The key is used to
	// determine the final position of the new node.
	// Returns 0 on success
	// 1 if the heap is already filled to capacity
	// 2 if a node with the given id already exists (but the heap
	//   is not filled to capacity)
	int insert(const std::string &id, int key, void * pv = NULL);

	// Set the key of the specified node to the specified value
	// Returns 0 on success
	// 1 if a node with the given id does not exist
	int setKey(const std::string &id, int key);

	// Return the data associated with the smallest key
	// and delete that node from the binary heap.
	// If pId is supplied (ie, it is not NULL), write to that address
	// the id of the node being deleted. If pKey is supplied, write to
	// that address the key of the node being deleted. If ppData is 
	// supplied, write to that address the associated void pointer.
	// Returns 0 on success
	// 1 if the heap is empty
	int deleteMin(std::string * pId = NULL, int * pKey = NULL, void * ppData = NULL);

	// Delete the node with the specified id from the binary heap.
	// If pKey is supplied, write to that address the key of the node
	// being deleted. If ppData is supplied, write to that address the
	// associated void pointer.
	// Returns 0 on success
	// 1 if a node with the given id does not exist
	int remove(const std::string &Id, int * pKey = NULL, void * ppData = NULL);

private:

	class node {
	public:
		std::string id; // The id of this node
		int key; // The key of this node
		void * pData;

		node() {}
		node(const std::string &i, int k, void * pv = NULL);
	};

	int capacity; // The capacity of the heap
	int size; // The current size of the heap
	std::vector<node> data; // The actual binary heap
	hashTable * mapping; // Maps ids to node pointers

	void percolateUp(int posCur);
	void percolateDown(int posCur);
	int getPos(node * pn);

};

#endif