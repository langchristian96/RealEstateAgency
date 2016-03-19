#pragma once
#pragma once
typedef struct
{
	char type[20];
	char address[50];
	double surface;
	int price;


}Offer;

Offer createOffer(char type[], char address[], double surface, int price);

char* getType(Offer* f);
char* getAddress(Offer* f);
double getSurface(Offer* f);
int getPrice(Offer* f);
void toString(Offer f, char str[]);
void testOffer();