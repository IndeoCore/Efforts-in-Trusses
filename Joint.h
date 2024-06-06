#ifndef JOINT_H
#define JOINT_H

#include <vector>
#include "Bar.h"
#include "Force.h"

using namespace std;

class Joint {
    protected:
        double coordX, coordY;
        vector<Bar*>* bars;
        vector<Force*>* forces;
        char jointId;
        int barCount = 0;
        int externalForcesCount = 0;
        double type;
        int isSolved = 0;
    private:
        static char jointsId;
    public:
        Joint(double X, double Y, double type);
        void addBar(Bar* bar);
        void addForce(Force* force);
        static char getNextId();
        int getBarCount();
        int getForceCount();
        vector<Bar*>* getBars();
        vector<Force*>* getForces();
        double getCoordX();
        double getCoordY();
        int getType();
        void solve();
        int getSolved();
        char getId();
        ~Joint();
    
};


#endif