#pragma once
#include "Offer.h"
#include "OfferRepo.h"
#include "OperationsStack.h"


typedef struct
{
	OfferRepo* repo;
	OperationsStack* undoStack;

	OperationsStack* redoStack;
}Controller;

typedef void(*operation)(DynamicArray*, Controller*, double, int);

Controller* createController(OfferRepo* repo, OperationsStack* s, OperationsStack* r);

// deallocates the allocated memory
void destroyController(Controller* c);
int addOfferCtrl(Controller* ctrl, char type[], char address[], double surface, int price);

OfferRepo* getRepo(Controller* ctrl);

int getLengthC(Controller* ctrl);
int removeOfferController(Controller* ctrl, char address[]);
int updateOfferController(Controller* ctrl, char type[], char address[], double surface, int price);

void containsString(DynamicArray* res, Controller* controller, char string[]);
void sortByPrice(DynamicArray* res);
void sortByPriceDescending(DynamicArray* res);
void OffersOfTypeAndSurface(DynamicArray* res, Controller* ctrl, char type[], double surface);

typedef OfferRepo(*operation1)(DynamicArray*);
void OffersOfPriceAndSurface(DynamicArray* res, Controller* ctrl, double surface, int price);
int undo(Controller* c);
int redo(Controller* c);
void testController();
