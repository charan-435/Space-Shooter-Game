#ifndef _BULLET_H_
#define _BULLET_H_
class Bullet
{
    public:
        Bullet(WINDOW* win,float y,int x,char c);
        void mv(float dist);
        void del(std::vector<Bullet> bullets,int i);
        void display();
        float yLoc;
        float xLoc;
    private:
        
        char ch;
        WINDOW* curwin;

};
Bullet::Bullet(WINDOW* win,float y,int x,char c)
{
    curwin=win;
    xLoc=x;
    yLoc=y;
    ch=c;
}
void Bullet::mv(float dist)
{
    mvwaddch(curwin,yLoc,xLoc,' ');
    yLoc-=dist;

}
void Bullet::del(std::vector<Bullet> bullets,int i)
{
    if(yLoc<-1)
    {
        bullets.erase(bullets.begin()+i);
    }
}
void Bullet::display()
{
    mvwaddch(curwin,yLoc,xLoc,ch);
}

#endif