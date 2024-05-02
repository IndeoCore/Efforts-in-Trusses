#ifndef FORCE_H
#define FORCE_H

class Force {
    protected:
        double magnitude;
        double direction[3];
    public:
        Force(double magnitude, double direction[3]);
        ~Force();
};

#endif