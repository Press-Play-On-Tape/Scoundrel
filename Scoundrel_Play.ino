#include <ArduboyFX.h>  


void play_Init() { 

    game.resetFrameCount();
    gameState = GameState::Play_Shuffle;

    // #ifdef DEBUG_RAND
    a.initRandomSeed();
    uint16_t r = random(8000);
    // r = 5362;
    // DEBUG_PRINT("Rand ");
    // DEBUG_PRINTLN(r);
    randomSeed(r);
    game.setRandomSeed(r);
    // #endif

    game.getPlayer().reset();

}



// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void play_Update() { 

    uint8_t justPressed = getJustPressedButtons();
    uint8_t pressed = getPressedButtons();

    game.incFrameCount();

    if (game.getHealthCount() == 0 && puff.getCounter() == 0) {


        if (pressed & A_BUTTON && pressed & B_BUTTON) {
        
            restartPressed++;

            if (restartPressed > 64) {

                restartPressed = 0;
                prevGameState = gameState;
                gameState = GameState::RestartGame;
                menuCusror = 0;
                return;

            }

        }
        else {

            restartPressed = 0;

        }
        
        switch (gameState) {

            case GameState::Play_Shuffle:  

                game.getDeck().createDeck();
                game.getDeck().shuffleDeck();
                game.setFrameCount(0);
                gameState = GameState::Play_Deal_00;

                game.resetRound();
                game.setRound(0);

                // game.getDeck().setDeckSize(5);
                // game.getDeck().setCard(43, Suit::Diamonds, Rank::Ten);
                // game.getDeck().setCard(42, Suit::Clubs, Rank::King);
                // game.getDeck().setCard(41, Suit::Clubs, Rank::Ten);
                // game.getDeck().setCard(40, Suit::Spades, Rank::Ten);
                // game.getDeck().setCard(39, Suit::Clubs, Rank::Four);
                // game.getDeck().setCard(38, Suit::Clubs, Rank::Three);

                break;

            case GameState::Play_Deal_00 ... GameState::Play_Deal_03:

                if (game.getFrameCount() >= 26) {

                    gameState++;
                    game.setFrameCount(0);
                    dealCard();

                    if (game.getDeck().getCardsRemaining() == 0) {


                        gameState = GameState::Play;
                        game.setFrameCount(0);

                    }

                }

                break;
                
            case GameState::Play:
                {

                    if (justPressed & RIGHT_BUTTON) {
        
                        switch (game.getCursorPosition()) {
                        
                            case CursorPosition::Run:
                                if (game.getPlayer().getCard(0).getRank() != Rank::None)             { game.setCursorPosition(CursorPosition::Card_00); }
                                else if (game.getPlayer().getCard(1).getRank() != Rank::None)        { game.setCursorPosition(CursorPosition::Card_01); }
                                else if (game.getPlayer().getCard(2).getRank() != Rank::None)        { game.setCursorPosition(CursorPosition::Card_02); }
                                else if (game.getPlayer().getCard(3).getRank() != Rank::None)        { game.setCursorPosition(CursorPosition::Card_03); }
                                break;
                        
                            case CursorPosition::Card_00:
                                if (game.getPlayer().getCard(1).getRank() != Rank::None)             { game.setCursorPosition(CursorPosition::Card_01); }
                                else if (game.getPlayer().getCard(2).getRank() != Rank::None)        { game.setCursorPosition(CursorPosition::Card_02); }
                                else if (game.getPlayer().getCard(3).getRank() != Rank::None)        { game.setCursorPosition(CursorPosition::Card_03); }
                                break;
                        
                            case CursorPosition::Card_01:
                                if (game.getPlayer().getCard(2).getRank() != Rank::None)             { game.setCursorPosition(CursorPosition::Card_02); }
                                else if (game.getPlayer().getCard(3).getRank() != Rank::None)        { game.setCursorPosition(CursorPosition::Card_03); }
                                break;
                        
                            case CursorPosition::Card_02:
                                if (game.getPlayer().getCard(3).getRank() != Rank::None)             { game.setCursorPosition(CursorPosition::Card_03); }
                                break;

                        }
                    
                    }
                    else if (justPressed & LEFT_BUTTON) {
                    
                        switch (game.getCursorPosition()) {
                        
                            case CursorPosition::Card_03:
                                if (game.getPlayer().getCard(2).getRank() != Rank::None)             { game.setCursorPosition(CursorPosition::Card_02); }
                                else if (game.getPlayer().getCard(1).getRank() != Rank::None)        { game.setCursorPosition(CursorPosition::Card_01); }
                                else if (game.getPlayer().getCard(0).getRank() != Rank::None)        { game.setCursorPosition(CursorPosition::Card_00); }
                                break;
                        
                            case CursorPosition::Card_02:
                                if (game.getPlayer().getCard(1).getRank() != Rank::None)             { game.setCursorPosition(CursorPosition::Card_01); }
                                else if (game.getPlayer().getCard(0).getRank() != Rank::None)        { game.setCursorPosition(CursorPosition::Card_00); }
                                break;
                        
                            case CursorPosition::Card_01:
                                if (game.getPlayer().getCard(0).getRank() != Rank::None)             { game.setCursorPosition(CursorPosition::Card_00); }
                                break;
                        
                            case CursorPosition::Card_00:
                                if (!game.getRun() && game.getPlayer().getCardCount() == 4 && game.getDeck().getCardsRemaining() > 0) { 
                                    game.setCursorPosition(CursorPosition::Run); 
                                }
                                break;

                        }

                    }
                    else if (justPressed & A_BUTTON) {

                        uint8_t cardIdx = static_cast<uint8_t>(game.getCursorPosition()) - static_cast<uint8_t>(CursorPosition::Card_00);
                        Card card = game.getPlayer().getCard(cardIdx);
                        
                        switch (game.getCursorPosition()) {
                        
                            case CursorPosition::Run:

                                puff.init(PuffMode::Run, 0);
                                game.setFrameCount(1);
                                break;

                            case CursorPosition::Card_00:

                                if (game.getPlayer().getCard(0).getSuit() == Suit::Diamonds) {

                                    menuCusror = 0;
                                    gameState = GameState::Equip;

                                }
                                else if (game.getPlayer().getCard(0).getSuit() == Suit::Hearts) {

                                    menuCusror = 0;

                                    if (game.getPlayer().getHealth() < 20 && !game.getHealthPlayed()) {
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

                                if (game.getPlayer().getCard(1).getSuit() == Suit::Diamonds) {

                                    menuCusror = 0;
                                    gameState = GameState::Equip;

                                }
                                else if (game.getPlayer().getCard(1).getSuit() == Suit::Hearts) {

                                    menuCusror = 0;

                                    if (game.getPlayer().getHealth() < 20 && !game.getHealthPlayed()) {
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

                                if (game.getPlayer().getCard(2).getSuit() == Suit::Diamonds) {

                                    menuCusror = 0;
                                    gameState = GameState::Equip;

                                }
                                else if (game.getPlayer().getCard(2).getSuit() == Suit::Hearts) {

                                    menuCusror = 0;

                                    if (game.getPlayer().getHealth() < 20 && !game.getHealthPlayed()) {
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

                                if (game.getPlayer().getCard(3).getSuit() == Suit::Diamonds) {

                                    menuCusror = 0;
                                    gameState = GameState::Equip;

                                }
                                else if (game.getPlayer().getCard(3).getSuit() == Suit::Hearts) {

                                    menuCusror = 0;

                                    if (game.getPlayer().getHealth() < 20 && !game.getHealthPlayed()) {
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
                        menuCusror = 1;
                    }
                    
                    else if (justPressed & LEFT_BUTTON) {
                        menuCusror = 0;
                    }

                    else if (justPressed & A_BUTTON) {

                        if (menuCusror == 0) {

                            uint8_t cardIdx = static_cast<uint8_t>(game.getCursorPosition()) - static_cast<uint8_t>(CursorPosition::Card_00);

                            puff.init(PuffMode::EquipWeapon, cardIdx);
                            game.setFrameCount(1);

                        }

                        gameState = GameState::Play;

                    }

                }

                break;

            case GameState::RestoreHealth:
                {

                    if (justPressed & RIGHT_BUTTON) {
                        menuCusror = 1;
                    }
                    
                    else if (justPressed & LEFT_BUTTON) {
                        menuCusror = 0;
                    }

                    else if (justPressed & A_BUTTON) {

                        if (menuCusror == 0) {

                            uint8_t cardIdx = static_cast<uint8_t>(game.getCursorPosition()) - static_cast<uint8_t>(CursorPosition::Card_00);

                            Card card = game.getPlayer().getCard(cardIdx);
                            puff.init(PuffMode::Heart, cardIdx);

                        }

                    }

                }

                break;                
        
            case GameState::BurnCard:
                {

                    if (justPressed & RIGHT_BUTTON) {
                        menuCusror = 1;
                    }
                    
                    else if (justPressed & LEFT_BUTTON) {
                        menuCusror = 0;
                    }

                    else if (justPressed & A_BUTTON) {

                        if (menuCusror == 0) {

                            uint8_t cardIdx = static_cast<uint8_t>(game.getCursorPosition()) - static_cast<uint8_t>(CursorPosition::Card_00);

                            Card card = game.getPlayer().getCard(cardIdx);
                            puff.init(PuffMode::Burn, cardIdx);

                        }
                        else {

                            gameState = GameState::Play;
                            break;                        

                        }

                    }

                }

                break;          

            case GameState::ChooseFight:
                {
                    uint8_t cardIdx = static_cast<uint8_t>(game.getCursorPosition()) - static_cast<uint8_t>(CursorPosition::Card_00);
                    Card card = game.getPlayer().getCard(cardIdx);

                    if (justPressed & DOWN_BUTTON) {
    
                        switch (menuCusror) {
                        
                            case 0:
                                if (game.getPlayer().getWeapon().getRank() == Rank::None) {
                                    menuCusror = 2;
                                }
                                else if (game.getPlayer().getDefeatCard(0).getRank() != Rank::None && game.getPlayer().getDefeatCard(0).getRank() <= card.getRank()) {
                                    menuCusror = 2;
                                }
                                else {
                                    menuCusror = 1;
                                }
                                break;
                        
                            case 1:
                                menuCusror = 2;
                                break;
                                
                        }

                    }
                    
                    else if (justPressed & UP_BUTTON) {

                        switch (menuCusror) {
                        
                            case 1:
                                menuCusror = 0;
                                break;
                        
                            case 2:
                                if (game.getPlayer().getWeapon().getRank() == Rank::None) {
                                    menuCusror = 0;
                                }
                                else if (game.getPlayer().getDefeatCard(0).getRank() != Rank::None && game.getPlayer().getDefeatCard(0).getRank() <= card.getRank()) {
                                    menuCusror = 0;

                                }
                                else {
                                    menuCusror = 1;
                                }
                                break;
                                

                        }

                    }

                    else if (justPressed & A_BUTTON) {

                        switch (menuCusror) {

                            case 0:
                                {                        
                                    uint8_t cardIdx = static_cast<uint8_t>(game.getCursorPosition()) - static_cast<uint8_t>(CursorPosition::Card_00);
                                    Card card = game.getPlayer().getCard(cardIdx);

                                    puff.init(PuffMode::Fight_BareHand, cardIdx);
                                    game.setFrameCount(1);
                                }

                                break;

                            case 1:
                                {                        
                                    uint8_t cardIdx = static_cast<uint8_t>(game.getCursorPosition()) - static_cast<uint8_t>(CursorPosition::Card_00);
                                    Card card = game.getPlayer().getCard(cardIdx);

                                    puff.init(PuffMode::Fight_Weapon, cardIdx);
                                    game.setFrameCount(1);

                                }

                                break;

                            case 2:
                                gameState = GameState::Play;
                                break;

                        }

                    }

                }

                break;    

            case GameState::YouWin: 
            case GameState::YouLose:

                if (justPressed & A_BUTTON) {
                
                    gameState = GameState::Score;

                }   

                break;   


            case GameState::Score: 

                if (justPressed & A_BUTTON) {
                
                    gameState = GameState::Title_Init;

                }   

                break;   
       
            case GameState::RestartGame:
                {

                    if (justPressed & RIGHT_BUTTON) {
                        menuCusror = 1;
                    }
                    
                    else if (justPressed & LEFT_BUTTON) {
                        menuCusror = 0;
                    }

                    else if (justPressed & A_BUTTON) {

                        if (menuCusror == 0) {

                            gameState = GameState::Title_Init;

                        }
                        else {

                            gameState = prevGameState;

                        }

                    }

                }

                break;      

        }

    }


    // Check for end of round ..

    if (game.getHealthCount() == 0 && puff.getCounter() == 0) {

        switch (gameState) {

            case GameState::Play:     
                    
                if (game.getDeck().getCardsRemaining() > 0) {

                    if (game.getPlayer().getCardCount() == 1) {

                        game.getPlayer().moveCards();
                        gameState = GameState::Play_Deal_01;
                        game.setFrameCount(0);
                        game.setHealthPlayed(false);
                        game.setCursorPosition(CursorPosition::Card_00);

                        if (game.getRunPrevRound()) {
                            game.setRun(false);
                        }

                        game.setRunPrevRound(false);

                    }

                }
                else {

                    if (game.getPlayer().getCardCount() == 0) {

                        gameState = GameState::YouWin;
                        game.setFrameCount(0);

                    }

                }

                break;

        }

    }


    // Housekeeping ..

    if (game.getFrameCount() % 8 == 1) {

        switch (game.getHealthCount()) {
        
            case 1 ... 100:

                game.getPlayer().incHealth(1);
                game.decHealthCount();

                if (game.getPlayer().getHealth() == 0) {

                    game.setFrameCount(0);
                    gameState = GameState::YouLose;

                }
                break;

            case -100 ... -1:

                game.getPlayer().decHealth(1);
                game.incHealthCount();

                if (game.getPlayer().getHealth() == 0) {

                    game.setFrameCount(0);
                    gameState = GameState::YouLose;

                }

                break;

        }

    }

    if (puff.getCounter() > 0 && game.getFrameCount() % 4 == 0) {

        puff.setCounter(puff.getCounter() + 1);

        switch (puff.getCounter()) {
        
            case 4:
                
                switch (puff.getPuffMode()) {

                    case PuffMode::EquipWeapon:
                        {
                            Card card = game.getPlayer().getCard(puff.getIndex());
                            game.getPlayer().setWeapon(card);
                            game.getPlayer().setPrevCard(game.getPlayer().getCard(puff.getIndex()));
                            game.getPlayer().getCard(puff.getIndex()).reset();
                            game.getPlayer().clearDefeated();
                        }
                        
                        break;

                    case PuffMode::Run:
                        {
                            Card card0 = game.getPlayer().getCard(0);
                            game.getDeck().addCard(card0);
                            game.getPlayer().getCard(0).reset();

                            Card card1 = game.getPlayer().getCard(1);
                            game.getDeck().addCard(card1);
                            game.getPlayer().getCard(1).reset();

                            Card card2 = game.getPlayer().getCard(2);
                            game.getDeck().addCard(card2);
                            game.getPlayer().getCard(2).reset();

                            Card card3 = game.getPlayer().getCard(3);
                            game.getDeck().addCard(card3);
                            game.getPlayer().getCard(3).reset();

                            Card prevCard;
                            game.getPlayer().setPrevCard(prevCard);

                        }

                        break;

                    case PuffMode::Heart:
                        {
                            Card card = game.getPlayer().getCard(puff.getIndex());
                            game.setHealthPlayed(true);
                            game.setHealthCount(static_cast<uint8_t>(card.getRank()));                            
                            game.getPlayer().setPrevCard(game.getPlayer().getCard(puff.getIndex()));
                            game.getPlayer().getCard(puff.getIndex()).reset();

                        }

                        break;
                        
                    case PuffMode::Burn:
                        {
                            Card card = game.getPlayer().getCard(puff.getIndex());
                            game.getPlayer().setPrevCard(game.getPlayer().getCard(puff.getIndex()));
                            game.getPlayer().getCard(puff.getIndex()).reset();
                        }
                        
                        break;


                }

                break;

            case 9:

                switch (puff.getPuffMode()) {

                    case PuffMode::EquipWeapon:

                        puff.setCounter(0);
                        resetCursor();

                        break;

                    case PuffMode::Run:
                    
                        gameState = GameState::Play_Deal_00;
                        game.setFrameCount(0);
                        game.setCursorPosition(CursorPosition::Card_00);       
                        puff.setCounter(0);
                        game.setRun(true);
                        game.setRunPrevRound(true);
                    
                        break;

                    case PuffMode::Burn:

                        puff.setCounter(0);
                        resetCursor();
                        gameState = GameState::Play;

                        break;

                }

                break;


            case 10:

                switch (puff.getPuffMode()) {

                    case PuffMode::Fight_Weapon:
                        {
                            Card card = game.getPlayer().getCard(puff.getIndex());

                            if (static_cast<uint8_t>(card.getRank()) > game.getPlayer().getWeaponValue()) {
                                game.setHealthCount(-static_cast<uint8_t>(card.getRank()) + game.getPlayer().getWeaponValue());
                            }

                            game.getPlayer().setPrevCard(game.getPlayer().getCard(puff.getIndex()));
                            game.getPlayer().getCard(puff.getIndex()).reset();
                            game.getPlayer().addDefeatCard(card);
                            gameState = GameState::Play;
                            resetCursor();
                            puff.setCounter(0);

                            if (game.getPlayer().getHealth() == 0) {

                                game.setFrameCount(0);
                                gameState = GameState::YouLose;
                                
                            }

                        }

                        break;

                }

                break;

            case 11:

                switch (puff.getPuffMode()) {

                    case PuffMode::Heart:
                        {
                            
                            resetCursor();
                            puff.setCounter(0);
                            gameState = GameState::Play;

                        }

                        break;

                }

                break;

            case 14:

                switch (puff.getPuffMode()) {

                    case PuffMode::Fight_BareHand:
                        {
                            Card card = game.getPlayer().getCard(puff.getIndex());

                            game.setHealthCount(-static_cast<uint8_t>(card.getRank()));

                            if (game.getPlayer().getHealth() > static_cast<uint8_t>(card.getRank())) {
                                game.getPlayer().setPrevCard(game.getPlayer().getCard(puff.getIndex()));
                                game.getPlayer().getCard(puff.getIndex()).reset();
                            }
                            gameState = GameState::Play;

                            resetCursor();
                            puff.setCounter(0);

                        }

                        break;

                }

                break;

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
                    renderPlayerHand(currentPlane, false, false);
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
            renderPlayerHand(currentPlane, puff.getCounter() == 0, false);

            if (puff.getCounter() > 0) {

                switch (puff.getPuffMode()) {

                    case PuffMode::EquipWeapon:

                        SpritesU::drawPlusMaskFX(16 + (puff.getIndex() * 18), 4, Images::Puff_00, ((puff.getCounter() - 1) * 3) + currentPlane);
                        SpritesU::drawPlusMaskFX(16, 34, Images::Puff_01, ((puff.getCounter() - 1) * 3) + currentPlane);

                        break;

                    case PuffMode::Run:

                        SpritesU::drawPlusMaskFX(16, 4, Images::Puff_00, ((puff.getCounter()  - 1) * 3) + currentPlane);
                        SpritesU::drawPlusMaskFX(16 + 36, 4, Images::Puff_01, ((puff.getCounter()  - 1) * 3) + currentPlane);
                        SpritesU::drawPlusMaskFX(16 + 18, 4, Images::Puff_00, ((puff.getCounter()  - 1) * 3) + currentPlane);
                        SpritesU::drawPlusMaskFX(16 + 18 + 36, 4, Images::Puff_01, ((puff.getCounter()  - 1) * 3) + currentPlane);

                        break;

                }

            }

            break;


        case GameState::Equip:

            SpritesU::drawOverwriteFX(25, 0, Images::Background, currentPlane);
            renderHUD(currentPlane);
            renderPlayerHand(currentPlane, false, true);
            SpritesU::drawPlusMaskFX(30, 20, Images::Equip, (menuCusror * 3) + currentPlane);

            break;

        case GameState::RestoreHealth:

            SpritesU::drawOverwriteFX(25, 0, Images::Background, currentPlane);
            renderHUD(currentPlane);
            renderPlayerHand(currentPlane, false, true);

            switch (puff.getCounter()) {

                case 0:

                    SpritesU::drawPlusMaskFX(25, 20, Images::RestoreHealth, (menuCusror * 3) + currentPlane);
                    break;

                default:
             
                    SpritesU::drawPlusMaskFX(16 + (puff.getIndex() * 18), 4, Images::Hearts, ((puff.getCounter()  - 1) * 3) + currentPlane);
                    break;

            }
                

            break;

        case GameState::BurnCard:

            SpritesU::drawOverwriteFX(25, 0, Images::Background, currentPlane);
            renderHUD(currentPlane);
            renderPlayerHand(currentPlane, false, true);

            switch (puff.getCounter()) {

                case 0:

                    SpritesU::drawPlusMaskFX(34, 20, Images::BurnCard, (menuCusror * 3) + currentPlane);
                    break;

                case 1 ... 9:

                    SpritesU::drawPlusMaskFX(17 + (puff.getIndex() * 18), 4, Images::Puff_00, ((puff.getCounter()  - 1) * 3) + currentPlane);

                    break;

            }
            
            break;

        case GameState::ChooseFight:
            {

                uint8_t cardIdx = static_cast<uint8_t>(game.getCursorPosition()) - static_cast<uint8_t>(CursorPosition::Card_00);
                Card card = game.getPlayer().getCard(cardIdx);
 
                SpritesU::drawOverwriteFX(25, 0, Images::Background, currentPlane);
                renderHUD(currentPlane);
                renderPlayerHand(currentPlane, false, true);

                switch (puff.getCounter()) {

                    case 0:

                        if (game.getPlayer().getWeapon().getRank() == Rank::None ||game.getPlayer().getDefeatCard(0).getRank() != Rank::None && game.getPlayer().getDefeatCard(0).getRank() <= card.getRank()) {

                            SpritesU::drawPlusMaskFX(23, 20, Images::ChooseFight, ((menuCusror + 3) * 3) + currentPlane);
                            SpritesU::drawOverwriteFX(50, 22, Images::Numbers_5x3_2D_WB, (static_cast<uint8_t>(card.getRank()) * 3) + currentPlane);
                        
                        }
                        else {

                            SpritesU::drawPlusMaskFX(23, 20, Images::ChooseFight, (menuCusror * 3) + currentPlane);
                            SpritesU::drawOverwriteFX(50, 22, Images::Numbers_5x3_2D_WB, (static_cast<uint8_t>(card.getRank()) * 3) + currentPlane);

                        }

                        break;

                    case 1 ... 6:

                        switch (puff.getPuffMode()) {

                            case PuffMode::Fight_BareHand:

                                SpritesU::drawPlusMaskFX(17 + (puff.getIndex() * 18), -1, Images::Knuckles, ((puff.getCounter()  - 1) * 3) + currentPlane);
                                break;

                            case PuffMode::Fight_Weapon:

                                SpritesU::drawPlusMaskFX(16 + 18 + 36, 34, Images::Puff_01, ((puff.getCounter()  - 1) * 3) + currentPlane);
                                SpritesU::drawPlusMaskFX(17 + (puff.getIndex() * 18), 4, Images::Sword, ((puff.getCounter()  - 1) * 3) + currentPlane);
                                break;

                        }

                        break;

                    case 7 ... 8:

                        switch (puff.getPuffMode()) {

                            case PuffMode::Fight_BareHand:

                                SpritesU::drawPlusMaskFX(17 + (puff.getIndex() * 18), -1, Images::Knuckles, ((puff.getCounter()  - 1) * 3) + currentPlane);
                                break;

                            case PuffMode::Fight_Weapon:

                                SpritesU::drawPlusMaskFX(16 + 18 + 36, 34, Images::Puff_01, ((puff.getCounter()  - 1) * 3) + currentPlane);
                                SpritesU::drawPlusMaskFX(17 + (puff.getIndex() * 18), 4, Images::Sword, ((puff.getCounter()  - 1) * 3) + currentPlane);
                                break;

                        }

                        break;

                    case 9:

                        switch (puff.getPuffMode()) {

                            case PuffMode::Fight_BareHand:

                                SpritesU::drawPlusMaskFX(17 + (puff.getIndex() * 18), -1, Images::Knuckles, ((puff.getCounter()  - 1) * 3) + currentPlane);
                                break;

                            case PuffMode::Fight_Weapon:

                                SpritesU::drawPlusMaskFX(17 + (puff.getIndex() * 18), 4, Images::Sword, ((puff.getCounter()  - 1) * 3) + currentPlane);
                                break;

                        }
    
                        break;


                    case 10 ... 14:

                        switch (puff.getPuffMode()) {

                            case PuffMode::Fight_BareHand:

                                SpritesU::drawPlusMaskFX(17 + (puff.getIndex() * 18), -1, Images::Knuckles, ((puff.getCounter()  - 1) * 3) + currentPlane);
                                break;

                        }

                        break;

                }

            }

            break;


        case GameState::YouWin:
            {
                SpritesU::drawOverwriteFX(25, 0, Images::Background, currentPlane);
                renderHUD(currentPlane);
                renderPlayerHand(currentPlane, false, false);

                uint8_t i = game.getFrameCount() < 70 ? game.getFrameCount() / 2 : 35;

                int8_t bounce = static_cast<int8_t>(pgm_read_byte(Constants::Bounce + i));
                SpritesU::drawPlusMaskFX(0, bounce - 16, Images::YouWin, currentPlane);
            }

            break;


        case GameState::YouLose:
            {
                SpritesU::drawOverwriteFX(25, 0, Images::Background, currentPlane);
                renderHUD(currentPlane);
                renderPlayerHand(currentPlane, false, false);

                uint8_t i = game.getFrameCount() < 70 ? game.getFrameCount() / 2 : 35;

                int8_t bounce = static_cast<int8_t>(pgm_read_byte(Constants::Bounce + i));
                SpritesU::drawPlusMaskFX(0, bounce - 16, Images::YouLose, currentPlane);
            }

            break;

        case GameState::RestartGame:

            SpritesU::drawOverwriteFX(25, 0, Images::Background, currentPlane);
            renderHUD(currentPlane);
            renderPlayerHand(currentPlane, false, false);
            SpritesU::drawPlusMaskFX(32, 20, Images::RestartGame, (menuCusror * 3) + currentPlane);
            
            break;

        case GameState::Score:
            {

                uint8_t count = 0;
                int16_t score = 0;
                
                for (uint8_t i = 0; i < 4; i++) {

                    if (game.getPlayer().getCard(i).getSuit() == Suit::Spades || game.getPlayer().getCard(i).getSuit() == Suit::Clubs) {
                        count++;
                        score = score - static_cast<uint8_t>(game.getPlayer().getCard(i).getRank());
                    }

                }            

                for (uint8_t i = 0; i < game.getDeck().getCardsRemaining(); i++) {

                    if (game.getDeck().getCard(i)->getSuit() == Suit::Spades || game.getDeck().getCard(i)->getSuit() == Suit::Clubs) {
                        count++;
                        score = score - static_cast<uint8_t>(game.getDeck().getCard(i)->getRank());
                    }

                }         

                if (score == 0) {
                
                    score = game.getPlayer().getHealth();

                    if (score == 20) {

                        if (game.getPlayer().getPrevCard().getSuit() == Suit::Hearts) {
                            score = score + static_cast<uint8_t>(game.getPlayer().getPrevCard().getRank());
                        }

                    }

                }   

                SpritesU::drawOverwriteFX(0, 0, Images::Fire, (3 * ((game.getFrameCount()/6) % 16)) + currentPlane);
                SpritesU::drawPlusMaskFX(0, 0, Images::YourScore, currentPlane);

                if (score < 0) {

                    SpritesU::drawPlusMaskFX(24, 37, Images::YourScore_Lower, currentPlane);
                    SpritesU::drawPlusMaskFX(97, 37, Images::Numbers_5x3_2D_MB, (count * 3) + currentPlane);
                    SpritesU::drawPlusMaskFX(74, 45, Images::Numbers_5x3_2D_MB, ((-score / 10) * 3) + currentPlane);
                    SpritesU::drawPlusMaskFX(78, 45, Images::Numbers_5x3_2D_MB, ((-score % 100) * 3) + currentPlane);

                }
                else {

                    SpritesU::drawPlusMaskFX(24, 37, Images::YourScore_Lower, 3 + currentPlane);
                    SpritesU::drawPlusMaskFX(97, 37, Images::Numbers_5x3_2D_MB, (count * 3) + currentPlane);
                    SpritesU::drawPlusMaskFX(74, 45, Images::Numbers_5x3_2D_MB, (score * 3) + currentPlane);
                
                }

            }

            break;

    }

}
