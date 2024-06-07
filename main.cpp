#include "Bar.h"
#include "Joint.h"
#include "Force.h"
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include "eigen/Eigen/Dense"

using namespace std;

void algorithm(vector<Joint*>* joints, int barCounter, vector<Force*>* forces);
void algorithmRecursive(vector<Joint*>* joints, double r[], double normalForces[], int barCounter);

int main() {
    int barCounter = 0;
    int jointCounter = 0;
    int forceCounter = 0;
    cout << "Ola, seja bem vindo(a) a calculadora de esforcos em trelicas 2D!" << endl;
    cout << "Para uma boa experiencia, precisamos estabelecer algumas limitacoes do programa:" << endl;
    cout << "1. E obrigatorio que a trelica possua exatamente 1 articulacao fixa e 1 articulacao movel, nem mais, nem menos" << endl;
    cout << "2. O numero de barras precisa corresponder a (2 * numero de nos - 3),  isto e, se tem 5 nos, precisamos de 7 barras" << endl;
    cout << "3. Para nao extrapolar o tempo de compilacao, pedimos que use no maximo ate 8 nos." << endl;
    cout << "4. Todas as juntas moveis serao tratadas como tendo uma reacao na vertical " 
    << "e todas juntas estaticas terao uma reacao na vertical e outra na horizontal" << endl;
    cout << "5. Pela caracterisica do problema, momentos externos nao podem ser incluidos." << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "Vamos comecar a montar nossa trelica!" << endl << endl;
    cout << endl << "Digite o numero de juntas: ";
    cin >> jointCounter;
    vector<Joint*>* joints = new vector<Joint*>();
    cout << endl << "Agora iremos adicionar as forcas externas." << endl;
    cout << "Considere o angulo da forca como sendo o angulo com o eixo X no sentido anti-horario(orientado positivamente para a direita)" << endl;
    cout << "O angulo sera = pi * (o valor que voce digitou), isto eh, se voce digitar 1.5, vai ser correspondente a 3pi/2 ou 270 graus" << endl;
    cout << "A ordem das forcas nao influencia nos calculos, mas serao usadas como identificador na hora de adicionar as juntas, entao lembre-se da ordem" << endl;
    cout << endl << "Diga quantas forcas externas estao atuando nessa trelica: ";
    cin >> forceCounter;
    vector <Force*>* externalForces = new vector<Force*>();
    for(int i = 0; i < forceCounter; i++){
        double magnitude, angle;
        cout << endl << "Digite a magnitude da " << i + 1 << " forca: " << endl;
        cin >> magnitude;
        cout << endl << "Digite o angulo da " << i + 1 << " forca: PI * " << endl;
        cin >> angle;
        angle *= M_PI;
        externalForces->push_back(new Force(magnitude, angle));
    }
    cout << endl << "Para continuar a montagem, vamos adicionar as juntas." << endl;
    cout << "Para construir uma junta, voce precisa incluir 3 parametros:" << endl;
    cout << "1 - Coordenada em X, 2 - Coordenada em Y, 3 - Tipo da junta." << endl;
    cout << "Tome (0, 0) como o primeiro no" << endl;
    cout << "Tipo: digite 0 para um no, 1 para um anel (junta movel), e 2 para uma articulacao (junta estatica)" << endl;
    cout << "Para facilitar os calculos, o anel sempre sera representado com uma reacao na vertical (Anel barra o eixo Y)" << endl;
    cout << "Para toda junta criada, sera necessario dizer, se existirem, quais forcas externas estao aplicadas naquele no" << endl; 
    for(unsigned int i = 0; i < jointCounter; i++){
        int forceApplied;
        double x, y, type;
        cout << endl << "Digite a coordenada X da " << i + 1 << " junta" << endl;
        cin >> x;
        cout << "Digite a coordenada Y da " << i + 1 << " junta" << endl;
        cin >> y;
        cout << "Digite o tipo da " << i + 1 << " junta" << endl;
        cin >> type;
        joints->push_back(new Joint(x, y, type));
        cout << "Diga, se houverem, quantas forcas serao aplicadas nessa junta (0 caso nenhuma): ";
        cin >> forceApplied;
        for(int f = 0; f < forceApplied; f++){
            int forceId;
            cout  << "Digite qual sera a forca a ser aplicada:";
            cin >> forceId;
            forceId--;
            externalForces->at(forceId)->setX(joints->at(i)->getCoordX());
            externalForces->at(forceId)->setY(joints->at(i)->getCoordY());
            joints->at(i)->addForce(externalForces->at(forceId));
        }
    }
    cout << endl << "Agora, para finalizar, me diga quais nos estao ligados entre si (possuem uma barra os ligando)" << endl << endl;
    for(unsigned int i = 0; i < jointCounter; i++){
        for (unsigned int k = i + 1; k < jointCounter; k++){
            int ligadas;
            cout << "Os nos " << joints->at(i)->getId() << " e " << joints->at(k)->getId() << " estao ligados?" << endl;
            cout << "Digite 1 pra sim e 0 pra nao: ";
            cin >> ligadas;
            if(ligadas){
                double angle = 0;
                if(joints->at(k)->getCoordX() == joints->at(i)->getCoordX()){
                    angle = M_PI_2;
                } else{
                    angle = atan((joints->at(k)->getCoordY() -  joints->at(i)->getCoordY()) / (joints->at(k)->getCoordX() -  joints->at(i)->getCoordX()));
                    if(angle < 0){
                        angle += M_PI;
                    }
                }
                Bar* barNova = new Bar(angle);
                joints->at(i)->addBar(barNova);
                joints->at(k)->addBar(barNova);
                barCounter++;
            }
            cout << endl;
        }
    }
    cout << endl << "Perfeito! Agora irei calcular os modulos das forcas das barras (tracao ou compressao)! Aguarde um instante..." << endl << endl;
    algorithm(joints, barCounter, externalForces);
    return 0;
}

void algorithm(vector <Joint*>* joints, int barCounter, vector <Force*>* forces){
    int type1Id, type2Id;
    double momentumX = 0, momentumY = 0, totalMomentum;
    double totalForceX = 0, totalForceY = 0;
    double normalForces[barCounter];
    for(int i = 0; i < barCounter; i++){
        normalForces[i] = 0;
    }
    for(unsigned int i = 0; i < joints->size(); i++){
        if (joints->at(i)->getType() == 1){
            type1Id = i;
        } else if(joints->at(i)->getType() == 2){
            type2Id = i;
        }
    }
    for(unsigned int i = 0; i < forces->size(); i++){
        totalForceX += forces->at(i)->getCompX();
        totalForceY += forces->at(i)->getCompY();
        momentumX += (forces->at(i)->getCompX() * (forces->at(i)->getY() - joints->at(type2Id)->getCoordY()));
        momentumY += (forces->at(i)->getCompY() * (-(forces->at(i)->getX() - joints->at(type2Id)->getCoordX())));
    }
    totalMomentum = (momentumX + momentumY);
    double momentumVbCoef = joints->at(type2Id)->getCoordX() - joints->at(type1Id)->getCoordX();
    Eigen::Matrix3f A;
    Eigen::Vector3f b;
    Eigen::Vector3f r; 
    A << 0, 1, 0,
         1, 0, 1,
         0, 0, momentumVbCoef;
    b << -totalForceX,
         -totalForceY,
         -totalMomentum;
    r = A.colPivHouseholderQr().solve(b);
    double rRecursive[3];
    for(int i = 0; i < 3; i++){
        rRecursive[i] = r[i];
    }
    for(unsigned int i = 0; i < joints->size(); i++){
        if(joints->at(i)->getBarCount() == 2){
            double forceEqX = 0;
            double forceEqY = 0;
            if(joints->at(i)->getType() == 2){
                forceEqY = r[0];
                forceEqX = r[1];
            } else if(joints->at(i)->getType() == 1){
                forceEqY = r[2];
            }
            for(unsigned int k = 0; k < joints->at(i)->getForces()->size(); k++){
                forceEqX += joints->at(i)->getForces()->at(k)->getCompX();
                forceEqY += joints->at(i)->getForces()->at(k)->getCompY();
            }
            Eigen::Matrix2f coef;
            Eigen::Vector2f indep;
            Eigen::Vector2f normRes;
            coef << cos(joints->at(i)->getBars()->at(0)->getBarAngle()), cos(joints->at(i)->getBars()->at(1)->getBarAngle()),
                    sin(joints->at(i)->getBars()->at(0)->getBarAngle()), sin(joints->at(i)->getBars()->at(1)->getBarAngle());
            indep << -forceEqX,
                     -forceEqY;
            normRes = coef.colPivHouseholderQr().solve(indep);
            normalForces[joints->at(i)->getBars()->at(0)->getId()-1] = normRes[0];
            joints->at(i)->getBars()->at(0)->solve();
            normalForces[joints->at(i)->getBars()->at(1)->getId()-1] = normRes[1];
            joints->at(i)->getBars()->at(1)->solve();
            joints->at(i)->solve();
        }
    }
    algorithmRecursive(joints, rRecursive, normalForces, barCounter);

    for (int i = 0; i < barCounter; i++){
        cout << "Normal na barra ";
        if(normalForces[i] < -0.00001 || normalForces[i] > 0.00001){
            cout << i + 1 << ": " << abs(normalForces[i]) << "N"<< endl; 
        } else{
            cout << i + 1 << ": 0" << endl;
        }
    }
}

void algorithmRecursive(vector<Joint*>* joints, double r[], double normalForces[], int barCounter){
    for(unsigned int i = 0; i < joints->size(); i++){
        if(joints->at(i)->getSolved() == 0){
            double solveCount = 0;
            int indices[2];
            int ind = 0;
            for(unsigned int count = 0; count < joints->at(i)->getBars()->size(); count++){
                if(joints->at(i)->getBars()->at(count)->getSolved()){
                    solveCount++;
                } else{
                    if(ind < 2){
                        indices[ind] = count;
                        ind++;
                    }
                }
            }
            if(joints->at(i)->getBars()->size() - solveCount == 2){
                double forceEqX = 0;
                double forceEqY = 0;
                if(joints->at(i)->getType() == 2){
                    forceEqY = r[0];
                    forceEqX = r[1];
                } else if(joints->at(i)->getType() == 1){
                    forceEqY = r[2];
                }
                for(unsigned int k = 0; k < joints->at(i)->getBars()->size(); k++){
                    if(joints->at(i)->getBars()->at(k)->getSolved()){
                        forceEqX += -normalForces[joints->at(i)->getBars()->at(k)->getId()-1] * cos(joints->at(i)->getBars()->at(k)->getBarAngle());
                        forceEqY += -normalForces[joints->at(i)->getBars()->at(k)->getId()-1] * sin(joints->at(i)->getBars()->at(k)->getBarAngle());
                    }
                }
                for(unsigned int k = 0; k < joints->at(i)->getForces()->size(); k++){
                    forceEqX += joints->at(i)->getForces()->at(k)->getCompX();
                    forceEqY += joints->at(i)->getForces()->at(k)->getCompY();
                }
                Eigen::Matrix2f coef;
                Eigen::Vector2f indep;
                Eigen::Vector2f normRes;
                coef << cos(joints->at(i)->getBars()->at(indices[0])->getBarAngle()), cos(joints->at(i)->getBars()->at(indices[1])->getBarAngle()),
                        sin(joints->at(i)->getBars()->at(indices[0])->getBarAngle()), sin(joints->at(i)->getBars()->at(indices[1])->getBarAngle());
                indep << -forceEqX,
                         -forceEqY;
                normRes = coef.colPivHouseholderQr().solve(indep);
                normalForces[joints->at(i)->getBars()->at(indices[0])->getId()-1] = normRes[0];
                joints->at(i)->getBars()->at(indices[0])->solve();
                normalForces[joints->at(i)->getBars()->at(indices[1])->getId()-1] = normRes[1];
                joints->at(i)->getBars()->at(indices[1])->solve();
                joints->at(i)->solve();
            } else if (joints->at(i)->getBars()->size() - solveCount == 1){
                double forceEqX = 0;
                double forceEqY = 0;
                if(joints->at(i)->getType() == 2){
                    forceEqY = r[0];
                    forceEqX = r[1];
                } else if(joints->at(i)->getType() == 1){
                    forceEqY = r[2];
                }
                for(unsigned int k = 0; k < joints->at(i)->getBars()->size(); k++){
                    if(joints->at(i)->getBars()->at(k)->getSolved()){
                        forceEqX += -normalForces[joints->at(i)->getBars()->at(k)->getId()-1] * cos(joints->at(i)->getBars()->at(k)->getBarAngle());
                        forceEqY += -normalForces[joints->at(i)->getBars()->at(k)->getId()-1] * sin(joints->at(i)->getBars()->at(k)->getBarAngle());
                    }
                }
                for(unsigned int k = 0; k < joints->at(i)->getForces()->size(); k++){
                    forceEqX += joints->at(i)->getForces()->at(k)->getCompX();
                    forceEqY += joints->at(i)->getForces()->at(k)->getCompY();
                }
                Eigen::Matrix2f coef;
                Eigen::Vector2f indep;
                Eigen::Vector2f normRes;
                coef << cos(joints->at(i)->getBars()->at(indices[0])->getBarAngle()), 0,
                        sin(joints->at(i)->getBars()->at(indices[0])->getBarAngle()), 0;
                indep << -forceEqX,
                         -forceEqY;
                normRes = coef.colPivHouseholderQr().solve(indep);
                normalForces[joints->at(i)->getBars()->at(indices[0])->getId()-1] = normRes[0];
                joints->at(i)->getBars()->at(indices[0])->solve();
                joints->at(i)->solve();
            }
        }
    }
}


