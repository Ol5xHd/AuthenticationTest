#pragma once

#include <new>
#include <utility>

// a node of available memory
struct MemoryNode {
	size_t size; // total size of a node
	MemoryNode* next; // next node
};

// custom memory manager for heap control;
// the idea is to store list of MemoryNodes, each pointing to a block of free memory;
// every MemoryNode object is existing in the very beginning of its memory block;
// when it's need to create object in heap memory it will be created in the beginning of memory block big enough,
//     and corresponding MemoryNode object will be moved by the size of created object;
// MemoryNode object may be just discarded if its size is equal to the size of requested memory;
// can't create objects with size less then sizeof(MemoryNode) - to control such a small memory blocks
//     additional data structure/algorithm is required
// main methods are createObject and deleteObject
class HeapManager {
public:
	static constexpr long DEFAULT_BUFFER_SIZE = 500 * 1024;

	HeapManager(const HeapManager& heapManager) = delete;
	HeapManager& operator=(const HeapManager& heapManager) = delete; // non-copyable
	HeapManager(HeapManager&& heapManager) noexcept;
	HeapManager& operator=(HeapManager&& heapManager) noexcept; // movable, but what for?
	~HeapManager();

	// get an instance of the class
	static HeapManager* getHeapManager();

	// print short info (total, used and free memory)
	void printInfo() const;
	// print detailed info (addresses of memory nodes and their sizes)
	void printInfoDetailed() const;
	
	// create any object in allocated buffer
	template<typename T, typename... Args>
	T* createObject(Args&&... args) {
		// need to limit possible minimum size for allocation to avoid problems of freeing memory afterwards
		size_t memoryNodeSize = sizeof(MemoryNode);
		size_t& minimumSize = memoryNodeSize;
		size_t requestedSize = sizeof(T);
		if (requestedSize < minimumSize) {
			requestedSize = minimumSize;
		}
		
		// finding a free memory node node big enough
		MemoryNode* prev = nullptr;
		MemoryNode* current = root;
		while (current) {
			void* placementAddress = &(*current);
			if (current->size >= requestedSize + memoryNodeSize) {
				// possible to create both requested object and new MemoryNode object inside this node
				void* newNodeAddress = (void*)((char*)placementAddress + requestedSize);
				MemoryNode* newNode = new(newNodeAddress) MemoryNode{ current->size - requestedSize, current->next };
				if (prev) {
					prev->next = newNode;
				}
				else {
					root = newNode;
				}

				T* obj = new(placementAddress) T(std::forward<Args>(args)...);
				
				// try to merge new node with next if they are ajacent
				if (newNode->next) {
					if (((char*)&(*newNode) + memoryNodeSize) == (char*)&(*(newNode->next))) {
						newNode->size += newNode->next->size + sizeof(MemoryNode);
						newNode->next = newNode->next->next;
					}
				}

				return obj;
			}
			else if (current->size == requestedSize) {
				// possible to create requested object in the place of the current MemoryNode
				if (prev) {
					prev->next = current->next;
				}
				else {
					// possible to use the last node here - root will be nullptr, but it's ok
					root = root->next;
				}
				T* obj = new(placementAddress) T(std::forward<Args>(args)...);
				return obj;
			}

			prev = current;
			current = current->next;
		}

		throw std::bad_alloc();
	}

	// delete created object and free ussed memory
	template<typename T>
	void deleteObject(T* ptr) {
		size_t freedSize = sizeof(T);
		size_t minimumSize = sizeof(MemoryNode);
		if (freedSize < minimumSize) {
			freedSize = minimumSize;
		}

		if (!root || (char*)ptr < (char*)&(*root)) {
			// freed memory is before the current root
			MemoryNode* newRoot = new((void*)ptr) MemoryNode{ freedSize, root };
			root = newRoot;
			return;
		}

		// finding an appropriate position for a new free memory node
		MemoryNode* prev = nullptr;
		MemoryNode* current = root;
		while (current && (char*)&(*current) < (char*)ptr) {
			prev = current;
			current = current->next;
		}
		if (current) {
			// somewhere in the middle
			MemoryNode* newNode = new((void*)ptr) MemoryNode{ freedSize, current };
			prev->next = newNode; // prev won't be nullptr here - see above
		}
		else {
			// new node will be the last
			MemoryNode* newNode = new((void*)ptr) MemoryNode{ freedSize, nullptr };
			prev->next = newNode;
		}
	}
protected:
	// protected constructor to cprevent creating multiple instances of the class
	HeapManager();
private:
	static size_t bufferSize; // total allocated buffer size
	static void* bufferPtr; // pointer to buffer
	static MemoryNode* root; // root node of free memory list
	static HeapManager* heapManagerObj; // common instance of the class
};
