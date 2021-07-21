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

            weightSet.push_back(((double) rand() / RAND_MAX) *  10 - 5.0);

        }
        weights1.push_back(weightSet);

    }

    for (int i = 0; i < 8; i++) {

        std::vector<double> weightSet;
        for (int k = 0; k < 4; k++) {

            weightSet.push_back(((double) rand() / RAND_MAX) * 10 - 5.0);

        }
        weights2.push_back(weightSet);

    }

    x = bX;
    y = bY;
    hunger = 30;
    thirst = 20;
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

void Bunny::reset(int bX, int bY) {

    x = bX;
    y = bY;
    hunger = 30;
    thirst = 20;
    fitness = 0;
    alive = true;

}

void Bunny::repredouce(Bunny bunny1, Bunny bunny2) {

    int cutoff = rand() % 5 + 1;
    int cutoff2 = rand() % (10 - cutoff) + cutoff;

    for (int k = 0; k < cutoff; k++) {

        std::vector<double> newWeightSet = bunny1.getWeights1()[k];
        weights1[k] = newWeightSet;

    }

    for (int k = cutoff; k < cutoff2; k++) {

        std::vector<double> newWeightSet = bunny2.getWeights1()[k];
        weights1[k] = newWeightSet;

    }

    for (int k = cutoff2; k < weights1.size(); k++) {

        std::vector<double> newWeightSet = bunny1.getWeights1()[k];
        weights1[k] = newWeightSet;

    }

    cutoff = rand() % 4 + 1;
    cutoff2 = rand() % (8 - cutoff) + cutoff;

    for (int k = 0; k < cutoff; k++) {

        std::vector<double> newWeightSet = bunny2.getWeights2()[k];
        weights2[k] = newWeightSet;

    }

    for (int k = cutoff; k < cutoff2; k++) {

        std::vector<double> newWeightSet = bunny1.getWeights2()[k];
        weights2[k] = newWeightSet;

    }

    for (int k = cutoff2; k < weights2.size(); k++) {

        std::vector<double> newWeightSet = bunny2.getWeights2()[k];
        weights2[k] = newWeightSet;

    }

    for (int i = 0; i < weights1.size(); i++) {

        for (int k = 0; k < weights1[i].size(); k++) {

            double mutate = ((double) rand() / RAND_MAX) * 100;
            if (mutate < 5) {

                weights1[i][k] = ((double) rand() / RAND_MAX) *  10 - 5.0;

            }

        }

    }

    for (int i = 0; i < weights2.size(); i++) {

        for (int k = 0; k < weights2[i].size(); k++) {

            double mutate = ((double) rand() / RAND_MAX) * 100;
            if (mutate < 5) {

                weights2[i][k] = ((double) rand() / RAND_MAX) *  10 - 5.0;

            }

        }

    }

}