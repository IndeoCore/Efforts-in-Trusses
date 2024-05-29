#include "../include/Bar.h"

int Bar::nextNumber = 1;

Bar::Bar(double angle){
    cout << "Angulos variam de -π/2 a π/2" << endl;
    cout << "Obs: angulos positivos indicam a parte da direita da barra mais alta, como em: / ";
    cout << " e angulos negativos significam a parte da esquerda mais alta." << endl;
    cout << "Para facilitar os calculos, represente a barra na vertical sempre com angulo de π/2";
    this->barAngle = angle;
    this->barNumber = this->getNumber();
    Bar::nextNumber++;
}

Bar::~Bar(){

}

int Bar::getNumber(){
    return Bar::nextNumber;
}