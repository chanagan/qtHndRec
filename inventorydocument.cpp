#include "inventorydocument.h"

InventoryDocument::InventoryDocument()
{

}

void InventoryDocument::LoadInventory(QString currentPath)
{
    setCurrentDocPath(currentPath);
    LoadInventoryDocument();
}

void InventoryDocument::LoadInventoryDocument()
{
    QFile inputFile(getCurrentDocPath());
    if (inputFile.open(QIODevice::ReadOnly)) {
        QTextStream in(&inputFile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            allInventoryLines->append(line);
        }
        inputFile.close();
    }

    QMessageBox msgBox;
    msgBox.setText("This is the load inventory item: "+ getCurrentDocPath());
    msgBox.exec();
    allInventoryLines = new QStringList () ;
}

