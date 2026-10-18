#include <iostream>
#include "combat.h"
#include "party.h"

using namespace std;

// 2.1. Підвищення рівня героя
bool levelUp(PartyList& party, const char* searchName)
{
    int index = findHeroIndex(party, searchName);

    if (index == -1)
    {
        return false;
    }

    party.heroes[index].level++;
    party.heroes[index].hp += 10;

    cout << searchName << " підвищив рівень до "
        << party.heroes[index].level
        << "! HP: " << party.heroes[index].hp << endl;

    return true;
}

// 2.2. Видача нової зброї
bool equipWeapon(PartyList& party, const char* searchName, Item newWeapon)
{
    int index = findHeroIndex(party, searchName);

    if (index == -1)
    {
        return false;
    }

    party.heroes[index].weapon = newWeapon;

    cout << searchName << " отримав зброю "
        << party.heroes[index].weapon.name
        << " (сила " << party.heroes[index].weapon.power
        << ")!\n";

    return true;
}

// 2.3. Завдання шкоди герою
bool damageHero(PartyList& party, const char* searchName, int amount)
{
    int index = findHeroIndex(party, searchName);

    if (index == -1 || amount < 0)
    {
        return false;
    }

    party.heroes[index].hp -= amount;

    if (party.heroes[index].hp < 0)
    {
        party.heroes[index].hp = 0;
    }

    cout << searchName << " отримав " << amount
        << " од. шкоди. HP: "
        << party.heroes[index].hp << endl;

    return true;
}

// 2.4. Лікування героя
bool healHero(PartyList& party, const char* searchName, int amount)
{
    int index = findHeroIndex(party, searchName);

    if (index == -1 || amount < 0)
    {
        return false;
    }

    party.heroes[index].hp += amount;

    if (party.heroes[index].hp > 100)
    {
        party.heroes[index].hp = 100;
    }

    cout << searchName << " відновив здоров'я. HP: "
        << party.heroes[index].hp << endl;

    return true;
}