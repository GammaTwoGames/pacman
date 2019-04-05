#ifndef Character_h
#define Character_h

class Character
{
protected:
    int r;
    double x;
    double y;
    int xi;
    int yi;
    int test_228;
    int count;
    int mov;
    double vel;
public:
    virtual void draw(sf::RenderWindow* window) = 0;
};

#endif /* Character_h */
