#ifndef DEF_SIN
#define DEF_SIN

class Pendulum{
    private:
        double angle;
        double speed;

    public:
        Pendulum();
        virtual void run(double elapsedTime);
        void act(double dSpeed);
        double getAngle();
        double getSpeed();
        ~Pendulum();
};


#endif

