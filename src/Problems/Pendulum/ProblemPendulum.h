#ifndef PROBLEMPENDULUM_H_
#define PROBLEMPENDULUM_H_

class ProblemPendulum{
    private:
        double angle;
        double speed;

    public:
        ProblemPendulum();
        virtual void run(double elapsedTime);
        void act(double dSpeed);
        double getAngle();
        double getSpeed();
        ~ProblemPendulum();
};


#endif

