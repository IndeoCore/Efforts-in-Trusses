#include "../include/Joint.h"

char Joint::jointId = 'A';

Joint::Joint(double X, double Y){
    this->coordX = X;
    this->coordY = Y;
    this->jointId = this->getId();
    Joint::jointId++;
}

Joint::~Joint(){
    while(!bars->empty()){
        Bar* bar = bars->front();
        bars->pop_front();
        delete bar;
    }
    while(!reactions->empty()){
        Force* reaction = reactions->front();
        reactions->pop_front();
        delete reaction;
    }
    delete reactions;
}

void Joint::addBar(Bar* bar){
    bars->push_back(bar);
    this->barCount++;
}

void Joint::addReact(Force* reaction){
    reactions->push_back(reaction);
}

char Joint::getId(){
    return Joint::jointId;
}