//
// Created by Suliman Alsaid on 2/10/20.
//

#ifndef SIMON_GAME_H
#define SIMON_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <vector>

class Game {
public:
    Game();
private:
    sf::RenderWindow win;
    sf::RectangleShape squares[4];
    sf::RectangleShape highlightedSquares[4];
    bool highlight[4];
    std::vector<int> sequence;
    std::vector<int> guesses;
    int currentIndex;
    sf::Clock clock;

    sf::SoundBuffer buffers[4];
    sf::Sound sounds[4];
    int b = -1;

    bool sequencePlayed;
    bool sequenceStarted;
    bool setPause = false;

    void loop();

    void input();

    void draw();

    void logic();
};


#endif //SIMON_GAME_H
