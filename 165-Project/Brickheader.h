#ifndef BRICKHEADER_H
#define BRICKHEADER_H
#include <iostream>
#include <vector>

using namespace std; 
class PowerUp {
public:
    PowerUp(int x, int y) : x(x), y(y) {}
    virtual ~PowerUp() {}

    virtual string applyEffect() = 0;

    int x, y;
};

class SpeedBoost : public PowerUp {
public:
    SpeedBoost(int x, int y) : PowerUp(x, y) {}

    string applyEffect() {
    powerUpMessage = "POWERUP: Speed Boost!";
    extern float ballVelX;
    extern float ballVelY;
    ballVelX += .7;
    ballVelY += 1;
    cout << powerUpMessage << endl;                                  
    return powerUpMessage;
}
private:
    std::string powerUpMessage;
};

class ExtraLife : public PowerUp {
public:
    ExtraLife(int x, int y) : PowerUp(x, y) {}

    string applyEffect() {
    powerUpMessage = "POWERUP: Extra Life!";
    extern int chances;
    chances += 1;
    cout << powerUpMessage << endl;
    return powerUpMessage;
}
private:
    std::string powerUpMessage;
};

class EnlargePaddle : public PowerUp {
public:
    EnlargePaddle(int x, int y) : PowerUp(x, y) {
    }

    string applyEffect() {
        powerUpMessage = "POWERUP: Paddle Enlarged!";
        cout << powerUpMessage << endl;
        extern float barWidth;
        barWidth += 5; // increase barWidth by 80
        return powerUpMessage;
    }
private:
    std::string powerUpMessage;
};

class Nothing : public PowerUp{
    public:
    Nothing(int x, int y):PowerUp(x, y){

    }
   string applyEffect() {
    powerUpMessage = "";
    cout << powerUpMessage << endl;
    return powerUpMessage;
}
private:
    std::string powerUpMessage;
};
class Nothing2 : public PowerUp{
    public:
    Nothing2(int x, int y):PowerUp(x, y){

    }
   string applyEffect() {
    powerUpMessage = "";
    cout << powerUpMessage << endl;
    return powerUpMessage;
}
private:
    std::string powerUpMessage;
};
class Nothing3 : public PowerUp{
    public:
    Nothing3(int x, int y):PowerUp(x, y){

    }
   string applyEffect() {
    powerUpMessage = "";
    cout << powerUpMessage << endl;
    return powerUpMessage;
}
private:
    std::string powerUpMessage;
};

#endif
