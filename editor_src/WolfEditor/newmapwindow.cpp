#include "newmapwindow.h"

NewMapWindow::NewMapWindow(int& height,int& width,int& minPlayers,int& maxPlayers,QWidget *parent) : QWidget(parent),map(map),mapHeight(height),mapWidth(width),mapMinPlayers(minPlayers),mapMaxPlayers(maxPlayers)
{

    QLabel *heightLabel;
    heightLabel = new QLabel(this);
    heightLabel->setObjectName(QString::fromUtf8("heightLabel"));
    heightLabel->setGeometry(QRect(50, 10, 89, 25));
    heightLabel->setText("Altura");

    QLabel *widthLabel;
    widthLabel = new QLabel(this);
    widthLabel->setObjectName(QString::fromUtf8("widthLabel"));
    widthLabel->setGeometry(QRect(139, 10, 89, 25));
    widthLabel->setText("Ancho");

    this->heightEdit = new QLineEdit(this);
    heightEdit->setObjectName(QString::fromUtf8("heightEdit"));
    heightEdit->setGeometry(QRect(50, 30, 63, 25));

    this->widthEdit = new QLineEdit(this);
    widthEdit->setObjectName(QString::fromUtf8("widthEdit"));
    widthEdit->setGeometry(QRect(139, 30, 63, 25));

    QPushButton* createNewMap = new QPushButton(this);
    createNewMap->setObjectName(QString::fromUtf8("createNewMap"));
    createNewMap->setGeometry(QRect(50, 60, 89, 25));
    QPushButton* cancelNewMap = new QPushButton(this);
    cancelNewMap->setObjectName(QString::fromUtf8("cancelNewMap"));
    cancelNewMap->setGeometry(QRect(159, 60, 89, 25));

    createNewMap->setText("Create");
    cancelNewMap->setText("Cancel");

    heightLabel->raise();
    widthLabel->raise();
    createNewMap->raise();
    cancelNewMap->raise();

    this->setWindowFlags(Qt::Window);
    this->resize(139*2 + 50,100);
    this->setWindowTitle("New Map");

    QObject::connect(cancelNewMap, SIGNAL(clicked()), this, SLOT(on_cancelNewMap_clicked()));
    QObject::connect(createNewMap, SIGNAL(clicked()), this, SLOT(on_createNewMap_clicked()));

}

void NewMapWindow::on_createNewMap_clicked(){


    this->mapHeight = std::stoi(this->heightEdit->text().toUtf8().constData());
    this->mapWidth = std::stoi(this->widthEdit->text().toUtf8().constData());
    this->mapMinPlayers = 2;
    this->mapMaxPlayers = 16;
    emit this->newMapCreated();
    this->close();

}
void NewMapWindow::on_cancelNewMap_clicked(){
    this->close();

}

