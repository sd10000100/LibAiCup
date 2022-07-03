//**************************************
// Written for Russian Ai Cups with love 
// for horses and pain in the knees
// by sd10000100 on 15.01.2020.
//
// Геометрические функции
//**************************************

//TODO: переписать для более универсального класса вектора
#pragma once
#include "Point2D.h"
#include "Vect2D.h"
#include <tuple>

using namespace std;

// Случайное целое число [a,b]
inline int random_int(int a, int b){
    return rand() % (b - a + 1) + a;
}

// расстояние между 2-мя точками
template<typename T>
double distanceSqr(Point2D<T> a, Point2D<T> b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

inline double distanceSqr(std::tuple<int, int> a, std::tuple<int, int> b) {
    return (std::get<0>(a) - std::get<0>(b)) * (std::get<0>(a) - std::get<0>(b)) + (std::get<1>(a) - std::get<1>(b)) * (std::get<1>(a) - std::get<1>(b));
}

inline double distance(std::tuple<int, int> a, std::tuple<int, int> b) {
    return sqrt((std::get<0>(a) - std::get<0>(b)) * (std::get<0>(a) - std::get<0>(b)) + (std::get<1>(a) - std::get<1>(b)) * (std::get<1>(a) - std::get<1>(b)));
}


// ориентированная площадь треугольника
// Исп-я понятие косого (псевдополяр) произвед векторов
// a ^ b = |a||b|sin(<(a,b))=2S
// угол вращения между векторами против часовой стрелки
// 2s=|x1 y1 1|
//    |x2 y2 1|=(x2-x1)(y3-y1)-(y2-y1)(x3-x1)
//    |x3 y3 1|
template<typename T>
double orientedArea (Point2D<T> a, Point2D<T> b, Point2D<T> c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

inline double orientedAreaInt (tuple<int,int> a, tuple<int,int> b, tuple<int,int> c) {
    return (get<0>(b) - get<0>(a)) * (get<1>(c) - get<1>(a)) - (get<1>(b)- get<1>(a)) * (get<0>(c) - get<0>(a));
}

// проверка, что точки не лежат на одной плоскости
inline bool isPointNotOnSamePlane (double a, double b, double c, double d) {
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
           && orientedArea<T>(a,b,c) * orientedArea<T>(a,b,d) <= 0
           && orientedArea<T>(c,d,a) * orientedArea<T>(c,d,b) <= 0;
}


// Чтобы отрезки AB и CD пересекались, нид чтобы A и B находились
// по разные стороны от прямой CD и аналогично C и D по разные стороны от AB
// Нужно вычислить ориентированные площади треугольников и сравнить знаки
inline bool intersectInt (tuple<int,int> a, tuple<int,int> b, tuple<int,int> c, tuple<int,int> d) {
    return isPointNotOnSamePlane (get<0>(a), get<0>(b), get<0>(c), get<0>(d))
           && isPointNotOnSamePlane (get<1>(a), get<1>(b), get<1>(c), get<1>(d))
           && orientedAreaInt(a,b,c) * orientedAreaInt(a,b,d) <= 0
           && orientedAreaInt(c,d,a) * orientedAreaInt(c,d,b) <= 0;
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
// Примеч2: нужно, чтобы вершины были отсортированы по углу относительно центра многоугольника
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

// Формула Гаусса вычисления площади выпуклого многоугольника 
// points : точки вершины многоугольника, отсортированные по углу относительно центра многоугольника
// Примеч2: нужно, чтобы вершины были отсортированы по углу относительно центра многоугольника
template <typename T>
double GaussS(std::vector<Point2D<T>> points)
{
    using Point2D = Point2D<T>;
    double res = 0;
	for (int i=0; i<points.size(); i++) {
        Point2D temp;
        if(i==0) {
            temp = points[points.size()-1];
        }
        else {   
            temp = points[i-1];
        }
        Point2D p2 = points[i];
		res += (temp.x - p2.x) * (temp.y + p2.y);
	}
	return fabs (res) / 2;
}
