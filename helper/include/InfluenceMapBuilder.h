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
        InfluenceMap(int sizeX, int sizeY, T initValue);
        ~InfluenceMap();
        double** matr;
        int sizeX;
        int sizeY;
        void ShowMap();
        void PutPotential(double power, double step, Point2D p);
        void PutAvgPotential(double power, double step, Point2D p);
        double getSumOfVectorOnInfluenceMap(Point2D fromV, Point2D toV);
        Point2D GetMinPotentialByRadius(int radius, Point2D source);
    private:
        
        
        double **array_generator(unsigned int dim1, unsigned int dim2);
        void array_destroyer(double **ary, unsigned int dim1);
        int signedMax(int a, int b);
        int getSign(int x);
        double putp(double oldV, double newV);
        bool isCorrectCoordinate(int x, int y);
};



#endif //AICUP2019_INFLUENCEMAPBUILDER_H
