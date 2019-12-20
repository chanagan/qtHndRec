#include "invstockitem.h"


InvStockItem::InvStockItem(QString nsnIn, int linIndex)
{

    nsn = nsnIn;
    nsnIdx = linIndex;
    hasSerialNums = false;
    dataFirstLine = 0;
    dataLineCount = 0;
}
