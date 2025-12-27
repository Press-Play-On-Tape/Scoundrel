#include <ArduboyFX.h>  


void renderPlayerHand(uint8_t currentPlane, bool highlight, bool greyNonSelected) {

    for (uint8_t i = 0; i < 4; i++) {

        Card &card = game.getPlayer().getCard(i);
        bool thisCardSelected = static_cast<uint8_t>(game.getCursorPosition()) - static_cast<uint8_t>(CursorPosition::Card_00) == i;

        if (!greyNonSelected) {

            if (card.getRank() != Rank::None && (thisCardSelected && game.getFrameCount(64) || !highlight || !thisCardSelected)) {

                SpritesU::drawPlusMaskFX(24 + (i * 18), 7, Images::Cards_Bottom, card.getCardIndex() + currentPlane);

            }

        }
        else {

            if (card.getRank() != Rank::None) {

                if (thisCardSelected) {

                    SpritesU::drawPlusMaskFX(24 + (i * 18), 7, Images::Cards_Bottom, card.getCardIndex() + currentPlane);

                }
                else {

                    SpritesU::drawPlusMaskFX(24 + (i * 18), 7, Images::Cards_Bottom_Grey, card.getCardIndex() + currentPlane);
                
                }
            
            }
        
        }

    }


    // Defeated cards ..

    for (int8_t i = 9; i >= 0; i--) {

        Card &card = game.getPlayer().getDefeatCard(i);

        if (card.getRank() != Rank::None) {

            if (i == 0) {

                if (card.getRank() != Rank::None && static_cast<uint8_t>(card.getRank()) != game.getPlayer().getWeaponValue()) {

                    SpritesU::drawPlusMaskFX(78 - (i * 8), 39, Images::Cards_Bottom_Grey, card.getCardIndex() + currentPlane);

                }
                else {

                    SpritesU::drawPlusMaskFX(78 - (i * 8), 39, Images::Cards_Bottom, card.getCardIndex() + currentPlane);

                }
                
            }
            else {

                SpritesU::drawPlusMaskFX(78 - (i * 8), 39, Images::Cards_Bottom_Grey, card.getCardIndex() + currentPlane);

            }

        }

    }



    // Weapon ..

    Card &weapon = game.getPlayer().getWeapon();
    Card &defeatedCard = game.getPlayer().getDefeatCard(0);

    if (weapon.getRank() != Rank::None) {

        if (defeatedCard.getRank() != Rank::None && static_cast<uint8_t>(defeatedCard.getRank()) == game.getPlayer().getWeaponValue()) {

            SpritesU::drawPlusMaskFX(24, 39, Images::Cards_Bottom_Grey, weapon.getCardIndex() + currentPlane);

        }
        else {

            SpritesU::drawPlusMaskFX(24, 39, Images::Cards_Bottom, weapon.getCardIndex() + currentPlane);

        }

    }

}

void renderHUD(uint8_t currentPlane) {

    SpritesU::drawOverwriteFX(103, 0, Images::HUD, currentPlane);

    SpritesU::drawPlusMaskFX(112, 16, Images::Numbers_5x3_2D_MB, (game.getDeck().getCardsRemaining() * 3) + currentPlane);
    SpritesU::drawPlusMaskFX(112, 35, Images::Numbers_5x3_2D_MB, (game.getPlayer().getHealth() * 3) + currentPlane);
    SpritesU::drawPlusMaskFX(112, 54, Images::Numbers_5x3_2D_MB, (game.getPlayer().getWeaponValue() * 3) + currentPlane);

    if (game.getDeck().getCardsRemaining() > 0) {
        SpritesU::drawOverwriteFX(0, 8, Images::Hand_Full, currentPlane);
    }
    else {
        SpritesU::drawOverwriteFX(0, 8, Images::Hand_Full_Grey, currentPlane);
    }


    if (game.getCursorPosition() != CursorPosition::Run || (game.getCursorPosition() == CursorPosition::Run && game.getFrameCount(64))) {

        SpritesU::drawOverwriteFX(1, 53, Images::Run, ((game.getRun() || game.getPlayer().getCardCount() < 4 || game.getDeck().getCardsRemaining() == 0) * 3) + currentPlane);

    }

}