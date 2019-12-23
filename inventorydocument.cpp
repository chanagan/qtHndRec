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
    LoadInventorySerials();
}

void InventoryDocument::LoadInventoryDocument()
{
    InvStockItem *invStockItem;
    int lineIndex;

    QString fileName = getCurrentDocPath();
    QFile inputFile(fileName);
    QStringList lineFields;
    QMessageBox msgBox;

    lineIndex = 0;

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
//        tmpLine = allInventoryLines->at(linesIndex);

        // first, back up until hit (LIN)
        itemDone = false;
        do {
            // keep track of how many fields we've filled for this item
            // already have NSN
            linesIndex--;
            // first, don't go back beyond the first line
            if (linesIndex > numOfLines) {
                itemDone = true;
                continue;
            }
            // split the fields out to get the key field
            tmpLine = allInventoryLines->at(linesIndex);
            lineFields = tmpLine.split(' ');

            // if we backed up to this, we're near the beginning
            if (lineFields[0] == "(LIN)") {
                tmpStockItem->setLin(lineFields[1]);
                fldCount++;
                itemDone = true;
                continue;
            }
            if (linesIndex == lastItemHighLine) {
                itemDone = true;
                continue;
            }
            if (lineFields[0] == "(QTY)") {
                tmpStockItem->setQuantity(lineFields[1]);
                fldCount++;
                continue;
            }
            if (lineFields[0] == "(NOM)") {
                tmpStockItem->setNomen(tmpLine.mid(6));
                fldCount++;
                continue;
            }
            if (lineFields[0] == "(MPO)") {
                tmpStockItem->setMpo(lineFields[1]);
                fldCount++;
                continue;
            }
        } while (! itemDone);

        linesIndex = tmpStockItem->getNsnIdx();

        // if we don't have enough fields yet,
        // now go forward to find the rest of the fields
        if (fldCount < fldCountReq) {
            do {
                linesIndex++;
                // first, don't go beyond the last line
                if (linesIndex > numOfLines) {
                    itemDone = true;
                    break;
                }
                // split the fields out to get the key field
                tmpLine = allInventoryLines->at(linesIndex);
                lineFields = tmpLine.split(' ');

                if (lineFields[0] == "(QTY)") {
                    tmpStockItem->setQuantity(lineFields[1]);
                    fldCount++;
                    continue;
                }
                if (lineFields[0] == "(NOM)") {
                    tmpStockItem->setNomen(tmpLine.mid(6));
                    fldCount++;
                    continue;
                }
                if (lineFields[0] == "(MPO)") {
                    tmpStockItem->setMpo(lineFields[1]);
                    fldCount++;
                    continue;
                }
                if (lineFields[0] == "(LIN)") {
                    tmpStockItem->setLin(lineFields[1]);
                    fldCount++;
                    continue;
                }
            } while (fldCount < fldCountReq);
        }
        lastItemHighLine = linesIndex;
        linesIndex = tmpStockItem->getNsnIdx();
    }
}

void InventoryDocument::LoadInventorySerials()
{
    bool itemDone;
    int nsnCount = nsnList.count();
    int numOfLines = getNumOfLines();

    int lastItemHighLine = 0;
    InvStockItem* tmpStockItem;
    QString tmpLine;
    QStringList lineFields;

    // loop through al the stock items (NSNs)
    for (int i = 0; i < numOfLines; i++) {
        int tmpStockItemIndex;
        int linesIndex;

        tmpLine = allInventoryLines->at(i);
        lineFields = tmpLine.split(' ');

        // look for the 'Serial / Equipment' line
        // it will have > 0 (DATA) lines sometime after
        //   with serial numbers
        if (lineFields[0] == "Serial") {
            int serialLineLocation;

            // store this line location
            serialLineLocation = i;
            tmpStockItemIndex = 0;
            do {
                i++;
                tmpLine = allInventoryLines->at(i);
                lineFields = tmpLine.split(' ');
                if (lineFields[0] == "(MATNR)") {
                    tmpStockItemIndex = FindStockItem(i);
                    tmpStockItem = nsnList.at(tmpStockItemIndex);
                    // let it know it has serial numbers
                    tmpStockItem->setHasSerialNums(true);
                }
            } while (tmpStockItemIndex == 0);

            // at this point, we have the stock item for this
            //  set of serial numbers;

            // so go back to the 'Serial . .' line
            i = serialLineLocation;

            // we're here because this stock item has serial numbers
            // the line(s) start with (DATA) and have > 0 ';' separated serials
            QString tmpString;
            bool done = false;
            do {
                i++;
                tmpLine = allInventoryLines->at(i);
                tmpString = tmpLine.left(6);
                if (tmpString == "(DATA)") {
                    int dataLineCount = 0;
                    // set the first line of DATA for this item
                    tmpStockItem->setDataFirstLine(i);
                    tmpString = tmpLine.mid(7);
                    lineFields = tmpString.split(';');
                    dataLineCount++;

                    while (! done) {
                        i++;
                        tmpLine = allInventoryLines->at(i);
                        tmpString = tmpLine.left(6);
                        if (tmpString == "(DATA)") {
                            tmpString = tmpLine.mid(7);
                            lineFields = tmpString.split(';');
                            dataLineCount++;
                        } else {
                            // this line is not part of what we want
                            //  so back off this line in case it's
                            //  part of the next one
                            i--;
                            tmpStockItem->setDataLineCount(dataLineCount);
                            done = true;
                        }
                    } // (! done)
                } //  (tmpString == "(DATA)")

            } while (! done);
            continue;
        } // (lineFields[0] == "Serial")
    } // (int i = 0; i < numOfLines; i++)
}

int InventoryDocument::FindStockItem(int lineNum)
{
    InvStockItem *tmpStockItem;
    int nsnCount;

    nsnCount = nsnList.size();

    for (int i = 0; i < nsnCount; i++) {
        tmpStockItem = nsnList.at(i);
        if (tmpStockItem->getNsnIdx() == lineNum) {
            return i;
        }
    }

    return 0;
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

