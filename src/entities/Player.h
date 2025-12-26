#pragma once

#include <Arduboy2.h>
#include "../utils/Constants.h"
#include "../utils/Enums.h"
#include "../utils/Utils.h"
#include "Card.h"

struct Player {


    private:
    
        uint8_t health;
        uint8_t defeatCardIdx;

        Card cards[4];
        Card defeatCards[10];
        Card weapon;

    public:

        uint8_t getHealth()                             { return this->health; }
        Card &getCard(uint8_t idx)                      { return this->cards[idx]; }
        Card &getDefeatCard(uint8_t idx)                { return this->defeatCards[idx]; }
        Card &getWeapon()                               { return this->weapon; }

        void setHealth(uint8_t val)                     { this->health = val; }
        void setCard(uint8_t idx, Card &card)           { this->cards[idx] = card; }
        void setWeapon(Card &card)                      { this->weapon = card; }


        uint8_t getCardCount() {
        
            uint8_t count = 0;

            if (this->getCard(0).getRank() != Rank::None) count++;
            if (this->getCard(1).getRank() != Rank::None) count++;
            if (this->getCard(2).getRank() != Rank::None) count++;
            if (this->getCard(3).getRank() != Rank::None) count++;

            return count;

        }

        uint8_t getWeaponValue() {
        
            if (this->defeatCardIdx > 0) {

                if (this->defeatCards[0].getRank() < this->getWeapon().getRank()) {
                    return static_cast<uint8_t>(this->defeatCards[0].getRank());
                }

            }
            
            return static_cast<uint8_t>(this->weapon.getRank());
        
        }

        void moveCards() {
        
            while (this->cards[0].getRank() == Rank::None) {

                for (uint8_t i = 0; i < 3; i++) {

                    this->cards[i].setRank(this->cards[i + 1].getRank());
                    this->cards[i].setSuit(this->cards[i + 1].getSuit());

                    this->cards[i + 1].setRank(Rank::None);
                    this->cards[i + 1].setSuit(Suit::None);

                }

            }

        }

        void reset() {

            this->health = 20;
            this->defeatCardIdx = 0; 
            this->weapon.reset(); 

            for (uint8_t i = 0; i < 4; i++) {
            
                this->cards[i].reset();

            }
        
            for (uint8_t i = 0; i < 10; i++) {
            
                this->defeatCards[i].reset();

            }

        }

        void clearDefeated() {

            for (uint8_t i = 0; i < 10; i++) {
                this->defeatCards[i].reset();
            }

            this->defeatCardIdx = 0;

        }

        void addDefeatCard(Card &card) {

            if (defeatCardIdx > 0) {
            
                for (uint8_t i = 9; i > 0; i--) {

                    this->defeatCards[i].setRank(this->defeatCards[i - 1].getRank());
                    this->defeatCards[i].setSuit(this->defeatCards[i - 1].getSuit());

                }

            }

            this->defeatCards[0].init(card.getSuit(), card.getRank());
            defeatCardIdx++;

        }

        void incHealth(uint8_t val) {
        
            this->health = this->health + val;
            if (this->health > 20) this->health = 20;

        }

        void decHealth(uint8_t val) {
        
            if (this->health< val) this->health = val;
            this->health = this->health - val;
            
        }

        void playCard(uint8_t idx, bool isHumanPlayer) {

            Card &card = this->cards[idx];

        }

        void addCard(Card *card)   { 

            #if defined(DEBUG) && defined(DEBUG_PLAY_ADDCARD)
                DEBUG_PRINT(F("Card "));
                DEBUG_PRINT(getCardCount());
                DEBUG_PRINT_SPACE();
                DEBUG_PRINT_CARD(card->getSuit(), card->getRank());
                DEBUG_PRINTLN();
            #endif

            this->cards[this->getCardCount()].init(card->getSuit(), card->getRank()); 

        }

};
