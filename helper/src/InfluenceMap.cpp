#include "InfluenceMap.h"
#include <iostream>

const double** InfluenceMap::field(){
    return (const double**)this->field_;
}

const int InfluenceMap::sizeX(){
    return this->sizeX_;
}

const int InfluenceMap::sizeY(){
    return this->sizeY_;
}

InfluenceMap::InfluenceMap(int sizeX, int sizeY, double initValue){
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

InfluenceMap::~InfluenceMap(){
    delete [] this->field_[0];
    delete [] this->field_;
}

void InfluenceMap::show(){
    for (int i=0;i<sizeX_;i++) {
        for (int j=0;j<sizeY_;j++) {
            std::cout<<this->field_[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}

void InfluenceMap::clear(double initValue){
    for (int i=0;i<sizeX_;i++) {
        for (int j=0;j<sizeY_;j++) {
            this->field_[i][j] = initValue;
        }
    }
}

// получить максимальное по модулю
int InfluenceMap::signedMax(int a, int b) {
    if(abs(a)>=abs(b))
        return a;
    else return b;

}

// получить знак числа
int InfluenceMap::getSign(int x)
{
    if (x>0)
        return 1;
    else return -1;
}

bool InfluenceMap::isCorrectCoordinate(int x, int y)
{
    if(x>=0 && x<sizeX_ && y>=0 && y<sizeY_)
        return true;
    return false;
}

//put square potential
void InfluenceMap::putPotential(double power, double step, tuple<int,int> point)
{
    int s = 0;
    int x = int(abs(floor(get<0>(point))));
    int y = int(abs(floor(get<1>(point))));
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

double InfluenceMap::getAvgValue(double oldV, double newV)
{
    if(oldV==behindWallValue_)
        return behindWallValue_;
    else if(oldV == 0)
        return newV;
    else
        return (oldV+newV)/2;

}


void InfluenceMap::putAvgPotential(double power, double step, tuple<int,int> p)
{
    int s = 0;
    int x = int(abs(floor(get<0>(p))));
    int y = int(abs(floor(get<1>(p))));
    for(int l = 0;l<fabs(power);l=l+step, s++)
    {
        for(int temp = y-s;temp<=s+y;temp++)
        {
            int tempArrMinX = int(floor(x-s));
            int tempArrMaxX = int(floor(x+s));
            if(tempArrMinX>=0 && tempArrMinX<sizeX_ && temp>=0 && temp<sizeY_ && field_[tempArrMinX][temp]<behindWallValue_)
                field_[tempArrMinX][temp]=getAvgValue(field_[tempArrMinX][temp],getSign(power)*(abs(power)-l));
            if(tempArrMaxX<sizeX_ && tempArrMaxX>=0 && temp>=0 && temp<sizeY_ && field_[tempArrMaxX][temp]<behindWallValue_)
                field_[tempArrMaxX][temp]=getAvgValue(field_[tempArrMaxX][temp],getSign(power)*(abs(power)-l));
        }
        for(int temp = x-s+1;temp<=s+x-1;temp++)
        {
            int tempArrMinY = int(floor(y-s));
            int tempArrMaxY = int(floor(y+s));
            if(isCorrectCoordinate(temp, tempArrMinY) && field_[temp][tempArrMinY]<behindWallValue_)
                field_[temp][tempArrMinY]=getAvgValue(field_[temp][tempArrMinY],getSign(power)*(abs(power)-l));
            if(isCorrectCoordinate(temp, tempArrMaxY) && field_[temp][tempArrMaxY]<behindWallValue_)
                field_[temp][tempArrMaxY]=getAvgValue(field_[temp][tempArrMaxY],getSign(power)*(abs(power)-l));
        }
    }
}



double InfluenceMap::getSumOfVectorPath(tuple<int,int> fromV, tuple<int,int> toV){
    double sum = 0;
    int sqareStartX =  fmin(floor(get<0>(fromV)), floor(get<0>(toV)));
    int sqareFinishX = fmax(ceil(get<0>(fromV)),ceil(get<0>(toV)));
    int sqareStartY = fmin(floor(get<1>(fromV)),floor(get<1>(toV)));
    int sqareFinishY = fmax(ceil(get<1>(fromV)),ceil(get<1>(toV)));

    for(int i = sqareStartX; i<=sqareFinishX;i++)
    {
        for(int j = sqareStartY; j<=sqareFinishY;j++) {
            if (isCorrectCoordinate(i, j) && (
                    intersectInt(fromV, toV, make_tuple(size_t(i), size_t(j)), make_tuple(size_t(i), size_t(j) + 1))
                    ||
                    intersectInt(fromV, toV, make_tuple(size_t(i), size_t(j)), make_tuple(size_t(i) + 1, size_t(j)))
                    ||
                    intersectInt(fromV, toV, make_tuple(size_t(i) + 1, size_t(j)),
                              make_tuple(size_t(i) + 1, size_t(j) + 1))
                    ||
                    intersectInt(fromV, toV, make_tuple(size_t(i), size_t(j) + 1),
                              make_tuple(size_t(i) + 1, size_t(j) + 1))
            )) {
                sum += field_[i][j];
            }
            else if(!isCorrectCoordinate(i, j))
            {sum +=behindWallValue_;}
        }
    }
    return sum;
}

tuple<int,int> InfluenceMap::getPointWithMinSum(int radius, tuple<int,int> source) {

    double min = 10000;
    tuple<int,int> minPos = make_tuple(get<0>(source),get<1>(source));
    int x = int(abs(floor(get<0>(source))));
    int y = int(abs(floor(get<1>(source))));

    for (int temp = y-radius+1; temp < y+radius; temp++) {
        int minX = x-radius;
        int maxX = x+radius;
        double minSum = getSumOfVectorPath(source, make_tuple(minX,temp));
        double maxSum = getSumOfVectorPath(source, make_tuple(maxX,temp));
        if(minSum<min)
        {
            min = minSum;
            minPos = make_tuple(minX,temp);
        }
        if(maxSum<min)
        {
            min = maxSum;
            minPos = make_tuple(maxX,temp);
        }
    }
    for (int temp = x-radius+1; temp < x+radius; temp++) {
        int minY = y-radius;
        int maxY = y+radius;
        double minSum = getSumOfVectorPath(source, make_tuple(temp,minY));
        double maxSum = getSumOfVectorPath(source, make_tuple(temp,maxY));
        if(minSum<min)
        {
            min = minSum;
            minPos = make_tuple(temp,minY);
        }
        if(maxSum<min)
        {
            min = maxSum;
            minPos = make_tuple(temp,maxY);
        }
    }
    return minPos;

}