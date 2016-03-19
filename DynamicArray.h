#pragma once

#include "Offer.h"
typedef Offer TElement;
typedef struct
{
	TElement* offers;
	int length;
	int capacity;
}DynamicArray;
/// <summary>
/// Creates a dynamic array of offers, with a given capacity.
/// </summary>
/// <param name="capacity">Integer, maximum capacity for the dynamic array.</param>
/// <returns>A pointer the the created dynamic array.</returns>

DynamicArray* createDynamicArray(int capacity);


/// <summary>
/// Destroys the dynamic array.
/// </summary>
/// <param name="arr">The dynamic array to be destoyed.</param>
/// <returns>A pointer the the created dynamic array.</returns>
void destroy(DynamicArray* arr);


/// <summary>
/// Adds an offer to the dynamic array.
/// </summary>
/// <param name="arr">The dynamic array.</param>
/// <param name="p">The planet to be added.</param>
void add(DynamicArray* arr, TElement t);

void update(DynamicArray* arr, TElement t, int pos);
void delete(DynamicArray* arr, int pos);

/// <summary>
/// Returns the length of the dynamic array.
/// </summary>
/// <param name="arr">The dynamic array.</param>
int getLength(DynamicArray* arr);

/// <summary>
/// Returns the element on a given position.
/// </summary>
/// <param name="arr">The dynamic array.</param>
/// <param name="pos">The position - must be a valid position.</param>
/// <returns>The element on the given position.</returns>
TElement get(DynamicArray* arr, int pos);


/// <summary>
/// Swaps the elements on the given positions.
/// </summary>
/// <param name="arr">The dynamic array.</param>
/// <param name="i">First position - must be a valid position.</param>
/// <param name="j">Second position - must be a valid position.</param>
void swapElementsOnPositions(DynamicArray* arr, int i, int j);



// Tests
void testsDynamicArray();