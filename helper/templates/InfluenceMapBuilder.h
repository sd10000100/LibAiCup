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
#include <iostream>

template<typename T>
class InfluenceMap{
    using Point2D = Point2D<T>;

    public:
        // Создание потенциального поля 
        // sizeX - ширина карты
        // sizeY - высота карты
        // initValue - инициализирующее значение для заполнения ячеек карты 
        InfluenceMap(int sizeX, int sizeY, T initValue=0);
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
        double getSumOfVectorPath(Point2D from, Point2D to);

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


template<typename T>
const double** InfluenceMap<T>::field(){
    return (const double**)this->field_;
}

template<typename T>
const int InfluenceMap<T>::sizeX(){
    return this->sizeX_;
}

template<typename T>
const int InfluenceMap<T>::sizeY(){
    return this->sizeY_;
}

template<typename T>
InfluenceMap<T>::InfluenceMap(int sizeX, int sizeY, T initValue){
    this->field_ = new double * [sizeX];
    this->field_[0] = new double [sizeX*sizeY];
    for (int i = 1; i != sizeX; ++i) {
        this->field_[i] =this->field_[i-1] + sizeY;
    }

    this->sizeX_ = sizeX;
    this->sizeY_ = sizeY;
    for (int i=0;i<sizeX;i++) {
        for (int j=0;j<sizeY;j++) {
            this->field_[i][j] = initValue;
        }
    }
}

template<typename T>
InfluenceMap<T>::~InfluenceMap(){
    delete [] this->field_[0];
    delete [] this->field_;
}

template<typename T>
void InfluenceMap<T>::show(){
    for (int i=0;i<sizeX_;i++) {
        for (int j=0;j<sizeY_;j++) {
            std::cout<<this->field_[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}

template<typename T>
void InfluenceMap<T>::clear(T initValue){
    for (int i=0;i<sizeX_;i++) {
        for (int j=0;j<sizeY_;j++) {
            this->matr[i][j] = initValue;
        }
    }
}

// получить максимальное по модулю
template<typename T>
int InfluenceMap<T>::signedMax(int a, int b) {
    if(abs(a)>=abs(b))
        return a;
    else return b;

}

// получить знак числа
template<typename T>
int InfluenceMap<T>::getSign(int x)
{
    if (x>0)
        return 1;
    else return -1;
}

template<typename T>
bool InfluenceMap<T>::isCorrectCoordinate(int x, int y)
{
    if(x>=0 && x<sizeX_ && y>=0 && y<sizeY_)
        return true;
    return false;
}

//put square potential
template<typename T>
void InfluenceMap<T>::putPotential(double power, double step, Point2D point)
{
    int s = 0;
    int x = int(abs(floor(point.x)));
    int y = int(abs(floor(point.y)));
    for(int l = 0;l<fabs(power);l=l+step, s++)
    {
        for(int temp = y-s;temp<=s+y;temp++)
        {
            int tempArrMinX = int(floor(x-s));
            int tempArrMaxX = int(floor(x+s));
            if(isCorrectCoordinate(tempArrMinX, temp))
                field_[tempArrMinX][temp]=signedMax(field_[tempArrMinX][temp],getSign(power)*(abs(power)-l));
            if(isCorrectCoordinate(tempArrMaxX, temp))
                field_[tempArrMaxX][temp]=signedMax(field_[tempArrMaxX][temp],getSign(power)*(abs(power)-l));
        }
        for(int temp = x-s+1;temp<=s+x-1;temp++)
        {
            int tempArrMinY = int(floor(y-s));
            int tempArrMaxY = int(floor(y+s));
            if(isCorrectCoordinate(temp, tempArrMinY))
                field_[temp][tempArrMinY]=signedMax(field_[temp][tempArrMinY],getSign(power)*(abs(power)-l));
            if(isCorrectCoordinate(temp, tempArrMaxY))
                field_[temp][tempArrMaxY]=signedMax(field_[temp][tempArrMaxY],getSign(power)*(abs(power)-l));
        }
    }
}

template<typename T>
double InfluenceMap<T>::getAvgValue(double oldV, double newV)
{
    if(oldV==behindWallValue_)
        return behindWallValue_;
    else if(oldV == 0)
        return newV;
    else
        return (oldV+newV)/2;

}


template<typename T>
void InfluenceMap<T>::putAvgPotential(double power, double step, Point2D p)
{
    int s = 0;
    int x = int(abs(floor(p.x)));
    int y = int(abs(floor(p.y)));
    for(int l = 0;l<fabs(power);l=l+step, s++)
    {
        for(int temp = y-s;temp<=s+y;temp++)
        {
            int tempArrMinX = int(floor(x-s));
            int tempArrMaxX = int(floor(x+s));
            if(tempArrMinX>=0 && tempArrMinX<sizeX && temp>=0 && temp<sizeY && field_[tempArrMinX][temp]<behindWallValue_)
                field_[tempArrMinX][temp]=getAvgValue(field_[tempArrMinX][temp],getSign(power)*(abs(power)-l));
            if(tempArrMaxX<sizeX && tempArrMaxX>=0 && temp>=0 && temp<sizeY && field_[tempArrMaxX][temp]<behindWallValue_)
                field_[tempArrMaxX][temp]=getAvgValue(field_[tempArrMaxX][temp],getSign(power)*(abs(power)-l));
        }
        for(int temp = x-s+1;temp<=s+x-1;temp++)
        {
            int tempArrMinY = int(floor(y-s));
            int tempArrMaxY = int(floor(y+s));
            if(tempArrMinY>=0 && tempArrMinY<sizeY && temp>=0 && temp<sizeX && field_[temp][tempArrMinY]<behindWallValue_)
                field_[temp][tempArrMinY]=getAvgValue(field_[temp][tempArrMinY],getSign(power)*(abs(power)-l));
            if(tempArrMaxY>=0 && tempArrMaxY<sizeY  && temp>=0 && temp<sizeX && field_[temp][tempArrMaxY]<behindWallValue_)
                field_[temp][tempArrMaxY]=getAvgValue(field_[temp][tempArrMaxY],getSign(power)*(abs(power)-l));
        }
    }
}



template<typename T>
double InfluenceMap<T>::getSumOfVectorPath(Point2D fromV, Point2D toV){
    double sum = 0;
    int sqareStartX =  fmin(floor(fromV.x), floor(toV.x));
    int sqareFinishX = fmax(ceil(fromV.x),ceil(toV.x));
    int sqareStartY = fmin(floor(fromV.y),floor(toV.y));
    int sqareFinishY = fmax(ceil(fromV.y),ceil(toV.y));

    for(int i = sqareStartX; i<=sqareFinishX;i++)
    {
        for(int j = sqareStartY; j<=sqareFinishY;j++) {
            if (isCorrectCoordinate(i, j) && (
                    intersect<T>(fromV, toV, Point2D(size_t(i), size_t(j)), Point2D(size_t(i), size_t(j) + 1))
                    ||
                    intersect<T>(fromV, toV, Point2D(size_t(i), size_t(j)), Point2D(size_t(i) + 1, size_t(j)))
                    ||
                    intersect<T>(fromV, toV, Point2D(size_t(i) + 1, size_t(j)),
                              Point2D(size_t(i) + 1, size_t(j) + 1))
                    ||
                    intersect<T>(fromV, toV, Point2D(size_t(i), size_t(j) + 1),
                              Point2D(size_t(i) + 1, size_t(j) + 1))
            )) {
                sum += field_[i][j];
            }
            else if(!isCorrectCoordinate(i, j))
            {sum +=behindWallValue_;}
        }
    }
    return sum;
}

template<typename T>
Point2D<T> InfluenceMap<T>::getPointWithMinSum(int radius, Point2D source) {

    double min = 10000;
    Point2D minPos = source;
    int x = int(abs(floor(source.x)));
    int y = int(abs(floor(source.y)));

    for (int temp = y-radius+1; temp < y+radius; temp++) {
        int minX = x-radius;
        int maxX = x+radius;
        double minSum = getSumOfVectorPath(source, Point2D(minX,temp));
        double maxSum = getSumOfVectorPath(source, Point2D(maxX,temp));
        if(minSum<min)
        {
            min = minSum;
            minPos.x = minX;
            minPos.y = temp;
        }
        if(maxSum<min)
        {
            min = maxSum;
            minPos.x = maxX;
            minPos.y = temp;
        }
    }
    for (int temp = x-radius+1; temp < x+radius; temp++) {
        int minY = y-radius;
        int maxY = y+radius;
        double minSum = getSumOfVectorPath(source, Point2D(temp,minY));
        double maxSum = getSumOfVectorPath(source, Point2D(temp,maxY));
        if(minSum<min)
        {
            min = minSum;
            minPos.x = temp;
            minPos.y = minY;
        }
        if(maxSum<min)
        {
            min = maxSum;
            minPos.x = temp;
            minPos.y = maxY;
        }
    }
    return minPos;

}