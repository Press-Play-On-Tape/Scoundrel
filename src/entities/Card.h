#pragma once

#include <Arduboy2.h>
#include "../utils/Constants.h"
#include "../utils/Enums.h"
#include "../utils/Utils.h"
#include "Card.h"

struct Card {

    private:

        Suit suit;
        Rank rank;

    public:

        Suit getSuit()                      { return this->suit; }
        Rank getRank()                      { return this->rank; }

        void setSuit(Suit val)              { this->suit = val; }
        void setRank(Rank val)              { this->rank = val; }

        void reset() {
        
            this->setSuit(Suit::None);
            this->setRank(Rank::None);
            
        }

        void init(uint8_t cardIndex) {

            this->suit = static_cast<Suit>(cardIndex / 13);
            this->rank = static_cast<Rank>(cardIndex % 13);

        }

        void init(Suit suit, uint8_t cardNumber) {

            this->suit = suit;
            this->rank = static_cast<Rank>(cardNumber);

        }

        void init(Suit suit, Rank rank) {

            this->suit = suit;
            this->rank = rank;

        }

        uint8_t getCardIndex() {

            return (3 * ((static_cast<uint8_t>(this->getSuit()) * 13) + (static_cast<uint8_t>(this->getRank()) - 2)));
            
        }

};

