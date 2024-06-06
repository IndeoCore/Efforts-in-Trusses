#ifndef BAR_H
#define BAR_H

#include "Force.h"

class Bar {
    protected:
        double barAngle;
        int barId;
        int isSolved = 0;
    private:
        static int nextNumber;
    public:
        Bar(double angle);
        static int getNextNumber();
        double getBarAngle();
        void solve();
        int getSolved();
        int getId();
        ~Bar();
    
};

#endif