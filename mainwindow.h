#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionLoad_Inventory_triggered();
    void on_actionOpen_triggered();
    void on_action_Save_triggered();
    void on_action_New_triggered();
    void on_actionClose_triggered();

    //    void on_findButton_clicked();

private:
    Ui::MainWindow *ui;
//    void loadTextFile();
};

#endif // MAINWINDOW_H
