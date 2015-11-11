#include <cmath>
//#include "SinVariation.h"
#include "Problems/Pendulum/ProblemPendulum.h"

using namespace std;

ProblemPendulum::ProblemPendulum(){
    this->angle = 0.0;
    this->speed = 0.0;
}

void ProblemPendulum::run(double elapsedTime){
    this->angle = angle + speed;
}

void ProblemPendulum::act(double dSpeed){
    this->speed = this->speed + dSpeed;
}

double ProblemPendulum::getAngle(){
    return this->angle;
}

double ProblemPendulum::getSpeed(){
    return this->speed;
}
