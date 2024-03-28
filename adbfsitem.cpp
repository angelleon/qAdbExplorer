#include "adbfsitem.h"

AdbFsItem::AdbFsItem(const AdbFsData &data, AdbFsItem *parent) : itemData(data)
{
    this->parent = parent;
}

AdbFsItem::~AdbFsItem() {
    qDeleteAll(children);
}

void AdbFsItem::appendChild(AdbFsItem *child) {
    children.append(child);
}


int AdbFsItem::childCount() const {
    return children.count();
}
int AdbFsItem::columnCount() const {
    return itemData.count();
}

QVariant AdbFsItem::data(int column) const {
    if (column < 0 || column >= itemData.size()) {
        return QVariant();
    }
    return itemData.at(column);
}

int AdbFsItem::row() const {
    if (!parent) {
        return 0;
    }
    return parent->children.indexOf(const_cast<AdbFsItem*>(this));
}

AdbFsItem *AdbFsItem::parentItem() {
    return parent;
}


AdbFsItem *AdbFsItem::child(int row) {
    if (row < 0 || row >= children.size()) {
        return nullptr;
    }
    return children.at(row);
}


AdbFsItem::ItemType AdbFsItem::itemType() const {
    return ItemType::Folder;
}
