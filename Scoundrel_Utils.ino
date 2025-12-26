#include <ArduboyFX.h>  
#include "src/utils/ArduboyG.h"
#include "src/utils/Constants.h"
#include "src/utils/Enums.h"
#include "fxdata/fxdata.h"
#include "src/utils/SpritesU.hpp"


void resetCursor() {

    if (game.player.getCard(0).getRank() != Rank::None)         game.setCursorPosition(CursorPosition::Card_00);
    else if (game.player.getCard(1).getRank() != Rank::None)    game.setCursorPosition(CursorPosition::Card_01);
    else if (game.player.getCard(2).getRank() != Rank::None)    game.setCursorPosition(CursorPosition::Card_02);
    else if (game.player.getCard(3).getRank() != Rank::None)    game.setCursorPosition(CursorPosition::Card_03);

}

void chooseFightMenuPosition() {

    uint8_t cardIdx = static_cast<uint8_t>(game.getCursorPosition()) - static_cast<uint8_t>(CursorPosition::Card_00);
    Card card = game.player.getCard(cardIdx);
    
    if (game.player.getDefeatCard(0).getRank() != Rank::None) {
    
        if (game.player.getDefeatCard(0).getRank() > card.getRank()) {
            equipMenu = 1;
        }
        else {
            equipMenu = 0;
        }
        
    }
    else if (game.player.getWeapon().getRank() != Rank::None) {
    
        equipMenu = 1;

    }
    else {

        equipMenu = 0;

    }

    gameState = GameState::ChooseFight;
    
}


uint8_t getJustPressedButtons() {

    a.pollButtons();

    return a.justPressedButtons();

}


uint8_t getPressedButtons() {

    return a.pressedButtons();

}


void play_CardSelected() {


}
