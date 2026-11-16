#ifndef STORAGEUNIT_H
#define STORAGEUNIT_H

#include <string>

class StorageUnit {
public:
    void menu();
    bool addQuantity(int id, const std::string& category, double quantity);
    bool removeQuantity(int id, double quantity);

private:
    void addUnit();
    void viewUnits() const;
    void updateCapacity();
    int findUnit(int id, std::string& category, double& capacity, double& current) const;
};

#endif
