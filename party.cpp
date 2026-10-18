#include <iostream>
#include <cstring>
#include "party.h"

using namespace std;

// 1.1. Додавання героя в кінець масиву
void recruitHero(PartyList& party, Character newHero)
{
    Character* newHeroes = new Character[party.size + 1];

    for (int i = 0; i < party.size; i++)
    {
        newHeroes[i] = party.heroes[i];
    }

    newHeroes[party.size] = newHero;

    delete[] party.heroes;

    party.heroes = newHeroes;
    party.size++;

    cout << "Героя " << newHero.name
        << " додано до табору!\n";
}

// 1.2. Пошук індексу героя за іменем
int findHeroIndex(const PartyList& party, const char* searchName)
{
    for (int i = 0; i < party.size; i++)
    {
        if (strcmp(party.heroes[i].name, searchName) == 0)
        {
            return i;
        }
    }

    return -1;
}

// 1.3. Отримання копії героя за іменем
Character getHeroByName(const PartyList& party, const char* searchName)
{
    int index = findHeroIndex(party, searchName);

    if (index == -1)
    {
        Character emptyHero{};
        emptyHero.level = -1;
        return emptyHero;
    }

    return party.heroes[index];
}

// Допоміжна функція: виведення одного героя
void printHero(const Character& hero)
{
    cout << "Ім'я: " << hero.name << endl;
    cout << "Клас: " << hero.classType << endl;
    cout << "Рівень: " << hero.level << endl;
    cout << "HP: " << hero.hp << endl;

    cout << "Сила: " << hero.stats.strength << endl;
    cout << "Спритність: " << hero.stats.agility << endl;
    cout << "Інтелект: " << hero.stats.intelligence << endl;

    cout << "Зброя: " << hero.weapon.name << endl;
    cout << "Сила зброї: " << hero.weapon.power << endl;
}

// 1.4. Виведення всіх героїв табору
void printParty(const PartyList& party)
{
    cout << "\n========== ТАБІР ГЕРОЇВ ==========\n";

    if (party.size == 0)
    {
        cout << "Табір порожній!\n";
        return;
    }

    for (int i = 0; i < party.size; i++)
    {
        cout << "\n--- Герой #" << i + 1 << " ---\n";
        printHero(party.heroes[i]);
    }

    cout << "\n==================================\n";
}

// 3.1. Видалення героя з табору
bool dismissHero(PartyList& party, const char* searchName)
{
    int index = findHeroIndex(party, searchName);

    if (index == -1)
    {
        return false;
    }

    // Особливий випадок: у таборі лише один герой
    if (party.size == 1)
    {
        delete[] party.heroes;
        party.heroes = nullptr;
        party.size = 0;

        cout << "Героя " << searchName
            << " видалено. Табір порожній!\n";

        return true;
    }

    // Виділяємо новий масив на одного героя менше
    Character* newHeroes = new Character[party.size - 1];

    int j = 0;

    for (int i = 0; i < party.size; i++)
    {
        if (i != index)
        {
            newHeroes[j] = party.heroes[i];
            j++;
        }
    }

    delete[] party.heroes;

    party.heroes = newHeroes;
    party.size--;

    cout << "Героя " << searchName
        << " видалено з табору!\n";

    return true;
}


// 3.2. Обчислення загальної сили табору
int totalPartyPower(const PartyList& party)
{
    int totalPower = 0;

    for (int i = 0; i < party.size; i++)
    {
        totalPower += party.heroes[i].level * 10
            + party.heroes[i].weapon.power;
    }

    return totalPower;
}


// 3.3. Пошук індексу найсильнішого героя
int findStrongestHeroIndex(const PartyList& party)
{
    if (party.size == 0)
    {
        return -1;
    }

    int strongestIndex = 0;

    int maxStats =
        party.heroes[0].stats.strength
        + party.heroes[0].stats.agility
        + party.heroes[0].stats.intelligence;

    for (int i = 1; i < party.size; i++)
    {
        int currentStats =
            party.heroes[i].stats.strength
            + party.heroes[i].stats.agility
            + party.heroes[i].stats.intelligence;

        if (currentStats > maxStats)
        {
            maxStats = currentStats;
            strongestIndex = i;
        }
    }

    return strongestIndex;
}


// 3.4. Сортування героїв за спаданням рівня
void sortByLevelDescending(PartyList& party)
{
    for (int i = 0; i < party.size - 1; i++)
    {
        for (int j = 0; j < party.size - i - 1; j++)
        {
            if (party.heroes[j].level
                < party.heroes[j + 1].level)
            {
                Character temp = party.heroes[j];
                party.heroes[j] = party.heroes[j + 1];
                party.heroes[j + 1] = temp;
            }
        }
    }

    cout << "Героїв відсортовано за спаданням рівня!\n";
}