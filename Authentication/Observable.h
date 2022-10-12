#pragma once

#include "HeapManager.h"
#include "Observer.h"

struct ObserverNode {
    ObserverNode(Observer* observer) :
        ptr(observer), next(nullptr) {}

    Observer* ptr;
    ObserverNode* next;
};

class Observable
{
public:
    Observable(HeapManager* heapManagerObj);
    virtual ~Observable();

    void addObserver(Observer* observer);
    void notifyUpdate();
protected:
    HeapManager* heapManager;
private:
    // simple and ineffective way to store observers - but easy to control memory
    ObserverNode* observersHead;
};