#include <iostream>
#include <string>
#include <map>

using namespace std;

map<string, string> itemPull() {
    map<string, string> commonItems;
    map<string, string> uncommonItems;
    map<string, string> rareItems;
    map<string, string> epicItems;
    map<string, string> legendaryItems;
    return;
}

int main() {
    string input{};
    string menu{"(1) Open a box.\n(2) Browse shop.\n(3) Check inventory.\n(4) Close game.\nPlease enter an option: "};
//    system("color 86");
    cout << menu;
    cin >> input;
    return 0;
}