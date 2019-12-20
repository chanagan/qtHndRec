#include "inventorydocument.h"

InventoryDocument::InventoryDocument()
{

}

void InventoryDocument::LoadInventory(QString currentPath)
{
    allInventoryLines = new QStringList () ;

    setCurrentDocPath(currentPath);
    LoadInventoryDocument();
    LoadInventoryStock();
}

void InventoryDocument::LoadInventoryDocument()
{
    InvStockItem *invStockItem;
    int lineIndex = 0;

    QString fileName = getCurrentDocPath();
    QFile inputFile(fileName);
    QStringList lineFields;
    QMessageBox msgBox;

    if (inputFile.open(QIODevice::ReadOnly)) {
        QTextStream in(&inputFile);
        while (!in.atEnd()) {
            QString line = in.readLine();

            // check to see if we have any use for this line
            if (! lineIsUsed(line)) {
                continue;
            }

            // get some per/document data
            lineFields = line.split(' ');

            if (lineFields[0] == "(CurrentDate)") {
                setInvDate(lineFields[1]);
                continue;
            }
            if (lineFields[0] == "(Inv") {
                setInvNum(lineFields[3]);
                continue;
            }
            if (lineFields[0] == "(MATNR)") {
                msgBox.setText("Have record: " + line);
                invStockItem = new InvStockItem(lineFields[1], lineIndex);
                //TODO: make array of stock items
                nsnList.append(invStockItem);
//                msgBox.exec();

            }
            allInventoryLines->append(line);
            lineIndex++;
        }
        inputFile.close();
        setNumOfLines(allInventoryLines->size());
    }

    msgBox.setText("This is the load inventory item: "+ getCurrentDocPath());
    msgBox.exec();
}

void InventoryDocument::LoadInventoryStock()
{
    bool itemDone;
    int nsnCount = nsnList.count();
    int fldCountReq = 5;

    int lastItemHighLine = 0;
    InvStockItem* tmpStockItem;
    QString tmpLine;
    QStringList lineFields;

    // loop through all the stock items (NSNs)
    for (int i = 0; i < nsnCount; i++) {
        int fldCount = 1;
        int linesIndex;

        tmpStockItem = nsnList[i];
        linesIndex = tmpStockItem->getNsnIdx();
        tmpLine = allInventoryLines->at(linesIndex);

        itemDone = false;
    }
}

bool InventoryDocument::lineIsUsed(QString workString)
{
    if (workString.isEmpty()) {
        return false;
    }
    // don't need these lines, so bypass them
    if (workString.contains("(CHARG)")) {return false;}
    if (workString.contains("(UOM)")) {return false;}
    if (workString.contains("(CIIC)")) {return false;}
    if (workString.contains("SLOC:")) {return false;}
    if (workString.contains("REMARK :")) {return false;}
    if (workString.contains("ORIED QTY :")) {return false;}
    if (workString.contains("Filler_5")) {return false;}
    if (workString.contains("DISCREPANCIES")) {return false;}
    if (workString.contains("Signature")) {return false;}
    if (workString.contains("DODAAC")) {return false;}
    if (workString.contains("INDICATED ABOVE")) {return false;}
    if (workString.contains("UIC")) {return false;}

    if (workString.startsWith("Inv Doc")) {return false;}
    if (workString.startsWith("FE:") || workString.startsWith("(FE:")) {return false;}
    if (workString.startsWith("Date ")) {return false;}
    if (workString.startsWith("(Listing)")) {return false;}
    if (workString.startsWith("LGOBE")) {return false;}
    if (workString.startsWith("Date Pre")) {return false;}
    if (workString.startsWith("Page ")) {return false;}
    if (workString.startsWith("UIC:")) {return false;}
    if (workString.startsWith("\f")) {return false;}

    // none of the above elements, so go record
    return true;
}

