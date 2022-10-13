#include <iostream>
#include <string>
#include <map>
#include <list>
#include <time.h>
#include <stdlib.h>

using namespace std;

// Random global variables that idk how else to declare
string rarity{ };
map<string, int> inventory;
int legendaryChance{ 5 };
int epicChance{ 20 };
int rareChance{ 100 };
int uncommonChance{ 350 };
int currency{ 0 };
bool oneTime{ false };
bool couponApplied{ false };
bool doubleSellApplied{ false };
int pulled{ 0 };
int totalEarned{ 0 };

// Global variables for upgrades.   Increments/Caps     Total Purchases
int uncommonChanceIncrease = 0;  // 14         900      50
int rareChanceIncrease = 0;      // 10         775      70
int epicChanceIncrease = 0;      // 5          650      130
int legendaryChanceIncrease = 0; // 3          555      185

float sellPriceModifier = 1.00;   // Self * 1.05        inf.

int cost1{ 300 };
int cost2{ 1000 };
int cost3{ 2500 };
int cost4{ 5000 };
int cost5{ 1000 };

// Global variables for crafting.
map<string, bool> craftedItems;

// int doubleDropChance;

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

    legendaryItems["Casper the Friendly Ghost"] = (int) (12500 * sellPriceModifier);
    legendaryItems["Flying Dutchman"] = (int) (12500 * sellPriceModifier);
    legendaryItems["Headless Horseman"] = (int) (12500 * sellPriceModifier);
    legendaryItems["Spooky Scary Skeleton"] = (int) (12500 * sellPriceModifier);
    

    if (roll <= legendaryChance + legendaryChance)
    {
        rarity = "Legendary";
        return legendaryItems;
    } else if (roll <= epicChance + epicChanceIncrease)
    {
        rarity = "Epic";
        return epicItems;
    } else if (roll <= rareChance + rareChanceIncrease)
    {
        rarity = "Rare";
        return rareItems;
    } else if (roll <= uncommonChance + uncommonChanceIncrease)
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

    result["5 Legendary Casper the Friendly Ghost"] = 0;
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
    cout << "Press enter to continue\n";
    return "";
}

void promptRarity();

void sellMenu(int selector, int invIndex) {
    int input{};
    system("cls");
    map<string, int> rarityMap = itemMap(selector);
    int i{1};
    for(auto it = rarityMap.begin(); it != rarityMap.end(); it++) {
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
            totalEarned += it->second;
            cout << "Sold " << it->first << " for " << it->second << " Spoopy coins.\nYou now have " << currency << " Spoopy coins.\n";
            cout << "You now have " << invIt->second << " " << invIt->first.substr(2) << ".\n";
            cin.ignore();
            cin.get();    
        }
        sellMenu(selector, invIndex);
    }    
    else if (input == i) {
        promptRarity();
    } else {
        sellMenu(selector, invIndex);
    }
    
    system("cls");
}

void buyMenu();

void promptBuyOrSell() {
    system("cls");
    int input{};
    cout << "(1) Buy upgrades\n(2) Sell items\n(3) Back to menu\nPlease enter an option: ";
    cin >> input;
    if(input == 1) {
        buyMenu();
    }
    else if(input == 2) {
        promptRarity();
    }
    else {
        system("cls");
        return;
    }
}

void promptRarity() {
    system("cls");
    int input{};
    cout << "(1) Common\n(2) Uncommon\n(3) Rare\n(4) Epic\n(5) Legendary\n(6) Back to buy or sell.\nPlease enter an option: ";
    cin >> input;
    if(input == 1) {
        sellMenu(uncommonChance+1+uncommonChanceIncrease, 0);
    }    
    else if(input == 2) {
        sellMenu(uncommonChance+uncommonChanceIncrease, 1);
    }
    else if(input == 3) {
        sellMenu(rareChance+rareChanceIncrease, 2);
    }
    else if(input == 4) {
        sellMenu(epicChance+epicChanceIncrease, 3);
    }    
    else if(input == 5) {
        sellMenu(legendaryChance+legendaryChanceIncrease, 4);
    }
    else {
        promptBuyOrSell();
    }
}

void buyMenu() {
    system("cls");
    int input{};

    cout << "(1) Uncommon chance upgrade level " << uncommonChanceIncrease/14+1 << " for " << cost1 << " Spoopy coins.\n(2) Rare chance upgrade level " << rareChanceIncrease/10 + 1 << " for " << cost2 << " Spoopy coins.\n(3) Epic chance upgrade level "<< epicChanceIncrease/5 + 1 << " for " << cost3 << " Spoppy coins.\n(4) Legendary chance upgrade level "<< legendaryChanceIncrease/3 + 1 << " for " << cost4 << " Spoopy coins.\n(5) Sell price multiplier for " << cost5 << " Spoopy coins. (Currently " << sellPriceModifier << "x)\n(6) Back to buy or sell\nPlease enter an option: ";
    cin >> input;   

    if(input == 1) {
        
        if (currency >= cost1) {
            system("cls");
            uncommonChanceIncrease += 14;
            currency -= cost1;
            cost1 = (int) ((double) cost1 * 1.01);
            cout << "Successfully bought the Uncommon chance increase, your chance of an Uncommon is now: " << (float) (uncommonChanceIncrease+250)/10 << "%";
            cin.ignore();
            cin.get();       
            buyMenu();
        }   else {
            system("cls");
            cout << "You don't have enough Spoopy coins!! You have " << currency << " Spoopy coins currently and need " << cost1 - currency << " more.";
            cin.ignore();
            cin.get();
            buyMenu();       
        }
    }
    else if(input == 2) {
        if  (uncommonChanceIncrease>=140) {
            if(currency >= cost2) {
                system("cls");
                rareChanceIncrease += 10;
                currency -= cost2;
                cost2 += (int) ((double) cost2 * 1.015);
                cout << "Successfully bought the Rare chance increase, your chance of a Rare is now: " << (float) (rareChanceIncrease+80)/10 << "%";
                cin.ignore();
                cin.get();           
                buyMenu(); 
            } else {
                system("cls");
                cout << "You don't have enough Spoopy coins!! You have " << currency << " Spoopy coins currently and need " << cost2 - currency << " more.";
                cin.ignore();
                cin.get();
                buyMenu();            
            }
        } else {
            system("cls");
            cout << "Your Uncommon Chance Upgrade is at level " << uncommonChanceIncrease/14 << " and needs to be at level 10 to get this upgrade.";
            cin.ignore();
            cin.get();
            buyMenu();        
        }
    }
    else if(input == 3) {

        if (rareChanceIncrease >= 300) {
            if(currency >= cost3) {
                system("cls");
                epicChanceIncrease += 5;
                currency -= cost3;
                cost3 = (int) ((double) cost3 * 1.02);
                cout << "Successfully bought the Epic chance increase, your chance of a Epic is now: " << (float) (epicChanceIncrease+15)/10 << "%";
                cin.ignore();
                cin.get();
                buyMenu();            
            } else {
                system("cls");
                cout << "You don't have enough Spoopy coins!! You have " << currency << " Spoopy coins currently and need " << cost3 - currency << " more.";
                cin.ignore();
                cin.get();
                buyMenu();
            }
        } else {
            system("cls");
            cout << "Your Rare Chance Upgrade is at level " << rareChanceIncrease/10 << " and needs to be at level 30 to get this upgrade.";
            cin.ignore();
            cin.get();
            buyMenu();
        }
    }
    else if(input == 4) {

        if (epicChanceIncrease >= 350) {
            if (currency >= cost4) {
                system("cls");
                legendaryChanceIncrease += 3;
                currency -= cost4;
                cost4 = (int) ((double) cost4 * 1.025);
                cout << "Successfully bought the Legendary chance increase, your chance of a Legendary is now: " << (float) (legendaryChanceIncrease+5)/10 << "%";
                cin.ignore();
                cin.get();
                buyMenu();
            } else {
                system("cls");
                cout << "You don't have enough Spoopy coins!! You have " << currency << " Spoopy coins currently and need " << cost4 - currency << " more.";
                cin.ignore();
                cin.get();
                buyMenu();
            }
        } else {
            system("cls");
            cout << "Your Epic Chance Upgrade is at level " << epicChanceIncrease/5 << " and needs to be at level 70 to get this upgrade.";
            cin.ignore();
            cin.get();
            buyMenu();
        }
    }

    else if(input == 5) {
        if(currency >= cost5) {
            system("cls");
            sellPriceModifier *= 1.05;
            currency -= cost5;
            cost5 = (int) ((double) cost5 * 1.035);
            cout << "Successfully bought Sell Price Multiplier, current value is at: " << sellPriceModifier << "x sell value.";
            cin.ignore();
            cin.get();
            buyMenu();
        } else {
            system("cls");
            cout << "You don't have enough Spoopy coins!! You have " << currency << " Spoopy coins currently and need " << cost5 - currency << " more.";
            cin.ignore();
            cin.get();
            buyMenu();
        }
    }
    else {
        promptBuyOrSell();
    }
}

void printRecipe(map<string, int> recipe, string name)
{
    system("cls");
    cout << name << "\n";
    for (auto it = recipe.begin(); it != recipe.end(); ++it) {
        cout << "Need " << it->second << " " << it->first.substr(2) << "\n";
    }
}

void openCraftingMenu();
void craft(map<string, int> recipe);

void canCraft(map<string, int> recipe, string item) {
    if(craftedItems[item]) {
        system("cls");
        cout << "You already crafted this item.";
        cin.ignore();
        cin.get();
        openCraftingMenu();
        return;
    }
    for(auto it = recipe.begin(); it != recipe.end(); ++it) {
        if(inventory[it->first] < it->second) {
            system("cls");
            cout << "Not enough materials to craft this item.";
            cin.ignore();
            cin.get();
            openCraftingMenu();
            return;
        };
    }
    craft(recipe);
    craftedItems[item] = true;
    system("cls");
    cout << "Successfully crafted this item.";
    cin.ignore();
    cin.get();
    openCraftingMenu();
}

void craft(map<string, int> recipe) 
{
    for(auto it = recipe.begin(); it != recipe.end(); ++it) 
    {
        inventory[it->first] = inventory[it->first] - it->second;
    }
}

void promptCraft(map<string, int> recipe, string item) 
{
    string input{};
    cout << "Would you like to craft this item? (Y/N)\n";
    cin >> input;
    if (input == "Y" || input == "y") {
        canCraft(recipe, item);
    }
    else {
        openCraftingMenu(); 
    }
};


void openCraftingMenu() {

    map<string, int> coupon;
    coupon["2 Uncommon Candle"] = 10;
    coupon["4 Epic Witch"] = 5;
    coupon["5 Legendary Headless Horseman"] = 2;
    coupon["5 Legendary Spooky Scary Skeleton"] = 2;

    map<string, int> doubleSell;
    doubleSell["3 Rare Cat"] = 5;
    doubleSell["3 Rare Jack O'Lantern"] = 10;
    doubleSell["5 Legendary Casper the Friendly Ghost"] = 3;

    map<string, int> doubleDrop;
    doubleDrop["1 Common Candycorn"] = 30;
    doubleDrop["3 Rare Tombstone"] = 9;
    doubleDrop["4 Epic Skeleton"] = 9;
    doubleDrop["5 Legendary Flying Dutchman"] = 3;

    system("cls");
    int input{};
    cout << "(1) 50% Off Coupon\n(2) 2x Sell Price\n(3) 10% Chance Double Drop\n(4) Back to menu\nPlease enter an option: ";
    cin >> input;   
    if(input == 1) {
        printRecipe(coupon, "50% Off Coupon made of spooky calcium.");
        promptCraft(coupon, "Coupon");
    }
    else if(input == 2) {
        printRecipe(doubleSell, "2x Sell Price because traders love friendly ghosts.");
        promptCraft(doubleSell, "Double Sell");
    }
    else if(input == 3) {
        printRecipe(doubleDrop, "10% Chance Drop Duplicator courtesy of the Flying Dutchman's crew.");
        promptCraft(doubleDrop, "Double Drop");
    }
    else {
        system("cls");
        return;
    }
}

void openStats() {
    system("cls");
    cout << "Current balance: " << currency << "\nTotal Earned: " << totalEarned << "\nTimes pulled: " << pulled << "\n";
    cout << "Press enter to continue\n";
    cin.ignore();
    cin.get();
    system("cls");
    return;
}

int main() {
    if(oneTime == false) {
        srand(time(NULL));
        inventory = initInventory();
        oneTime = true;
        craftedItems["Coupon"] = false;
        craftedItems["Double Sell"] = false;
        craftedItems["Double Drop"] = false;
    }
    int input{};
    string menu{"(1) Open a box\n(2) Check inventory\n(3) Browse shop\n(4) Open crafting\n(5) Open stats\n(0) Close game\nPlease enter an option: "};
    string dump{};
    string item{};
    while (true) {
        if(couponApplied == false && craftedItems["Coupon"]) {
            cost1 = cost1/2;
            cost2 = cost2/2;
            cost3 = cost3/2;
            cost4 = cost4/2;
            cost5 = cost5/2;
            couponApplied = true;
        }
        if(doubleSellApplied == false && craftedItems["Double Sell"]) {
            sellPriceModifier = sellPriceModifier * 2;
            doubleSellApplied = true;
        }
        system("color 02");
        cout << menu;
        cin >> input;

        if(input == 1) {
            system("cls");
            pulled++;
            item = itemPull();
            addToInventory(item, rarity);
            cout << "\n\nYou got a " << rarity << " " << item  << "!\n\n";
            if(craftedItems["Double Drop"] && rand() % 100 < 10) {
                addToInventory(item, rarity);
                cout << "You got a double of this drop!";
            }
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
        if(input == 4) {
            openCraftingMenu();
        }
        if(input == 5) {
            openStats();
        }
        if(input == 0) {
            system("cls");
            exit(0);
        }
    }
    return 0;
}