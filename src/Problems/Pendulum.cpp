#include <cmath>
//#include "SinVariation.h"
#include "Pendulum.h"

using namespace std;

Pendulum::Pendulum(){
    this->angle = 0.0;
    this->speed = 0.0;
}

void Pendulum::run(double elapsedTime){
    this->angle = angle + speed;
}

void Pendulum::act(double dSpeed){
    this->speed = this->speed + dSpeed;
}

double Pendulum::getAngle(){
    return this->angle;
}

double Pendulum::getSpeed(){
    return this->speed;
}
