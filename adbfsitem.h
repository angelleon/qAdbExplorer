#ifndef ADBFSITEM_H
#define ADBFSITEM_H

#include <QList>
#include <QVariant>

#include "adbfsdata.h"


class AdbFsItem
{
public:
    explicit AdbFsItem(const AdbFsData &data, AdbFsItem *parent=nullptr);
    ~AdbFsItem();

    AdbFsItem *child(int row);
    void appendChild(AdbFsItem *child);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    AdbFsItem *parentItem();

    enum ItemType {
        Device,
        Storage,
        Folder,
        File,
        Symlink,
        Node,
        Fifo
    };

    ItemType itemType() const;

private:
    QList<AdbFsItem *> children;
    AdbFsData itemData;
    AdbFsItem *parent;

};

#endif // ADBFSITEM_H
