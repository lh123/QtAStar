#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <list>
#include <vector>

class MapView;
class Point;
class ANode;
class AStar;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    void onMapUpdate(std::vector<std::vector<Point *>> *map);
    void onPathSolved();

private:
    void aStarThread();
    std::list<ANode> mPath;
    std::vector<std::vector<Point>> mMap;
    MapView *mView;
    AStar *mStar;
};

#endif // MAINWINDOW_H
