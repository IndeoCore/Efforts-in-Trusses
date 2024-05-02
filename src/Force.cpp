#include "../include/Force.h"

Force::Force(double magnitude, double direction[3]){
    this->magnitude = magnitude;
    for (int i = 0; i < 3; i++){
        this->direction[i] = direction[i];
    }
}