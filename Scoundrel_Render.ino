#include <ArduboyFX.h>  


void renderPlayerHand(uint8_t currentPlane, bool highlight, bool greyNonSelected) {

    for (uint8_t i = 0; i < 4; i++) {

        Card &card = game.player.getCard(i);
        bool thisCardSelected = static_cast<uint8_t>(game.getCursorPosition()) - static_cast<uint8_t>(CursorPosition::Card_00) == i;

        if (!greyNonSelected) {

            if (card.getRank() != Rank::None && (thisCardSelected && game.getFrameCount(64) || !highlight || !thisCardSelected)) {

                SpritesU::drawPlusMaskFX(24 + (i * 18), 7, Images::Cards_Bottom, card.getCardIndex() + currentPlane);

            }

        }
        else {

            if (card.getRank() != Rank::None && thisCardSelected) {

                SpritesU::drawPlusMaskFX(24 + (i * 18), 7, Images::Cards_Bottom, card.getCardIndex() + currentPlane);

            }
            else {

                SpritesU::drawPlusMaskFX(24 + (i * 18), 7, Images::Cards_Bottom_Grey, card.getCardIndex() + currentPlane);
            
            }
        
        }

    }


    // Defeated cards ..

    for (int8_t i = 9; i >= 0; i--) {

        Card &card = game.player.getDefeatCard(i);

        if (card.getRank() != Rank::None) {

            if (i == 0) {

                SpritesU::drawPlusMaskFX(78 - (i * 8), 39, Images::Cards_Bottom, card.getCardIndex() + currentPlane);

            }
            else {

                SpritesU::drawPlusMaskFX(78 - (i * 8), 39, Images::Cards_Bottom_Grey, card.getCardIndex() + currentPlane);

            }

        }

    }



    // Weapon ..

    Card &card = game.player.getWeapon();
    bool thisCardSelected = game.getCursorPosition() == CursorPosition::Weapon;

    if (card.getRank() != Rank::None && (thisCardSelected && game.getFrameCount(64) || !highlight || !thisCardSelected)) {

        SpritesU::drawPlusMaskFX(24, 39, Images::Cards_Bottom, card.getCardIndex() + currentPlane);

    }

}

void renderHUD(uint8_t currentPlane) {

    SpritesU::drawOverwriteFX(103, 0, Images::HUD, currentPlane);

    SpritesU::drawOverwriteFX(112, 16, Images::Numbers_5x3_2D_MB, currentPlane);
    SpritesU::drawOverwriteFX(112, 35, Images::Numbers_5x3_2D_MB, (game.player.getHealth() * 3) + currentPlane);
    SpritesU::drawOverwriteFX(112, 54, Images::Numbers_5x3_2D_MB, (game.player.getWeaponValue() * 3) + currentPlane);


}