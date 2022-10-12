#include "Observable.h"

Observable::Observable(HeapManager* heapManagerObj) :
	heapManager(heapManagerObj), observersHead(nullptr) {}

Observable::~Observable() {
	ObserverNode* current = observersHead;
	while (current) {
		ObserverNode* toDelete = current;
		current = current->next;
		heapManager->deleteObject<ObserverNode>(toDelete);
	}
}

void Observable::addObserver(Observer* observer) {
	ObserverNode* newNode = heapManager->createObject<ObserverNode>(observer);

	if (!observersHead) {
		observersHead = newNode;
		return;
	}

	ObserverNode* current = observersHead;
	while (current->next) {
		current = current->next;
	}
	current->next = newNode;
}

void Observable::notifyUpdate() {
	ObserverNode* current = observersHead;
	while (current) {
		current->ptr->update();
		current = current->next;
	}
}