#define ABG_IMPLEMENTATION
#define ABG_TIMER1
#define ABG_SYNC_PARK_ROW
#define SPRITESU_IMPLEMENTATION

#include <ArduboyFX.h>  
#include <FixedPointsCommon.h>
#include "src/utils/ArduboyG.h"
#include "src/utils/Enums.h"
#include "src/utils/Constants.h"
#include "src/utils/Utils.h"
#include "src/entities/Card.h"
#include "src/entities/Deck.h"
#include "src/entities/Player.h"
#include "src/entities/Game.h"
#include "src/entities/Puff.h"
#include "fxdata/fxdata.h"
#include "fxdata/images/Images.h"
#include "src/utils/Random.h"

#define SPRITESU_OVERWRITE
#define SPRITESU_PLUSMASK
#define SPRITESU_RECT
#define SPRITESU_FX

#include "src/utils/SpritesU.hpp"

extern ArduboyGBase_Config<ABG_Mode::L4_Triplane> a;
decltype(a) a;

#include <stdio.h>
#include <stdlib.h>
#include "time.h"

Game game;

uint8_t winningBidIdx;
uint8_t playerCurrentlyBidding;

#if not defined(DEBUG) && not defined(DEBUG_BASIC)
GameState gameState = GameState::SplashScreen_Start;
#else
GameState gameState = GameState::Title_Init;
#endif
GameState prevGameState = GameState::SplashScreen_Start;

uint8_t titleCounter = 0;
uint8_t menuCusror = 0;
uint8_t restartPressed = 0;
Puff puff;

void setup() {

    a.boot();
    abg_detail::send_cmds_prog<0xDB, 0x20>();
    a.startGray();
    
    FX::begin(FX_DATA_PAGE, FX_SAVE_PAGE);
    game.setFrameCount(0);
    a.initRandomSeed();

}

void loop() {

    FX::enableOLED();
    a.waitForNextPlane(BLACK);
    FX::disableOLED();

    switch (gameState) {

        #if not defined(DEBUG) && not defined(DEBUG_BASIC)
            case GameState::SplashScreen_Start ... GameState::SplashScreen_End:
                splashScreen(a);
                break;
        #endif

        case GameState::Title_Init:
            title_Init();
            [[fallthrough]];

        case GameState::Title_Start ... GameState::Title_End:
            title(a);
            break;

        case GameState::Play_Init:
            play_Init();
            [[fallthrough]];

        case GameState::Play_Start ... GameState::Play_End:
            play(a);
            break;


    }

}


void dealCard() {

    Card *card = game.getDeck().getCard();
    game.getPlayer().addCard(card);

}

void DEBUG_PRINT_HAND(uint8_t player) {

    #ifdef DEBUG_BASIC
        
        switch (player) {

            case 0 ... 3:

                DEBUG_PRINT(F("P"));
                DEBUG_PRINT(player);
                DEBUG_PRINT_SPACE();

                for (uint8_t i = 0; i < game.getPlayer()s[player].getCardCount(); i++) {
                    if (game.getPlayer()s[player].getCard(i).getRank() != Rank::Ten) DEBUG_PRINT_SPACE();
                    DEBUG_PRINT_CARD(game.getPlayer()s[player].getCard(i).getSuit(), game.getPlayer()s[player].getCard(i).getRank());
                    DEBUG_PRINT_SPACE();
                }

                DEBUG_PRINTLN();
                break;

            case 4:

                DEBUG_PRINT(F("K  "));

                DEBUG_PRINT_CARD(gameRound.getKitty()->getSuit(), gameRound.getKitty()->getRank());

                DEBUG_PRINTLN();
                break;

        }

    #endif

}

void DEBUG_PRINT_HANDS() {

    #ifdef DEBUG_BASIC 

        DEBUG_PRINTLN(F("      1   2   3   4   5   6   7   8   9  10"));

        for (uint8_t i = gameRound.getCurrentPlayer_Idx(); i < gameRound.getCurrentPlayer_Idx() + 4; i++) {
            
            uint8_t playerIdx = i % 4;

            if (game.getPlayer()s[playerIdx].isPlaying()) {

                if (gameRound.getWinningBid_Idx() == playerIdx) {
                    DEBUG_PRINT(F("*"));
                }
                else {
                    DEBUG_PRINT_SPACE();
                }

                DEBUG_PRINT_HAND(playerIdx);
            }

        }

        DEBUG_PRINT_SPACE();
        DEBUG_PRINT_HAND(4);
        DEBUG_PRINTLN();     

    #endif

}