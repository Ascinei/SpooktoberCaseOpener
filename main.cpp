#include <iostream>
#include <string>
#include <map>
#include <time.h>

using namespace std;

// Random global variables that idk how else to declare
string rarity{};
map<string, int> inventory;
int legendaryChance{5};
int epicChance{20};
int rareChance{100};
int uncommonChance{350};
int currency{0};
bool oneTime{false};

// Global variables for upgrades.   Increments/Caps
int uncommonChanceIncrease = 0;  // 14         900
int rareChanceIncrease = 0;      // 7          775
int epicChanceIncrease = 0;      // 5          650
int legendaryChanceIncrease = 0; // 3          500

float sellPriceModifier = 1.8;   // 0.1        inf.

map<string, int> itemMap(int roll) {
    map<string, int> commonItems;
    map<string, int> uncommonItems;
    map<string, int> rareItems;
    map<string, int> epicItems;
    map<string, int> legendaryItems;

    commonItems["Candycorn"] = (int) (5 * sellPriceModifier);
    commonItems["Cobweb"] = (int) (5 * sellPriceModifier);
    commonItems["Stick"] = (int) (5 * sellPriceModifier);
    commonItems["Rock"] = (int) (5 * sellPriceModifier);
    
    uncommonItems["Bat"] = (int) (30 * sellPriceModifier);
    uncommonItems["Pumpkin"] = (int) (30 * sellPriceModifier);
    uncommonItems["Spider"] = (int) (30 * sellPriceModifier);
    uncommonItems["Candle"] = (int) (30 * sellPriceModifier);
    
    rareItems["Cat"] = (int) (200 * sellPriceModifier);
    rareItems["Jack O'Lantern"] = (int) (200 * sellPriceModifier);
    rareItems["Coffin"] = (int) (200 * sellPriceModifier);
    rareItems["Tombstone"] = (int) (200 * sellPriceModifier);

    epicItems["Skeleton"] = (int) (2000 * sellPriceModifier);
    epicItems["Vampire"] = (int) (2000 * sellPriceModifier);
    epicItems["Witch"] = (int) (2000 * sellPriceModifier);
    epicItems["Ghost"] = (int) (2000 * sellPriceModifier);

    legendaryItems["Headless Horseman"] = (int) (12500 * sellPriceModifier);
    legendaryItems["Flying Dutchman"] = (int) (12500 * sellPriceModifier);
    legendaryItems["Headless Horseman"] = (int) (12500 * sellPriceModifier);
    legendaryItems["Spooky Scary Skeleton"] = (int) (12500 * sellPriceModifier);
    

    if (roll <= 5)
    {
        system("color 86");
        rarity = "Legendary";
        return legendaryItems;
    } else if (roll <= 15)
    {
        rarity = "Epic";
        return epicItems;
    } else if (roll <= 75)
    {
        rarity = "Rare";
        return rareItems;
    } else if (roll <= 200)
    {
        rarity = "Uncommon";
        return uncommonItems;
    }
    rarity = "Common";
    return commonItems;
}

void updateUpgrades() {
    
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
    result["1 Common Candycorn"] = 0;
    result["1 Common Cobweb"] = 0;
    result["1 Common Stick"] = 0;
    result["1 Common Rock"] = 0;
    
    result["2 Uncommon Bat"] = 0;
    result["2 Uncommon Pumpkin"] = 0;
    result["2 Uncommon Spider"] = 0;
    result["2 Uncommon Candle"] = 0;
    
    result["3 Rare Cat"] = 0;
    result["3 Rare Jack O'Lantern"] = 0;
    result["3 Rare Coffin"] = 0;
    result["3 Rare Tombstone"] = 0;

    result["4 Epic Skeleton"] = 0;
    result["4 Epic Vampire"] = 0;
    result["4 Epic Witch"] = 0;
    result["4 Epic Ghost"] = 0;

    result["5 Legendary eadless Horseman"] = 0;
    result["5 Legendary Flying Dutchman"] = 0;
    result["5 Legendary Headless Horseman"] = 0;
    result["5 Legendary Spooky Scary Skeleton"] = 0;
    
    return result;
}

string rarityToStringInt(string rarity) {
    if(rarity == "Common") return "1";
    else if(rarity == "Uncommon") return "2";
    else if(rarity == "Rare") return "3";
    else if(rarity == "Epic") return "4";
    else if(rarity == "Legendary") return "5";
    return "-1";
}

void addToInventory(string item, string rarity) {
    inventory.find(rarityToStringInt(rarity) + " " + rarity + " " + item)->second+=1;
}

string checkInventory() {
    system("cls");
    for(auto it = inventory.begin(); it != inventory.end(); ++it) {
        cout << it->first.substr(2) << ": " << it->second << "\n";
    }
    return "";
}

void promptRarity();

void sellMenu(int selector, int invIndex) {
    int input{};
    system("cls");
    map<string, int> rarityMap = itemMap(selector);
    int i{1};
    for(auto it = rarityMap.begin(); it != rarityMap.end(); ++it) {
        cout << "(" << i << ") " << it->first << ": " << it->second << " Spoopy coins" << "\n";
        i++;
    }
    cout << "(" << i << ") " << "Back to rarity menu\n";
    cout << "What would you like to sell: \n";
    cin >> input;
    if (input > 0 && input < i) {
        auto invIt = inventory.begin();
        advance(invIt, invIndex*4 + input - 1);
        if (invIt->second==0) {
            system("cls");
            cout << "You have no " << invIt->first.substr(2) << " to sell!\n";
            cin.ignore();
            cin.get();
        }
        else {
            cout << "You have " << invIt->second << " " << invIt->first.substr(2) << ".\n";
            inventory.find(invIt->first)->second-=1;
            auto it = rarityMap.begin();
            advance(it, input - 1);
            system("cls");
            currency += it->second;
            cout << "Sold " << it->first << " for " << it->second << " Spoppy coins.\nYou now have " << currency << " Spoopy coins.\n";
            cout << "You now have " << invIt->second << " " << invIt->first.substr(2) << ".\n";
            cin.ignore();
            cin.get();    
        }
        sellMenu(selector, invIndex);
    }    
    if (input == i) {
        promptRarity();
    } else {
        sellMenu(selector, invIndex);
    }
    
    system("cls");
}

int main();

void promptBuyOrSell() {
    system("cls");
    int input{};
    cout << "(1) Buy upgrades\n(2) Sell items\n(3) Back to menu\nPlease enter an option: ";
    cin >> input;
    if(input == 2) {
        promptRarity();
    }
    if(input == 3) {
        system("cls");
        main();
    }
}

void promptRarity() {
    system("cls");
    int input{};
    cout << "(1) Common\n(2) Uncommon\n(3) Rare\n(4) Epic\n(5) Legendary\n(6) Back to buy or sell.\nPlease enter an option: ";
    cin >> input;
    if(input == 1) {
        sellMenu(uncommonChance+1, 0);
    }    
    if(input == 2) {
        sellMenu(uncommonChance, 1);
    }
    if(input == 3) {
        sellMenu(rareChance, 2);
    }
    if(input == 4) {
        sellMenu(epicChance, 3);
    }    
    if(input == 5) {
        sellMenu(legendaryChance, 4);
    }
    if(input == 6) {
        promptBuyOrSell();
    }
}


int main() {
    if(oneTime == false) {
        srand(time(NULL));
        inventory = initInventory();
        oneTime = true;
    }
    int input{};
    string menu{"(1) Open a box.\n(2) Check inventory.\n(3) Browse shop.\n(4) Open crafting.\n(0) Close game.\nPlease enter an option: "};
    string dump{};
    string item{};
    while (true) {
        system("color 02");
        cout << menu;
        cin >> input;

        if(input == 1) {
            system("cls");
            item = itemPull();
            addToInventory(item, rarity);
            cout << "\n\nYou got a " << rarity << " " << item  << "!\n\n";
            cin.ignore();
            cin.get();
            system("color 02");
            system("cls");
        }
        if(input == 2) {
            checkInventory();
            cin.ignore();
            cin.get();
            system("color 02");
            system("cls");
        }
        if(input == 3) {
            promptBuyOrSell();
        }
        if(input == 0) {
            system("cls");
            exit(0);
        }
    }
    return 0;
}