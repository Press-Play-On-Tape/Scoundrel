#pragma once

#include <Arduboy2.h>
#include "../utils/Constants.h"
#include "../utils/Enums.h"
#include "Card.h"
#include "Player.h"

struct Game {

    private:

        // Card hand[4];
        uint8_t round = 0;
        uint16_t randomSeed = 0;
        uint16_t frameCount = 0;
        bool healthPlayed = false;
        CursorPosition cursorPosition = CursorPosition::Card_00;
        int8_t healthCount = 0;

    public:

        Player player;
        Deck deck;
//        GameRound *gameRound;

        uint16_t getFrameCount()                        { return this->frameCount; }
        uint16_t getFrameCount(uint8_t val)             { return this->frameCount % val < val / 2; }
        bool getHealthPlayed()                          { return this->healthPlayed; }
        // Card *getHand(uint8_t playerIdx)                { return &this->hand[playerIdx]; }
        uint8_t getRound()                              { return this->round; }
        int8_t getHealthCount()                         { return this->healthCount; }
        CursorPosition getCursorPosition()              { return this->cursorPosition; }

        void setHealthPlayed(bool val)                  { this->healthPlayed = val; }
        void setRandomSeed(uint16_t val)                { this->randomSeed = val; }
        void setFrameCount(uint16_t val)                { this->frameCount = val; }
        void setCursorPosition(CursorPosition val)      { this->cursorPosition = val; }
        void setRound(uint8_t val)                      { this->round = val; }
        void setHealthCount(int8_t val)                 { this->healthCount = val; }

        void resetRound() {
        
            this->healthPlayed = false;
            // this->highestBid.reset(Constants::No_Player);

            for (uint8_t i = 0; i < 4; i++) {

                // this->hand[i].reset();
                // this->playedCards[i] = 0;
                // this->tricksWon[i] = 0;

                // for (uint8_t playerIdx = 0; playerIdx < 4; playerIdx++) {
                //     this->hasSuitInHand[playerIdx][i] = TriState::Maybe; 
                // }

            }

        }


        void resetHand(uint8_t winningPlayer) {
        
            // this->firstPlayer = winningPlayer;
            // this->currentPlayer = winningPlayer;

        }

        void resetHand() {

            // for (uint8_t i = 0; i < 4; i++) {
            //     this->hand[i].reset();
            // }

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