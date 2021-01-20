#include "../include/InfluenceMapBuilder.h"
#include <iostream>

template<typename T>
double InfluenceMap<T>::**array_generator(unsigned int dim1, unsigned int dim2) {
    double **ptrary = new double * [dim1];
    for (int i = 0; i < dim1; i++) {
        ptrary[i] = new double [dim2];
    }
    return ptrary;
}

template<typename T>
void InfluenceMap<T>::array_destroyer(double **ary, unsigned int dim1) {
    for (int i = 0; i < dim1; i++) {
        delete [] ary[i];
    }
    delete [] ary;
}

template<typename T>
InfluenceMap<T>::InfluenceMap(int sizeX, int sizeY, T initValue){
    this->matr = new double * [sizeX];
    for (int i = 0; i < sizeX; i++) {
        this->matr[i] = new double [sizeY];
    }
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    for (int i=0;i<sizeX;i++) {
        for (int j=0;j<sizeY;j++) {
            this->matr[i][j] = initValue;
        }
    }
}

template<typename T>
InfluenceMap<T>::~InfluenceMap(){
    array_destroyer(this->matr, this->sizeX);
}

template<typename T>
void InfluenceMap<T>::ShowMap(){
    for (int i=0;i<sizeX;i++) {
        for (int j=0;j<sizeY;j++) {
            std::cout<<this->matr[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}



template<typename T>
int InfluenceMap<T>::signedMax(int a, int b)
{
    if(abs(a)>=abs(b))
        return a;
    else return b;

}

template<typename T>
int InfluenceMap<T>::getSign(int x)
{
    if (x>0)
        return 1;
    else return -1;
}

template<typename T>
void InfluenceMap<T>::PutPotential(double power, double step, Point2D p)
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
            if(tempArrMinX>=0 && tempArrMinX<sizeX && temp>=0 && temp<sizeY)
                matr[tempArrMinX][temp]=signedMax(matr[tempArrMinX][temp],getSign(power)*(abs(power)-l));
            if(tempArrMaxX<sizeX && tempArrMaxX>=0 && temp>=0 && temp<sizeY)
                matr[tempArrMaxX][temp]=signedMax(matr[tempArrMaxX][temp],getSign(power)*(abs(power)-l));
        }
        for(int temp = x-s+1;temp<=s+x-1;temp++)
        {
            int tempArrMinY = int(floor(y-s));
            int tempArrMaxY = int(floor(y+s));
            if(tempArrMinY>=0 && tempArrMinY<sizeY && temp>=0 && temp<sizeX)
                matr[temp][tempArrMinY]=signedMax(matr[temp][tempArrMinY],getSign(power)*(abs(power)-l));
            if(tempArrMaxY>=0 && tempArrMaxY<sizeY  && temp>=0 && temp<sizeX)
                matr[temp][tempArrMaxY]=signedMax(matr[temp][tempArrMaxY],getSign(power)*(abs(power)-l));
        }
    }
}

template<typename T>
double InfluenceMap<T>::putp(double oldV, double newV)
{
    if(oldV==80)
        return 80;
    else if(oldV == 0)
        return newV;
    else
        return (oldV+newV)/2;

}

template<typename T>
void InfluenceMap<T>::PutAvgPotential(double power, double step, Point2D p)
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
            if(tempArrMinX>=0 && tempArrMinX<sizeX && temp>=0 && temp<sizeY && matr[tempArrMinX][temp]<80)
                matr[tempArrMinX][temp]=putp(matr[tempArrMinX][temp],getSign(power)*(abs(power)-l));
            if(tempArrMaxX<sizeX && tempArrMaxX>=0 && temp>=0 && temp<sizeY && matr[tempArrMaxX][temp]<80)
                matr[tempArrMaxX][temp]=putp(matr[tempArrMaxX][temp],getSign(power)*(abs(power)-l));
        }
        for(int temp = x-s+1;temp<=s+x-1;temp++)
        {
            int tempArrMinY = int(floor(y-s));
            int tempArrMaxY = int(floor(y+s));
            if(tempArrMinY>=0 && tempArrMinY<sizeY && temp>=0 && temp<sizeX && matr[temp][tempArrMinY]<80)
                matr[temp][tempArrMinY]=putp(matr[temp][tempArrMinY],getSign(power)*(abs(power)-l));
            if(tempArrMaxY>=0 && tempArrMaxY<sizeY  && temp>=0 && temp<sizeX && matr[temp][tempArrMaxY]<80)
                matr[temp][tempArrMaxY]=putp(matr[temp][tempArrMaxY],getSign(power)*(abs(power)-l));
        }
    }
}

template<typename T>
bool InfluenceMap<T>::isCorrectCoordinate(int x, int y)
{
    if(x>=0 && x<sizeX && y>=0 && y<sizeY)
        return true;
    return false;
}

template<typename T>
double InfluenceMap<T>::getSumOfVectorOnInfluenceMap(Point2D fromV, Point2D toV){
    double sum = 0;
    int sqareStartX =  fmin(floor(fromV.x), floor(toV.x));
    int sqareFinishX = fmax(ceil(fromV.x),ceil(toV.x));
    int sqareStartY = fmin(floor(fromV.y),floor(toV.y));
    int sqareFinishY = fmax(ceil(fromV.y),ceil(toV.y));

    for(int i = sqareStartX; i<=sqareFinishX;i++)
    {
        for(int j = sqareStartY; j<=sqareFinishY;j++) {
            if (isCorrectCoordinate(i, j, sizeX, sizeY) && (
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
                sum += matr[i][j];
            }
            else if(!isCorrectCoordinate(i, j, sizeX, sizeY))
            {sum +=80;}
        }
    }
    return sum;
}

template<typename T>
Point2D<T> InfluenceMap<T>::GetMinPotentialByRadius(int radius, Point2D source) {

    double min = 10000;
    Point2D minPos = source;
    int x = int(abs(floor(source.x)));
    int y = int(abs(floor(source.y)));

    for (int temp = y-radius+1; temp < y+radius; temp++) {
        int minX = x-radius;
        int maxX = x+radius;
        double minSum = getSumOfVectorOnInfluenceMap(source, Point2D(minX,temp));
        double maxSum = getSumOfVectorOnInfluenceMap(source, Point2D(maxX,temp));
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
        double minSum = getSumOfVectorOnInfluenceMap(source, Point2D(temp,minY));
        double maxSum = getSumOfVectorOnInfluenceMap(source, Point2D(temp,maxY));
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