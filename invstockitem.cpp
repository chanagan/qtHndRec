#include "invstockitem.h"


int InvStockItem::getNsnIdx() const
{
    return nsnIdx;
}

QString InvStockItem::getLin() const
{
    return lin;
}

void InvStockItem::setLin(const QString &value)
{
    lin = value;
}

QString InvStockItem::getQuantity() const
{
    return quantity;
}

void InvStockItem::setQuantity(const QString &value)
{
    quantity = value;
}

QString InvStockItem::getNomen() const
{
    return nomen;
}

void InvStockItem::setNomen(const QString &value)
{
    nomen = value;
}

QString InvStockItem::getMpo() const
{
    return mpo;
}

void InvStockItem::setMpo(const QString &value)
{
    mpo = value;
}

bool InvStockItem::getHasSerialNums() const
{
    return hasSerialNums;
}

void InvStockItem::setHasSerialNums(bool value)
{
    hasSerialNums = value;
}

int InvStockItem::getDataFirstLine() const
{
    return dataFirstLine;
}

void InvStockItem::setDataFirstLine(int value)
{
    dataFirstLine = value;
}

int InvStockItem::getDataLineCount() const
{
    return dataLineCount;
}

void InvStockItem::setDataLineCount(int value)
{
    dataLineCount = value;
}

InvStockItem::InvStockItem(QString nsnIn, int linIndex)
{
    
    nsn = nsnIn;
    nsnIdx = linIndex;
    hasSerialNums = false;
    dataFirstLine = 0;
    dataLineCount = 0;
}
