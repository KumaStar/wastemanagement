#include <iostream>
#include <limits>
#include "Waste.h"
#include "StorageUnit.h"
#include "Collection.h"
#include "Report.h"

using namespace std;

int readChoice() {
    int choice;
    while (!(cin >> choice)) {
        cout << "Enter a valid number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

int main() {
    Waste waste;
    StorageUnit storage;
    Collection collection;
    Report report;

    while (true) {
        cout << "\n========================================\n";
        cout << " SMART INDUSTRIAL WASTE MANAGEMENT\n";
        cout << "========================================\n";
        cout << "1. Waste Classification\n";
        cout << "2. Storage Management\n";
        cout << "3. Collection Management\n";
        cout << "4. Reports and Alerts\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        int choice = readChoice();

        switch (choice) {
            case 1: waste.menu(storage); break;
            case 2: storage.menu(); break;
            case 3: collection.menu(storage); break;
            case 4: report.menu(); break;
            case 5:
                cout << "Thank you for using the system.\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}
