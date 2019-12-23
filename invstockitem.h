#ifndef INVSTOCKITEM_H
#define INVSTOCKITEM_H

#include <QtCore>

class InvStockItem
{
    bool hasSerialNums;
    int nsnIdx;
    int dataFirstLine;
    int dataLineCount;

    QString lin;
    QString mpo;
    QString nomen;
    QString quantity;
    QString nsn;

public:
    InvStockItem(QString nsnIn, int lineIdx);
    int getNsnIdx() const;
    QString getLin() const;
    void setLin(const QString &value);
    QString getQuantity() const;
    void setQuantity(const QString &value);
    QString getNomen() const;
    void setNomen(const QString &value);
    QString getMpo() const;
    void setMpo(const QString &value);
    bool getHasSerialNums() const;
    void setHasSerialNums(bool value);
    int getDataFirstLine() const;
    void setDataFirstLine(int value);
    int getDataLineCount() const;
    void setDataLineCount(int value);
};

#endif // INVSTOCKITEM_H
