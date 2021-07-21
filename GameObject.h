#ifndef GameObjectH
#define GameObjectH

#include <string>

class GameObject {

    private:
        int type;
        std::string color;

    public:
        GameObject(int gType, std::string gColor);
        int getType() {return type;}
        std::string getColor() {return color;}

};

#endif