#include "Offer.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

Offer createOffer(char type[], char address[], double surface, int price)
{
	//Creates an instance of Offer
	Offer s;
	strcpy(s.type, type);
	strcpy(s.address, address);
	s.surface = surface;
	s.price = price;

	return s;


}



char* getType(Offer* f)
{
	//Getter for type

	return f->type;//equivalent to return (*f).type;
}


char* getAddress(Offer* f)
{
	//Getter for address
	return f->address;
}
double getSurface(Offer* f)
{
	//Getter for surface
	return f->surface;
}
int getPrice(Offer* f)
{
	//Getter for surface
	return f->price;
}

void toString(Offer f, char str[])
{
	//Puts the string in str
	sprintf(str, "type %19s,\n address %49s,\n surface %lf,\n price %d \n", f.type, f.address, f.surface, f.price);


}

void testOffer()
{
	//Tester for Offer
	char type[] = "house", address[] = "test";
	int price = 10;
	double surface = 11;
	Offer f = createOffer(type, address, surface, price);
	assert(strcmp(getType(&f), "house") == 0);
	assert(strcmp(getAddress(&f), "test") == 0);
	assert(getPrice(&f) == 10);
	assert(getSurface(&f) == 11);
}