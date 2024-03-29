//**************************************
// Written for Russian Ai Cups with love 
// for horses and pain in the knees
// by sd10000100 on 15.01.2020.
//
// Потенциальное поле (карта влияния)
//**************************************

//TODO: переписать методы внедрения потенциала по квадрату
//      добавить методы внедрения потенциала по ромбу
//      добавить методы внедрения потенциала по кругу
//      переписать методы для определения оптимального направления 
//          (или астар уже тут бацать?)
#pragma once

#include <cmath>
#include <vector>
#include "Geometry.h"
#include <tuple>

using namespace std;

class InfluenceMap{

    public:
        // Создание потенциального поля 
        // sizeX - ширина карты
        // sizeY - высота карты
        // initValue - инициализирующее значение для заполнения ячеек карты 
        InfluenceMap(int sizeX, int sizeY, double initValue=0);
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
        void clear(double initValue);

        // Нанести потенциал на карту. 
        // Ячейка заполняется максимальным потенциалом из нанесенных
        // power - сила потенциала
        // step - на сколько затухает сила потенциала с каждой волной на карте
        // point - точка нанесения потенциала на карту
        void putPotential(double power, double step, tuple<int,int> point);

        // Нанести потенциал на карту по квадрату. 
        // Ячейка заполняется значением power по сторонам квадрата с половиной стороны step
        // power - сила потенциала
        // step - половина стороны квадрата
        // point - точка нанесения потенциала на карту
        void putPotentialOnSquare(double power, double step, tuple<int,int> point);


        // Нанести точечный потенциал на карту. 
        // Ячейка заполняется введенным значением
        // power - сила потенциала
        // point - точка нанесения потенциала на карту
        void putPoint(double power, tuple<int,int> point);

        // Нанести потенциал на карту. 
        // Ячейка заполняется средним потенциалом из нового и нанесенных
        // power - сила потенциала
        // step - на сколько затухает сила потенциала с каждой волной на карте
        // point - точка нанесения потенциала на карту
        void putAvgPotential(double power, double step, tuple<int,int> point);

        // Получить сумму ячеек на пути из точки from в точку to
        // from, to - начальная и конечная точки
        // Result - сумма ячеек на пути из точки from в точку to
        double getSumOfVectorPath(tuple<int,int> from, tuple<int,int> to);

        // Получить точку на расстоянии radius с минимальным потенциалом
        // radius - на каком радиусе искать точку
        // source - точка, из которой ищется направление
        // Result - точка на расстоянии radius с минимальным потенциалом
        tuple<int,int> getPointWithMinSum(int radius, tuple<int,int> source);
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
