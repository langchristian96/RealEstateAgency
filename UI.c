#include "Controller.h"
#include "Offer.h"
#include "OfferRepo.h"
#include "UI.h"
#include <stdio.h>
#include "DynamicArray.h"

UI* createUI(Controller* ctrl)
{
	UI* ui = malloc(sizeof(UI));
	if (ui == NULL)
		return NULL;

	ui->ctrl = ctrl;
	return ui;


}


void destroyUI(UI* ui)
{
	if (ui == NULL)
		return;

	free(ui);
	ui = NULL;
}

int updateOfferUI(UI* ui)
{

	char type[20], address[50], oldAddress[50];
	double surface;
	int price;
	printf("Insert new type\n");
	scanf("%19s", type);
	printf("Insert address(without white spaces)\n");
	scanf("%49s", address);
	printf("Insert new surface\n");
	scanf("%lf", &surface);
	printf("Insert new price\n");
	scanf("%d", &price);

	return updateOfferController(ui->ctrl, type, address, surface, price);
}

int addOfferUI(UI* ui)
{
	char type[20], address[50];
	double surface;
	int price;
	printf("Insert type\n");
	scanf("%19s", type);
	if (strcmp(type, "house") != 0 && strcmp(type, "apartment") != 0 && strcmp(type, "penthouse") != 0)
	{
		printf("Type must be house, apartment or penthouse.\n");
		return -2;
	}
	printf("Insert address(without white spaces)\n");
	scanf("%49s", address);
	printf("Insert surface\n");
	scanf("%lf", &surface);
	printf("Insert price\n");
	scanf("%d", &price);

	return addOfferCtrl(ui->ctrl, type, address, surface, price);
}
void printMenu()
{
	printf("1 Add offer\n");
	printf("2 Get all offers\n");
	printf("3 Remove an offer\n");
	printf("4 Update an offer\n");
	printf("5 Show offers with a given substring as address(ordered by price)\n");
	printf("6 Show all offers  of a given type, having the surface greater than a given value\n");
	printf("7 Filter offers with price less than a given one and bigger surface than a given one \n");
	printf("8 Undo\n");
	printf("9 Redo\n");
	printf("0 Exit\n");

}

int validCommand(int command)
{
	if (command >= 0 && command <= 6)
		return 1;
	return 0;
}


void getAllUI(UI* ui)
{
	printf("\n\n");
	OfferRepo* repo = getRepo(ui->ctrl);

	int i = getLength(repo->offersDynArr);


	for (int j = 0; j < i; j++)
	{
		char str[200];
		toString(getOfferOnPos(repo, j), str);
		printf("%s\n", str);


	}
}
void TypeAndSurface(UI* ui)
{

	// create a dynamic array
	DynamicArray* res = createDynamicArray(5);
	char type[20];
	double surface;
	printf("Input type \n");
	scanf("%20s", type);
	printf("Input surface \n");
	scanf("%lf", &surface);
	OffersOfTypeAndSurface(res, ui->ctrl, type, surface);
	int length = getLength(res);
	if (length == 0)
	{
		printf("No offers with the given substring as address \n");
	}
	else
	{
		for (int i = 0; i < length; i++)
		{
			char str[200];
			toString(get(res, i), str);
			printf("%s\n", str);
		}
	}

}

void priceAndSurface(UI* ui)
{


	// create a dynamic array
	DynamicArray* res = createDynamicArray(5);
	operation o;
	o = &OffersOfPriceAndSurface;
	int price;
	double surface;
	printf("Input price\n");
	scanf("%d", &price);
	printf("Input surface\n");
	scanf("%lf", &surface);
	o(res, ui->ctrl, surface, price);
	int length = getLength(res);
	if (length == 0)
	{
		printf("No offers with the given specifications \n");
	}
	else
	{
		for (int i = 0; i < length; i++)
		{
			char str[200];
			toString(get(res, i), str);
			printf("%s\n", str);
		}
	}

}
void containsStringUI(UI* ui)
{


	// create a dynamic array
	DynamicArray* res = createDynamicArray(5);
	char addr[50];
	printf("Input substring \n");

	scanf("%49s", addr);
	operation1 o;
	printf("Press 1 for ascending sorting or 2 for descending\n");
	int command;
	scanf("%d", &command);
	if (command == 1)
		o = &sortByPrice;
	else if (command == 2)
		o = &sortByPriceDescending;
	else
	{
		printf("Something went wrong \n");
		return 0;
	}
	containsString(res, ui->ctrl, addr);
	o(res);
	int length = getLength(res);
	if (length == 0)
	{
		printf("No offers with the given substring as address \n");
	}
	else
	{
		for (int i = 0; i < length; i++)
		{
			char str[200];
			toString(get(res, i), str);
			printf("%s\n", str);
		}
	}
}

int removeOfferUI(UI* ui)
{
	char address[50];
	printf("Input address \n");
	scanf("%49s", address);

	printf("Are you sure you want to remove the offer (1 - yes, 0 - no)? \n");

	int r = 0;
	scanf("%d", &r);
	if (r == 0)
		return -1;
	return removeOfferController(ui->ctrl, address);



}

void startUI(UI* ui)
{
	while (1)
	{
		printMenu();
		printf("Input command\n");
		int command;
		scanf("%d", &command);
		if (command == 0)
			break;
		switch (command)
		{
		case 1:
		{

			int res = addOfferUI(ui);
			if (res == 1)
				printf("Offer succesfully added\n");
			else
				printf("Error\n");
		}break;
		case 2:
		{
			printf("\n");
			getAllUI(ui);
		}break;
		case 3:
		{
			int res = removeOfferUI(ui);
			if (res == 1)
				printf("Offer succesfully removed. \n");

			else if (res == 0)
				printf("Offer does not exist.\n");
		}break;
		case 4:
		{
			int res = updateOfferUI(ui);
			if (res == 1)
				printf("Offer succesfully updated. \n");
			else if (res == 0)
				printf("Offer does not exist. \n");
		}break;
		case 5:
		{
			containsStringUI(ui);

		}break;
		case 6:
		{
			TypeAndSurface(ui);
		}break;
		case 7:
		{
			priceAndSurface(ui);
		}break;
		case 8:
		{
			int rez = undo(ui->ctrl);

			if (rez == 0)
				printf("Undo cannot be done.\n");
			else
				printf("Done.\n");
			
		}break;
		case 9:
		{
			int rez = redo(ui->ctrl);
			if (rez == 0)
				printf("Redo cannot be done.\n");
			else
				printf("Done.\n");
			
		}break;
		default:
		{printf("Wrong input\n"); }break;
		}

	}

}