// Lab34Ver2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "OperationsStack.h"
#include <stdio.h>
#include "Offer.h"
#include "OfferRepo.h"
#include "Controller.h"
#include <crtdbg.h>
#include "UI.h"
int main()
{
	OfferRepo* repo = createRepo();
	if (repo == NULL)
	{
		printf("Repository could not be created! Memory error.");
		return 1;
	}

	OperationsStack undoStack = createStack();

	OperationsStack redoStack = createStack();
	Controller* ctrl = createController(repo,&undoStack,&redoStack);
	if (ctrl == NULL)
	{
		printf("Controller could not be created! Memory error.");
		return 1;
	}
	addOfferCtrl(ctrl, "house", "independentei,Nr.99", 12, 13);
	addOfferCtrl(ctrl, "house", "independentei,Nr.99A", 121, 13);
	addOfferCtrl(ctrl, "house", "independentei,Nr.99B", 12, 130);
	addOfferCtrl(ctrl, "penthouse", "independentei,Nr.999", 12, 13);
	addOfferCtrl(ctrl, "apartment", "independentei,Nr.999A", 1212, 131);
	addOfferCtrl(ctrl, "apartment", "independentei,Nr.999B", 12111, 1305);
	addOfferCtrl(ctrl, "apartment", "romania", 12111, 1305);
	addOfferCtrl(ctrl, "apartment", "romania2", 12111, 1305);
	clearStack(ctrl->undoStack);
	testOffer();
	testRepo();

	UI* ui = createUI(ctrl);
	if (ui == NULL)
	{
		printf("UI could not be created! Memory error.");
		return 1;
	}
	testsDynamicArray();
	testController();
	startUI(ui);


	// we must deallocate all the allocated resources
	destroyUI(ui);
	destroyController(ctrl);
	destroyRepo(repo);

	_CrtDumpMemoryLeaks();
	return 0;
}

