#pragma once

#include "types.h"

void recruitHero(PartyList& party, Character newHero);
int findHeroIndex(const PartyList& party, const char* searchName);
Character getHeroByName(const PartyList& party, const char* searchName);
void printHero(const Character& hero);
void printParty(const PartyList& party);

// ЕТАП 3: DELETE + аналітика
bool dismissHero(PartyList& party, const char* searchName);
int totalPartyPower(const PartyList& party);
int findStrongestHeroIndex(const PartyList& party);
void sortByLevelDescending(PartyList& party);
