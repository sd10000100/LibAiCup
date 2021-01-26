//
// Created by badru on 15.01.2020.
//

#ifndef LIBAICUP_INFLUENCEMAPBUILDER_H
#define LIBAICUP_INFLUENCEMAPBUILDER_H

#include <cmath>
#include <vector>
#include "Geometry.h"

template<typename T>
class InfluenceMap{
    using Point2D = Point2D<T>;

    public:
        // Создание потенциального поля 
        // sizeX - ширина карты
        // sizeY - высота карты
        // initValue - инициализирующее значение для заполнения ячеек карты 
        InfluenceMap(int sizeX, int sizeY, T initValue);
        // Деструктор
        ~InfluenceMap();
        // Карта влияния
        const double** field();
        // Ширина
        const int sizeX();
        // Высота
        const int sizeY();
        // Вывести в консоль карту
        void show();
        // Очистить карту, заполнив указанным значением
        // initValue - инициализирующее значение для заполнения ячеек карты 
        void clear(T initValue);

        // Нанести потенциал на карту. 
        // Ячейка заполняется максимальным потенциалом из нанесенных
        // power - сила потенциала
        // step - на сколько затухает сила потенциала с каждой волной на карте
        // point - точка нанесения потенциала на карту
        void putPotential(double power, double step, Point2D point);

        // Нанести потенциал на карту. 
        // Ячейка заполняется средним потенциалом из нового и нанесенных
        // power - сила потенциала
        // step - на сколько затухает сила потенциала с каждой волной на карте
        // point - точка нанесения потенциала на карту
        void putAvgPotential(double power, double step, Point2D point);

        // Получить сумму ячеек на пути из точки from в точку to
        // from, to - начальная и конечная точки
        // Result - сумма ячеек на пути из точки from в точку to
        double getSumOfVector(Point2D from, Point2D to);

        // Получить точку на расстоянии radius с минимальным потенциалом
        // radius - на каком радиусе искать точку
        // source - точка, из которой ищется направление
        // Result - точка на расстоянии radius с минимальным потенциалом
        Point2D getPointWithMinSum(int radius, Point2D source);
    private:
        double** field_; //T** ?
        int sizeX_;
        int sizeY_;
        int behindWallValue_ = 80;
        int signedMax(int a, int b);
        int getSign(int x);
        double getAvgValue(double oldV, double newV);
        bool isCorrectCoordinate(int x, int y);
};



#endif
