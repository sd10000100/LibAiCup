//
// Created by badru on 15.01.2020.
// Классы узла карты и поиска пути. Определение
// Описание алгоритма взято отсюда https://lsreg.ru/realizaciya-algoritma-poiska-a-na-c/

#include "AStar.h"

using namespace pathfind;

double AStar::getHeuristicPathLength(std::tuple<int, int> from, std::tuple<int, int> to)
{
    return fabs(std::get<0>(from) - std::get<0>(to)) + fabs(std::get<1>(from) - std::get<1>(to));
}

PathNode AStar::getPathNodeWithMinF(std::list<PathNode> list)
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

std::vector<std::tuple<int, int>> AStar::getPathForNode(PathNode pathNode)
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

std::vector<PathNode> AStar::getNeighbours(PathNode currentPathNode, Vect2D goal,int sizeX, int sizeY, const double** field, bool isDiag)
{
    std::vector<PathNode> result ={};

    // Соседними точками являются соседние по стороне клетки.
    std::vector<Vect2D> neighbourPoints = {};

    int x = floor(std::get<0>(currentPathNode.position));
    int y = floor(std::get<1>(currentPathNode.position));
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
        if (std::get<0>(point) < 0 || std::get<0>(point) >= sizeX)
            continue;
        if (std::get<1>(point) < 0 || std::get<1>(point) >= sizeY)
            continue;
        PathNode neighbourNode;
        neighbourNode.position = point;
        neighbourNode.cameFrom = std::make_shared<pathfind::PathNode>(currentPathNode);
        neighbourNode.pathLengthFromStart = currentPathNode.pathLengthFromStart +1;
        neighbourNode.potential =  currentPathNode.potential + field[std::get<0>(point)][std::get<1>(point)];
        neighbourNode.heuristicEstimatePathLength = getHeuristicPathLength(neighbourNode.position, goal);
        result.push_back(neighbourNode);
    }
    return result;
}

std::vector<std::tuple<int, int>> AStar::findPath(Vect2D from, Vect2D to, int sizeX, int sizeY,const double** field)
{
    // Шаг 1. Создается 2 списка вершин — ожидающие рассмотрения и уже рассмотренные. 
    // В ожидающие добавляется точка старта, список рассмотренных пока пуст.
    std::list<PathNode> idle = {};
    std::list<PathNode> visited = {};

    from = std::make_tuple(floor(std::get<0>(from)), floor(std::get<1>(from)));
    to = std::make_tuple(floor(std::get<0>(to)), floor(std::get<1>(to)));

    int width = sizeX;
    int height = sizeY;

    PathNode startNode = PathNode();
    startNode.cameFrom = nullptr;
    startNode.position = from;
    startNode.pathLengthFromStart = 0;
    startNode.potential = field[std::get<0>(from)][std::get<1>(from)];
    startNode.heuristicEstimatePathLength = getHeuristicPathLength(from, to);
            
    idle.push_back(startNode);

    while (idle.size()> 0) {
        // Шаг 2. Для каждой точки рассчитывается F = G + H. G — расстояние от старта до точки, H — примерное расстояние от точки до цели
        // Шаг 3. Из списка точек на рассмотрение выбирается точка с наименьшим F
        PathNode currentNode = getPathNodeWithMinF(idle);
        if (floor(std::get<0>(currentNode.position)) == floor(std::get<0>(to)) && floor(std::get<1>(currentNode.position)) == floor(std::get<1>(to))) {
            // Шаг 4. Если точка — цель, то мы нашли маршрут
            return getPathForNode(currentNode);
        }
        // Шаг 5. Переносим точку из списка ожидающих рассмотрения в список уже рассмотренных.

        idle.pop_front();
        visited.push_back(currentNode);

        // Шаг 6. Получаем список соседних точек
        auto neighs = getNeighbours(currentNode, to, width, height, field, true);
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
                idleNodeIter->cameFrom = std::make_shared<pathfind::PathNode>(neighbourNode);
                idleNodeIter->pathLengthFromStart = neighbourNode.pathLengthFromStart;
            }
        }

    }
    // Шаг 10. Если список точек на рассмотрение пуст, а до цели мы так и не дошли — значит маршрут не существует.
    return {};
}