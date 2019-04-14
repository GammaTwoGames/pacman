#ifndef Dots_h
#define Dots_h

#include <SFML/Graphics.hpp>


class Dots
{
    int map[N][N];
public:
    Dots();
    void draw(sf::RenderWindow* window);
    void check(int i, int j);
};

Dots::Dots()
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            map[i][j] = MAP[i][j];
        }
    }
}

void Dots::draw(sf::RenderWindow* window)
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(map[i][j] == 0)
            {
                sf::CircleShape shape;
                shape.setRadius(4);
                shape.setFillColor(sf::Color::Yellow);
                shape.setPosition(X*i + X/2, X*j + X/2);
                shape.setOrigin(4, 4);
                window -> draw(shape);
            }
            if(map[i][j] == 3)
            {
                sf::CircleShape shape;
                shape.setRadius(10);
                shape.setFillColor(sf::Color::Yellow);
                shape.setPosition(X*i + X/2, X*j + X/2);
                shape.setOrigin(10, 10);
                window -> draw(shape);
            }
        }
    }
}

void Dots::check(int i, int j)
{
    if(map[i][j] == 0)
    {
        ++score;
        if(score == 188)
        {
            fail = -1;
        }
        map[i][j] = 2;
    }

    if(map[i][j] == 3)
    {
        dis = 3;
        map[i][j] = 2;
    }
}

#endif /* Dots_h */
