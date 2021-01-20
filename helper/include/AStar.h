//
// Created by badru on 15.01.2020.
//

#ifndef LIBAICUP_ASTAR_H
#define LIBAICUP_ASTAR_H

#include "vector"
#include <cmath>
#include <list>
#include <algorithm>
#include "InfluenceMapBuilder.h"

// A*
template<typename T>
struct PathNode
{
    using Vect2D = Point2D<T>;
    // Координаты точки на карте.
    Vect2D Position;
    // Длина пути от старта (G).
    double PathLengthFromStart=10000;
    // Точка, из которой пришли в эту точку.
    PathNode<T>* CameFrom;
    // Примерное расстояние до цели (H).
    double HeuristicEstimatePathLength;
    double potential = 0; 

    std::vector<Vect2D> path = {};
    // Ожидаемое полное расстояние до цели (F).
    double EstimateFullPathLength() {
        return  potential;//this->PathLengthFromStart+ this->HeuristicEstimatePathLength
    }

    const double EstimateFullPathLengthConst() const {
        return potential;//this->PathLengthFromStart + + this->HeuristicEstimatePathLength 
    }

    bool operator < (const PathNode &node) const
    {
        return EstimateFullPathLengthConst()<node.EstimateFullPathLengthConst();
    }

    bool operator == (const PathNode<T> &node)
    {
        return floor(Position.x) == floor(node.Position.x) && floor(Position.y) == floor(node.Position.y);
    }
};

template<typename T>
class AStar {
public :
    using Vect2D = Point2D<T>;
    using PathNode = PathNode<T>;
    AStar(){};

    bool isPointInUnit(const Vect2D point, const Vect2D unitPosition, const Vect2D unitSize);

    double GetHeuristicPathLength(Vect2D from, Vect2D to);

    PathNode GetMinF(std::list<PathNode> list);

    std::vector<Vect2D> GetPathForNode(PathNode pathNode);

    std::vector<PathNode> GetNeighbours(PathNode pathNode, Vect2D goal,int sizeX, int sizeY, double** matr);//, const Game &game, const Unit &currentUnit

    std::vector<Vect2D> FindPath(Vect2D from, Vect2D to, int sizeX, int sizeY,double** matr);//, const Game &game, const Unit &currentUnit
};

#endif //AICUP2019_ASTAR_H
