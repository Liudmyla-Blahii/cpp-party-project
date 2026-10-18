#pragma once

#include "types.h"

bool levelUp(PartyList& party, const char* searchName);
bool equipWeapon(PartyList& party, const char* searchName, Item newWeapon);
bool damageHero(PartyList& party, const char* searchName, int amount);
bool healHero(PartyList& party, const char* searchName, int amount);
bool saveParty(const PartyList& party, const char* filename);
bool loadParty(PartyList& party, const char* filename);