#include "Bar.h"

int Bar::nextNumber = 1;

Bar::Bar(double angle){
    
    this->barAngle = angle;
    this->barId = this->getNextNumber();
    Bar::nextNumber++;
}

Bar::~Bar(){

}

int Bar::getNextNumber(){
    return Bar::nextNumber;
}

int Bar::getId(){
    return this->barId;
}

double Bar::getBarAngle(){
    return this->barAngle;
}

void Bar::solve(){
    this->isSolved = 1;
}

int Bar::getSolved(){
    return isSolved;
}