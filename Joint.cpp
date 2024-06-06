#include "Joint.h"

char Joint::jointsId = 'A';

Joint::Joint(double X, double Y, double type){
    this->coordX = X;
    this->coordY = Y;
    this->type = type;
    this->jointId = this->getNextId();
    this->bars = new vector<Bar*>();
    this->forces = new vector<Force*>();
    Joint::jointsId++;
}

Joint::~Joint(){
    while(!bars->empty()){
        bars->pop_back();
    }
    while(!forces->empty()){
        forces->pop_back();
    }
    delete bars;
    delete forces;
}

void Joint::addBar(Bar* bar){
    bars->push_back(bar);
    this->barCount++;
}


void Joint::addForce(Force* force){
    forces->push_back(force);
    this->externalForcesCount++;
}

char Joint::getNextId(){
    return Joint::jointsId;
}

char Joint::getId(){
    return this->jointId;
}

int Joint::getBarCount(){
    return this->barCount;
}

int Joint::getForceCount(){
    return this->externalForcesCount;
}

int Joint::getType(){
    return this->type;
}

vector<Bar*>* Joint::getBars(){
    return this->bars;
}

vector<Force*>* Joint::getForces(){
    return this->forces;
}

double Joint::getCoordX(){
    return this->coordX;
}

double Joint::getCoordY(){
    return this->coordY;
}

void Joint::solve(){
    this->isSolved = 1;
}

int Joint::getSolved(){
    return isSolved;
}