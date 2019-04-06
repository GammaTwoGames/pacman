#ifndef Enemy_h
#define Enemy_h

using namespace std;

class Enemy : public Character
{
private:
    bool looking();
    int pifagor(int p_xi, int p_yi, int dx, int dy);
    void move_left();
    void move_down();
    void move_right();
    void move_up();
    sf::Texture texture;
public:
    Enemy();
    int good_way(int p_xi, int p_yi);
    void init(int _xi, int _yi);
    void draw(sf::RenderWindow* window);
    void move(int p_xi, int p_yi);
    void check_fail(double p_x, double p_y);
    int get_xi()
    {
        return looking();
    }
};

Enemy::Enemy()
{
    r = X/2;
    count = 100;
    mov = 20;
    texture.loadFromFile("res/ghost.jpeg", sf::IntRect(0, 0, 500, 500));
}
void Enemy::init(int _xi, int _yi)
{
    x = _xi*X + X/2;
    xi = _xi;
    y = _yi*X + X/2;
    yi = _yi;
}


void Enemy::draw(sf::RenderWindow* window)
{
    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(2*r, 2*r));
    //shape.setFillColor(sf::Color::Red);
    shape.setPosition(x, y);
    shape.setOrigin(r, r);
    shape.setTexture(&texture);
    window -> draw(shape);
}
void Enemy::move_left()
{
    if(count > 0)
    {
        x -= 0.4;
        --count;
    }
    else
    {
        --xi;
        count = 100;
        mov += 20;
    }
    //cout<<"done";

}
void Enemy::move_down()
{
    if(count > 0)
    {
        y += 0.4;
        --count;
    }
    else
    {
        ++yi;
        count = 100;
        mov += 20;
    }

}
void Enemy::move_right()
{
    if(count > 0)
    {
        x += 0.4;
        --count;
    }
    else
    {
        ++xi;
        count = 100;
        mov += 20;
    }

}
void Enemy::move_up()
{
    if(count > 0)
    {
        y -= 0.4;
        --count;
    }
    else
    {
        --yi;
        count = 100;
        mov += 20;
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

int Enemy::good_way(int p_xi, int p_yi)
{
    int ans = 0;
    int dl = - 1e6;
    if (pifagor(p_xi, p_yi, 0, - 1) > dl) {ans = 1; dl = pifagor(p_xi, p_yi, 0, - 1);}
    if (pifagor(p_xi, p_yi, 0,   1) > dl) {ans = 2; dl = pifagor(p_xi, p_yi, 0,   1);}
    if (pifagor(p_xi, p_yi, 1,   0) > dl) {ans = 3; dl = pifagor(p_xi, p_yi, 1,   0);}
    if (pifagor(p_xi, p_yi,-1,   0) > dl) {ans = 4; dl = pifagor(p_xi, p_yi,-1,   0);}
    return ans;
}

void Enemy::move(int p_xi, int p_yi)
{
    if (mov > 10)
    {
        if (looking() == 1)
        {
            int gw = good_way(p_xi, p_yi);
            cout<<"tuta"<<gw<<" "<<MAP[xi - 1][yi]<<endl;
            if((gw == 1) && (MAP[xi][yi - 1] != 1))
            {
                mov = 1;
                move_up();
            }
            if((gw == 2) && MAP[xi][yi + 1] != 1)
            {
                mov = 2;
                move_down();
            }
            if((gw == 3) && MAP[xi + 1][yi] != 1)
            {
                mov = 3;
                move_right();
            }
            if((gw == 4)  && MAP[xi - 1][yi] != 1)
            {
                mov = 4;
                move_left();
            }

            if (mov > 10)
            {
                if(p_yi - yi < 0 && MAP[xi][yi - 1] != 1)
                {
                    mov = 1;
                    move_up();
                }
                else if(p_yi - yi > 0 && MAP[xi][yi + 1] != 1)
                {
                    mov = 2;
                    move_down();
                }
                else if(p_xi - xi > 0 && MAP[xi + 1][yi] != 1)
                {
                    mov = 3;
                    move_right();
                }
                else if(p_xi - xi < 0 && MAP[xi - 1][yi] != 1)
                {
                    mov = 4;
                    move_left();

                }
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
                move_up();
                break;
            case 2:
                move_down();
                break;
            case 3:
                move_right();
                break;
            case 4:
                move_left();
                break;

            default:
                break;
        }
    }
}
void Enemy::check_fail(double p_x, double p_y)
{
    if(pow(p_x - x, 2) + pow(p_y - y, 2) < X*X/4)
    {
        fail = 1;
    }
}

#endif /* Enemy_h */
