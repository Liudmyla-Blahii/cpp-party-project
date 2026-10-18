#include "combat.h"
#include <cstdio>

// ЗБЕРЕЖЕННЯ ГЕРОЇВ У ФАЙЛ
bool saveParty(const PartyList& party, const char* filename)
{
    FILE* file = nullptr;

    // Відкриваємо файл для бінарного запису
    if (fopen_s(&file, filename, "wb") != 0 || file == nullptr)
    {
        cout << "Помилка відкриття файлу для запису!\n";
        return false;
    }

    // 1. Записуємо кількість героїв
    bool success =
        fwrite(&party.size, sizeof(int), 1, file) == 1;

    // 2. Записуємо весь масив героїв
    if (success && party.size > 0)
    {
        success =
            fwrite(party.heroes, sizeof(Character),
                party.size, file) ==
            static_cast<size_t>(party.size);
    }

    // Закриваємо файл
    if (fclose(file) != 0)
    {
        success = false;
    }

    if (!success)
    {
        cout << "Помилка запису у файл!\n";
        return false;
    }

    cout << "Табір успішно збережено у "
        << filename << '\n';

    return true;
}


// ЗАВАНТАЖЕННЯ ГЕРОЇВ ІЗ ФАЙЛУ
bool loadParty(PartyList& party, const char* filename)
{
    FILE* file = nullptr;

    // Відкриваємо файл для бінарного читання
    if (fopen_s(&file, filename, "rb") != 0 || file == nullptr)
    {
        cout << "Помилка відкриття файлу для читання!\n";
        return false;
    }

    // 1. Читаємо кількість героїв
    int count = 0;

    if (fread(&count, sizeof(int), 1, file) != 1 ||
        count < 0 || count > 100000)
    {
        fclose(file);
        cout << "Некоректний формат файлу!\n";
        return false;
    }

    // 2. Виділяємо пам'ять для завантажених героїв
    Character* newHeroes = nullptr;

    if (count > 0)
    {
        newHeroes = new Character[count];

        // 3. Читаємо масив героїв
        size_t readCount =
            fread(newHeroes, sizeof(Character), count, file);

        if (readCount != static_cast<size_t>(count))
        {
            delete[] newHeroes;
            fclose(file);

            cout << "Помилка читання героїв!\n";
            return false;
        }
    }

    fclose(file);

    // 4. Замінюємо старий табір завантаженими даними
    delete[] party.heroes;

    party.heroes = newHeroes;
    party.size = count;

    cout << "Завантажено героїв: "
        << party.size << '\n';

    return true;
}