#include "AStar.h"
#include <cmath>

AStar::AStar(std::vector<std::vector<int>>& map)
{
    mCallBack = nullptr;
    mMap = map;
    for (int i = 0; i<mMap.size(); i++) {
        std::vector<Point *> v;
        for (int j = 0; j<mMap.at(i).size(); j++) {
            int value = mMap.at(i).at(j);
            PointType type = value == 0 ? PointType::NORMAL : PointType::WALL;
            Point *p = new Point(type);
            v.push_back(p);
        }
        mAstarMap.push_back(std::move(v));
    }
}

AStar::~AStar()
{
    realse();
}

std::list<ANode> AStar::findPath(int startX, int startY, int endX, int endY)
{
    ANode *start = mAstarMap[startY][startX]->node;
    mEnd = mAstarMap[endY][endX]->node;
    start->x = startX;
    start->y = startY;

    mEnd->x = endX;
    mEnd->y = endY;
    ANode *ret = findPath(start, mEnd);
    std::list<ANode> path;
    while (ret != nullptr) {
        path.push_front(ANode(*ret));
        ret = ret->parent;
    }
    return path;
}

std::vector<std::vector<Point>> AStar::dumpMap()
{
    std::vector<std::vector<Point>> map;
    for (auto row : mAstarMap) {
        std::vector<Point> crow;
        for (auto p : row) {
            crow.push_back(Point(*p));
        }
        map.push_back(std::move(crow));
    }
    return map;
}

void AStar::setCallBack(const CallBack & call)
{
    this->mCallBack = call;
}

ANode *AStar::findPath(ANode *start, ANode *end)
{
    mOpenList.clear();
    mCloseList.clear();
    mOpenList.push_back(start);
    while (!mOpenList.empty()) {
        ANode *currentNode = getLeastFNode();
        mOpenList.remove(currentNode);
        mCloseList.push_back(currentNode);

        addSurroundNodeToOpenList(currentNode);

        if (mCallBack != nullptr) {
            mCallBack(&mAstarMap);
        }
        if (isInOpenList(end)) {
            return end;
        }
    }
    return nullptr;
}

int AStar::calcG(ANode *node)
{
    int extraG = COST;
    if (node->parent == nullptr) {
        return extraG;
    } else {
        return node->parent->G + extraG;
    }
}

int AStar::calcH(ANode *node, ANode *end)
{
    return abs(end->x - node->x) + abs(end->y - node->y);
}

int AStar::calcF(ANode *node)
{
    return node->G + node->H;
}

ANode *AStar::getLeastFNode()
{
    ANode *retNode = mOpenList.back();
    for (auto lit = mOpenList.rbegin(); lit != mOpenList.rend(); lit++) {
        if (**lit < *retNode) {
            retNode = *lit;
        }
    }
    return retNode;
}

bool AStar::isInOpenList(ANode *node)
{
    bool ret = false;
    for (ANode *tNode : mOpenList) {
        if (*node == *tNode) {
            ret = true;
            break;
        }
    }
    return ret;
}

bool AStar::isInCloseList(ANode *node)
{
    bool ret = false;
    for (ANode *tNode : mCloseList) {
        if (*node == *tNode) {
            ret = true;
            break;
        }
    }
    return ret;
}

void AStar::addSurroundNodeToOpenList(ANode *node)
{
    int x = node->x;
    int y = node->y;
    for (int i = y - 1; i <= y + 1; i++) {
        for (int j = x - 1; j <= x + 1; j++) {
            if (i >= 0 && i < mAstarMap.size() && j >= 0 && j < mAstarMap.at(i).size() && abs(j - x) != abs(i - y)) {
                Point *p = mAstarMap[i][j];
                if (p->type == PointType::WALL) {
                    continue;
                }
                ANode *tnode = p->node;

                if (tnode->x < 0 || tnode->y < -1) {//初始化节点
                    tnode->x = j;
                    tnode->y = i;
                }
                if (!isInCloseList(tnode)) {
                    if (!isInOpenList(tnode)) {
                        tnode->parent = node;
                        int G = calcG(tnode);
                        tnode->G = G;
                        int H = calcH(tnode, mEnd);
                        tnode->H = H;
                        int F = calcF(tnode);
                        tnode->F = F;

                        mOpenList.push_back(tnode);
                    } else {
                        if (tnode->G > node->G + COST) {
                            tnode->parent = node;
                            int G = calcG(tnode);
                            tnode->G = G;
                            int H = calcH(tnode, mEnd);
                            tnode->H = H;
                            int F = calcF(tnode);
                            tnode->F = F;
                        }
                    }
                }
            }
        }
    }
}

void AStar::realse()
{
    for (auto lit = mAstarMap.begin(); lit != mAstarMap.end(); lit++) {
        std::vector<Point *> v = *lit;
        for (auto lit2 = v.begin(); lit2 != v.end(); lit2++) {
            delete *lit2;
        }
        v.clear();
    }
    mAstarMap.clear();
    mOpenList.clear();
    mCloseList.clear();
    mEnd = nullptr;
}
