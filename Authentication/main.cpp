#include <iostream>
#include <new>

#include "AuthController.h"
#include "AuthModel.h"
#include "AuthView.h"
#include "HeapManager.h"

int main()
{
	HeapManager* heapManager;
	try {
		heapManager = HeapManager::getHeapManager();
	}
	catch ( std::bad_alloc &e ) {
		std::cout << "Can't allocate memory for heap manager!" << std::endl;
		std::cout << e.what() << std::endl;
		return 1;
	}

	AuthModel* authModel = heapManager->createObject<AuthModel>(heapManager);
	AuthView* authView = heapManager->createObject<AuthView>(authModel);
	AuthController* authController = heapManager->createObject<AuthController>(authModel, authView);

	authController->start();

	return 0;
}
