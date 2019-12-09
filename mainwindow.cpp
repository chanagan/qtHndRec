#include "mainwindow.h"

#include "ui_mainwindow.h"

#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadTextFile();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLoad_Inventory_triggered()
{
    QMessageBox msgBox;
    QString fileName;

    fileName = QFileDialog::getOpenFileName(this,
                                            tr("Open Inventory"), ":/.", tr("Inv Files (*.txt)"));
    msgBox.setText("This is the load inventory item: "+ fileName);
    msgBox.exec();
}


//void MainWindow::on_findButton_clicked()
//{
////    QString searchString = ui->lineEdit->text();
////    ui->textEdit->find(searchString, QTextDocument::FindWholeWords);
//}

void MainWindow::loadTextFile()
{
//    QFile inputFile("/inv_latest_A.txt");
    QFile inputFile(":/input.txt");
    inputFile.open(QIODevice::ReadOnly);

    QTextStream in(&inputFile);
    QString line = in.readAll();
    inputFile.close();

    ui->textMain->setPlainText(line);
    QTextCursor cursor = ui->textMain->textCursor();
    cursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor, 1);


}

void MainWindow::on_actionOpen_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("Clicked Open");
    msgBox.exec();

}

void MainWindow::on_action_Save_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("Clicked on_action_Save_triggered");
    msgBox.exec();
}

void MainWindow::on_action_New_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("Clicked on_action_New_triggered");
    msgBox.exec();
}

void MainWindow::on_actionClose_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("Clicked on_actionClose_triggered");
    msgBox.exec();
}
