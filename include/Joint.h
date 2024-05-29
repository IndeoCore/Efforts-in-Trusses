#ifndef JOINT_H
#define JOINT_H

#include <list>
#include <../src/Bar.cpp>
#include <../src/Force.cpp>

using namespace std;

class Joint {
    protected:
        double coordX, coordY;
        list<Bar*>* bars;
        list<Force*>* reactions;
        char jointId;
        int barCount = 0;
    private:
        static char jointId;
    public:
        Joint(double X, double Y);
        void addBar(Bar* bar);
        void addReact(Force* reaction);
        static char getId();
        ~Joint();
    
};


#endif