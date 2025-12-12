#ifndef _PLAYER_H_
#define _PLAYER_H_
#include<string>
#include<ncurses.h>
#include "bullet.h"
class Player
{
    public:
    Player(WINDOW* win,int y,int x,std::string s);
    void mv(float dist);
    void shoot(std::vector<Bullet*> &bullets);
    void display();
    float xLoc,yLoc;
    std::string ch;

    private:
    int xMax,yMax;
    WINDOW* curwin;
};

Player::Player(WINDOW* win,int y,int x,std::string s)
{
    curwin=win;
    yLoc=y;
    xLoc=x;
    getmaxyx(curwin,yMax,xMax);
    keypad(curwin,true);
    ch=s;
}
void Player::mv(float dist)
{
    xLoc+=dist;
    if(xLoc>xMax-1-ch.size()) xLoc=xMax-1-ch.size();
    if(xLoc<2){xLoc=1;}
}
void Player::shoot(std::vector<Bullet*> &bullets)
{
    Bullet *bul = new Bullet(curwin, (yLoc) - 1, (xLoc) + (ch).size() / 2, '!');
    bullets.push_back(bul);
}
void Player::display()
{
    mvwaddstr(curwin,yLoc,xLoc,ch.c_str());
}
#endif