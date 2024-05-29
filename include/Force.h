#ifndef FORCE_H
#define FORCE_H

#include <iostream>
#include <string>
#include <cmath>

using namespace std;


class Force {
    protected:
        double compX, compY;
        int type;
    public:
        Force(double magnitude, double ang);
        ~Force();
        void print(int id);
        void print(char id);
};

#endif