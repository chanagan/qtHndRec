#ifndef INVSTOCKITEM_H
#define INVSTOCKITEM_H

#include <QtCore>

class InvStockItem
{
    bool hasSerNums;
    int nsn_idx;
    int data_first_line;
    int data_line_count;

public:
    InvStockItem(QString nsn_in, int lin_idx);
};

#endif // INVSTOCKITEM_H
