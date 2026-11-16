SMART INDUSTRIAL WASTE MANAGEMENT SYSTEM
=========================================

A simple C++ command-line project divided into four modules.

MODULES / TEAM DIVISION
-----------------------
Member 1: Waste Classification
  Files: Waste.h, Waste.cpp
  Add, view and search waste records. Categories: wet, dry, hazardous.

Member 2: Storage Management
  Files: StorageUnit.h, StorageUnit.cpp
  Add storage units, view capacity and update capacity. Shows utilization.

Member 3: Admin and Collection
  Files: Collection.h, Collection.cpp
  Record collections, reduce stored quantity and view collection history.
  Capacity update is included in Storage Management for simplicity.

Member 4: Reports and Alerts
  Files: Report.h, Report.cpp
  Category summary, collection summary, monthly summary and 90% capacity alerts.

MAIN PROGRAM
------------
main.cpp connects all four modules through the main menu.

REQUIREMENTS
------------
- C++11 or newer (C++17 recommended)
- Standard C++ libraries only
- No external libraries or database

HOW TO COMPILE
--------------
Open a terminal in this project folder and run:

g++ -std=c++17 main.cpp Waste.cpp StorageUnit.cpp Collection.cpp Report.cpp -o waste_management

Run on Windows:
  waste_management.exe

Run on Linux/macOS:
  ./waste_management

IMPORTANT
---------
Run the program from the project folder so it can find the "data" directory.
The data files are created automatically when records are saved.
Use dates in YYYY-MM-DD format.
Storage units are category-specific: wet waste goes into a wet unit, etc.
A waste record can only be added if its matching storage unit exists and has enough capacity.
Collection records reduce the quantity stored in that unit.

FIRST-TIME TEST
---------------
1. Choose Storage Management > Add storage unit.
2. Add one unit for wet, one for dry, and one for hazardous waste.
3. Choose Waste Classification > Add waste record.
4. Enter a category, quantity, date and matching storage ID.
5. View storage units to see updated capacity.
6. Record a collection to reduce stored quantity.
7. Open Reports and Alerts to see summaries and warnings.

LIMITATIONS
-----------
- This is a basic academic prototype, not an industrial safety system.
- Dates are entered manually; there is no automatic calendar validation.
- Alerts are based on 90% capacity utilization.
- Overflow prediction and maintenance tracking are left as future scope.
