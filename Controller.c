#include "Controller.h"
#include "OfferRepo.h"
#include "Offer.h"
#include <string.h>
#include <assert.h>
#include "DynamicArray.h"
#include "OperationsStack.h"

Controller* createController(OfferRepo* repo,OperationsStack* s,OperationsStack* r)
{
	//Creates an instance of Controller
	Controller* c = malloc(sizeof(Controller));
	if (c == NULL)
		return NULL;
	c->repo = repo;
	c->undoStack = s;
	c->redoStack = r;

	return c;

}


void destroyController(Controller* c)
{
	//destroyer
	if (c == NULL)
		return;
	free(c);
	c = NULL;
}

int addOfferCtrl(Controller* ctrl, char type[], char address[], double surface, int price)
{
	//The function adds an Offer to the controller
	//Input: ctrl of type Controller*, type - char array, address - char array, surface-double,price-int
	//Output: 1 if added sucesfully, 0 otherwise
	Offer f = createOffer(type, address, surface, price);
	int res = addOffer(ctrl->repo, f);
	if (res == 1)
	{
		
		Operation o = createOperation(f, "add");
		push(ctrl->undoStack, o);
		clearStack(ctrl->redoStack);
	}
	return res;

}

int getLengthC(Controller* ctrl)
{
	//Gets the length of the repository linked to the controller
	return getLengthRepo(ctrl->repo);

}
OfferRepo* getRepo(Controller* ctrl)
{
	//The functions returns the repository linked to the controller
	return ctrl->repo;

}

void containsString(DynamicArray* arr, Controller* controller, char string[])
{
	//The function returns a repository that contains all the Offers that contain a given substring
	//Input: controller of type Controller*, string-char array
	//Output: object of type OfferRepo that contains the specified Offers
	OfferRepo* repo = createRepo();
	int repoLength = getLengthRepo(controller->repo);
	for (int i = 0; i < repoLength; i++)
	{
		Offer f = getOfferOnPos(controller->repo, i);
		if (strstr(getAddress(&f), string) != 0)
			add(arr, f);



	}

}
void sortByPrice(DynamicArray* arr)
{
	//The functions sorts all the offers from a repository by price in ascending order
	//Input: repo of type OfferRepo
	//Output: the sorted repository

	int inter = 1;
	while (inter)
	{
		inter = 0;
		for (int i = 0; i<getLength(arr) - 1; i++)
		{
			Offer aux, f1, f2;
			f1 = get(arr, i);
			f2 = get(arr, i + 1);
			if (getPrice(&f1) > getPrice(&f2))
			{
				swapElementsOnPositions(arr, i, i + 1);
				inter = 1;
			}
		}
	}

}

void OffersOfTypeAndSurface(DynamicArray* arr, Controller* ctrl, char type[], double surface)
{
	//The functions makes a repo of type OfferRepo and stores all the Offers of a given type and with a surface bigger than a given one
	//Input:arr of type DynamicArray*, ctrl of type Controller*, type- char array, surface-double
	//Output: repository containing the specified Offers
	if (ctrl == NULL)
		return;
	int repolength = getLengthRepo(ctrl->repo);
	for (int i = 0; i < repolength; i++)
	{
		Offer f = getOfferOnPos(ctrl->repo, i);
		if (strcmp(type, getType(&f)) == 0 && surface<getSurface(&f))
			add(arr, f);
	}

}

void OffersOfPriceAndSurface(DynamicArray* arr, Controller* ctrl, double surface, int price)
{
	//The function creates a repository and stores all the offers with the surface bigger than a given one
	//and the price less than a given one
	//Input:arr of type DynamicArray*, ctrl of type Controller*, surface-double,price-int
	//Output: repostory with the specified Offers
	if (ctrl == NULL)
		return NULL;
	int repolength = getLengthRepo(ctrl->repo);
	for (int i = 0; i < repolength; i++)
	{

		Offer f = getOfferOnPos(ctrl->repo, i);
		if (getPrice(&f) < price&& getSurface(&f) >= surface)
			add(arr, f);
	}

}
int updateOfferController(Controller* ctrl, char type[], char address[], double surface, int price)
{
	//The function updates an Offer
	//Input: ctrl of type Controller, oldAddress- char array,address-char array,surface-double,price-int
	//Output:integer - 0 if the offer does not exist, 1 if succesful
	Offer f = createOffer(type, address, surface, price);
	Offer f2;
	
	int pos = find(ctrl->repo, address);
	if (pos != -1)
		f2 = getOfferOnPos(ctrl->repo, pos);
	int res = updateOffer(ctrl->repo, f);

	if (res == 1)
	{
		Operation o = createOperation(f2, "update");
		push(ctrl->undoStack, o);
		clearStack(ctrl->redoStack);
	}
	return res;

}
int removeOfferController(Controller* ctrl, char address[])
{
	//The function removes an offer if it exists
	//Input: ctrl of type Controller*, address - char array
	//Output:integer - 1 if succesful, 0 otherwise

	Offer f = createOffer("", "", -1, -1);
	int pos = find(ctrl->repo, address);
	if (pos != -1)
		f = getOfferOnPos(ctrl->repo, pos);
	int res = deleteOffer(ctrl->repo, address);
	if (res == 1)
	{
		Operation o = createOperation(f, "remove");
		push(ctrl->undoStack, o);
		clearStack(ctrl->redoStack);
	}
	return res;
}
void sortByPriceDescending(DynamicArray* arr)
{
	//The functions sorts all the offers from a repository by price in descending order
	//Input: arr of type DynamicArray*
	//Output: the sorted repository

	int inter = 1;
	while (inter)
	{
		inter = 0;
		for (int i = 0; i<getLength(arr) - 1; i++)

		{
			Offer aux, f1, f2;
			f1 = get(arr, i);
			f2 = get(arr, i + 1);
			if (getPrice(&f1) < getPrice(&f2))
			{
				swapElementsOnPositions(arr, i, i + 1);
				inter = 1;
			}
		}
	}

}


int undo(Controller* c)
//Function for undo
{
	if (isEmpty(c->undoStack)) {

		return 0;
	}
	Operation o = pop(c->undoStack);

	if (strcmp(getOperationType(&o), "add") == 0)
	{
		Offer p = getOffer(&o);

		Operation oo = createOperation(p, "remove");
		push(c->redoStack, oo);
		char address[50];
		strcpy(address, getAddress(&p));
		deleteOffer(c->repo, address);
	}

	if (strcmp(getOperationType(&o), "update") == 0)
	{
		Offer p = getOffer(&o);
		Offer f2;
		int pos = find(c->repo, getAddress(&p));
		if (pos != -1)
			f2 = getOfferOnPos(c->repo, pos);

		Operation oo = createOperation(f2, "update");

		push(c->redoStack, oo);
		char address[50];
		strcpy(address, getAddress(&p));
		updateOffer(c->repo, p);
	}
	if (strcmp(getOperationType(&o), "remove") == 0)
	{
		Offer p = getOffer(&o);

		Operation oo = createOperation(p, "add");
		push(c->redoStack, oo);
		return addOffer(c->repo, p);
	}

	return 1;

}


int redo(Controller* c)
//Function for redo
{
	if (isEmpty(c->redoStack)) {

		return 0;
	}
	Operation o = pop(c->redoStack);

	if (strcmp(getOperationType(&o), "add") == 0)
	{
		Offer p = getOffer(&o);

		Operation oo = createOperation(p, "remove");
		push(c->undoStack, oo);

		char address[50];
		strcpy(address, getAddress(&p));
		deleteOffer(c->repo, address);
	}

	if (strcmp(getOperationType(&o), "update") == 0)
	{
		Offer p = getOffer(&o);

		Offer f2;

		int pos = find(c->repo, getAddress(&p));
		if (pos != -1)
			f2 = getOfferOnPos(c->repo, pos);

		Operation oo = createOperation(f2, "update");
		push(c->undoStack, oo);
		char address[50];
		strcpy(address, getAddress(&p));
		updateOffer(c->repo, p);
	}
	if (strcmp(getOperationType(&o), "remove") == 0)
	{
		Offer p = getOffer(&o);

		Operation oo = createOperation(p, "add");
		push(c->undoStack, oo);
		return addOffer(c->repo, p);
	}

	return 1;

}

void testController()
{
	//Tester for Controller
	OfferRepo* repo = createRepo();

	OperationsStack undoStack = createStack();

	OperationsStack redoStack = createStack();
	Controller* ctrl = createController(repo,&undoStack,&redoStack);
	assert(getLengthC(ctrl) == 0);
	addOfferCtrl(ctrl, "house", "independenteiNr99", 12, 13);
	assert(getLengthC(ctrl) == 1);
	addOfferCtrl(ctrl, "house", "independenteiNr99A", 121, 13);
	addOfferCtrl(ctrl, "house", "independenteiNr99B", 12, 130);
	addOfferCtrl(ctrl, "penthouse", "independenteiNr99C", 122, 134);
	addOfferCtrl(ctrl, "penthouse", "independenteiNr99D", 129, 135);
	addOfferCtrl(ctrl, "apartment", "independenteiNr99E", 128, 13);
	int res;
	assert(getLengthC(ctrl) == 6);
	res = removeOfferController(ctrl, "independenteiNr99");
	assert(res == 1);
	assert(getLengthC(ctrl) == 5);
	destroyRepo(repo);
	destroyController(ctrl);

}