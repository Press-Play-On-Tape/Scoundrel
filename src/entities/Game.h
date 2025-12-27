#pragma once

#include <Arduboy2.h>
#include "../utils/Constants.h"
#include "../utils/Enums.h"
#include "Card.h"
#include "Player.h"

struct Game {

    private:

        uint8_t round = 0;
        uint16_t randomSeed = 0;
        uint16_t frameCount = 0;

        bool healthPlayed = false;
        bool run = false;
        bool runPrevRound = false;

        CursorPosition cursorPosition = CursorPosition::Card_00;
        int8_t healthCount = 0;

        Player player;
        Deck deck;

    public:

        uint16_t getFrameCount()                        { return this->frameCount; }
        uint16_t getFrameCount(uint8_t val)             { return this->frameCount % val < val / 2; }
        uint8_t getRound()                              { return this->round; }
        int8_t getHealthCount()                         { return this->healthCount; }
        bool getHealthPlayed()                          { return this->healthPlayed; }
        bool getRun()                                   { return this->run; }
        bool getRunPrevRound()                          { return this->runPrevRound; }

        Player &getPlayer()                             { return this->player; }
        Deck &getDeck()                                 { return this->deck; }
        CursorPosition getCursorPosition()              { return this->cursorPosition; }

        void setRandomSeed(uint16_t val)                { this->randomSeed = val; }
        void setFrameCount(uint16_t val)                { this->frameCount = val; }
        void setRound(uint8_t val)                      { this->round = val; }
        void setHealthCount(int8_t val)                 { this->healthCount = val; }
        void setHealthPlayed(bool val)                  { this->healthPlayed = val; }
        void setRun(bool val)                           { this->run = val; }
        bool setRunPrevRound(bool val)                  { this->runPrevRound = val; }

        void setPlayer(Player &val)                     { this->player = val; }
        void setDeck(Deck &val)                         { this->deck = val; }
        void setCursorPosition(CursorPosition val)      { this->cursorPosition = val; }

        void resetRound() {
        
            this->healthPlayed = false;
            this->run = false;
            this->runPrevRound = false;

        }

        void incFrameCount() {

            this->frameCount++;

        }

        void resetFrameCount() {

            this->frameCount = 0;
            
        }

        void decHealthCount() {

            this->healthCount--;

        }

        void incHealthCount() {

            this->healthCount++;

        }

};