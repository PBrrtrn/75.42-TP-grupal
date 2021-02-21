#ifndef NEWMAPWINDOW_H
#define NEWMAPWINDOW_H

#include <QWidget>
#include <QLabel>
#include "Map.h"
#include <QPushButton>
#include <QLineEdit>

class NewMapWindow : public QWidget
{
    Q_OBJECT
public:
    explicit NewMapWindow(Map& map,QWidget *parent = nullptr);

private:
    Map& map;
    QLineEdit* heightEdit;
    QLineEdit* widthEdit;

private slots:
      void on_createNewMap_clicked();
      void on_cancelNewMap_clicked();

signals:
      void newMapCreated();

};

#endif // NEWMAPWINDOW_H
