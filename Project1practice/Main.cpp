#include <SFML/Graphics.hpp>
#include <time.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include<cmath>

using namespace sf;
const int Height = 21;
const int Width = 19;
const int ts = 25;

int q = 0;
bool life = true;
//Abstract Class
class sprites {
public:
    //Pure Virtual Function
    virtual void update() = 0;
};
//map generation
String TileMap[Height] = {
"AAAAAAAAAAAAAAAAAAA",
"A1       A       2A",
"A AA AAA A AAA AA A",
"A        A        A",
"A AA A AAAAA A AA A",
"A    A   A   A    A",
"AAAA AAA A AAA AAAA",
"BBBA A       A ABBB",
"AAAA A AAAAA A AAAA",
"BBBB   ABBBA   BBBB",
"AAAA A AAAAA A AAAA",
"BBBA A       A ABBB",
"AAAA A AAAAA A AAAA",
"A        A        A",
"A AA AAA A AAA AA A",
"A  A     C     A  A",
"AA A A AAAAA A A AA",
"A    A   A   A    A",
"A AAAAAA A AAAAAA A",
"A3               4A",
"AAAAAAAAAAAAAAAAAAA",
};
//Inheritance
class Player :public sprites{


public:
    float frame = 0;
    int x = 9, y = 15;
    int newx = 0, newy = 0;
    int rotate = 1, ti = 0;
    public:
    void update() {
        frame = frame + 0.01;
        if (frame > 5.0)
            frame = frame - 5.0;
        ti++;
        if (ti >= 300) {
            switch (rotate)
            {
            case 1:
                if (TileMap[y][newx + 1] != 'A')
                    newx += 1;
                break;
            case 2:
                if (TileMap[y][newx - 1] != 'A')
                    newx -= 1;
                break;
            case 3:
                if (TileMap[newy - 1][x] != 'A')
                    newy -= 1;
                break;
            case 4:
                if (TileMap[newy + 1][x] != 'A')
                    newy += 1;
                break;

            }
            ti = 0;
        }
        if (TileMap[newy][newx] == ' ' || TileMap[newy][newx] == 'B') {
            if (TileMap[newy][newx] == ' ')
                q++;
            if (TileMap[newy][newx] == '1' || TileMap[newy][newx] == '2' ||
                TileMap[newy][newx] == '3' || TileMap[newy][newx] == '4')
                life = false;
            TileMap[y][x] = 'B';
            TileMap[newy][newx] = 'C';
            x = newx;
            y = newy;



        }

        if (newy == 9 && (newx == 0 || newx == 18)) {
            if (newx == 0)
                newx = 17;
            else
                newx = 1;
            TileMap[y][x] = 'B';
            TileMap[newy][newx] = 'C';
            x = newx;
            y = newy;
        }
    }

};

class Enemy:public sprites  {
public:
    int x[4] = { 1, 17, 1, 17 }, y[4] = { 1, 1, 19, 19 };
    int newx[4] = { 0,0 ,0 , 0 }, newy[4] = { 0,0, 0, 0 };
    int rotate[4] = { 1,1,1,1 }, ti = 0;

    void update() {
        ti++;
        if (ti >= 300) {
            for (int i = 0; i < 4; i++) {
                rotate[i] = rand() % 4 + 1;
                newx[i] = x[i];
                newy[i] = y[i];
                switch (rotate[i])
                {
                case 1:
                    if (TileMap[y[i]][newx[i] + 1] != 'A')
                        newx[i] += 1;
                    break;
                case 2:
                    if (TileMap[y[i]][newx[i] - 1] != 'A')
                        newx[i] -= 1;
                    break;
                case 3:
                    if (TileMap[newy[i]-1][x[i] ]!= 'A')
                        newy[i] -= 1;
                    break;
                case 4:
                    if (TileMap[newy[i] + 1][x[i]] != 'A')
                        newy[i] += 1;
                    break;
                }
            }
            ti = 0;
        }
        for (int i = 0; i < 4; i++) {
            if (TileMap[newy[i]][newx[i]] == ' ' || TileMap[newy[i]][newx[i]] == 'B'||TileMap[newy[i]][newx[i]]=='C') {
                if (TileMap[newy[i]][newx[i]] == 'B')
                    TileMap[y[i]][x[i]] = 'B';
                else if (TileMap[newy[i]][newx[i]] == ' ')
                    TileMap[y[i]][x[i]] = ' ';
                else if (TileMap[newy[i]][newx[i]] == 'C')
                    life = false;
                if (i == 0)
                    TileMap[newy[i]][newx[i]] = '1';
                if (i == 1)
                    TileMap[newy[i]][newx[i]] = '2';
                if (i == 2)
                    TileMap[newy[i]][newx[i]] = '3';
                if (i == 3)
                    TileMap[newy[i]][newx[i]] = '4';
                x[i] = newx[i];
                y[i] = newy[i];
            }

            if (newy[i] == 9 && (newx[i] == 0 || newx[i] == 18)) {
                if (newx[i] == 0)
                    newx[i] = 17;
                else
                    newx[i] = 1;

                TileMap[y[i]][x[i]] = 'B';
                if (i == 0)
                    TileMap[newy[i]][newx[i]] = '1';
                if (i == 1)
                    TileMap[newy[i]][newx[i]] ='2';
                x[i] = newx[i];
                y[i] = newy[i];


            }
        }
    }
    
};
int main()
{
    srand(time((0)));
    sf::RenderWindow window(VideoMode(Width * ts, Height * ts), "Pacman", Style::Default);
    Texture t;
    t.loadFromFile("title.png");
    Sprite sprite(t);
    Texture yw;
    yw.loadFromFile("youwin.png");
    Sprite youwin(yw);
    youwin.setPosition(100, 210);  // function overwrites previous position
    Texture yl;
    yl.loadFromFile("youlose.png");
    Sprite youlose(yl);
    youlose.setPosition(100, 210);
    //Pointer to abstract base class
    sprites *upd;
    Player p;
    Enemy en;
    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();


            if (q < 171 && life)
                if (event.type == Event::KeyPressed) {
                    p.newx = p.x;
                    p.newy = p.y;
                    if (event.key.code == Keyboard::Right)
                        p.rotate = 1;
                    if (event.key.code == Keyboard::Left)
                        p.rotate = 2;
                    if (event.key.code == Keyboard::Up)
                        p.rotate = 3;
                    if (event.key.code == Keyboard::Down)
                        p.rotate = 4;
                }


        }
        if (q < 171 && life) {
            //Assign the adress of derived class object to base class pointer
            upd = &p;
            //update of player class is called
            upd->update();
            //Assign the adress of derived class object to base class pointer
            upd = &en;
            //update of player class is called
            upd->update();
        }
        window.clear(sf::Color::Black);

        for (int i = 0; i < Height; i++)
             for (int j = 0; j < Width; j++)
            {


                if (TileMap[i][j] == 'A')
                    sprite.setTextureRect(sf::IntRect(0, 0, ts, ts));

                if (TileMap[i][j] == 'C')
                    sprite.setTextureRect(sf::IntRect(ts * int(p.frame), ts * p.rotate, ts, ts));

                if (TileMap[i][j] == ' ')
                    sprite.setTextureRect(sf::IntRect(ts, 0, ts, ts));
                if (TileMap[i][j] == '1')
                    sprite.setTextureRect(IntRect(ts * 5, ts * en.rotate[0], ts, ts));
                if (TileMap[i][j] == '2')
                    sprite.setTextureRect(IntRect(ts * 5, ts * en.rotate[1], ts, ts));
                if (TileMap[i][j] == '3')
                    sprite.setTextureRect(IntRect(ts * 5, ts * en.rotate[2], ts, ts));
                if (TileMap[i][j] == '4')
                    sprite.setTextureRect(IntRect(ts * 5, ts * en.rotate[3], ts, ts));
                if (TileMap[i][j] == 'B')
                    continue;


                sprite.setPosition(j * ts, i * ts);
                window.draw(sprite);

            }
        
        if (q == 171)
            window.draw(youwin);
        if (!life)
            window.draw(youlose);
        window.display();


    }


    return 0;
}

