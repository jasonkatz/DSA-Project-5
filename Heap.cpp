#include "Heap.h"
#include <vector>
#include <string>
#include <climits>

heap::heap(int cap) {
	capacity = cap;
	size = 0;
	data.resize(capacity + 1);
	mapping = new hashTable(capacity * 2);
}

int heap::insert(const std::string &id, int key, void * pv) {
	if (size == capacity) {
		return 1;
	}

	if (mapping->contains(id)) {
		return 2;
	}

	data[++size] = node(id, key, pv);
	mapping->insert(id, &data[size]);
	percolateUp(size);

	return 0;
}

int heap::setKey(const std::string &id, int key) {
	// Return 1 if node with given id does not exist
	if (!mapping->contains(id)) {
		return 1;
	}

	// Swap out old key for new key
	node * pn = static_cast<node *>(mapping->getPointer(id));
	int oldKey = pn->key;
	pn->key = key;
	int hole = getPos(pn);

	// If new key is a reduction, percolate up
	if (key < oldKey) {
		percolateUp(hole);
	}

	// If new key is an increase, percolate down
	if (key > oldKey) {
		percolateDown(hole);
	}

	return 0;
}

int heap::deleteMin(std::string * pId, int * pKey, void * ppData) {
	// Return 1 if heap is empty
	if (size == 0) {
		return 1;
	}

	// Set optional data parameters
	node n = data[1];
	
	// Delete item from hash table
	mapping->remove(n.id);

	if (pId) {
		*pId = n.id;
	}
	if (pKey) {
		*pKey = n.key;
	}
	if (ppData) {
		*(static_cast<void **>(ppData)) = n.pData;
	}

	// Swap root node with last node and new root down
	data[1] = data[size--];
	mapping->setPointer(data[1].id, &data[1]);
	percolateDown(1);

	return 0;
}

int heap::remove(const std::string &id, int * pKey, void * ppData) {
	// Return 1 if node with given id does not exist
	if (!mapping->contains(id)) {
		return 1;
	}

	// Set optional data parameters
	node * pn = static_cast<node *>(mapping->getPointer(id));

	if (pKey) {
		*pKey = pn->key;
	}
	if (ppData) {
		ppData = pn->pData;
	}

	// Set key to least possible value, percolate up, then deleteMin
	pn->key = INT_MIN;
	percolateUp(getPos(pn));
	deleteMin();

	return 0;
}

void heap::percolateUp(int posCur) {
	node tmp = data[posCur];
	for (; posCur > 1 && tmp.key < data[posCur / 2].key; posCur /= 2) {
		data[posCur] = data[posCur / 2];
		mapping->setPointer(data[posCur].id, &data[posCur]);
	}
	data[posCur] = tmp;
	mapping->setPointer(data[posCur].id, &data[posCur]);
}

void heap::percolateDown(int posCur) {
	int child;
	node tmp = data[posCur];
	for (; posCur * 2 <= size; posCur = child) {
		child = posCur * 2;
		if (child != size && data[child + 1].key < data[child].key) {
			++child;
		}
		if (data[child].key < tmp.key) {
			data[posCur] = data[child];
			mapping->setPointer(data[posCur].id, &data[posCur]);
		} else {
			break;
		}
	}
	data[posCur] = tmp;
	mapping->setPointer(data[posCur].id, &data[posCur]);
}

int heap::getPos(node * pn) {
	int pos = pn - &data[0];
	return pos;
}

heap::node::node(const std::string &i, int k, void * pv) {
	id = i;
	key = k;
	pData = pv;
}