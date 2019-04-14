#ifndef Enemy_h
#define Enemy_h


#include <SFML/Graphics.hpp>

using namespace std;

class Enemy : public Character
{
private:
    //int ans[];
    int disgrace;
    bool looking();
    int pifagor(int p_xi, int p_yi, int dx, int dy);
    void move_left(float time);
    void move_down(float time);
    void move_right(float time);
    void move_up(float time);
    bool move_simple(int dr, float time);
    sf::Texture texture1;
    sf::Texture texture2;
public:
    Enemy();
    int good_way(int p_xi, int p_yi, int n);
    void init(int _xi, int _yi);
    void draw(sf::RenderWindow* window);
    void move(int p_xi, int p_yi, float time);
    void check_fail(double p_x, double p_y);

    void make_disgrace()
    {
        disgrace = 1000;
    }
};

Enemy::Enemy()
{
    r = X/2;
    count = 100;
    mov = 20;
    texture1.loadFromFile("res/ghost.jpeg", sf::IntRect(0, 0, 500, 500));
    texture2.loadFromFile("res/ghost2.jpeg", sf::IntRect(0, 0, 500, 500));
    disgrace = 0;
}
void Enemy::init(int _xi, int _yi)
{
    x = _xi*X + X/2;
    xi = _xi;
    y = _yi*X + X/2;
    yi = _yi;

    count = 100;
    mov = 21;

}


void Enemy::draw(sf::RenderWindow* window)
{
    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(2*r, 2*r));
    //shape.setFillColor(sf::Color::Red);
    shape.setPosition(x, y);
    shape.setOrigin(r, r);
    if (disgrace == 0)
        shape.setTexture(&texture1);
    else
        shape.setTexture(&texture2);
    window -> draw(shape);
}

void Enemy::move_left(float time)
{
    if(count > 0)
    {
        x -= 0.4 * time;
        count -= time;
    }
    else
    {
        --xi;
        count = 100;
        mov += 20;

        x = (xi)*X + 20;
    }
    //cout<<"done";

}
void Enemy::move_down(float time)
{
    if(count > 0)
    {
        y += 0.4*time;
        count -= time;
    }
    else
    {
        ++yi;
        count = 100;
        mov += 20;
        y = yi*X + 20;
    }

}
void Enemy::move_right(float time)
{
    if(count > 0)
    {
        x += 0.4*time;
        count -= time;
    }
    else
    {
        ++xi;
        count = 100;
        mov += 20;
        x = xi*X + 20;
    }

}
void Enemy::move_up(float time)
{
    if(count > 0)
    {
        y -= 0.4*time;
        count -= time;
    }
    else
    {
        --yi;
        count = 100;
        mov += 20;
        y = yi*X + 20;
    }

}

bool Enemy::looking()
{
    bool rb = 1;
    if (((MAP[xi - 1][yi] == 1) && (MAP[xi + 1][yi] == 1)) && ((MAP[xi][yi - 1] == 0) && (MAP[xi][yi + 1] == 0))) rb = 0;
    if (((MAP[xi - 1][yi] == 0) && (MAP[xi + 1][yi] == 0)) && ((MAP[xi][yi - 1] == 1) && (MAP[xi][yi + 1] == 1))) rb = 0;
    return rb;
}

int Enemy::pifagor(int p_xi, int p_yi, int dx, int dy)
{
    int real_length;
    real_length = (p_xi - xi)*(p_xi - xi) + (p_yi - yi)*(p_yi - yi);
    int future_length;
    future_length = (p_xi - xi - dx)*(p_xi - xi - dx) + (p_yi - yi - dy)*(p_yi - yi - dy);
    return real_length - future_length;
}

int comp(const void *i, const void *j)
{
    return *(int*)i - *(int*)j;
}

int Enemy::good_way(int p_xi, int p_yi, int n)
{
    int dl = - 1e6;
    int ans[4];
    int pif[4];
    pif[0] =  pifagor(p_xi, p_yi, 0, - 1);
    pif[1] =  pifagor(p_xi, p_yi, 0,   1);
    pif[2] =  pifagor(p_xi, p_yi, 1,   0);
    pif[3] =  pifagor(p_xi, p_yi,-1,   0);

    for (int i = 0; i < 4; i ++)
         if (pif[i] > dl) {ans[0] = i + 1; dl = pif[i];}
    dl = - 1e6;
    for (int i = 0; i < 4; i ++)
         if ((pif[i] > dl) && (i != ans[0] - 1)) {ans[1] = i + 1; dl = pif[i];}
    dl = - 1e6;
    for (int i = 0; i < 4; i ++)
         if ((pif[i] > dl) && (i != ans[0] - 1) && (i != ans[1] - 1)) {ans[2] = i + 1; dl = pif[i];}
    dl = - 1e6;
    for (int i = 0; i < 4; i ++)
         if ((pif[i] > dl) && (i != ans[0] - 1) && (i != ans[1] - 1) && (i != ans[2] - 1)) {ans[3] = i + 1; dl = pif[i];}
    return ans[n];
}

bool Enemy::move_simple(int dr, float time)
{
        bool ret = 0;
        if((dr == 1) && (MAP[xi][yi - 1] != 1) && (MAP[xi][yi - 1] != 9))
        {
            mov = 1;
            move_up(time);
            ret = 1;
        }
        if((dr == 2) && MAP[xi][yi + 1] != 1 && MAP[xi][yi + 1] != 9)
        {
            mov = 2;
            move_down(time);
            ret = 1;
        }
        if((dr == 3) && MAP[xi + 1][yi] != 1 && MAP[xi + 1][yi] != 9)
        {
            mov = 3;
            move_right(time);
            ret = 1;
        }
        if((dr == 4)  && MAP[xi - 1][yi] != 1 && MAP[xi - 1][yi] != 9)
        {
            mov = 4;
            move_left(time);
            ret = 1;
        }
    return ret;

}

void Enemy::move(int p_xi, int p_yi, float time)
{
    if (disgrace == 0)
    {
        if (mov > 10)
        {
            if (looking() == 1)
            {
                bool a228 = 0;
                for (int i = 0; i < 4; i ++)
                    if (a228 == 0)
                    {
                        int gw = good_way(p_xi, p_yi, i);
                        a228 = move_simple(gw, time);
                    }
            }
            else
            {
                mov -= 10;
            }
        }
        else
        {
            switch (mov) {
                case 1:
                    move_up(time);
                    break;
                case 2:
                    move_down(time);
                    break;
                case 3:
                    move_right(time);
                    break;
                case 4:
                    move_left(time);
                    break;

                default:
                    break;
            }
        }
    }
    else
    {
        disgrace -= time;
        if (mov > 10)
        {
            if (looking() == 1)
            {
                bool a228 = 0;
                while (a228 == 0)
                {
                    a228 = move_simple(rand()%4 + 1,time);
                }
            }
            else
            {
                mov -= 10;
            }
        }
        else
        {
            switch (mov) {
                case 1:
                    move_up(time);
                    break;
                case 2:
                    move_down(time);
                    break;
                case 3:
                    move_right(time);
                    break;
                case 4:
                    move_left(time);
                    break;

                default:
                    break;
            }
        }

    }
}
void Enemy::check_fail(double p_x, double p_y)
{
    if(pow(p_x - x, 2) + pow(p_y - y, 2) < X*X/4)
    {
        if (disgrace == 0)
        {
            fail -= 1;
            xi = 11;
            yi = 11;
        }
        else
            init((N - 1)/2, (N - 1)/2);
    }
}

#endif /* Enemy_h */
