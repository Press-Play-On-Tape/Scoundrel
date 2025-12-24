#include <ArduboyFX.h>  


void play_Init() { 

    game.resetFrameCount();
    gameState = GameState::Play_Shuffle;
    // gameRound.setScore(0, 0);
    // gameRound.setScore(1, 0);

    // #ifdef DEBUG_RAND
    a.initRandomSeed();
    uint16_t r = random(8000);
    r = 5583;
    DEBUG_PRINT("Rand ");
    DEBUG_PRINTLN(r);
    randomSeed(r);
    game.setRandomSeed(r);
    // #endif

    game.player.reset();

}



// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void play_Update() { 

    uint8_t justPressed = getJustPressedButtons();

    game.incFrameCount();

    if (game.getHealthCount() == 0) {

        switch (gameState) {

            case GameState::Play_Shuffle:  

                game.deck.createDeck();
                game.deck.shuffleDeck();
                game.setFrameCount(0);
                gameState = GameState::Play_Deal_00;

                game.resetRound();
                game.setRound(0);

                // for (uint8_t player = 0; player < 4; player++) {
                //     game.players[player].reset();
                // }

                // gameRound.setDealer_Idx(gameRound.getDealer_Idx() + 1); 
                // playerCurrentlyBidding = (gameRound.getDealer_Idx() + 1) % 4;
                // gameRound.setDealer_Idx(0); //SJH
                // playerCurrentlyBidding = (0 + 1) % 4;
                // gameRound.setDealer_Idx(3); //SJH
                // playerCurrentlyBidding = (3 + 1) % 4;


            case GameState::Play_Deal_00 ... GameState::Play_Deal_03:
                {

                    if (game.getFrameCount() == 26) {
                        gameState++;
                        game.setFrameCount(0);
                        dealCard();
                    }
                    
                }

                break;
                
            case GameState::Play:
                {

                    if (justPressed & RIGHT_BUTTON) {
        
                        switch (game.getCursorPosition()) {
                        
                            case CursorPosition::Card_00:
                                if (game.player.getCard(1).getRank() != Rank::None)             { game.setCursorPosition(CursorPosition::Card_01); }
                                else if (game.player.getCard(2).getRank() != Rank::None)        { game.setCursorPosition(CursorPosition::Card_02); }
                                else if (game.player.getCard(3).getRank() != Rank::None)        { game.setCursorPosition(CursorPosition::Card_03); }
                                break;
                        
                            case CursorPosition::Card_01:
                                if (game.player.getCard(2).getRank() != Rank::None)             { game.setCursorPosition(CursorPosition::Card_02); }
                                else if (game.player.getCard(3).getRank() != Rank::None)        { game.setCursorPosition(CursorPosition::Card_03); }
                                break;
                        
                            case CursorPosition::Card_02:
                                if (game.player.getCard(3).getRank() != Rank::None)             { game.setCursorPosition(CursorPosition::Card_03); }
                                break;

                        }
                    
                    }
                    else if (justPressed & LEFT_BUTTON) {
                    
                        switch (game.getCursorPosition()) {
                        
                            case CursorPosition::Card_03:
                                if (game.player.getCard(2).getRank() != Rank::None)             { game.setCursorPosition(CursorPosition::Card_02); }
                                else if (game.player.getCard(1).getRank() != Rank::None)        { game.setCursorPosition(CursorPosition::Card_01); }
                                else if (game.player.getCard(0).getRank() != Rank::None)        { game.setCursorPosition(CursorPosition::Card_00); }
                                break;
                        
                            case CursorPosition::Card_02:
                                if (game.player.getCard(1).getRank() != Rank::None)             { game.setCursorPosition(CursorPosition::Card_01); }
                                else if (game.player.getCard(0).getRank() != Rank::None)        { game.setCursorPosition(CursorPosition::Card_00); }
                                break;
                        
                            case CursorPosition::Card_01:
                                if (game.player.getCard(0).getRank() != Rank::None)             { game.setCursorPosition(CursorPosition::Card_00); }
                                break;

                        }

                    }
                    else if (justPressed & UP_BUTTON) {
                    
                        switch (game.getCursorPosition()) {
                        
                            case CursorPosition::Weapon:
                                if (game.player.getCard(0).getRank() != Rank::None)             { game.setCursorPosition(CursorPosition::Card_00); }
                                else if (game.player.getCard(1).getRank() != Rank::None)        { game.setCursorPosition(CursorPosition::Card_01); }
                                else if (game.player.getCard(2).getRank() != Rank::None)        { game.setCursorPosition(CursorPosition::Card_02); }
                                else if (game.player.getCard(3).getRank() != Rank::None)        { game.setCursorPosition(CursorPosition::Card_03); }
                                break;
                        
                        }

                    }
                    else if (justPressed & DOWN_BUTTON) {
                    
                        switch (game.getCursorPosition()) {
                        
                            case CursorPosition::Card_00 ... CursorPosition::Card_03:
                                game.setCursorPosition(CursorPosition::Weapon); 
                                break;
                        
                        }

                    }
                    else if (justPressed & A_BUTTON) {

                        uint8_t cardIdx = static_cast<uint8_t>(game.getCursorPosition()) - static_cast<uint8_t>(CursorPosition::Card_00);
                        Card card = game.player.getCard(cardIdx);
                        
                        switch (game.getCursorPosition()) {
                        
                            case CursorPosition::Card_00:

                                if (game.player.getCard(0).getSuit() == Suit::Diamonds) {

                                    equipMenu = 0;
                                    gameState = GameState::Equip;

                                }
                                else if (game.player.getCard(0).getSuit() == Suit::Hearts) {

                                    equipMenu = 0;

                                    if (game.player.getHealth() < 20 && !game.getHealthPlayed()) {
                                        gameState = GameState::RestoreHealth;
                                    }
                                    else {
                                        gameState = GameState::BurnCard;
                                    }

                                }
                                else {
                    
                                    chooseFightMenuPosition();

                                }

                                break;
                        
                            case CursorPosition::Card_01:

                                if (game.player.getCard(1).getSuit() == Suit::Diamonds) {

                                    equipMenu = 0;
                                    gameState = GameState::Equip;

                                }
                                else if (game.player.getCard(1).getSuit() == Suit::Hearts) {

                                    equipMenu = 0;

                                    if (game.player.getHealth() < 20 && !game.getHealthPlayed()) {
                                        gameState = GameState::RestoreHealth;
                                    }
                                    else {
                                        gameState = GameState::BurnCard;
                                    }

                                }
                                else {
                                
                                    chooseFightMenuPosition();

                                }

                                break;
                        
                            case CursorPosition::Card_02:

                                if (game.player.getCard(2).getSuit() == Suit::Diamonds) {

                                    equipMenu = 0;
                                    gameState = GameState::Equip;

                                }
                                else if (game.player.getCard(2).getSuit() == Suit::Hearts) {

                                    equipMenu = 0;

                                    if (game.player.getHealth() < 20 && !game.getHealthPlayed()) {
                                        gameState = GameState::RestoreHealth;
                                    }
                                    else {
                                        gameState = GameState::BurnCard;
                                    }

                                }
                                else {

                                    chooseFightMenuPosition();

                                }

                                break;
                        
                            case CursorPosition::Card_03:

                                if (game.player.getCard(3).getSuit() == Suit::Diamonds) {

                                    equipMenu = 0;
                                    gameState = GameState::Equip;

                                }
                                else if (game.player.getCard(3).getSuit() == Suit::Hearts) {

                                    equipMenu = 0;

                                    if (game.player.getHealth() < 20 && !game.getHealthPlayed()) {
                                        gameState = GameState::RestoreHealth;
                                    }
                                    else {
                                        gameState = GameState::BurnCard;
                                    }

                                }
                                else {
                                
                                    chooseFightMenuPosition();

                                }

                                break;

                        }

                    }

                }

                break;
            
            case GameState::Equip:
                {

                    if (justPressed & RIGHT_BUTTON) {
                        equipMenu = 1;
                    }
                    
                    else if (justPressed & LEFT_BUTTON) {
                        equipMenu = 0;
                    }

                    else if (justPressed & A_BUTTON) {

                        if (equipMenu == 0) {

                            uint8_t cardIdx = static_cast<uint8_t>(game.getCursorPosition()) - static_cast<uint8_t>(CursorPosition::Card_00);

                            Card card = game.player.getCard(cardIdx);
                            game.player.setWeapon(card);
                            game.player.getCard(cardIdx).reset();
                            game.player.clearDefeated();
                            game.setCursorPosition(CursorPosition::Weapon);

                        }

                        gameState = GameState::Play;

                    }

                }

                break;

            case GameState::RestoreHealth:
                {

                    if (justPressed & RIGHT_BUTTON) {
                        equipMenu = 1;
                    }
                    
                    else if (justPressed & LEFT_BUTTON) {
                        equipMenu = 0;
                    }

                    else if (justPressed & A_BUTTON) {

                        if (equipMenu == 0) {

                            uint8_t cardIdx = static_cast<uint8_t>(game.getCursorPosition()) - static_cast<uint8_t>(CursorPosition::Card_00);

                            Card card = game.player.getCard(cardIdx);
                            game.setHealthPlayed(true);
                            game.setHealthCount(static_cast<uint8_t>(card.getRank()));
                            game.player.getCard(cardIdx).reset();
                            resetCursor();

                        }

                        gameState = GameState::Play;

                    }

                }

                break;                
        
            case GameState::BurnCard:
                {

                    if (justPressed & RIGHT_BUTTON) {
                        equipMenu = 1;
                    }
                    
                    else if (justPressed & LEFT_BUTTON) {
                        equipMenu = 0;
                    }

                    else if (justPressed & A_BUTTON) {

                        if (equipMenu == 0) {

                            uint8_t cardIdx = static_cast<uint8_t>(game.getCursorPosition()) - static_cast<uint8_t>(CursorPosition::Card_00);

                            Card card = game.player.getCard(cardIdx);
                            game.player.getCard(cardIdx).reset();
                            // game.setCursorPosition(CursorPosition::Weapon);
                            resetCursor();

                        }

                        gameState = GameState::Play;

                    }

                }

                break;          

            case GameState::ChooseFight:
                {
                    uint8_t cardIdx = static_cast<uint8_t>(game.getCursorPosition()) - static_cast<uint8_t>(CursorPosition::Card_00);
                    Card card = game.player.getCard(cardIdx);

                    if (justPressed & DOWN_BUTTON) {
    
                        switch (equipMenu) {
                        
                            case 0:
                                if (game.player.getWeapon().getRank() == Rank::None) {
                                    equipMenu = 2;
                                }
                                else if (game.player.getDefeatCard(0).getRank() != Rank::None && game.player.getDefeatCard(0).getRank() <= card.getRank()) {
                                    equipMenu = 2;
                                }
                                else {
                                    equipMenu = 1;
                                }
                                break;
                        
                            case 1:
                                equipMenu = 2;
                                break;
                                
                        }

                    }
                    
                    else if (justPressed & UP_BUTTON) {

                        switch (equipMenu) {
                        
                            case 1:
                                equipMenu = 0;
                                break;
                        
                            case 2:
                                if (game.player.getWeapon().getRank() == Rank::None) {
                                    equipMenu = 0;
                                }
                                else if (game.player.getDefeatCard(0).getRank() != Rank::None && game.player.getDefeatCard(0).getRank() <= card.getRank()) {
                                    equipMenu = 0;

                                }
                                else {
                                    equipMenu = 1;
                                }
                                break;
                                

                        }

                    }

                    else if (justPressed & A_BUTTON) {

                        switch (equipMenu) {

                            case 0:
                                {                        
                                    uint8_t cardIdx = static_cast<uint8_t>(game.getCursorPosition()) - static_cast<uint8_t>(CursorPosition::Card_00);

                                    Card card = game.player.getCard(cardIdx);
                                    game.setHealthCount(-static_cast<uint8_t>(card.getRank()));
                                    game.player.getCard(cardIdx).reset();
                                    gameState = GameState::Play;
                                    resetCursor();
                                }

                                break;

                            case 1:
                                {                        
                                    uint8_t cardIdx = static_cast<uint8_t>(game.getCursorPosition()) - static_cast<uint8_t>(CursorPosition::Card_00);
                                    Card card = game.player.getCard(cardIdx);

                                    if (static_cast<uint8_t>(card.getRank()) > game.player.getWeaponValue()) {
                                        game.setHealthCount(-static_cast<uint8_t>(card.getRank()) + game.player.getWeaponValue());
                                    }

                                    game.player.getCard(cardIdx).reset();
                                    game.player.addDefeatCard(card);
                                    gameState = GameState::Play;
                                    resetCursor();

                                }

                                break;

                            case 2:
                                gameState = GameState::Play;
                                break;

                        }

                    }

                }

                break;          

        }


        // Check for end of round ..

        switch (gameState) {

            case GameState::Play:     

                if (game.player.getCardCount() == 1 && game.getHealthCount() == 0) {
                    
                    game.player.moveCards();
                    gameState = GameState::Play_Deal_01;
                    game.setFrameCount(0);
                    game.setHealthPlayed(true);
                    game.setCursorPosition(CursorPosition::Card_00);

                }

                break;

        }

    }


    // Housekeeping ..

    if (game.getFrameCount() % 8 == 1) {

        if (game.getHealthCount() > 0) {
            game.player.incHealth(1);
            game.decHealthCount();
        }
        else if (game.getHealthCount() < 0) {
            game.player.decHealth(1);
            game.incHealthCount();
        }

    }

}


void play(ArduboyGBase_Config<ABG_Mode::L4_Triplane> &a) {

    uint8_t currentPlane = a.currentPlane();
    if (a.needsUpdate()) play_Update();

    switch (gameState) {

        case GameState::Play_Deal_00 ... GameState::Play_Deal_03:

            SpritesU::drawOverwriteFX(25, 0, Images::Background, currentPlane);
            renderHUD(currentPlane);

            switch (gameState) {
            
                case GameState::Play_Deal_00:
                    SpritesU::drawPlusMaskFX(25, 8, Images::Flip, ((game.getFrameCount() / 2) * 3) + currentPlane);
                    break;
            
                case GameState::Play_Deal_01:
                    renderPlayerHand(currentPlane, false, false);
                    SpritesU::drawPlusMaskFX(43, 8, Images::Flip, ((game.getFrameCount() / 2) * 3) + currentPlane);
                    break;
            
                case GameState::Play_Deal_02:
                    renderPlayerHand(currentPlane, false, false);
                    SpritesU::drawPlusMaskFX(61, 8, Images::Flip, ((game.getFrameCount() / 2) * 3) + currentPlane);
                    break;
            
                case GameState::Play_Deal_03:
                    renderPlayerHand(currentPlane, false, false);
                    SpritesU::drawPlusMaskFX(79, 8, Images::Flip, ((game.getFrameCount() / 2) * 3) + currentPlane);
                    break;

            }

            break;

        case GameState::Play:

            SpritesU::drawOverwriteFX(25, 0, Images::Background, currentPlane);
            renderHUD(currentPlane);
            renderPlayerHand(currentPlane, true, false);
            break;


        case GameState::Equip:

            SpritesU::drawOverwriteFX(25, 0, Images::Background, currentPlane);
            renderHUD(currentPlane);
            renderPlayerHand(currentPlane, false, true);
            SpritesU::drawPlusMaskFX(30, 20, Images::Equip, (equipMenu * 3) + currentPlane);

            break;

        case GameState::RestoreHealth:

            SpritesU::drawOverwriteFX(25, 0, Images::Background, currentPlane);
            renderHUD(currentPlane);
            renderPlayerHand(currentPlane, false, true);
            SpritesU::drawPlusMaskFX(25, 20, Images::RestoreHealth, (equipMenu * 3) + currentPlane);

            break;

        case GameState::BurnCard:

            SpritesU::drawOverwriteFX(25, 0, Images::Background, currentPlane);
            renderHUD(currentPlane);
            renderPlayerHand(currentPlane, false, true);
            SpritesU::drawPlusMaskFX(34, 20, Images::BurnCard, (equipMenu * 3) + currentPlane);

            break;

        case GameState::ChooseFight:
            {

                uint8_t cardIdx = static_cast<uint8_t>(game.getCursorPosition()) - static_cast<uint8_t>(CursorPosition::Card_00);
                Card card = game.player.getCard(cardIdx);
 
                SpritesU::drawOverwriteFX(25, 0, Images::Background, currentPlane);
                renderHUD(currentPlane);
                renderPlayerHand(currentPlane, false, true);
                SpritesU::drawPlusMaskFX(23, 20, Images::ChooseFight, (equipMenu * 3) + currentPlane);
                SpritesU::drawOverwriteFX(50, 22, Images::Numbers_5x3_2D_WB, (static_cast<uint8_t>(card.getRank()) * 3) + currentPlane);
            }

            break;
    }

}
