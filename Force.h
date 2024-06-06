#ifndef FORCE_H
#define FORCE_H

#include <iostream>
#include <string>
#include <cmath>

using namespace std;


class Force {
    protected:
        double compX, compY;
        double X, Y;
    public:
        Force(double magnitude, double ang);
        ~Force();
        void print();
        double getCompX();
        double getCompY();
        void setX(double x);
        void setY(double y);
        double getX();
        double getY();
};

#endif