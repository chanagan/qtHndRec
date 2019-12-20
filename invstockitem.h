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
};

#endif // INVSTOCKITEM_H
