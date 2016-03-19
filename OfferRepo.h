#pragma once

#include "Offer.h"
#include "DynamicArray.h"

typedef struct
{
	DynamicArray* offersDynArr;



}OfferRepo;

OfferRepo* createRepo();
int addOffer(OfferRepo* repo, Offer of);
int find(OfferRepo* repo, char address[]);
int getLengthRepo(OfferRepo* repo);
int updateOffer(OfferRepo* repo, Offer of);
Offer getOfferOnPos(OfferRepo* repo, int pos);
void destroyRepo(OfferRepo* repo);
int deleteOffer(OfferRepo* repo, char address[]);

void testRepo();