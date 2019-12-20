#include "invstockitem.h"


int InvStockItem::getNsnIdx() const
{
    return nsnIdx;
}

InvStockItem::InvStockItem(QString nsnIn, int linIndex)
{

    nsn = nsnIn;
    nsnIdx = linIndex;
    hasSerialNums = false;
    dataFirstLine = 0;
    dataLineCount = 0;
}
