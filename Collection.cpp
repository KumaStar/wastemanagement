#include "Collection.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>

using namespace std;

static const string COLLECTION_FILE = "data/collection.txt";

int Collection::nextId() const {
    ifstream in(COLLECTION_FILE);
    string line;
    int highest = 0;
    while (getline(in, line)) {
        stringstream ss(line);
        string id;
        if (getline(ss, id, '|')) {
            try { highest = max(highest, stoi(id)); } catch (...) {}
        }
    }
    return highest + 1;
}

void Collection::recordCollection(StorageUnit& storage) {
    int storageId;
    cout << "Enter storage unit ID: ";
    if (!(cin >> storageId)) {
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid ID.\n"; return;
    }
    double quantity;
    cout << "Enter collected quantity (kg): ";
    if (!(cin >> quantity) || quantity <= 0) {
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter a quantity greater than zero.\n"; return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string date;
    cout << "Enter collection date (YYYY-MM-DD): ";
    getline(cin, date);

    if (!storage.removeQuantity(storageId, quantity)) {
        cout << "Collection not recorded. Check the storage ID and stored quantity.\n";
        return;
    }

    ofstream out(COLLECTION_FILE, ios::app);
    out << nextId() - 1 << "|" << storageId << "|" << quantity << "|" << date << "\n";
    cout << "Collection recorded and storage quantity updated.\n";
}

void Collection::viewCollections() const {
    ifstream in(COLLECTION_FILE);
    string line;
    cout << "\nCollection ID | Storage ID | Quantity (kg) | Date\n";
    cout << "------------------------------------------------\n";
    bool found = false;
    while (getline(in, line)) {
        stringstream ss(line);
        string id, storageId, quantity, date;
        getline(ss, id, '|'); getline(ss, storageId, '|');
        getline(ss, quantity, '|'); getline(ss, date, '|');
        cout << id << " | " << storageId << " | " << quantity << " | " << date << "\n";
        found = true;
    }
    if (!found) cout << "No collection records found.\n";
}

void Collection::menu(StorageUnit& storage) {
    while (true) {
        cout << "\n--- Collection Management ---\n";
        cout << "1. Record collection\n2. View collection history\n3. Back\nChoice: ";
        int choice;
        if (!(cin >> choice)) {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice.\n"; continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (choice == 1) recordCollection(storage);
        else if (choice == 2) viewCollections();
        else if (choice == 3) return;
        else cout << "Invalid choice.\n";
    }
}
