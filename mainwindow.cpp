#include "mainwindow.h"
#include "mapview.h"
#include "astarmap.h"
#include "AStar.h"
#include <thread>
#include <QDebug>
#include <QLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mView = new MapView(this);
    mStar = new AStar(map);
    setCentralWidget(mView);
    layout()->setSizeConstraint(QLayout::SetFixedSize);
    connect(this,&MainWindow::onPathSolved,this,[this](){
        mView->setPath(mPath);
        mView->setMap(mMap);
        mView->update();
    });
    std::thread *astarThread = new std::thread(&MainWindow::aStarThread,this);
    astarThread->detach();

}

MainWindow::~MainWindow()
{
    delete mStar;
}

void MainWindow::aStarThread()
{
//    mPath = mStar->findPath(2,17,42,17); //map1
    mPath = mStar->findPath(3,7,11,7);
    mMap = mStar->dumpMap();
    emit onPathSolved();
}
