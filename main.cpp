#include "functions.h"
#include <cstdlib>
#include <chrono>
int main()
{
    int restart = 1;
    while (restart)
    {
        restart = 0;
        initscr();
        curs_set(0);
        noecho();
        set_escdelay(0); // No delay after ESC
        int ymax, xmax;
        srand(time(0));
        getmaxyx(stdscr, ymax, xmax);
        WINDOW *game_win = newwin(9 * ymax / 10, xmax, ymax / 10, 0);
        WINDOW *score_win = newwin(1 * ymax / 10, xmax, 0, 0);
        getmaxyx(game_win, ymax, xmax);
        refresh();
        box(game_win, 0, 0);
        wrefresh(game_win);
        nodelay(game_win, true);
        keypad(game_win, true);

        Player *p = new Player(game_win, ymax - 2, xmax / 2, "<<|>>");
        p->display();
        int player_speed = 2;
        // Bullet Variables
        vector<Bullet *> bullets;
        float bul_speed = 20;
        float bul_time = 0;
        float bul_cooldown = 0.2;
        // Enemy Variables
        vector<Enemy *> enemies;
        float enemy_speed = 5;
        float enemy_time = 0;
        float enemy_cooldown = 2;
        vector<Bullet *> enemy_bullets;
        float enemy_bul_cooldown = 2;
        int y_step = 2;
        vector<float> times;
        int score = 0;
        int lives = 3;
        bool running = true;
        bool paused = false;
        auto lastTime = chrono::steady_clock::now();

        while (running)
        {
            // time calculation

            // Player Movement
            int key;
            key = wgetch(game_win);
            if (key == 'q' || key == 27)
            {
                running = false;
                endwin();
                return 0;
            }
            if (key == KEY_UP && bul_time > bul_cooldown)
            {
                p->shoot(bullets);
                bul_time = 0;
            }
            if (key == KEY_RIGHT)
            {
                mvwaddstr(game_win, p->yLoc, p->xLoc, std::string(p->ch.size(), ' ').c_str());
                p->mv(player_speed);
            }
            else if (key == KEY_LEFT)
            {
                mvwaddstr(game_win, p->yLoc, p->xLoc, std::string(p->ch.size(), ' ').c_str());
                p->mv(-player_speed);
            }
            if (key == 'p')
            {
                paused = !paused;
                if (paused)
                {

                    string pause_msg = "PAUSED - Press 'p' to continue";
                    // Draw pause message in center of game window
                    mvwprintw(score_win, 2, xmax / 2 - pause_msg.size() / 2, "%s", pause_msg.c_str());
                    wrefresh(score_win);

                    // Block until 'p' is pressed again
                    int c;
                    while ((c = wgetch(game_win)) != 'p')
                    {
                        if (c == 'q' || c == 27)
                        {
                            running = false;
                            endwin();
                            return 0;
                        }
                    }
                    paused = false; // resume
                    wclear(score_win);
                    box(game_win, 0, 0);
                    wrefresh(score_win);
                    lastTime = chrono::steady_clock::now();
                    p->display(); // redraw player
                }
            }

            float dt = 0;
            if (!paused)
            {
                auto now = chrono::steady_clock::now();
                dt = chrono::duration<float>(now - lastTime).count();
                lastTime = now;
                bul_time += dt;
                enemy_time += dt;
                for (int i = 0; i < times.size(); i++)
                {
                    times[i] += dt;
                }
                int prev = 0;
                // Enemy Spawning
                if (enemy_time > enemy_cooldown)
                {
                    spawn_enemy(game_win, enemies, times, enemy_speed, Random(prev, xmax - 6, 5));
                    enemy_time = 0;
                }

                p->display();

                // Enemy Movement and Collision Detection
                for (int i = 0; i < enemies.size();)
                {
                    mvwaddstr(game_win, enemies[i]->yLoc, enemies[i]->xLoc, std::string(enemies[i]->ch.size(), ' ').c_str());
                    enemies[i]->mv(enemies[i]->speed * dt);
                    if (enemies[i]->xLoc > (xmax - enemies[i]->ch.size() - 2) && enemies[i]->speed > 0)
                    {
                        enemies[i]->speed = -enemies[i]->speed;
                        enemies[i]->yLoc += y_step;
                    }
                    else if (enemies[i]->xLoc < 2 && enemies[i]->speed < 0)
                    {
                        enemies[i]->speed = -enemies[i]->speed;
                        enemies[i]->yLoc += y_step;
                    }
                    auto col = collision(bullets, enemies[i]);
                    if (col.first)
                    {
                        score += 10;
                        mvwaddch(game_win, bullets[col.second]->yLoc, bullets[col.second]->xLoc, ' ');
                        delete_bullet(bullets, col.second);
                        delete_enemy(enemies, i, times);
                    }
                    else
                    {
                        enemies[i]->display();
                        i++;
                    }
                }

                // Enemy Bullets Spawning
                for (int i = 0; i < enemies.size(); i++)
                {
                    if (times[i] > enemy_bul_cooldown && abs(enemies[i]->xLoc - p->xLoc) < p->ch.size())
                    {
                        enemies[i]->shoot(enemy_bullets);
                        times[i] = 0;
                    }
                }
                // Enemy Bullets Deletion
                for (int i = 0; i < enemy_bullets.size();)
                {
                    enemy_bullets[i]->mv(-bul_speed * dt);
                    if (enemy_bullets[i]->yLoc > ymax - 1)
                    {
                        delete_bullet(enemy_bullets, i);
                    }
                    else
                    {
                        enemy_bullets[i]->display();
                        i++;
                    }
                }
                // Player Bullet Deletion
                for (int i = 0; i < bullets.size();)
                {
                    bullets[i]->mv(bul_speed * dt);
                    if (bullets[i]->yLoc < 1)
                    {
                        mvwaddch(game_win, bullets[i]->yLoc, bullets[i]->xLoc, ' ');
                        delete_bullet(bullets, i);
                    }
                    else
                    {
                        bullets[i]->display();
                        i++;
                    }
                }
                auto player_col = player_collision(enemy_bullets, p);
                if (player_col.first)
                {
                    mvwaddch(game_win, enemy_bullets[player_col.second]->yLoc, enemy_bullets[player_col.second]->xLoc, ' ');
                    delete_bullet(enemy_bullets, player_col.second);
                    lives -= 1;
                }
                for (int i = 0; i < enemies.size(); i++)
                {
                    if (enemies[i]->yLoc >= ymax || lives < 1)
                    {
                        string out = "GAME OVER\n";
                        string final_score="Your score is "+to_string(score);
                        string res = "Press 'r' to restart\n";
                        mvwprintw(game_win, ymax / 2, xmax / 2 - out.size() / 2, "%s", out.c_str());
                        mvwprintw(game_win, ymax / 2+2, xmax / 2 - final_score.size() / 2, "%s", final_score.c_str());
                        mvwprintw(game_win, ymax / 2 + 4, xmax / 2 - res.size() / 2, "%s", res.c_str());
                        wrefresh(game_win);
                        running = false;
                    }
                }
            }
            if (score > 150 && score < 400)
            {
                enemy_speed = 10;
                enemy_cooldown = 4;
                y_step = 3;
            }
            else if (score >= 400 && score < 600)
            {
                enemy_speed = 15;
                enemy_cooldown = 3;
                y_step = 4;
            }
            else if (score > 600 && score < 1000)
            {
                enemy_speed = 20;
                enemy_cooldown = 2;
                y_step = 5;
            }
            else if (score >= 1000 && score < 2000)
            {
                enemy_speed = 30;
                enemy_cooldown = 1;
                y_step = 6;
            }
            else if (score >= 2000)
            {
                enemy_speed = 40;
                enemy_cooldown = 0.5;
                y_step = 7;
            }
            mvwprintw(score_win, 1, 2, "SCORE: %d \n", score);
            mvwprintw(score_win, 3, 2, "Remaining Lives : %d", lives);
            wrefresh(score_win);
            wrefresh(game_win);
        }
        int ch;
        while (true)
        {
            ch = wgetch(game_win);
            if (ch == 'r')
            {
                restart = 1;
                delwin(score_win);
                delwin(game_win);
                endwin();
                break;
            }
            if (ch == 'q' || ch == 27)
            {
                restart = 0;
                endwin();
                break;
            }
        }
    }
    return 0;
}