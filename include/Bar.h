#ifndef BAR_H
#define BAR_H

#include "../src/Force.cpp"

class Bar {
    protected:
        double barAngle;
        int barNumber;
        Force* normal;
    private:
        static int nextNumber;
    public:
        Bar(double angle);
        static int getNumber();
        ~Bar();
    
};

#endif