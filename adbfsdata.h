#ifndef ADBFSDATA_H
#define ADBFSDATA_H

#include <QList>
#include <QVariant>

class AdbFsData
{
public:
    explicit AdbFsData(QString name, QString path);
    QList<QVariant> get();
    qsizetype count() const;
    qsizetype size() const;
    QVariant at(qsizetype i) const;

private:
    QList<QVariant> data;
};

#endif // ADBFSDATA_H
