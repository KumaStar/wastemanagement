#ifndef COLLECTION_H
#define COLLECTION_H

#include "StorageUnit.h"

class Collection {
public:
    void menu(StorageUnit& storage);

private:
    void recordCollection(StorageUnit& storage);
    void viewCollections() const;
    int nextId() const;
};

#endif
