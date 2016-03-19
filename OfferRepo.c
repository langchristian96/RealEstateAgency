#include "Offer.h"
#include "OfferRepo.h"
#include <string.h>
#include <assert.h>
#include <stddef.h>
#include "DynamicArray.h"
#include <stdlib.h>

OfferRepo* createRepo()
{
	//Creates an instance of OfferRepo
	OfferRepo* repo = malloc(sizeof(OfferRepo));
	if (repo == NULL)
		return NULL;
	repo->offersDynArr = createDynamicArray(2);
	return repo;

}

void destroyRepo(OfferRepo* repo)
{
	//destroyer
	if (repo == NULL)
		return;
	destroy(repo->offersDynArr);
	free(repo);
	repo = NULL;
}


int find(OfferRepo* repo, char address[])
{
	//The functions searches an Offer by a given address
	//Input: repo of type OfferRepo, array of type char(address)
	//Output:returns the position if it was found
	//and -1 otherwise

	if (repo == NULL)
		return -1;
	Offer* f = NULL;

	for (int i = 0; i <getLengthRepo(repo); i++)
	{
		if (strcmp(get(repo->offersDynArr, i).address, address) == 0)
			return i;
	}
	return -1;

}

int getLengthRepo(OfferRepo* repo)
{
	//Gets the length of the repo
	if (repo == NULL)
		return 0;
	return getLength(repo->offersDynArr);

}

int addOffer(OfferRepo* repo, Offer of)
{
	//Adds an Offer to the repo
	//Input: repo of type OfferRepo
	//		of of type Offer
	//Output: returns 0 if the address already exists
	//			or 1 otherwise
	if (repo == NULL)
		return -1;
	if (find(repo, of.address) != -1)
		return 0;
	add(repo->offersDynArr, of);
	return 1;

}


Offer getOfferOnPos(OfferRepo* repo, int pos)
{
	//The functions gets the Offer that is located at the position i in the repo
	//Input: repo of type OfferRepo, pos of type integer
	//Output: Offer
	if (repo == NULL || pos < 0 || pos >= getLength(repo->offersDynArr))
		return createOffer("", "", -1, -1);
	return get(repo->offersDynArr, pos);

}
int updateOffer(OfferRepo* repo, Offer of)
{
	//Updates an offer from the repo
	//Input: repo of type OfferRepo*, char array address, of of type Offer
	//Output: returns 0 if the offer does not exist and 1 otherwise
	int pos;
	pos = find(repo, getAddress(&of));
	if (pos == -1)
		return 0;
	update(repo->offersDynArr, of, pos);
	return 1;
}
int deleteOffer(OfferRepo* repo, char address[])
{
	//The function deletes an Offer from the repo
	//Input: repo of type OfferRepo*, char array address
	//Output: 0 if the offer with the given address does not exist and 1 otherwise
	int pos = find(repo, address);

	if (pos == -1)
		return 0;
	delete(repo->offersDynArr, pos);
	return 1;

}


void testRepo()
{
	//Tester for Repository
	OfferRepo* repo = createRepo();
	assert(getLength(repo->offersDynArr) == 0);
	Offer f1 = createOffer("house", "adresatest", 12, 13), f2;
	int res;
	res = addOffer(repo, f1);
	
	assert(find(repo, "adresatest") == 0);
	f2 = getOfferOnPos(repo, 0);
	assert(strcmp(f2.address,f1.address)==0);
	assert(getLength(repo->offersDynArr) == 1);
	assert(res == 1);
	res = deleteOffer(repo, "adresatest");
	assert(getLength(repo->offersDynArr) == 0);
	assert(res == 1);
	assert(find(repo, "test") == -1);
	destroyRepo(repo);
}