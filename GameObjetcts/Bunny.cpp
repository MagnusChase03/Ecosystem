#include "Bunny.h"

Bunny::Bunny(int bX, int bY) : GameObject(2, "pink") {

    for (int i = 0; i < 10; i++) {

        inputs.push_back(0.0);

    }

    for (int i = 0; i < 8; i++) {

        hidden.push_back(0.0);

    }

    for (int i = 0; i < 4; i++) {

        output.push_back(0.0);

    }

    for (int i = 0; i < 10; i++) {

        std::vector<double> weightSet;
        for (int k = 0; k < 8; k++) {

            weightSet.push_back(((double) rand() / RAND_MAX) *  5 - 2.0);

        }
        weights1.push_back(weightSet);

    }

    for (int i = 0; i < 8; i++) {

        std::vector<double> weightSet;
        for (int k = 0; k < 4; k++) {

            weightSet.push_back(((double) rand() / RAND_MAX) * 5 - 2.0);

        }
        weights2.push_back(weightSet);

    }

    x = bX;
    y = bY;
    hunger = 20;
    thirst = 15;
    fitness = 0;
    alive = true;

}

int Bunny::getOutput(std::vector<double> spacesNear) {

    inputs[0] = hunger;
    inputs[1] = thirst;
    for (int i = 0; i < spacesNear.size(); i++) {

        inputs[i + 2] = spacesNear[i];

    }

    for (int i = 0; i < hidden.size(); i++) {

        double total;
        for (int k = 0; k < inputs.size(); k++) {

            total += inputs[k] * weights1[k][i];

        }

        hidden[i] = sigmoid(total);

    }

    for (int i = 0; i < output.size(); i++) {

        double total;
        for (int k = 0; k < hidden.size(); k++) {

            total += hidden[k] * weights2[k][i];

        }

        output[i] = sigmoid(total);

    }

    int action = 0;
    double best = output[0];
    for (int i = 0; i < output.size(); i++) {

        if (output[i] > best) {

            action = i;
            best = output[i];

        }

    }
    
    return action;

}