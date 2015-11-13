#ifndef PROBLEMPENDULUM_H_
#define PROBLEMPENDULUM_H_

class ProblemPendulum{
    private:
        float angle;
        float speed;

    public:
        ProblemPendulum();
        virtual void run(float elapsedTime);
        void act(float dSpeed);
        float getAngle();
        float getSpeed();
        ~ProblemPendulum();
};


#endif

