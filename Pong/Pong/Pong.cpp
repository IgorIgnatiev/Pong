// Pong.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include"C_Player.h"
#include"C_Ball.h"
#include<SFML/Graphics.hpp>

using namespace sf;


void move_1(C_Ball& obj)
{
    obj.move();
}


int main()
{
    RenderWindow window(VideoMode(1000, 500), "Pong");
    C_Player player_1(20.0f, 60.0f, 40, 10);
    C_Player player_2(20.0f, 60.0f, 940, 10);
    C_Ball ball(20.0f, 20.0f, 100, 100, 1000, 500);
    Font font;
    Text text;
    Text won;
    bool win = false;
    won.setFont(font);
    won.setCharacterSize(100);
    won.setPosition(50, 200);
    won.setFillColor(Color::White);
    text.setFont(font);
    if (!font.loadFromFile("font.ttf"))
    {
        std::cout << "Error\n";
    }

    std::thread* ball_move = new std::thread(move_1, std::ref(ball));
    ball_move->detach();

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Up && player_2.getPosition().y > 0)
                {
                    player_2.setPosition(player_2.getPosition().x, player_2.getPosition().y - 20);
                }
                else if (event.key.code == Keyboard::Down && (player_2.getPosition().y + player_2.getSize().y) < window.getSize().y)
                {
                    player_2.setPosition(player_2.getPosition().x, player_2.getPosition().y + 20);
                }
                else if (event.key.code == Keyboard::W && player_1.getPosition().y > 0)
                {
                    player_1.setPosition(player_1.getPosition().x, player_1.getPosition().y - 20);
                }
                else if (event.key.code == Keyboard::S && (player_1.getPosition().y + player_1.getSize().y) < window.getSize().y)
                {
                    player_1.setPosition(player_1.getPosition().x, player_1.getPosition().y + 20);
                }
            }
        }
        if (ball.getPosition().x + ball.getSize().x == player_2.getPosition().x && ball.getPosition().y + ball.getSize().y >= player_2.getPosition().y && ball.getPosition().y + ball.getSize().y <= player_2.getPosition().y + player_2.getSize().y)
        {
            short* r = new short(rand() % 3);
            ball.set_move_x(false);
            if (*r == 1)
            {
                ball.set_move_y(true);
            }
            else
            {
                ball.set_move_y(false);
            }
            delete r;
        }
        else if (ball.getPosition().x == player_1.getPosition().x + player_1.getSize().x && ball.getPosition().y + ball.getSize().y >= player_1.getPosition().y && ball.getPosition().y + ball.getSize().y <= player_1.getPosition().y + player_1.getSize().y)
        {
            short* r = new short(rand() % 3);
            ball.set_move_x(true);
            if (*r == 1)
            {
                ball.set_move_y(true);
            }
            else
            {
                ball.set_move_y(false);
            }
            delete r;
        }
        if (ball.getPosition().x <= 0)
        {
            player_2.inc();
            std::this_thread::sleep_for(std::chrono::seconds(2));
            ball.setPosition(100, window.getSize().y / 2);
            ball.set_move_x(true);
            
        }
        else if (ball.getPosition().x >= window.getSize().x)
        {
            player_1.inc();
            std::this_thread::sleep_for(std::chrono::seconds(2));
            ball.setPosition(900, window.getSize().y / 2); 
            ball.set_move_x(false);
        }
        char* score =(char*) malloc(4);
        _itoa_s(player_1.get_points(), score, 2, 10);
        strcpy_s(score + 1, 2, ":");
        _itoa_s(player_2.get_points(), score + 2, 2, 10);
 
        text.setString(score);
        text.setFillColor(Color::White);
        text.setPosition(500, 0);
       

        window.clear();
        window.draw(player_1);
        window.draw(player_2);
        window.draw(ball);
        window.draw(text);

        if (player_1.get_points() == 3)
        {
            won.setString("Winner: player_1");
            window.draw(won);
            win = true;

        }
        else if (player_2.get_points() == 3)
        {
            won.setString("Winner: player_2");
            window.draw(won);
            win = true;
        }
        window.display();
        if (win == true)
        {
            system("pause");
        }
        delete score;
    }
}

