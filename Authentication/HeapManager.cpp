#include <iostream>
#include <new>
#include "stdlib.h"

#include "HeapManager.h"

size_t HeapManager::bufferSize = 0;
void* HeapManager::bufferPtr = nullptr;
MemoryNode* HeapManager::root = nullptr;
HeapManager* HeapManager::heapManagerObj = nullptr;

HeapManager::HeapManager() {
	bufferSize = DEFAULT_BUFFER_SIZE;
	bufferPtr = malloc(bufferSize);

	if (bufferPtr == nullptr) {
		throw std::bad_alloc();
	}

	root = new(bufferPtr) MemoryNode{ bufferSize, nullptr };
}

HeapManager::~HeapManager() {
	free(bufferPtr);
}

HeapManager::HeapManager(HeapManager&& heapManager) noexcept {}

HeapManager& HeapManager::operator=(HeapManager&& heapManager) noexcept {
	return *this;
}

HeapManager* HeapManager::getHeapManager() {
	if (heapManagerObj) {
		return heapManagerObj;
	}

	heapManagerObj = new HeapManager();
	return heapManagerObj;
}

void HeapManager::printInfo() const {
	size_t memoryFree = 0;
	size_t maxNodeSize = 0;
	MemoryNode* current = root;
	while (current) {
		memoryFree += current->size;
		if (current->size > maxNodeSize) {
			maxNodeSize = current->size;
		}
		current = current->next;
	}

	std::cout << "Memory total: \t" << bufferSize << std::endl;
	std::cout << "Memory free: \t" << memoryFree << std::endl;
	std::cout << "Memory used: \t" << bufferSize - memoryFree << std::endl;
	// simple custom metric - ratio of the biggest node to the total buffer
	std::cout << "Fragmentation degree: " << (1 - (maxNodeSize / (double)bufferSize)) * 100 << "%" << std::endl;
}

void HeapManager::printInfoDetailed() const {
	std::cout << "Memory buffer starts at: \t" << bufferPtr << std::endl;
	std::cout << "Memory total size: \t\t" << bufferSize << std::endl;
	std::cout << "Free blocks:" << std::endl;

	MemoryNode* current = root;
	while (current) {
		std::cout << "address: " << & (*current) << "\t" << "size: " << current->size << std::endl;
		current = current->next;
	}
}
