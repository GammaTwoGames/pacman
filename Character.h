#ifndef Character_h
#define Character_h

#include <SFML/Graphics.hpp>

class Character
{
protected:
    int r;
    double x;
    double y;
    int xi;
    int yi;
    float count = 0;
    int mov;
    double vel;

public:
    virtual void draw(sf::RenderWindow* window) = 0;
    double get_x()
    {
        return x;
    }
    double get_xi()
    {
        return xi;
    }
    double get_yi()
    {
        return yi;
    }

};

#endif /* Character_h */
