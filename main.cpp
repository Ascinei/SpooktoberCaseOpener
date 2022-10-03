#include <iostream>
#include <string>
#include <map>
#include <time.h>

using namespace std;

string rarity{};
map<string, int> inventory;

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
    string item{};

    int roll = rand() % 1000;
    map<string, int> iMap = itemMap(roll);
    int val = rand() % iMap.size();
    auto itemS = iMap.begin();
    advance(itemS, val);
    item = itemS->first;;
    return item;
}

map<string, int> initInventory()
{
    map<string, int> result;
    result["#1 (Common) Candycorn"] = 0;
    result["#2 (Common) Cobweb"] = 0;
    result["#3 (Common) Stick"] = 0;
    result["#4 (Common) Rock"] = 0;
    
    result["#5 (Uncommon) Bat"] = 0;
    result["#6 (Uncommon) Pumpkin"] = 0;
    result["#7 (Uncommon) Spider"] = 0;
    result["#8 (Uncommon) Pumpkin"] = 0;
    
    result["#9 (Rare) Cat"] = 0;
    result["#10 (Rare) Jack O'Lantern"] = 0;
    result["#11 (Rare) Coffin"] = 0;
    result["#12 (Rare) Tombstone"] = 0;

    result["#13 (Epic) Skeleton"] = 0;
    result["#14 (Epic) Vampire"] = 0;
    result["#15 (Epic) Witch"] = 0;
    result["#16 (Epic) Ghost"] = 0;

    result["#17 (Legendary) Headless Horseman"] = 0;
    result["#18 (Legendary) Flying Dutchman"] = 0;
    result["#19 (Legendary) Headless Horseman"] = 0;
    result["#20 (Legendary) Spooky Scary Skeleton"] = 0;
    
    return result;
}


void addToInventory(string item) {
    inventory.find(item)->second+=1;
}

string checkInventory() {
    system("cls");
    for(auto it = inventory.begin(); it != inventory.end(); it++) {
        cout << it->first << ": " << it->second << "\n";
    }
    return "";
}


void sellMenu() {
    string input{};
    system("cls");
    cout << "Pretend I printed the whole map\n";
    cout << "What would you like to sell?\n";
    cin >> input;
    system("cls");
}

void promptBuyOrSell() {
    system("cls");
    string input{};
    cout << "(1) Buy items\n(2) Sell items\n(3) Back to menu\nPlease enter an option: ";
    cin >> input;
    if(input == "2") {
        sellMenu();
    }
    if(input == "3") {
        system("cls");
    }
}


int main() {
    srand(time(NULL));
    inventory = initInventory();
    string input{};
    string menu{"(1) Open a box.\n(2) Check inventory.\n(3) Browse shop.\n(4) Open crafting.\n(0) Close game.\nPlease enter an option: "};
    string dump{};
    string item{};
    while (true) {
        system("color 02");
        cout << menu;
        cin >> input;

        if(input == "1") {
            system("cls");
            item = itemPull();
            addToInventory(item);
            cout << "\n\nYou got a " << rarity << " " << item << "!\n\n";
            cin.ignore();
            cin.get();
            system("color 02");
            system("cls");
        }
        if(input == "2") {
            checkInventory();
            cin.ignore();
            cin.get();
            system("color 02");
            system("cls");
        }
        if(input == "3") {
            promptBuyOrSell();
        }
        if(input == "0") {
            system("cls");
            exit(0);
        }
    }
    return 0;
}