#include "OperationsStack.h"
#include <string.h>
#include <assert.h>
//OperationsStack used for undo Stack and redo Stack
Operation createOperation(Offer f, char operationType[])
{
	Operation o;
	o.offer = f;
	strcpy(o.operationType, operationType);

	return o;
}

char* getOperationType(Operation* o)
{
	return o->operationType;
}

Offer getOffer(Operation* o)
{
	return o->offer;
}

// ---------------------------------------------------------------
void clearStack(OperationsStack* s)
{
	s->length = 0;
}

OperationsStack createStack()
{
	OperationsStack s;
	s.length = 0;

	return s;
}

void push(OperationsStack* s, Operation o)
{
	if (isFull(s))
		return;

	s->operations[s->length] = o;
	s->length++;
}

Operation pop(OperationsStack* s)
{
	Operation o = createOperation(createOffer("", "", -1, -1), "");
	if (isEmpty(s)) {
		return o;
	}
	s->length--;
	return s->operations[s->length];
}

int isEmpty(OperationsStack* s)
{
	return (s->length == 0);
}

int isFull(OperationsStack* s)
{
	return s->length == 100;
}


// Tests
void testsStack()
{
	OperationsStack s = createStack();

	Offer f1 = createOffer("house","indepp",12,13);
	Offer f2 = createOffer("house", "indeppp", 12, 13);
	Operation o1 = createOperation(f1, "add");
	Operation o2 = createOperation(f2, "add");
	Operation o3 = createOperation(f1, "remove");

	push(&s, o1);
	push(&s, o2);
	push(&s, o3);

	assert(isFull(&s) == 0);
	assert(isEmpty(&s) == 0);
	assert(strcmp(pop(&s).operationType, "remove") == 0);
	assert(strcmp(pop(&s).operationType, "add") == 0);
	assert(strcmp(pop(&s).operationType, "add") == 0);
	assert(isEmpty(&s) == 1);
}