#include <iostream>
#include <windows.h>

#include "types.h"
#include "party.h"
#include "combat.h"

using namespace std;

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    PartyList party;

    // =============== ЕТАП 1: CREATE + READ ===============

    Character hero1 =
    {
        "Артур", "Воїн", 5, 80,
        { 20, 10, 5 },
        { "Меч", 15 }
    };

    Character hero2 =
    {
        "Мерлін", "Маг", 7, 60,
        { 5, 8, 25 },
        { "Посох", 20 }
    };

    Character hero3 =
    {
        "Леголас", "Лучник", 4, 70,
        { 10, 22, 8 },
        { "Лук", 12 }
    };

    cout << "========== НАБІР ГЕРОЇВ ==========\n";

    recruitHero(party, hero1);
    recruitHero(party, hero2);
    recruitHero(party, hero3);

    printParty(party);

    cout << "\n========== ПОШУК ГЕРОЯ ==========\n";

    int index = findHeroIndex(party, "Мерлін");

    if (index != -1)
    {
        cout << "Знайдено героя. Індекс: " << index << endl;
        printHero(getHeroByName(party, "Мерлін"));
    }
    else
    {
        cout << "Героя не знайдено!\n";
    }

    // =============== ЕТАП 2: UPDATE ===============

    cout << "\n========== ПІДВИЩЕННЯ РІВНЯ ==========\n";

    if (!levelUp(party, "Артур"))
    {
        cout << "Героя не знайдено!\n";
    }

    cout << "\n========== ЗМІНА ЗБРОЇ ==========\n";

    Item newWeapon = { "Легендарний меч", 50 };

    if (!equipWeapon(party, "Артур", newWeapon))
    {
        cout << "Героя не знайдено!\n";
    }

    cout << "\n========== БІЙ: ЗАВДАННЯ ШКОДИ ==========\n";

    if (!damageHero(party, "Артур", 40))
    {
        cout << "Героя не знайдено або неправильна шкода!\n";
    }

    cout << "\n========== ЛІКУВАННЯ ==========\n";

    if (!healHero(party, "Артур", 25))
    {
        cout << "Героя не знайдено або неправильне лікування!\n";
    }

    cout << "\n========== ОНОВЛЕНИЙ ТАБІР ==========\n";

    printParty(party);
    
    // =============== ЧИТАННЯ ГЕРОЯ ===============

    cout << "\n========== ІНФОРМАЦІЯ ПРО ГЕРОЯ ==========\n";

    Character hero = getHeroByName(party, "Мерлін");

    if (hero.level != -1)
    {
        printHero(hero);
    }
    else
    {
        cout << "Героя не знайдено!\n";
    }

    // =============== ЗАГАЛЬНА СИЛА ТАБОРУ ===============

    cout << "\n========== ЗАГАЛЬНА СИЛА ТАБОРУ ==========\n";

    cout << "Загальна сила: "
        << totalPartyPower(party) << endl;

    // =============== НАЙСИЛЬНІШИЙ ГЕРОЙ ===============

    cout << "\n========== НАЙСИЛЬНІШИЙ ГЕРОЙ ==========\n";

    int strongestIndex = findStrongestHeroIndex(party);

    if (strongestIndex != -1)
    {
        printHero(party.heroes[strongestIndex]);
    }
    else
    {
        cout << "У таборі немає героїв!\n";
    }

    // =============== ВИДАЛЕННЯ ГЕРОЯ ===============

    cout << "\n========== ГЕРОЙ ЗАГИНУВ У БОЮ ==========\n";

    if (!dismissHero(party, "Леголас"))
    {
        cout << "Героя не знайдено!\n";
    }

    // =============== СОРТУВАННЯ ГЕРОЇВ ===============

    cout << "\n========== СОРТУВАННЯ ЗА РІВНЕМ ==========\n";

    sortByLevelDescending(party);

    // =============== ФІНАЛЬНИЙ ТАБІР ===============

    cout << "\n========== ФІНАЛЬНИЙ ТАБІР ==========\n";

    printParty(party);
    // =============== ЗБЕРЕЖЕННЯ У ФАЙЛ ===============

    cout << "\n========== ЗБЕРЕЖЕННЯ ТАБОРУ ==========\n";

    if (saveParty(party, "heroes.dat"))
    {
        cout << "Герої успішно збережені!\n";
    }

    // =============== ОЧИЩЕННЯ ПАМ'ЯТІ ===============

    delete[] party.heroes;
    party.heroes = nullptr;
    party.size = 0;

    cout << "\nПам'ять очищено. Поточний табір порожній.\n";

    // =============== ЗАВАНТАЖЕННЯ З ФАЙЛУ ===============

    cout << "\n========== ЗАВАНТАЖЕННЯ ТАБОРУ ==========\n";

    if (loadParty(party, "heroes.dat"))
    {
        cout << "Герої успішно завантажені!\n";
        printParty(party);
    }

    // Звільнення пам'яті перед завершенням
    delete[] party.heroes;
    party.heroes = nullptr;
    party.size = 0;

    cout << "\nПам'ять звільнено. Програму завершено!\n";
  

}