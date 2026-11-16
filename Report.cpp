#include "Report.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

void Report::categorySummary() const {
    double wet = 0, dry = 0, hazardous = 0;
    ifstream in("data/waste.txt");
    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        string id, category, quantity;
        getline(ss, id, '|'); getline(ss, category, '|'); getline(ss, quantity, '|');
        try {
            double amount = stod(quantity);
            if (category == "wet") wet += amount;
            else if (category == "dry") dry += amount;
            else if (category == "hazardous") hazardous += amount;
        } catch (...) {}
    }
    cout << "\n--- Waste Category Summary (kg) ---\n";
    cout << fixed << setprecision(2);
    cout << "Wet: " << wet << "\nDry: " << dry
         << "\nHazardous: " << hazardous
         << "\nTotal: " << wet + dry + hazardous << "\n";
}

void Report::collectionSummary() const {
    double total = 0;
    int count = 0;
    ifstream in("data/collection.txt");
    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        string id, storageId, quantity, date;
        getline(ss, id, '|'); getline(ss, storageId, '|');
        getline(ss, quantity, '|'); getline(ss, date, '|');
        try { total += stod(quantity); ++count; } catch (...) {}
    }
    cout << "\n--- Collection Summary ---\n";
    cout << "Number of collection records: " << count << "\n";
    cout << fixed << setprecision(2) << "Total collected: " << total << " kg\n";
}

void Report::monthlySummary() const {
    string month;
    cout << "Enter month (YYYY-MM): ";
    getline(cin, month);
    if (month.size() != 7) {
        cout << "Use YYYY-MM format.\n";
        return;
    }

    double generated = 0, collected = 0;
    string line;
    ifstream wasteIn("data/waste.txt");
    while (getline(wasteIn, line)) {
        stringstream ss(line);
        string id, category, quantity, date;
        getline(ss, id, '|'); getline(ss, category, '|');
        getline(ss, quantity, '|'); getline(ss, date, '|');
        if (date.rfind(month, 0) == 0) {
            try { generated += stod(quantity); } catch (...) {}
        }
    }

    ifstream collectionIn("data/collection.txt");
    while (getline(collectionIn, line)) {
        stringstream ss(line);
        string id, storageId, quantity, date;
        getline(ss, id, '|'); getline(ss, storageId, '|');
        getline(ss, quantity, '|'); getline(ss, date, '|');
        if (date.rfind(month, 0) == 0) {
            try { collected += stod(quantity); } catch (...) {}
        }
    }

    cout << fixed << setprecision(2);
    cout << "\n--- Monthly Summary: " << month << " ---\n";
    cout << "Waste generated: " << generated << " kg\n";
    cout << "Waste collected: " << collected << " kg\n";
}

void Report::capacityAlerts() const {
    ifstream in("data/storage.txt");
    string line;
    bool any = false;
    cout << "\n--- Storage Capacity Alerts ---\n";
    while (getline(in, line)) {
        stringstream ss(line);
        string id, category, capText, currentText;
        getline(ss, id, '|'); getline(ss, category, '|');
        getline(ss, capText, '|'); getline(ss, currentText, '|');
        try {
            double cap = stod(capText), current = stod(currentText);
            double percent = (current / cap) * 100.0;
            if (percent >= 90.0) {
                cout << "WARNING: Storage unit " << id << " (" << category
                     << ") is " << fixed << setprecision(1) << percent << "% full.\n";
                any = true;
            }
        } catch (...) {}
    }
    if (!any) cout << "No storage units are at or above 90% capacity.\n";
}

void Report::menu() const {
    while (true) {
        cout << "\n--- Reports and Alerts ---\n";
        cout << "1. Category-wise waste summary\n2. Collection summary\n";
        cout << "3. Monthly summary\n4. Storage capacity alerts\n5. Back\nChoice: ";
        int choice;
        if (!(cin >> choice)) {
            cin.clear(); cin.ignore(10000, '\n');
            cout << "Invalid choice.\n"; continue;
        }
        cin.ignore(10000, '\n');
        if (choice == 1) categorySummary();
        else if (choice == 2) collectionSummary();
        else if (choice == 3) monthlySummary();
        else if (choice == 4) capacityAlerts();
        else if (choice == 5) return;
        else cout << "Invalid choice.\n";
    }
}
