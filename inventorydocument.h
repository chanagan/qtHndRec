#ifndef INVENTORYDOCUMENT_H
#define INVENTORYDOCUMENT_H

#include <QtCore>
#include <QMessageBox>

class InventoryDocument
{
    QString currentDocPath;
    QString invDate;
    QString invNum;

    QStringList *allInventoryLines;
    int numOfLines;

    void LoadInventoryDocument();
    bool lineIsUsed(QString workString);

public:
    InventoryDocument();
    void LoadInventory(QString currentPath);

    int getNumOfLines() const {return numOfLines;}
    void setNumOfLines(int value) {
        numOfLines = value;
    }

    QString getCurrentDocPath() const {return currentDocPath;}
    void setCurrentDocPath(const QString &value) {
        currentDocPath = value;
    }

    QString getInvDate() const {return invDate;}
    void setInvDate(const QString &value) {
        invDate = value;
    }

    QString getInvNum() const {return  invNum;}
    void setInvNum(const QString &value) {
        invNum = value;
    }
};

#endif // INVENTORYDOCUMENT_H
