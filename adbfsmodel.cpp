#include "adbfsmodel.h"

AdbFsModel::AdbFsModel(const QStringList devices, QObject *parent)
    : QAbstractItemModel(parent)
{
    adbFs = new AdbFsItem(AdbFsData("RootNode", "/"), nullptr);
}

QVariant AdbFsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        auto d = adbFs->data(section);
        qDebug() << "Returning header data from model: " << d;
        return d;
    }
    return QVariant();
}

QModelIndex AdbFsModel::index(int row, int column, const QModelIndex &parent) const
{
    qDebug() << "Returning index from " << row << ", " << column << ", "<< parent;
    if (!hasIndex(row, column, parent)) {
        qDebug() << "Model does not have index " << row << ", " << column;
        return QModelIndex();
    }
    AdbFsItem *parentItem;

    if (!parent.isValid())
        parentItem = adbFs;
    else
        parentItem = static_cast<AdbFsItem*>(parent.internalPointer());

    AdbFsItem *childItem = parentItem->child(row);
    if (childItem) {
        qDebug() << "Child found at " << row << ", " << column;
        return createIndex(row, column, childItem);
    }
    qDebug() << "Child not found at " << row << ", " << column;
    return QModelIndex();
}

QModelIndex AdbFsModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    AdbFsItem *childItem = static_cast<AdbFsItem*>(index.internalPointer());
    AdbFsItem *parentItem = childItem->parentItem();

    if (parentItem == adbFs)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int AdbFsModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;
    AdbFsItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = adbFs;
    else
        parentItem = static_cast<AdbFsItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int AdbFsModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    if (parent.isValid())
        return static_cast<AdbFsItem*>(parent.internalPointer())->columnCount();
    return adbFs->columnCount();
}

QVariant AdbFsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    AdbFsItem *item = static_cast<AdbFsItem*>(index.internalPointer());

    return item->data(index.column());
}

Qt::ItemFlags AdbFsModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index);
}
