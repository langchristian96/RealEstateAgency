#pragma once

#include "Offer.h"
#include <string.h>

//OperationsStack used for undo Stack and redo Stack
typedef struct
{
	Offer offer;
	char operationType[30];
} Operation;

char* getOperationType(Operation* o);

Offer getOffer(Operation* o);


Operation createOperation(Offer f, char operationType[]);

typedef struct
{
	Operation operations[100];
	int length;
} OperationsStack;

OperationsStack createStack();
void push(OperationsStack* s, Operation o);
Operation pop(OperationsStack* s);
int isEmpty(OperationsStack* s);
int isFull(OperationsStack* s);
void clearStack(OperationsStack* s);
void testsStack();