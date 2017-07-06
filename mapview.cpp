#include "mapview.h"
#include <QPainter>
MapView::MapView(QWidget *parent) : QWidget(parent)
{
    mPeerWidth = 15;
}

void MapView::setMap(const std::vector<std::vector<Point> > &map)
{
    mMap = map;
    updateGeometry();
}

void MapView::setPath(const std::list<ANode> path)
{
    mPath = path;
}

void MapView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QBrush wallBrush(Qt::black,Qt::SolidPattern);
    for(int i = 0;i<mMap.size();i++){
        for(int j = 0;j<mMap.at(i).size();j++){
            Point e = mMap.at(i).at(j);
            if(e.type == PointType::WALL){
                drawWall(j,i,painter);
            }else if(e.type == PointType::NORMAL){
                int deep = 0;
                if(e.node != nullptr){
                    deep = e.node->G;
                }
                drawBackground(j,i,deep,painter);
            }
        }
    }
    for(ANode node:mPath){
        if(node == mPath.front()){
            drawStart(node.x,node.y,painter);
        }else if(node == mPath.back()){
            drawEnd(node.x,node.y,painter);
        }else{
            drawPath(node.x,node.y,node.G,painter);
        }
    }
}

QSize MapView::sizeHint() const
{
    int w = 100,h = 100;
    if(!mMap.empty()){
        h = mMap.size() * mPeerWidth;
        w = mMap.at(0).size() * mPeerWidth;
    }
    return QSize(w,h);
}

QSize MapView::minimumSizeHint() const
{
    return sizeHint();
}

void MapView::drawWall(int x, int y, QPainter &painter)
{
    QBrush wallBrush(Qt::black,Qt::SolidPattern);
    painter.setBrush(wallBrush);
    painter.setPen(Qt::black);
    painter.drawRect(x*mPeerWidth,y*mPeerWidth,mPeerWidth,mPeerWidth);
    painter.setPen(Qt::white);
    painter.drawText(x*mPeerWidth,y*mPeerWidth,mPeerWidth+1,mPeerWidth,Qt::AlignCenter,"W");
}

void MapView::drawBackground(int x, int y,int deep, QPainter &painter)
{
    QColor color;
    if(deep > 0){
        int R = 255;
        int G = 255;
        int B = 255 - 2549 / (deep + 10);
        color = QColor::fromRgb(R,G,B);
    }else{
        color = Qt::white;
    }
    QBrush backBrush(color,Qt::SolidPattern);
    painter.setBrush(backBrush);
    painter.setPen(Qt::black);
    painter.drawRect(x*mPeerWidth,y*mPeerWidth,mPeerWidth,mPeerWidth);
    if(deep > 0){
         painter.drawText(x*mPeerWidth,y*mPeerWidth,mPeerWidth+1,mPeerWidth,Qt::AlignCenter,QString::number(deep));
    }
}

void MapView::drawPath(int x, int y, int deep, QPainter &painter)
{
    QBrush brush(QColor(30,144,255),Qt::SolidPattern);
    painter.setBrush(brush);
    painter.setPen(Qt::black);
    painter.drawRect(x*mPeerWidth,y*mPeerWidth,mPeerWidth,mPeerWidth);
    painter.setPen(Qt::white);
    painter.drawText(x*mPeerWidth,y*mPeerWidth,mPeerWidth+1,mPeerWidth,Qt::AlignCenter,QString::number(deep));
}

void MapView::drawStart(int x, int y, QPainter &painter)
{
    QBrush wallBrush(Qt::green,Qt::SolidPattern);
    painter.setBrush(wallBrush);
    painter.setPen(Qt::black);
    painter.drawRect(x*mPeerWidth,y*mPeerWidth,mPeerWidth,mPeerWidth);
    painter.setPen(Qt::black);
    painter.drawText(x*mPeerWidth,y*mPeerWidth,mPeerWidth+1,mPeerWidth,Qt::AlignCenter,"S");
}

void MapView::drawEnd(int x, int y, QPainter &painter)
{
    QBrush wallBrush(Qt::red,Qt::SolidPattern);
    painter.setBrush(wallBrush);
    painter.setPen(Qt::black);
    painter.drawRect(x*mPeerWidth,y*mPeerWidth,mPeerWidth,mPeerWidth);
    painter.setPen(Qt::black);
    painter.drawText(x*mPeerWidth,y*mPeerWidth,mPeerWidth+1,mPeerWidth,Qt::AlignCenter,"E");
}
