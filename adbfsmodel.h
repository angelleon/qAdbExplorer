#ifndef ADBFSMODEL_H
#define ADBFSMODEL_H

#include <QAbstractItemModel>
#include <QStringList>

#include "adbfsitem.h"

class AdbFsModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit AdbFsModel(const QStringList devices, QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
    AdbFsItem *adbFs;
};

#endif // ADBFSMODEL_H
