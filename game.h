#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <iostream>
#include <cmath>
#include <sstream>

#include "Character.h"
#include "Map.h"
#include "Dots.h"
#include "Pacman.h"
#include "Enemy.h"

#include <SFML/Graphics.hpp>

class Game
{
private:
    sf::Clock clock;
    double time = 0;

    Map map;

    int move = 0;

    int t50 = 0;
    int t100 = 0;
    int t150 = 0;

    int k = 2;

    Enemy enemy[5];

    Dots dots;

    sf::Font font;
    sf::Text text;

    std::stringstream ss;

public:
Game(int petoon)
{
    enemy[0].init(1, 1);
    enemy[1].init(16, 17);

    font.loadFromFile("res/arial.ttf");


    text.setFont(font);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::Blue);
    text.setPosition(X*N/2 - 100, X*N + 10);
}

void check_events(sf::RenderWindow* window)
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window->close();
                break;

            default:
                break;
        }
    }


    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        move = 4;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        move = 2;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        move = 3;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        move = 1;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        for(int i = 0; i < k; i++)
            enemy[i].make_disgrace();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::V))
    {
        fail = -1;
    }

}




void game_process()
    {
        Pacman packman(&dots);
        sf::RenderWindow window(sf::VideoMode(X*N, X*N + 100), "Packman 2.0");

        while (window.isOpen())
        {
            double timeA = clock.getElapsedTime().asMicroseconds();
            clock.restart();
            //cout<<timeA/0.4e4<<endl;
            cout<<scoreMax<<endl;
            timeA = timeA/0.4e4*1.3;
            timeA = (timeA > 3)?0.5:timeA;

            check_events(&window);
            packman.move(&move, timeA);

            if(score >= 30 && t50 == 0)
            {
                t50 = 1;
                enemy[2].init((N - 1)/2, (N - 1)/2);
                ++k;
            }
            else if(score >= 60 && t100 == 0)
            {
                t100 = 1;
                enemy[3].init((N - 1)/2, (N - 1)/2);
                ++k;
            }
            else if(score >= 90 && t150 == 0)
            {
                t150 = 1;
                enemy[4].init((N - 1)/2, (N - 1)/2);
                ++k;
            }

            for(int i = 0; i < k; i++)
            {
                enemy[i].move(packman.get_xi(), packman.get_yi(), timeA);
                enemy[i].check_fail(packman.get_x(), packman.get_y());
            }

            ss.str("");
            ss << "Score - " << score;
            text.setString(ss.str());

            window.clear();

            if (score == scoreMax) fail = - 1;

            if(fail > 1)
            {
                dots.draw(&window);
                map.draw(&window);
                packman.draw(&window);
                for(int i = 0; i < k; i++)
                {
                    enemy[i].draw(&window);
                }
                window.draw(text);
            }

            else if(fail == 1)
            {
                ss.str("");
                ss << "FAIL";
                text.setString(ss.str());
                window.draw(text);
                window.display();

                clock.restart();
                while(time < 1.0)
                {
                    time = clock.getElapsedTime().asSeconds();
                }
                window.close();

            }
            else if(fail == -1)
            {
                ss.str("");
                ss << "WICTORY";
                text.setString(ss.str());
                window.draw(text);
                window.display();

                clock.restart();
                while(time < 3.0)
                {
                    time = clock.getElapsedTime().asSeconds();
                }
                window.close();
            }

            if (dis == 3)
            {
                for(int i = 0; i < k; i++)
                    enemy[i].make_disgrace();
                dis = 0;
            }

            window.display();
        }
    }
};

#endif // GAME_H_INCLUDED
