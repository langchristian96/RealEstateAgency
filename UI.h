#pragma once
#include "Offer.h"
#include "DynamicArray.h"
#include "OfferRepo.h"
#include "Controller.h"

typedef struct
{
	Controller* ctrl;
}UI;

UI* createUI(Controller* ctrl);
void destroyUI(UI* ui);
int addOfferUI(UI* ui);
void printMenu();
void getAllUI(UI* ui);
void startUI(UI* ui);

int removeOfferUI(UI* ui);
