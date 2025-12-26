struct Deck {

    private:

        Card deck[44];
        uint8_t deckSize = 0;

    public:

        uint8_t getCardsRemaining() {
            return this->deckSize;
        }

        void createDeck() {

            this->deckSize = 0;

            for (Suit suit = Suit::Spades; suit <= Suit::Hearts; suit++) {

                for (Rank rank = Rank::Two;

                    rank <= (suit == Suit::Clubs || suit == Suit::Spades ? Rank::Ace : Rank::Ten);
                    rank++) {

                    this->deck[this->deckSize].setSuit(suit);
                    this->deck[this->deckSize].setRank(rank);
                    this->deckSize++;

                }

            }

        }

        void shuffleDeck() {

            for (uint8_t i = 0; i < this->deckSize; i++) {

                uint8_t r = random(i, this->deckSize);
                Card temp = this->deck[i];
                this->deck[i] = this->deck[r];
                this->deck[r] = temp;

            }

        }

        // Deal a card (card is removed from the deck)
        Card *getCard() {

            if (this->deckSize == 0) return nullptr;

            this->deckSize--;
            return &this->deck[this->deckSize];

        }

        // Add card to the end of the deck
        void addCard(Card &card) {

            if (this->deckSize >= 44) return;

            // Shift cards up to make room at index 0
            for (int8_t i = this->deckSize; i > 0; i--) {

                this->deck[i] = this->deck[i - 1];

            }

            // Insert at bottom
            this->deck[0].setRank(card.getRank());
            this->deck[0].setSuit(card.getSuit());

            this->deckSize++;
        }

};
