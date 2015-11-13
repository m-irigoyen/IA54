#include <cmath>
//#include "SinVariation.h"
#include "Problems/Pendulum/ProblemPendulum.h"

using namespace std;

ProblemPendulum::ProblemPendulum(){
    this->angle = 0.0;
    this->speed = 0.0;
}

void ProblemPendulum::run(float elapsedTime){
    this->angle = angle + speed;
}

void ProblemPendulum::act(float dSpeed){
    this->speed = this->speed + dSpeed;
}

float ProblemPendulum::getAngle(){
    return this->angle;
}

float ProblemPendulum::getSpeed(){
    return this->speed;
}
