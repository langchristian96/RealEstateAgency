#include "DynamicArray.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

DynamicArray* createDynamicArray(int capacity)
{
	DynamicArray* da = (DynamicArray*)malloc(sizeof(DynamicArray));
	if (da == NULL)
		return NULL;
	da->capacity = capacity;
	da->length = 0;
	da->offers = (TElement*)malloc(capacity*sizeof(TElement));
	if (da->offers == NULL)
		return NULL;
	return da;
}

void update(DynamicArray* arr, TElement t, int pos)
{
	arr->offers[pos] = t;


}

void destroy(DynamicArray* da)
{
	if (da == NULL)
		return;
	free(da->offers);
	da->offers = NULL;
	free(da);
	da = NULL;
}

void delete(DynamicArray* arr, int pos)
{
	for (int i = pos; i < arr->length - 1; i++)
		arr->offers[i] = arr->offers[i + 1];


	arr->length -= 1;
}

void resize(DynamicArray* da)
{
	if (da == NULL)
		return;
	da->capacity *= 2;
	da->offers = (TElement*)realloc(da->offers, da->capacity*sizeof(TElement));



}


void add(DynamicArray* da, TElement t)
{
	if (da == NULL)
		return;
	if (da->offers == NULL)
		return;
	if (da->length >= da->capacity)
		resize(da);

	da->offers[da->length] = t;
	da->length += 1;

}


int getLength(DynamicArray* arr)
{
	if (arr == NULL)
		return -1;

	return arr->length;
}

TElement get(DynamicArray* arr, int pos)
{
	return arr->offers[pos];
}


void swapElementsOnPositions(DynamicArray* arr, int i, int j)
{
	if (arr == NULL)
		return;
	if (arr->offers == NULL)
		return;

	TElement aux = arr->offers[i];
	arr->offers[i] = arr->offers[j];
	arr->offers[j] = aux;
}


// ------------------------------------------------------------------------------------------------------------
// Tests

void testsDynamicArray()
{
	DynamicArray* da = createDynamicArray(2);
	if (da == NULL)
		assert(0);

	assert(da->capacity == 2);
	assert(da->length == 0);

	Offer p1 = createOffer("house", "BldRepubliciinr99B", 12, 14);
	add(da, p1);
	assert(da->length == 1);




	destroy(da);
}