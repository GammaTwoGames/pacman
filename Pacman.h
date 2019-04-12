#ifndef Pacman_h
#define Pacman_h

class Pacman : public Character
{
private:
    Dots* dots;
    sf::Texture texture[2];
    void move_left();
    void move_down();
    void move_right();
    void move_up();
    bool check_simple(int dr);
    bool move_simple(int dr);
    int next_mov = 0;
    bool looking();
public:
    Pacman(Dots* _dots);
    int get_xi();
    int get_yi();
    int get_x();
    int get_y();
    void draw(sf::RenderWindow* window);
    void move(int* move);
};

Pacman::Pacman(Dots* _dots): dots(_dots)
//Pacman::Pacman()
{
    x = N*X/2;
    xi = (N - 1)/2;
    y = 16.5*X;
    yi = 16;
    r = X/2;
    count = 100;
    texture[0].loadFromFile("res/pacman.jpg", sf::IntRect(0, 0, 225, 225));
    texture[1].loadFromFile("res/pacman.jpg", sf::IntRect(260, 0, 225, 225));
    mov = 0;
    vel = 0.4;
}
int Pacman::get_xi()
{
    return xi;
}
int Pacman::get_yi()
{
    return yi;
}
int Pacman::get_x()
{
    return x;
}
int Pacman::get_y()
{
    return y;
}



void Pacman::draw(sf::RenderWindow* window)
{
    sf::CircleShape shape;
    shape.setRadius(r);
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(x, y);
    shape.setOrigin(r, r);
    shape.setTexture(&texture[(count/40)%2]);
    //if (mov = 1) shape.rotate(-90);
    //if (mov = 2) shape.rotate(90);
    //if (mov = 3) shape.rotate(0);
    //if (mov = 4) shape.rotate(180);
    window -> draw(shape);
}
void Pacman::move_left()
{
    if(count > 0)
    {
        x -= vel;
        --count;
    }
    else
    {
        --xi;
        count = 100;
        dots -> check(xi, yi);
        //*move = 0;
    }

}
void Pacman::move_down()
{
    if(count > 0)
    {
        y += vel;
        --count;
    }
    else
    {
        ++yi;
        count = 100;
        dots -> check(xi, yi);
        //*move = 0;
    }

}
void Pacman::move_right()
{
    if(count > 0)
    {
        x += vel;
        --count;
    }
    else
    {
        ++xi;
        count = 100;
        dots -> check(xi, yi);
        //*move = 0;
    }

}
void Pacman::move_up()
{
    if(count > 0)
    {
        y -= vel;
        --count;
    }
    else
    {
        --yi;
        count = 100;
        dots -> check(xi, yi);
        //*move = 0;
    }

}

bool Pacman::check_simple(int dr)
{
        int xf = xi, yf = yi;
        /*if (mov == 1) yf -= 1;
        if (mov == 2) yf += 1;
        if (mov == 3) xf += 1;
        if (mov == 4) xf -= 1; */

        bool ret = 0;
        if((dr == 1) && (MAP[xf][yf - 1] != 1))
        {
            ret = 1;
        }
        if((dr == 2) && MAP[xf][yf + 1] != 1)
        {
            ret = 1;
        }
        if((dr == 3) && MAP[xf + 1][yf] != 1)
        {
            ret = 1;
        }
        if((dr == 4)  && MAP[xf - 1][yf] != 1)
        {
            ret = 1;
        }
    return ret;
}

bool Pacman::move_simple(int dr)
{
        bool ret = 0;
        if((dr == 1) && (MAP[xi][yi - 1] != 1))
        {
            mov = 1;
            move_up();
            ret = 1;
        }
        if((dr == 2) && MAP[xi][yi + 1] != 1)
        {
            mov = 2;
            move_down();
            ret = 1;
        }
        if((dr == 3) && MAP[xi + 1][yi] != 1)
        {
            mov = 3;
            move_right();
            ret = 1;
        }
        if((dr == 4)  && MAP[xi - 1][yi] != 1)
        {
            mov = 4;
            move_left();
            ret = 1;
        }
    return ret;

}

bool Pacman::looking()
{
    bool rb = 1;
    if (((MAP[xi - 1][yi] == 1) && (MAP[xi + 1][yi] == 1)) && ((MAP[xi][yi - 1] == 0) && (MAP[xi][yi + 1] == 0))) rb = 0;
    if (((MAP[xi - 1][yi] == 0) && (MAP[xi + 1][yi] == 0)) && ((MAP[xi][yi - 1] == 1) && (MAP[xi][yi + 1] == 1))) rb = 0;
    return rb;
}

void Pacman::move(int* move)
{
    next_mov = *move;
    if ((check_simple(next_mov)) && ((count > 90) )) mov = next_mov;
    bool a = move_simple(mov);


}

#endif /* Pacman_h */

