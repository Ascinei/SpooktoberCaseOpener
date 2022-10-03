#include <iostream>
#include <string>
#include <map>
#include <time.h>
#include <stdlib.h>
#include <limits>
#include <conio.h>

using namespace std;

map<string, int> itemPull(int roll) {
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
        return legendaryItems;
    } else if (roll <= 20)
    {
        return epicItems;
    } else if (roll <= 100)
    {
        return rareItems;
    } else if (roll <= 350)
    {
        return uncommonItems;
    }

    return commonItems;
}

int main() {
    srand(time(NULL));
    string input{};
    string menu{"(1) Open a box.\n(2) Check inventory.\n(3) Browse shop.\n(4) Open crafting.\n(5) Close game.\nPlease enter an option: "};
    string dump{};
    string item{};
    while (true) {
        system("color 02");
        cout << menu;

        cin >> input;
        int roll = rand() % 1000;
        if(input == "1") {
            system("clear");
            item = itemPull(roll).begin()->first;
            cout << "\n\nYou got a " << item << "!\n\n";
            cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            cin.get();
            system("color 02");
            system("clear");
        }
            
    }
    return 0;
}