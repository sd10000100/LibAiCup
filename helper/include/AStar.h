//**************************************
// Written for Russian Ai Cups with love 
// for horses and pain in the knees
// by sd10000100 on 15.01.2020.
//
// А* поиск пути
//**************************************

// TODO: схлопнуть в один файл для всяких других конкурсов

#pragma once

#include <vector>
#include <cmath>
#include <list>
#include <memory>
#include <algorithm>

namespace pathfind
{
    // Узел на карте поиска пути
    template<typename T>
    struct PathNode
    {
        using Vect2D = std::tuple<T, T>;
        // Координаты точки на карте.
        Vect2D position;
        // Длина пути от старта (G).
        double pathLengthFromStart=10000;
        // Точка, из которой пришли в эту точку.
        std::shared_ptr<PathNode<T>> cameFrom;
        // Примерное расстояние до цели (H).
        double heuristicEstimatePathLength= 0;
        // Вес на данной точке (на взвешенной карте)
        double potential = 0; 
        // Ожидаемое полное расстояние до цели (F).
        double estimateFullPathLength() {
            return  this->potential + this->heuristicEstimatePathLength;
        }
        const double estimateFullPathLength() const {
            return this->potential + this->heuristicEstimatePathLength;
        }

        bool operator < (const PathNode &node) const
        {
            return estimateFullPathLength()<node.estimateFullPathLength();
        }

        bool operator == (const PathNode<T> &node)
        {
            return floor(std::get<0>(position)) == floor(std::get<0>(node.position)) && floor(std::get<1>(position)) == floor(std::get<1>(node.position));
        }
    };

    // Класс поиска пути
    template<typename T>
    class AStar {
    public :
        using Vect2D = std::tuple<T, T>;
        using PathNode = PathNode<T>;
        AStar(){};
        // Получить примерное расстояние (H) от точки до цели
        // from - точка, от которой вычисляется расстояние
        // to - целевая точка
        // Result - примерное расстояние (H) от точки до цели
        double getHeuristicPathLength(Vect2D from, Vect2D to);

        // Получить узел с минимальным ожидаемым расстоянием до цели (F)
        // pathNodes - список узлов, в котором производится поиск
        // Result - узел с минимальным ожидаемым расстоянием до цели (F)
        PathNode getPathNodeWithMinF(std::list<PathNode> pathNodes);

        // Получить полный путь до узла
        // pathNode - узел, от которого вычисляется пути по карте
        // Result - полный путь до узла
        // TODO: нужно ли брать в методы класса?
        std::vector<Vect2D> getPathForNode(PathNode pathNode);

        // Получить соседние узлы для текущего узла
        // currentPathNode - текущий узел
        // goal - целевая точка
        // sizeX, sizeY - размеры карты - ширина и высота
        // field - матрица на которой вычисляется поиск пути (потенциальное поле или карта влияния)
        // isDiagonalAllowed - true: поиск соседних узлов будет происходить так же по диагональным клеткам
        // Result - список соседних узлов для текущего узла
        std::vector<PathNode> getNeighbours(PathNode currentPathNode, Vect2D goal,int sizeX, int sizeY, const double** field, bool isDiagonalAllowed);

        // Получить полный путь до точки. Если такого не существует - возвращается пустой список
        // from - точка начала поиска
        // to - целевая точка
        // sizeX, sizeY - размеры карты - ширина и высота
        // field - матрица на которой вычисляется поиск пути (потенциальное поле или карта влияния)
        // Result - список точек, представляющий собой самый оптимальный путь
        std::vector<Vect2D> findPath(Vect2D from, Vect2D to, int sizeX, int sizeY,const double** field);
    };
}
