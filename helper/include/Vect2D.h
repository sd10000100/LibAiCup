//
// Created by badru on 18.01.2020.
//

#ifndef LIBAICUP_VECT2D_H
#define LIBAICUP_VECT2D_H

#include "Point2D.h"
// TODO: дописать а то несолидно

template<typename T>
struct Vect2D {
    using Point2D = Point2D<T>;
    Point2D start;
    Point2D finish;

    Vect2D(Point2D start, Point2D finish): start(start),finish(finish){}
    Point2D RelativeOrigin() {
        return Point2D(finish.x - start.x, finish.y - start.y);
    }

    //double length() { return sqrt(p1.x*p1.x + p1.y*p1.y); }

    void mult(double coeff) {
       finish.x = start.x + RelativeOrigin().x * coeff;
       finish.y = start.y + RelativeOrigin().y * coeff;
   }


    double angle(Vect2D<T> vector)
    {
        Point2D source = vector.RelativeOrigin();
        Point2D relative = RelativeOrigin();       
        double angle =  atan2(source.y, source.x) - atan2(relative.y, relative.x);
        if (angle < 0) { angle += 2 * M_PI; }
        return  angle;
    }

    void turn(double angle)
    {
        double x = RelativeOrigin().x * cos(angle) - RelativeOrigin().y * sin(angle);
        double y = RelativeOrigin().y * cos(angle) + RelativeOrigin().x * sin(angle);
        finish.x = start.x + x;
        finish.y = start.y + y;
    }
};
#endif
