#include "StorageUnit.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include <iomanip>
#include <algorithm>

using namespace std;

static const string STORAGE_FILE = "data/storage.txt";

int StorageUnit::findUnit(int wanted, string& category, double& capacity, double& current) const {
    ifstream in(STORAGE_FILE);
    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        string id;
        getline(ss, id, '|'); getline(ss, category, '|');
        string cap, cur;
        getline(ss, cap, '|'); getline(ss, cur, '|');
        try {
            if (stoi(id) == wanted) {
                capacity = stod(cap);
                current = stod(cur);
                return 1;
            }
        } catch (...) {}
    }
    return 0;
}

void StorageUnit::addUnit() {
    int id = 1;
    string line;
    ifstream in(STORAGE_FILE);
    while (getline(in, line)) {
        stringstream ss(line);
        string value;
        if (getline(ss, value, '|')) {
            try { id = max(id, stoi(value) + 1); } catch (...) {}
        }
    }

    cout << "\nStorage categories: wet, dry, hazardous\n";
    string category;
    cout << "Enter category for this unit: ";
    getline(cin, category);
    if (category != "wet" && category != "dry" && category != "hazardous") {
        cout << "Invalid category.\n";
        return;
    }

    double capacity;
    cout << "Enter maximum capacity (kg): ";
    if (!(cin >> capacity) || capacity <= 0) {
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Capacity must be greater than zero.\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    ofstream out(STORAGE_FILE, ios::app);
    out << id << "|" << category << "|" << capacity << "|0\n";
    cout << "Storage unit created. Its ID is " << id << ".\n";
}

void StorageUnit::viewUnits() const {
    ifstream in(STORAGE_FILE);
    string line;
    cout << "\nID | Category | Capacity (kg) | Stored (kg) | Remaining (kg) | Used (%)\n";
    cout << "-----------------------------------------------------------------------\n";
    bool found = false;
    while (getline(in, line)) {
        stringstream ss(line);
        string id, category, capText, curText;
        getline(ss, id, '|'); getline(ss, category, '|');
        getline(ss, capText, '|'); getline(ss, curText, '|');
        try {
            double cap = stod(capText), cur = stod(curText);
            double remaining = cap - cur;
            double percent = (cur / cap) * 100.0;
            cout << id << " | " << category << " | " << fixed << setprecision(2)
                 << cap << " | " << cur << " | " << remaining << " | "
                 << percent << "%\n";
            if (percent >= 90.0)
                cout << "  ALERT: Storage unit is almost full.\n";
            found = true;
        } catch (...) {}
    }
    if (!found) cout << "No storage units. Add a unit first.\n";
}

void StorageUnit::updateCapacity() {
    int wanted;
    cout << "Enter storage unit ID: ";
    if (!(cin >> wanted)) {
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid ID.\n"; return;
    }
    double newCapacity;
    cout << "Enter new maximum capacity (kg): ";
    if (!(cin >> newCapacity) || newCapacity <= 0) {
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Capacity must be greater than zero.\n"; return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    ifstream in(STORAGE_FILE);
    vector<string> lines;
    string line;
    bool updated = false;
    while (getline(in, line)) {
        stringstream ss(line);
        string id, category, capText, curText;
        getline(ss, id, '|'); getline(ss, category, '|');
        getline(ss, capText, '|'); getline(ss, curText, '|');
        if (id == to_string(wanted)) {
            try {
                if (newCapacity < stod(curText)) {
                    cout << "New capacity cannot be less than the current stored quantity.\n";
                    return;
                }
            } catch (...) { return; }
            line = id + "|" + category + "|" + to_string(newCapacity) + "|" + curText;
            updated = true;
        }
        lines.push_back(line);
    }
    if (!updated) { cout << "Storage unit not found.\n"; return; }

    ofstream out(STORAGE_FILE);
    for (const auto& item : lines) out << item << "\n";
    cout << "Capacity updated.\n";
}

bool StorageUnit::addQuantity(int wanted, const string& wasteCategory, double quantity) {
    ifstream in(STORAGE_FILE);
    vector<string> lines;
    string line;
    bool updated = false;
    while (getline(in, line)) {
        stringstream ss(line);
        string id, category, capText, curText;
        getline(ss, id, '|'); getline(ss, category, '|');
        getline(ss, capText, '|'); getline(ss, curText, '|');
        if (id == to_string(wanted)) {
            try {
                double cap = stod(capText), cur = stod(curText);
                if (category != wasteCategory || cur + quantity > cap) return false;
                line = id + "|" + category + "|" + capText + "|" + to_string(cur + quantity);
                updated = true;
            } catch (...) { return false; }
        }
        lines.push_back(line);
    }
    if (!updated) return false;
    ofstream out(STORAGE_FILE);
    for (const auto& item : lines) out << item << "\n";
    return true;
}

bool StorageUnit::removeQuantity(int wanted, double quantity) {
    ifstream in(STORAGE_FILE);
    vector<string> lines;
    string line;
    bool updated = false;
    while (getline(in, line)) {
        stringstream ss(line);
        string id, category, capText, curText;
        getline(ss, id, '|'); getline(ss, category, '|');
        getline(ss, capText, '|'); getline(ss, curText, '|');
        if (id == to_string(wanted)) {
            try {
                double cap = stod(capText), cur = stod(curText);
                if (quantity <= 0 || quantity > cur) return false;
                line = id + "|" + category + "|" + capText + "|" + to_string(cur - quantity);
                updated = true;
            } catch (...) { return false; }
        }
        lines.push_back(line);
    }
    if (!updated) return false;
    ofstream out(STORAGE_FILE);
    for (const auto& item : lines) out << item << "\n";
    return true;
}

void StorageUnit::menu() {
    while (true) {
        cout << "\n--- Storage Management ---\n";
        cout << "1. Add storage unit\n2. View storage units\n3. Update capacity\n4. Back\nChoice: ";
        int choice;
        if (!(cin >> choice)) {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice.\n"; continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (choice == 1) addUnit();
        else if (choice == 2) viewUnits();
        else if (choice == 3) updateCapacity();
        else if (choice == 4) return;
        else cout << "Invalid choice.\n";
    }
}
