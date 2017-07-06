#ifndef ASTAR_H
#define ASTAR_H
#include <cmath>
#include <list>
#include <vector>
#include <functional>

#define COST 1

enum PointType {
    START,//起点
    WALL,//障碍
    END,//终点
    NORMAL
};

struct ANode
{
    int x, y;
    int F, G, H; //F总代价 G到起点的代价 H到目标点的代价
    ANode *parent;

    ANode(const ANode &other) {
        this->x = other.x;
        this->y = other.y;
        this->F = other.F;
        this->G = other.G;
        this->H = other.H;
        parent = nullptr;
    }

    ANode(ANode &&other) {
        if (this != &other) {
            this->x = other.x;
            this->y = other.y;
            this->F = other.F;
            this->G = other.G;
            this->H = other.H;
            parent = nullptr;
            other.parent = nullptr;
        }
    }

    ANode(int x, int y, ANode *parent = nullptr) {
        this->x = x;
        this->y = y;
        this->parent = parent;
        F = 0;
        G = 0;
        H = 0;
    }

    ANode& operator=(const ANode &other){
        this->x = other.x;
        this->y = other.y;
        this->F = other.F;
        this->G = other.G;
        this->H = other.H;
        parent = nullptr;
    }

    bool operator==(const ANode &other) {
        return (other.x == x && other.y == y);
    }

    bool operator<(const ANode &other) {
        return F < other.F;
    }
};

struct Point {
    PointType type;
    ANode *node;

    Point(PointType type) {
        this->type = type;
        this->node = new ANode(-1, -1);
    }

    Point(const Point &other) {
        this->type = other.type;
        this->node = new ANode(*other.node);
    }

    Point(Point &&other) {
        if (this != &other) {
            this->type = other.type;
            this->node = other.node;
            other.node = nullptr;
        }
    }

    ~Point() {
        if (node != nullptr) {
            delete node;
            node = nullptr;
        }
    }

    Point& operator=(const Point &other){
        this->type = other.type;
        this->node = other.node;
        this->node = new ANode(*other.node);
    }
};

class AStar {
public:
    typedef std::function<void(std::vector<std::vector<Point *> > *)> CallBack;

    AStar(std::vector<std::vector<int>> &map);
    ~AStar();
    std::list<ANode> findPath(int startX, int startY, int endX, int endY);
    std::vector<std::vector<Point>> dumpMap();

    void setCallBack(const CallBack &call);
private:
    ANode *findPath(ANode *start, ANode *end);


    int calcG(ANode *node);
    int calcH(ANode *node, ANode *end);
    int calcF(ANode *node);
    ANode *getLeastFNode();
    bool isInOpenList(ANode* node);
    bool isInCloseList(ANode* node);
    void addSurroundNodeToOpenList(ANode *node);
    void realse();

    std::list<ANode *> mOpenList;
    std::list<ANode *> mCloseList;
    std::vector<std::vector<int>> mMap;
    std::vector<std::vector<Point *>> mAstarMap;

    ANode *mEnd;
    CallBack mCallBack;
};

#endif //ASTAR_H
