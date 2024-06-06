#include "Force.h"

Force::Force(double magnitude, double ang){
    this->compX = magnitude * cos(ang);
    this->compY = magnitude * sin(ang);
}

Force::~Force(){
    
}

void Force::print(){
    cout << this->compX << " * i + " << this->compY << " * j";
}

double Force::getCompX(){
    return this->compX;
}

double Force::getCompY(){
    return this->compY;
}

void Force::setX(double x){
    this->X = x;
}

void Force::setY(double y){
    this->Y = y;
}

double Force::getX(){
    return this->X;
}

double Force::getY(){
    return this->Y;
}
