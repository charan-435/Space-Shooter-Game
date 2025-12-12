#include<bits/stdc++.h>
#include "player.h"
#include "bullet.h"
#include "enemies.h"
#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_
using namespace std;
pair<bool, int> collision(const vector<Bullet *> bullets, Enemy *enemy)
{
    for (int i = 0; i < bullets.size(); i++)
    {
        if (bullets[i]->xLoc > enemy->xLoc && bullets[i]->xLoc < (enemy->xLoc + (enemy->ch).size()) && bullets[i]->yLoc <= enemy->yLoc)
        {
            return {1, i};
        }
    }
    return {0, -1};
}
pair<bool, int> player_collision(const vector<Bullet *> bullets, Player *player)
{
    for (int i = 0; i < bullets.size(); i++)
    {
        if (bullets[i]->xLoc > player->xLoc && bullets[i]->xLoc < (player->xLoc + (player->ch).size()) && bullets[i]->yLoc >= player->yLoc)
        {
            return {1, i};
        }
    }
    return {0, -1};
}
void spawn_enemy(WINDOW* game_win,vector<Enemy*> &enemies,vector<float> &times,float enemy_speed,int xLoc)
{
    Enemy *enemy = new Enemy(game_win, 2,xLoc, enemy_speed, ">>|<<");
    enemies.push_back(enemy);
    times.push_back(0);
}
void delete_enemy(vector<Enemy*> &enemies,int i,vector<float> &times)
{
    delete enemies[i];
    enemies.erase(enemies.begin() + i);
    times.erase(times.begin() + i);
}
void delete_bullet(vector<Bullet*> &bullets,int i)
{
    delete bullets[i];
    bullets.erase(bullets.begin() + i);
}
int Random(int &prev,int max,int size)
{
    while(true)
    {
        int lat=rand()%max;
        if(abs(lat-prev)>size)
        {
            prev=lat;
            return prev;
        }
    }

}
#endif