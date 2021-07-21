#ifndef BunnyH
#define BunnyH

#include "../GameObject.h"
#include <vector>
#include <cmath>

class Bunny : public GameObject {

    private:
        std::vector<double> inputs; // 10
        std::vector<double> hidden; // 8
        std::vector<double> output; // 4

        std::vector<std::vector<double>> weights1; // 80 (10 x 8)
        std::vector<std::vector<double>> weights2; // 32 (8 x 4)

        int x, y;
        int hunger;
        int thirst;
        int fitness;
        bool alive;

        double sigmoid(double num) {

            return 1 / (1 + exp(-1 * num));

        }

    public:
        Bunny(int bX, int bY);
        int getOutput(std::vector<double> spacesNear);
        int getX() {return x;}
        int getY() {return y;}
        void setX(int nX) {x = nX;}
        void setY(int nY) {y = nY;}

        int getHunger() {return hunger;}
        int getThirst() {return thirst;}
        void setHunger(int nX) {hunger = nX;}
        void setThirst(int nY) {thirst = nY;}
        bool isAlive() {return alive;}
        void setAlive(bool live) {alive = live;}


};

#endif