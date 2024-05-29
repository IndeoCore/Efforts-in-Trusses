#include "../include/Force.h"

Force::Force(double magnitude, double ang){
    cout << "Digite 1 para forca de tracao, 2 para forca de compressao ou 3 para reacoes vinculares: ";
    cin >> this->type;
    this->compX = magnitude * cos(ang);
    this->compY = magnitude * sin(ang);
}

void Force::print(int id){
    switch (this->type)
    {
    case 1:
        cout << "Forca de tracao N" << id <<" na barra " << id << "= " << this->compX << " . i + " << this->compY << " . j" << endl;
        cout << "Ou entao, modulo de N" << id << "= " << sqrt(pow(this->compX, 2) + pow(this->compY, 2)) << endl;
        break;
    
    case 2:
        cout << "Forca de compressao N" << id <<" na barra " << id << "= " << this->compX << " . i + " << this->compY << " . j" << endl;
        cout << "Ou entao, modulo de N" << id << "= " << sqrt(pow(this->compX, 2) + pow(this->compY, 2)) << endl;
        break;
    
    default:
        break;
    }
}

void Force::print(char id){
    switch (this->type)
    {
    case 3:
        if(this->compX != 0){
            cout << "Forca horizontal H" << id << " na articulacao " << id << "= " << this->compX << endl;
        }
        if(this->compY != 0){
            cout << "Forca vertical V" << id << " na articulacao " << id << "= " << this->compY << endl;
        }
        break;
    
    default:
        break;
    }
}