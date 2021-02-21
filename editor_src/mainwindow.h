#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "layoutitem.h"
#include "gamemapgrid.h"
#include <QFileDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
      //void on_botonArriba_clicked();
      //void on_botonAbajo_clicked();

      void on_wallList_currentIndexChanged(int index);
      void on_actionNew_triggered();
      void on_actionOpen_triggered();
      //void on_actionSave_triggered();
      void on_actionSaveAs_triggered();


private:
    Ui::MainWindow *ui;
    std::vector<std::vector<int>> map;
    AppStatus appStatus;
    void openFile();
    void saveFile();
    void newFile();
    //void mousePressEvent(QMouseEvent *event);
};
#endif // MAINWINDOW_H
