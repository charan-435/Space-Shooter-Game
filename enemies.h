#ifndef _ENEMY_H_
#define _ENEMY_H_
#include<string>
#include<ncurses.h>
class Enemy
{
    public:
    Enemy(WINDOW* win,int y,int x,int speed,std::string s);
    void mv(float dist);
    void shoot(std::vector<Bullet*> &enemy_bullets);
    void display();
    float xLoc,yLoc;
    int yMax,xMax;
    std::string ch;
    int speed;
    private:
    WINDOW* curwin;
};
Enemy::Enemy(WINDOW* win,int y,int x,int sp,std::string s)
{
    curwin=win;
    yLoc=y;
    xLoc=x;
    ch=s;
    speed=sp;
    getmaxyx(curwin,yMax,xMax);
}

void Enemy::mv(float dist)
{
    xLoc+=dist;
}
void Enemy::shoot(std::vector<Bullet*> &enemy_bullets)
{
    Bullet *bul = new Bullet(curwin, yLoc +1, xLoc + ch.size() / 2, '^');
    enemy_bullets.push_back(bul);
}
void Enemy::display()
{
    mvwaddstr(curwin,yLoc,xLoc,ch.c_str());
}
#endif