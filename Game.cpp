//
// Created by Suliman Alsaid on 2/10/20.
//

#include "Game.h"
#include <cstdlib>
#include <ctime>

int randNum(){

    return rand() % 4;

}

Game::Game() {
    win.create(sf::VideoMode(800, 800), "Simon");

    for(sf::RectangleShape& shape: squares)
        shape.setSize({400, 400});

    squares[0].setPosition(0,0);
    squares[1].setPosition(400,0);
    squares[2].setPosition(0,400);
    squares[3].setPosition(400,400);

    squares[0].setFillColor({0, 200, 0});
    squares[1].setFillColor({200, 0, 0});
    squares[2].setFillColor({200, 200, 0});
    squares[3].setFillColor({0, 0, 200});


    for(sf::RectangleShape& shape: highlightedSquares)
        shape.setSize({400, 400});

    highlightedSquares[0].setPosition(0,0);
    highlightedSquares[1].setPosition(400,0);
    highlightedSquares[2].setPosition(0,400);
    highlightedSquares[3].setPosition(400,400);

    highlightedSquares[0].setFillColor({128, 255, 128});
    highlightedSquares[1].setFillColor({255, 128, 128});
    highlightedSquares[2].setFillColor({255, 255, 128});
    highlightedSquares[3].setFillColor({128, 128, 255});

    for(bool& b: highlight){
        b = false;
    }

    srand(time(NULL));

    win.setFramerateLimit(60);

    sequencePlayed = false;
    sequenceStarted = false;
    sequence.push_back(randNum());

    currentIndex = 0;

    buffers[0].loadFromFile("green.ogg");
    buffers[1].loadFromFile("red.ogg");
    buffers[2].loadFromFile("yellow.ogg");
    buffers[3].loadFromFile("blue.ogg");

    for(int i = 0; i < 4; i++) {
        sounds[i].setBuffer(buffers[i]);
    }

    loop();



}

void Game::loop() {
    while(true) {
        logic();
        input();
        draw();

    }

}

void Game::input() {
    sf::Event e;

    while(win.pollEvent(e)) {
        switch(e.type) {
            case sf::Event::MouseButtonPressed: {
                int xcor = e.mouseButton.x;
                int ycor = e.mouseButton.y;
                if (xcor < 400) {
                    if (ycor < 400) {
                        highlight[0] = true;
                        sounds[0].play();
                    }
                    else {
                        highlight[2] = true;
                        sounds[2].play();
                    }
                } else {
                    if (ycor < 400) {
                        highlight[1] = true;
                        sounds[1].play();
                    }
                    else {
                        highlight[3] = true;
                        sounds[3].play();
                    }
                }
                break;
            }
            case sf::Event::MouseButtonReleased: {
                for(int i = 0; i < 4; i++) {
                    if(highlight[i]) {
                        if(i == sequence[currentIndex]) {
                            currentIndex++;
                        } else {
                            currentIndex = 0;
                            sequencePlayed = false;
                            sequenceStarted = false;
                            sequence.clear();
                            sequence.push_back(randNum());
                        }
                    }
                    highlight[i] = false;

                }
                break;
            }
            case sf::Event::Closed:
                exit(0);

        }
    }

}

void Game::draw() {
    win.clear(sf::Color::Black);
    for(int i = 0; i < 4; i++){
        if(highlight[i]) {
            win.draw(highlightedSquares[i]);
        } else {
            win.draw(squares[i]);
        }
    }
    win.display();

}

void Game::logic() {
    if(!sequenceStarted) {
        clock.restart();
        sequencePlayed = false;
        sequenceStarted = true;
    }

    if(sequenceStarted && !sequencePlayed) {
        for(bool& b : highlight)
            b = false;
        double d = clock.getElapsedTime().asMilliseconds()/500.0;
        if((d-((int)d)) <= .5) {
            int i = (int)d;
            if (i > sequence.size() - 1)
                sequencePlayed = true;
            else {
                highlight[sequence[i]] = true;
                if(b != i){
                    b = i;
                    sounds[sequence[b]].play();
                }

            }
        }
    }

    if(sequencePlayed) {
        if(currentIndex >= sequence.size()) {
            if(!setPause) {
                clock.restart();
                setPause = true;
            }
            else if(clock.getElapsedTime().asMilliseconds() > 500){
                currentIndex = 0;
                sequencePlayed = false;
                sequenceStarted = false;
                sequence.push_back(randNum());
                setPause = false;
                b = -1;
            }
        }
    }


}


