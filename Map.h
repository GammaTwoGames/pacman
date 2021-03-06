#ifndef Map_h
#define Map_h


#include <SFML/Graphics.hpp>

int MAP_PRE[N][N] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 3, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 3, 1},
    {1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
    {1, 0, 1, 1, 0, 1, 1, 1, 0, 3, 0, 1, 1, 1, 0, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
    {1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1},
    {1, 0, 1, 1, 0, 1, 0, 1, 1, 9, 1, 1, 0, 1, 0, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 9, 9, 9, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1},
    {1, 3, 1, 1, 0, 1, 0, 0, 0, 3, 0, 0, 0, 1, 0, 1, 1, 3, 1},
    {1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
int MAP[N][N];


class Map
{
private:
    int map[N][N];
    void draw_rect(sf::RenderWindow* window,int i, int j, int k);
public:
    Map();
    void draw(sf::RenderWindow* window);
};

Map::Map()
{
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            MAP[i][j] = MAP_PRE[j][i];
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            map[i][j] = MAP[i][j];
    scoreMax = 0;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            if (MAP_PRE[j][i] == 0) scoreMax++;
}

void Map::draw_rect(sf::RenderWindow* window,int i, int j, int k)
{
    float thick = 0.2;
    sf::RectangleShape shape;
    shape.setFillColor(sf::Color::Blue);
    if (k == 0)
    {
        shape.setSize(sf::Vector2f(X, X*thick));
        shape.setPosition(X*i, X*j);
    }
    if (k == 1)
    {
        shape.setSize(sf::Vector2f(X*thick, X));
        shape.setPosition(X*i + X*(1 - thick), X*j);
    }
    if (k == 2)
    {
        shape.setSize(sf::Vector2f(X, X*thick));
        shape.setPosition(X*i, X*j + X*(1 - thick));
    }
    if (k == 3)
    {
        shape.setSize(sf::Vector2f(X*thick, X));
        shape.setPosition(X*i, X*j);
    }
    shape.setOutlineThickness(0);
    window -> draw(shape);
}

void Map::draw(sf::RenderWindow* window)
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(map[i][j] == 1)
            {
                if (j - 1 >= 0)
                    if (map[i][j - 1] != 1)
                        draw_rect(window, i, j, 0);
                if (i + 1 < N)
                    if (map[i + 1][j] != 1)
                        draw_rect(window, i, j, 1);
                if (j + 1 < N)
                    if (map[i][j + 1] != 1)
                        draw_rect(window, i, j, 2);
                if (i - 1 >= 0)
                    if (map[i - 1][j] != 1)
                        draw_rect(window, i, j, 3);
            }
        }
    }
}

#endif /* Map_h

