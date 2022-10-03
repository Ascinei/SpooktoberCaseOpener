#include <iostream>
#include <string>
#include <map>
#include <time.h>

using namespace std;

string rarity{};

map<string, int> itemMap(int roll) {
    map<string, int> commonItems;
    map<string, int> uncommonItems;
    map<string, int> rareItems;
    map<string, int> epicItems;
    map<string, int> legendaryItems;

    commonItems["Candycorn"] = 5;
    commonItems["Cobweb"] = 5;
    commonItems["Stick"] = 5;
    commonItems["Rock"] = 5;
    
    uncommonItems["Bat"] = 30;
    uncommonItems["Pumpkin"] = 30;
    uncommonItems["Spider"] = 30;
    uncommonItems["Pumpkin"] = 30;
    
    rareItems["Cat"] = 200;
    rareItems["Jack O'Lantern"] = 200;
    rareItems["Coffin"] = 200;
    rareItems["Tombstone"] = 200;

    epicItems["Skeleton"] = 2000;
    epicItems["Vampire"] = 2000;
    epicItems["Witch"] = 2000;
    epicItems["Ghost"] = 2000;

    legendaryItems["Headless Horseman"] = 12500;
    legendaryItems["Flying Dutchman"] = 12500;
    legendaryItems["Headless Horseman"] = 12500;
    legendaryItems["Spooky Scary Skeleton"] = 12500;
    

    if (roll <= 5)
    {
        system("color 86");
        rarity = "Legendary";
        return legendaryItems;
    } else if (roll <= 20)
    {
        rarity = "Epic";
        return epicItems;
    } else if (roll <= 100)
    {
        rarity = "Rare";
        return rareItems;
    } else if (roll <= 350)
    {
        rarity = "Uncommon";
        return uncommonItems;
    }
    rarity = "Common";
    return commonItems;
}

string itemPull() {
    int roll = rand() % 1000;
    int val = rand() % itemMap(roll).size();
    auto itemS = itemMap(roll).begin();
    advance(itemS, val);
    return itemS->first;
}

int main() {
    srand(time(NULL));
    string input{};
    string menu{"(1) Open a box.\n(2) Check inventory.\n(3) Browse shop.\n(4) Open crafting.\n(0) Close game.\nPlease enter an option: "};
    string dump{};
    string item{};
    while (true) {
        system("color 02");
        cout << menu;

        cin >> input;

        if(input == "1") {
            system("clear");
            item = itemPull();
            cout << "\n\nYou got a " << rarity << " " << item << "!\n\n";
            cin.ignore();
            cin.get();
            system("color 02");
            system("clear");
        }
        if(input == "0") {
            system("clear");
            exit(0);
        }
    }
    return 0;
}