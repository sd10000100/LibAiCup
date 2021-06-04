//
// Created by badru on 15.01.2020.
// Классы узла карты и поиска пути. Определение
// Описание алгоритма взято отсюда https://lsreg.ru/realizaciya-algoritma-poiska-a-na-c/

#include "AStar.h"

using namespace pathfind;

template<typename T>
double AStar<T>::getHeuristicPathLength(Vect2D from, Vect2D to)
{
    return fabs(from.x - to.x) + fabs(from.y - to.y);
}

template<typename T>
PathNode<T> AStar<T>::getPathNodeWithMinF(std::list<PathNode> list)
{
    PathNode minElem;
    double minVal = 10000;
    double minPath = 10000;

    for(PathNode &item : list)
    {
        double temp = item.estimateFullPathLength();
        if(temp<minVal)
        {
            minElem = item;
            minVal = temp;
        }
    }
    return minElem;
}

template<typename T>
std::vector<Point2D<T>> AStar<T>::getPathForNode(PathNode pathNode)
{
    //return pathNode.path;
    std::vector<Vect2D> result = {};
   PathNode* currentNode = &pathNode;
   while (currentNode->cameFrom!=nullptr)
   {
       result.push_back(currentNode->position);
       *currentNode =  *currentNode->cameFrom;
   }
   //result.push_back(currentNode->position);
   std::reverse(std::begin(result), std::end(result));
   return result;
}

template<typename T>
std::vector<PathNode<T>> AStar<T>::getNeighbours(PathNode currentPathNode, Vect2D goal,int sizeX, int sizeY, const double** field, bool isDiag)
{
    std::vector<PathNode> result ={};

    // Соседними точками являются соседние по стороне клетки.
    std::vector<Vect2D> neighbourPoints = {};

    int x = floor(currentPathNode.position.x);
    int y = floor(currentPathNode.position.y);
    neighbourPoints.push_back(Vect2D(x + 1, y));
    neighbourPoints.push_back(Vect2D(x - 1, y));
    neighbourPoints.push_back(Vect2D(x, y + 1));
    neighbourPoints.push_back(Vect2D(x, y - 1));

    if (isDiag){
        neighbourPoints.push_back(Vect2D(x + 1, y-1));
        neighbourPoints.push_back(Vect2D(x - 1, y-1));
        neighbourPoints.push_back(Vect2D(x+1, y + 1));
        neighbourPoints.push_back(Vect2D(x-1, y + 1));
    }

    for (Vect2D point : neighbourPoints)
    {
        // Проверяем, что не вышли за границы карты.
        if (point.x < 0 || point.x >= sizeX)
            continue;
        if (point.y < 0 || point.y >= sizeY)
            continue;
        PathNode neighbourNode;
        neighbourNode.position.x = point.x;
        neighbourNode.position.y = point.y;
       // neighbourNode.path =  currentPathNode.path;
        neighbourNode.cameFrom =std::make_shared<pathfind::PathNode<T>>(currentPathNode);
        //neighbourNode.path.push_back(Vect2D(currentPathNode.position.x, currentPathNode.position.y));
        neighbourNode.pathLengthFromStart = currentPathNode.pathLengthFromStart +1;
        neighbourNode.potential =  currentPathNode.potential + field[point.x][point.y];
        neighbourNode.heuristicEstimatePathLength = getHeuristicPathLength(neighbourNode.position, goal);
        result.push_back(neighbourNode);
    }
    return result;
}

//
template<typename T>
std::vector<Point2D<T>> AStar<T>::findPath(Vect2D from, Vect2D to, int sizeX, int sizeY,const double** field)
{
    // Шаг 1. Создается 2 списка вершин — ожидающие рассмотрения и уже рассмотренные. 
    // В ожидающие добавляется точка старта, список рассмотренных пока пуст.
    std::list<PathNode> idle = {};
    std::list<PathNode> visited = {};

    from.x = floor(from.x);
    from.y = floor(from.y);

    to.x = floor(to.x);
    to.y = floor(to.y);

    int width = sizeX;
    int height = sizeY;

    PathNode startNode = PathNode();
    //startNode.path = {};
    startNode.position = from;
    startNode.cameFrom = nullptr;// std::make_shared<pathfind::PathNode<T>>(startNode);
    startNode.pathLengthFromStart = 0;
    startNode.potential = field[from.x][from.y];
    startNode.heuristicEstimatePathLength = getHeuristicPathLength(from, to);
            
    idle.push_back(startNode);

    while (idle.size()> 0) {
        // Шаг 2. Для каждой точки рассчитывается F = G + H. G — расстояние от старта до точки, H — примерное расстояние от точки до цели
        // Шаг 3. Из списка точек на рассмотрение выбирается точка с наименьшим F
        PathNode currentNode = getPathNodeWithMinF(idle);
        if (floor(currentNode.position.x) == floor(to.x) && floor(currentNode.position.y) == floor(to.y)) {
            // Шаг 4. Если точка — цель, то мы нашли маршрут
            return getPathForNode(currentNode);
        }
        // Шаг 5. Переносим точку из списка ожидающих рассмотрения в список уже рассмотренных.

        idle.pop_front();
        visited.push_back(currentNode);

        // Шаг 6. Получаем список соседних точек
        auto neighs = getNeighbours(currentNode, to, width, height, field, false);
        for (auto neighbourNode : neighs) {
            // Шаг 7. Если соседняя точка уже находится в рассмотренных — пропускаем ее
            auto visitedNodeIter = std::find(visited.begin(), visited.end(), neighbourNode);
            if(visitedNodeIter!=visited.end())
                continue;
            auto idleNodeIter = std::find(idle.begin(), idle.end(), neighbourNode);
            // Шаг 8. Если соседней точки еще нет в списке на ожидание — добавляем ее туда
            if (idleNodeIter == idle.end())
                idle.push_back(neighbourNode);
            else if (idleNodeIter->pathLengthFromStart > neighbourNode.pathLengthFromStart )
            {
                // Шаг 9.Если же соседняя точка в списке на рассмотрение — 
                // проверяем, если пришли более коротким путем, заменяем предыдущиую точку и путь
                //idleNodeIter->path = neighbourNode.path;
                startNode.cameFrom = std::make_shared<pathfind::PathNode<T>>(neighbourNode);
                idleNodeIter->pathLengthFromStart = neighbourNode.pathLengthFromStart;
            }
        }

    }
    // Шаг 10. Если список точек на рассмотрение пуст, а до цели мы так и не дошли — значит маршрут не существует.
    return {};
}