//
// Created by sd10000100 on 15.01.2020.
//
#ifndef LIBAICUP_GEOMETRY_H
#define LIBAICUP_GEOMETRY_H
#include "Vect2D.h"

// расстояние между 2-мя точками
template<typename T>
inline double distanceSqr(Vect2D<T> a, Vect2D<T> b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

// ориентированная площадь треугольника
// Исп-я понятие косого (псевдополяр) произвед векторов
// a ^ b = |a||b|sin(<(a,b))=2S
// угол вращения между векторами против часовой стрелки
// 2s=|x1 y1 1|
//    |x2 y2 1|=(x2-x1)(y3-y1)-(y2-y1)(x3-x1)
//    |x3 y3 1|
template<typename T>
double OrientedArea (Point2D<T> a, Point2D<T> b, Point2D<T> c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// проверка, что точки не лежат на одной плоскости
bool isPointNotOnSamePlane (double a, double b, double c, double d) {
    if (a > b) std::swap(a, b);
    if (c > d) std::swap(c, d);
    return std::max(a, c) <= std::min(b, d);
}

// Чтобы отрезки AB и CD пересекались, нид чтобы A и B находились
// по разные стороны от прямой CD и аналогично C и D по разные стороны от AB
// Нужно вычислить ориентированные площади треугольников и сравнить знаки
template<typename T>
bool intersect (Point2D<T> a, Point2D<T> b, Point2D<T> c, Point2D<T> d) {
    return isPointNotOnSamePlane (a.x, b.x, c.x, d.x)
           && isPointNotOnSamePlane (a.y, b.y, c.y, d.y)
           && OrientedArea(a,b,c) * OrientedArea(a,b,d) <= 0
           && OrientedArea(c,d,a) * OrientedArea(c,d,b) <= 0;
}



// проверка на нахождение точки внутри треугольника (подходит для выпуклых многоугольников)
// Проверяем каждую грань на пересечение с лучом из искомой точки (луч в рандомное место)
// Если кол-во перемещений кратно 2-м - точка не в многоугольнике
// инеаче - внутри
// Примеч: можно случайно попасть на стык ребер - решается выбором луча поизощреннее
template<typename T>
bool isPointInTriangle(Vect2D<T> p, Vect2D<T> p1, Vect2D<T> p2,Vect2D<T> p3){
    using Point2D = Point2D<T>;
    using Vect2D = Vect2D<T>;

    std::vector<Vect2D> stackEnges = {};
    int countIntersect = 0;
    stackEnges.push_back(Vect2D(Point2D(p1.x,p1.y),Point2D(p2.x,p2.y)));
    stackEnges.push_back(Vect2D(Point2D(p2.x,p2.y),Point2D(p3.x,p3.y)));
    stackEnges.push_back(Vect2D(Point2D(p3.x,p3.y),Point2D(p1.x,p1.y)));

    for(Vect2D item : stackEnges)
    {
        if(intersect (Point2D(p.x,p.y), Point2D(10000,1), item.start, item.finish))
            countIntersect++;
    }
    if(countIntersect%2==0)
        return false;
    else {
        return true;
    }
}

// вариативный шаблон для построения вектора из точек из списка аргументов
template <class Arg>
std::vector<Arg> GetArgsToArray(Arg first)
{
    return {first};
}

template <class T, class Arg, class... Other>
std::vector<Arg> GetArgsToArray(Arg first, Other... other)
{
    std::vector<Arg> res = {first};
    std::vector<Arg> sec = GetArgsToArray<T>(other...);
    res.insert(res.end(), sec.begin(), sec.end());
    return res;
}

template <class T,class... Args>
std::vector<Vect2D<T>> GetToArray(Args... args)
{
    std::vector<Vect2D<T>> stackEnges = {};
    stackEnges = GetArgsToArray(args...);
    return stackEnges;
}

// проверка на нахождение точки внутри выпуклого многоугольника
// Проверяем каждую грань на пересечение с лучом из искомой точки (луч в рандомное место)
// Если кол-во перемещений кратно 2-м - точка не в многоугольнике
// инеаче - внутри
// Примеч: можно случайно попасть на стык ребер - решается выбором луча поизощреннее
template <typename T,class... Args>
bool isPointInPolygon(Vect2D<T> p, Args ...args){
    std::vector<Point2D<T>> points = {};
    std::vector<Vect2D<T>> stackEnges = {};
    int countIntersect = 0;

    points = GetToArray(args...);

    if(points.size()==0) return false;

    Vect2D<T> first = points[0];
    for(int i=1; i<points.size();i++){
            stackEnges.push_back(Edge(first,points[i]));
            first = points[i];
    }

    stackEnges.push_back(Edge(first,stackEnges[0].start));
    for(Vect2D<T> item : stackEnges)
    {
        if(intersect (p, Vect2D<T>(10000,1), item.start, item.finish))
            countIntersect++;
    }
    if(countIntersect%2==0)
        return false;
    else {
        return true;
    }
}

#endif