#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QWidget>
#include <vector>
#include "AStar.h"

class MapView : public QWidget
{
    Q_OBJECT
public:
    explicit MapView(QWidget *parent = 0);
    void setMap(const std::vector<std::vector<Point>> &map);

    void setPath(const std::list<ANode> path);
    QSize sizeHint() const;
    QSize minimumSizeHint() const;
protected:
    void paintEvent(QPaintEvent *event);
signals:

public slots:
private:
    void drawWall(int x,int y,QPainter &painter);
    void drawBackground(int x,int y,int deep,QPainter &painter);
    void drawPath(int x,int y,int deep,QPainter &painter);
    void drawStart(int x,int y,QPainter &painter);
    void drawEnd(int x,int y,QPainter &painter);

    std::vector<std::vector<Point>> mMap;
    std::list<ANode> mPath;
    int mPeerWidth;
};

#endif // MAPVIEW_H
