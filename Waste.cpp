#include "Waste.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>

using namespace std;

static const string WASTE_FILE = "data/waste.txt";

static string readText(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}

static double readPositiveAmount(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value && value > 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Please enter a quantity greater than zero.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int Waste::nextId() const {
    ifstream in(WASTE_FILE);
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

void Waste::addWaste(StorageUnit& storage) {
    cout << "\nWaste categories: wet, dry, hazardous\n";
    string category = readText("Enter category: ");
    if (category != "wet" && category != "dry" && category != "hazardous") {
        cout << "Invalid category. Use wet, dry or hazardous.\n";
        return;
    }

    double quantity = readPositiveAmount("Enter quantity (kg): ");
    string date = readText("Enter date (YYYY-MM-DD): ");
    int storageId;
    cout << "Enter storage unit ID: ";
    if (!(cin >> storageId)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid storage ID.\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (!storage.addQuantity(storageId, category, quantity)) {
        cout << "Could not add waste. Check that the storage unit exists, matches the category, "
                "and has enough remaining capacity.\n";
        return;
    }

    ofstream out(WASTE_FILE, ios::app);
    out << nextId() - 1 << "|" << category << "|" << quantity << "|" << date
        << "|" << storageId << "\n";
    cout << "Waste record saved successfully.\n";
}

void Waste::viewWaste() const {
    ifstream in(WASTE_FILE);
    string line;
    cout << "\nID | Category | Quantity (kg) | Date | Storage ID\n";
    cout << "------------------------------------------------\n";
    bool found = false;
    while (getline(in, line)) {
        stringstream ss(line);
        string id, category, quantity, date, storageId;
        getline(ss, id, '|'); getline(ss, category, '|'); getline(ss, quantity, '|');
        getline(ss, date, '|'); getline(ss, storageId, '|');
        cout << id << " | " << category << " | " << quantity << " | "
             << date << " | " << storageId << "\n";
        found = true;
    }
    if (!found) cout << "No waste records found.\n";
}

void Waste::searchWaste() const {
    int wanted;
    cout << "Enter waste record ID: ";
    if (!(cin >> wanted)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid ID.\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    ifstream in(WASTE_FILE);
    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        string id, category, quantity, date, storageId;
        getline(ss, id, '|'); getline(ss, category, '|'); getline(ss, quantity, '|');
        getline(ss, date, '|'); getline(ss, storageId, '|');
        if (id == to_string(wanted)) {
            cout << "Record found: " << id << " | " << category << " | "
                 << quantity << " kg | " << date << " | Storage " << storageId << "\n";
            return;
        }
    }
    cout << "Record not found.\n";
}

void Waste::menu(StorageUnit& storage) {
    while (true) {
        cout << "\n--- Waste Classification ---\n";
        cout << "1. Add waste record\n2. View all records\n3. Search record\n4. Back\nChoice: ";
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (choice == 1) addWaste(storage);
        else if (choice == 2) viewWaste();
        else if (choice == 3) searchWaste();
        else if (choice == 4) return;
        else cout << "Invalid choice.\n";
    }
}
