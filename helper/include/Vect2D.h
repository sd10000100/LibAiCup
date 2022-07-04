//**************************************
// Written for Russian Ai Cups with love 
// for horses and pain in the knees
// by sd10000100 on 18.01.2020.
//
// Классы узла карты и поиска пути
//**************************************


#pragma once

#include <tuple>
// #include "Point2D.h"
// TODO: дописать а то несолидно
// TODO: Сделать повариабельнее шаблон, и конвертацию из и в tuple

template<typename T>
struct Vect2D {
    using Point2D = std::tuple<int,int>;
    Point2D start;
    Point2D finish;

    Vect2D(Point2D start, Point2D finish): start(start),finish(finish){}
    
    Point2D RelativeOrigin() {
        return std::make_tuple(std::get<0>(finish)-std::get<0>(start), std::get<1>(finish)-std::get<1>(start));
        //return Point2D(finish.x - start.x, finish.y - start.y);
    }

    double length() { 
        return sqrt((std::get<0>(finish)-std::get<0>(start))*(std::get<0>(finish)-std::get<0>(start)) + 
                    (std::get<1>(finish)-std::get<1>(start))*(std::get<1>(finish)-std::get<1>(start)) ); 
    }

    void mult(double coeff) {
        finish = std::make_tuple(std::get<0>(start)+std::get<0>(RelativeOrigin())*coeff, std::get<1>(start)+std::get<1>(RelativeOrigin())*coeff ) ;
    //    finish.x = start.x + RelativeOrigin().x * coeff;
    //    finish.y = start.y + RelativeOrigin().y * coeff;
   }


    double angle(Vect2D<T> vector)
    {
        Point2D source = vector.RelativeOrigin();
        Point2D relative = RelativeOrigin();       
        //double angle =  atan2(source.y, source.x) - atan2(relative.y, relative.x);
        double angle =  atan2(std::get<1>(source), std::get<0>(source)) - atan2(std::get<1>(relative), std::get<0>(relative));
        if (angle < 0) { angle += 2 * M_PI; }
        return  angle;
    }

    //angle - in radians!
    //radian = degree*PI/180
    void turn(double angle)
    {
        Point2D relative = this->RelativeOrigin();
        double x = std::get<0>(relative) * cos(angle) - std::get<1>(relative) * sin(angle);
        double y = std::get<1>(relative) * cos(angle) + std::get<0>(relative) * sin(angle);
        // finish.x = start.x + x;
        // finish.y = start.y + y;
        finish = std::make_tuple(std::get<0>(start)+x, std::get<1>(start)+y);
    }
};
