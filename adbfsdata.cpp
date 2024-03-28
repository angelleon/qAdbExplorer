#include "adbfsdata.h"

AdbFsData::AdbFsData(QString name, QString path)
{
    data = QList<QVariant>();
    data << name;
    data << path;
}


qsizetype AdbFsData::count() const {
    return data.count();
}


qsizetype AdbFsData::size() const {
    return count();
}


QVariant AdbFsData::at(qsizetype i) const {
    return data.at(i);
}
