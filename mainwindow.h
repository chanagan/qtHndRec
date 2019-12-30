#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QTextBrowser>
#include <QTimer>
#include <QMenuBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QTime>
#include <QPointer>
#include <QColorDialog>
#include <QSignalMapper>
#include <QMap>
#include <QSplitter>
#include <QToolBar>
#include <QMutex>
#include <QDragEnterEvent>
#include <QMimeData>

#include "getstartedwidget.h"

#include "inventorydocument.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initUi();

private slots:
    void on_actionLoad_Inventory_triggered();
    void on_actionOpen_triggered();
    void on_action_Save_triggered();
    void on_action_New_triggered();
    void on_actionClose_triggered();

    //    void on_findButton_clicked();

private:
//    Ui::MainWindow *ui;
    InventoryDocument *inventoryDocument;
//    void loadTextFile();
    GetStartedWidget *getStartedWidget;
    QStackedWidget *mainWidget;

};

#endif // MAINWINDOW_H
