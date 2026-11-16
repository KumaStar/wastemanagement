#ifndef WASTE_H
#define WASTE_H

#include <string>
#include "StorageUnit.h"

class Waste {
public:
    void menu(StorageUnit& storage);

private:
    void addWaste(StorageUnit& storage);
    void viewWaste() const;
    void searchWaste() const;
    int nextId() const;
};

#endif
