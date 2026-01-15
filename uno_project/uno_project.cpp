// Uno_project_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <random>
#include <fstream>

const char FILENAME[] = "UnoSaveState.txt";
struct card
{
    char color;
    char value[10];
    char text[20];
};
const int RED_COLOR_CODE = 91;
const int GREEN_COLOR_CODE = 92;
const int YELLOW_COLOR_CODE = 93;
const int BLUE_COLOR_CODE = 94;
const int MAGENTA_COLOR_CODE = 95;
const int MAX_DECK_SIZE = 108;
struct card drawDeck[MAX_DECK_SIZE];
int currentDrawDeckId = 0;
struct card discardDeck[MAX_DECK_SIZE];
int topDiscardDeckId = 0;
struct player
{
    struct card hand[MAX_DECK_SIZE] = {};
    int handSize = 7;
};
const int MAX_PLAYERS = 4;
struct player players[MAX_PLAYERS];
int numberOfPlayers = 0;
int currentPlayerId = 0;
int playerOrder = 1;
const char colors[] = { 'R', 'G', 'Y', 'B', };
const int COLORS_SIZE = 4;
const int colorCodes[] = { RED_COLOR_CODE, GREEN_COLOR_CODE, YELLOW_COLOR_CODE, BLUE_COLOR_CODE };
const char wildColor = 'W';
const int wildColorCode = MAGENTA_COLOR_CODE;
const int STARTING_NUMBER_OF_CARDS = 7;
const char UNO_STR[] = "uno";
char activeWildColor = '\0';


void fillUnoDeck(struct card drawDeck[MAX_DECK_SIZE]);
int main();
int GameFlow(int& userAnswer, bool& retFlag, std::mt19937& gen);
void DrawCard(int prevUserId,std::mt19937& gen);
void SaveGameConsoleText(int& userAnswer, player& currentPlayer, bool& isValidOption);
void StartNewGame(std::mt19937& gen);
void SaveGameInFile();
void displayCurrentPlayerHand(player& currentPlayer);
void FillPlayersHands(int numberOfPlayers);
void shuffleDeck(struct card drawDeck[MAX_DECK_SIZE], int arrSize, std::mt19937& gen);

void ClearConsole();

void ResetConsoleColor();

void SetConsoleColor(int textColor);

void PrintTextInColor(const char text[], int color);


void colorInCard(struct card currentCard);

void colorInTopDiscardCard();

bool checkIfPlayerCanPlayCard(struct card currentCard, struct card playerCard);


void BuildCardText(card& c);

bool LoadGameFromFile();


char ChooseColorForWild(int playerId);
void playCard(int cardIndex, player& currentPlayer, std::mt19937& gen);

void ReshuffleDiscardPile(std::mt19937& gen);




bool charEquals(const char a[], const char b[], int size);

char toLower(char c);
bool equalsIgnoreCase(const char* a, const char* b);


int main()
{

    

    //return 0;
    std::random_device rd;
    unsigned int seed = rd();
    //seed = 2899746807;// wild in player hand in 2 players
    //seed = 597823264; // wild in the top discard card
    std::mt19937 gen(seed);

    std::cout << "Welcome to Uno tm console edition :D" << std::endl
        << "Do you want to start a new game or continue the game from last time?" << std::endl
        << "(if no previous game exists new game will start)" << std::endl;
    char tempAnsw[1000];
    int userAnswer=-1;
    bool validUserAnswer = false;
    do {
        std::cout << "[0] start new game    [1] continue last game" << std::endl;
        std::cin >> tempAnsw;
        if (tempAnsw[0] == '0' )
        {
            userAnswer = 0;
            validUserAnswer = true;
        }else if (tempAnsw[0] == '1')
        {
            userAnswer = 1;

            validUserAnswer = true;
        }
        else
        {
            std::cout << "Invalid answer. Choose from the valid options : )" << std::endl;
        }
    } while (validUserAnswer == false);

    if (userAnswer == 0)
    {
        StartNewGame(gen);
    }
    else if (userAnswer == 1)
    {
        if (!LoadGameFromFile())
        {
            std::cout << "Starting new game instead...\n\n";
            StartNewGame(gen);
        }
        else {
            std::cout << "Loading successful\n";
        }
    }

    // ГЛАВЕН ИГРАЛЕН ЦИКЪЛ
    while (true)
    {
        bool retFlag;
        int retVal = GameFlow(userAnswer, retFlag,gen);

        if (retFlag)  // Ако трябва да излезем от играта
        {
            return retVal;
        }
    }
}

void ReshuffleDiscardPile(std::mt19937& gen)
{
    // Провери дали има карти за разбъркване (повече от само топ картата)
    if (topDiscardDeckId == 0)
    {
        std::cout << "\n>>> Cannot reshuffle - only top card in discard pile. <<<\n";
        std::cout << ">>> Continuing without reshuffling... <<<\n\n";
        return;  // Просто излез, не спирай играта
    }

    std::cout << "\n>>> Reshuffling discard pile into draw deck! <<<\n\n";

    // Запази топ картата
    struct card topCard = discardDeck[topDiscardDeckId];

    // Копирай всички карти ОСВЕН топ картата обратно в draw deck
    int cardsToShuffle = topDiscardDeckId;

    for (int i = 0; i < cardsToShuffle; i++)
    {
        drawDeck[currentDrawDeckId + i] = discardDeck[i];
    }

    // Разбъркай картите в draw deck
    shuffleDeck(drawDeck + currentDrawDeckId, cardsToShuffle, gen);

    // Нулирай discard pile, остави само топ картата
    discardDeck[0] = topCard;
    topDiscardDeckId = 0;

    std::cout << "Reshuffled " << cardsToShuffle << " cards back into draw deck!\n\n";
}

void playCard(int cardIndex, player& currentPlayer, std::mt19937& gen)
{
    // 1. ВЗЕМИ КАРТАТА
    struct card playedCard = currentPlayer.hand[cardIndex];

    // 2. ДОБАВИ В DISCARD PILE
    topDiscardDeckId++;
    discardDeck[topDiscardDeckId] = playedCard;

    // 3. ПРЕМАХНИ ОТ РЪКАТА
    for (int i = cardIndex; i < currentPlayer.handSize - 1; i++)
    {
        currentPlayer.hand[i] = currentPlayer.hand[i + 1];
    }
    currentPlayer.handSize--;
    /*bool isUno = false;
    std::cout << "Say Uno? y/N (deafault N);";
    char unoChar;
    std::cin >> unoChar;
    if (unoChar=='y'|| unoChar == 'Y')
    {
        std::cout << "YOU SAID UNO"<<std::endl;

    }*/

    // 4. АКО Е WILD, ИЗБЕРИ ЦВЯТ
    if (playedCard.color == wildColor)
    {
        std::cout << "You played a Wild card!\n";
        activeWildColor = ChooseColorForWild(currentPlayerId);
    }
    else
    {
        activeWildColor = '\0';
    }

    // 5. ПРОВЕРИ ЗА ПОБЕДИТЕЛ
    if (currentPlayer.handSize == 0)
    {
        ClearConsole();
        std::cout << "====================================\n";
        std::cout << "   PLAYER " << currentPlayerId << " WINS!\n";
        std::cout << "   CONGRATULATIONS!\n";
        std::cout << "====================================\n";
        std::cout << "\nPress Enter to exit...";
        std::cin.ignore();
        std::cin.get();
        exit(0);
    }

    // 6. ОБРАБОТИ СПЕЦИАЛНИ КАРТИ
    if (charEquals(playedCard.value, "Skip", 5))
    {
        std::cout << "\n>>> SKIP! Player " << ((currentPlayerId + playerOrder + numberOfPlayers) % numberOfPlayers) << " is skipped! <<<\n\n";
        // Премини към следващия играч ДВА ПЪТИ (прескачаш един)
        currentPlayerId = (currentPlayerId + playerOrder + numberOfPlayers) % numberOfPlayers;
        currentPlayerId = (currentPlayerId + playerOrder + numberOfPlayers) % numberOfPlayers;
        return;
    }
    else if (charEquals(playedCard.value, "Reverse", 8))
    {
        std::cout << "\n>>> REVERSE! Direction changed! <<<\n\n";

        playerOrder *= -1;  // Обърни посоката ПЪРВО

        // В игра с 2 играча, Reverse работи като Skip
        if (numberOfPlayers == 2)
        {
            std::cout << ">>> (In 2-player game, Reverse acts as Skip) <<<\n\n";
            // Премини ДВА ПЪТИ (skip) - ВАЖНО: И ДВАТА РЕДА!
            currentPlayerId = (currentPlayerId + playerOrder + numberOfPlayers) % numberOfPlayers;
            currentPlayerId = (currentPlayerId + playerOrder + numberOfPlayers) % numberOfPlayers;
            return;
        }

        // В игра с 3+ играча, само премини към следващия в НОВАТА посока
        currentPlayerId = (currentPlayerId + playerOrder + numberOfPlayers) % numberOfPlayers;
        return;

    }
    else if (charEquals(playedCard.value, "+2", 3))
    {
        std::cout << "\n>>> DRAW +2! <<<\n";
        int nextPlayerId = (currentPlayerId + playerOrder + numberOfPlayers) % numberOfPlayers;
        std::cout << "Player " << nextPlayerId << " must draw 2 cards!\n";

        int cardsDrawn = 0;

        // Опитай се да тегли до 2 карти
        for (int i = 0; i < 2; i++)
        {
            // Провери дали има карти
            if (currentDrawDeckId >= MAX_DECK_SIZE)
            {
                ReshuffleDiscardPile(gen);
            }

            // Ако има карти след reshuffle
            if (currentDrawDeckId < MAX_DECK_SIZE)
            {
                players[nextPlayerId].hand[players[nextPlayerId].handSize++] = drawDeck[currentDrawDeckId++];
                cardsDrawn++;
            }
            else
            {
                // Няма повече карти, спри
                break;
            }
        }

        std::cout << "Player " << nextPlayerId << " drew " << cardsDrawn << " card(s) and skips their turn!\n\n";

        // Прескочи следващия играч
        currentPlayerId = (currentPlayerId + playerOrder + numberOfPlayers) % numberOfPlayers;
        currentPlayerId = (currentPlayerId + playerOrder + numberOfPlayers) % numberOfPlayers;
        return;
    }
    else if (charEquals(playedCard.value, "+4", 3))
    {
        std::cout << "\n>>> WILD +4! <<<\n";
        int nextPlayerId = (currentPlayerId + playerOrder + numberOfPlayers) % numberOfPlayers;
        std::cout << "Player " << nextPlayerId << " must draw 4 cards!\n";

        int cardsDrawn = 0;

        // Опитай се да тегли до 4 карти
        for (int i = 0; i < 4; i++)
        {
            // Провери дали има карти
            if (currentDrawDeckId >= MAX_DECK_SIZE)
            {
                ReshuffleDiscardPile(gen);
            }

            // Ако има карти след reshuffle
            if (currentDrawDeckId < MAX_DECK_SIZE)
            {
                players[nextPlayerId].hand[players[nextPlayerId].handSize++] = drawDeck[currentDrawDeckId++];
                cardsDrawn++;
            }
            else
            {
                // Няма повече карти, спри
                break;
            }
        }

        std::cout << "Player " << nextPlayerId << " drew " << cardsDrawn << " card(s) and skips their turn!\n\n";

        // Прескочи следващия играч
        currentPlayerId = (currentPlayerId + playerOrder + numberOfPlayers) % numberOfPlayers;
        currentPlayerId = (currentPlayerId + playerOrder + numberOfPlayers) % numberOfPlayers;
        return;
    }
    // 7. ОБИКНОВЕНА КАРТА - ПРЕМИНИ КЪМ СЛЕДВАЩ ИГРАЧ
    currentPlayerId = (currentPlayerId + playerOrder + numberOfPlayers) % numberOfPlayers;
}

















int GameFlow(int& userAnswer, bool& retFlag, std::mt19937& gen)
{
    retFlag = false;  // По подразбиране не излизаме

    struct card currentCard = discardDeck[topDiscardDeckId];
    bool isValidOption = false;
    ClearConsole();

    do {
        do
        {
            std::cout << "Current player: " << currentPlayerId << std::endl;
            std::cout << "Current card: ";
            colorInTopDiscardCard();
            std::cout << std::endl << "Your hand: " << std::endl;

            displayCurrentPlayerHand(players[currentPlayerId]);
            std::cout << "[" << players[currentPlayerId].handSize << "] Draw card" << std::endl;
            std::cout << "[" << players[currentPlayerId].handSize + 1 << "] Save game and exit" << std::endl;
            std::cout << "What do you want to do?" << std::endl;
            std::cin >> userAnswer;
        } while (!(userAnswer >= 0 && userAnswer <= players[currentPlayerId].handSize + 1));

        if (userAnswer == players[currentPlayerId].handSize)
        {
            isValidOption = true;
        }
        else if (userAnswer == players[currentPlayerId].handSize + 1)
        {
            SaveGameConsoleText(userAnswer, players[currentPlayerId], isValidOption);
        }
        
        else {
            struct card playerCard = players[currentPlayerId].hand[userAnswer];
            isValidOption = checkIfPlayerCanPlayCard(currentCard, playerCard);
        }

        if (!isValidOption && userAnswer < players[currentPlayerId].handSize)
        {
            ClearConsole();
            std::cout << "Invalid choice - you cannot play this card!\n\n";
        }

        

    } while (!isValidOption);

    // ОБРАБОТИ ИЗБОРА
    if (userAnswer == players[currentPlayerId].handSize)
    {
        // Draw card
        DrawCard(currentPlayerId,gen);
        card drawnCard= players[currentPlayerId].hand[players[currentPlayerId].handSize-1];
        bool canPlayDrawnCard= checkIfPlayerCanPlayCard(discardDeck[topDiscardDeckId], drawnCard);
        if (canPlayDrawnCard)
        {
            std::cout << "can play ";
            colorInCard(drawnCard);
            std::cout << " on top card ";
            colorInTopDiscardCard();//(discardDeck[topDiscardDeckId]);
            std::cout << std::endl;
            std::cout << "Do you want to play "; 
            colorInCard( drawnCard);
            std::cout<< "?"<< std::endl;


            std::cout << "[1] play card   [2] don't play card"<<std::endl;
            std::cin >> userAnswer;
            if (userAnswer==1)
            {
                playCard(players[currentPlayerId].handSize-1 , players[currentPlayerId], gen);
            }
            return 0;
        }
        else
        {
            std::cout << "can't play ";
            colorInCard(drawnCard);
            std::cout << " on top card ";
            colorInTopDiscardCard();//(discardDeck[topDiscardDeckId]);
            std::cout<< std::endl;

        }

        // След теглене, играчът пропуска хода си
        std::cout << "Press Enter to continue... uno 1";
        std::cin.ignore();
        std::cin.get();

        currentPlayerId = (currentPlayerId + playerOrder + numberOfPlayers) % numberOfPlayers;
    }
    else if (userAnswer == players[currentPlayerId].handSize + 1)
    {
        // Save and exit
        SaveGameInFile();
        retFlag = true;  // ВАЖНО: Сигнализираме че трябва да излезем
        return 0;
    }
    else
    {
        int currPlayerIdBeforePlay = currentPlayerId;
        // ИГРАЙ КАРТАТА
        playCard(userAnswer, players[currentPlayerId],gen);
        char temp[1000];
        std::cout << "enter Uno, or something else to continue(entering Uno means you are saying it)" << std::endl;

        //std::cin>>temp;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.getline(temp, 100);

        if (equalsIgnoreCase(temp, UNO_STR))
        {
            std::cout << "You Said Uno!" << std::endl;


        }

        if (players[currPlayerIdBeforePlay].handSize == 1)
        {
            if (equalsIgnoreCase(temp, UNO_STR))
            {
                std::cout << "You Said Uno Correctly!\nNo need to draw cards as penalty\n";
            }
            else
            {
                std::cout << "You Forgot to say Uno! Draw 1 card as penalty.\n";
                DrawCard(currPlayerIdBeforePlay,gen); // твоя функция за теглене
            }
        }
        else
        {
            if (equalsIgnoreCase(temp, UNO_STR))
            {
                std::cout << "You Said Uno incorrectly!\nDraw 1 card as penalty.\n";
                std::cout << "current player: "<<currentPlayerId<<"\ncurrPlayerIdBeforePlay: "<< currPlayerIdBeforePlay<<"\n";
                DrawCard(currPlayerIdBeforePlay,gen);

                /*if (currentPlayerId == currPlayerIdBeforePlay)
                {
                    currentPlayerId = (currentPlayerId + playerOrder + numberOfPlayers) % numberOfPlayers;
                }*/
            }

        }
        /*if (currentPlayerId == currPlayerIdBeforePlay)
        {
            currentPlayerId = (currentPlayerId + playerOrder + numberOfPlayers) % numberOfPlayers;
        }*/

        std::cout << temp << std::endl;
        if (equalsIgnoreCase(temp, UNO_STR)){

        std::cout << "Press Enter to continue...";
        //std::cin.ignore();
        std::cin.get();
        }
    }

    return 0;
}

void DrawCard(int userId,std::mt19937& gen)
{
    int currentPlayerId = userId;
    std::cout << "Drawing a card...\n";
    // Провери дали има карти в дека
    if (currentDrawDeckId >= MAX_DECK_SIZE - 1)
    {
        //std::cout << "No more cards in deck!\n";
        // TODO: Reshuffle логика
        ReshuffleDiscardPile(gen);
    }
    else
    {
        players[currentPlayerId].hand[players[currentPlayerId].handSize] = drawDeck[currentDrawDeckId++];
        players[currentPlayerId].handSize++;
        std::cout << "You drew: ";
        colorInCard(players[currentPlayerId].hand[players[currentPlayerId].handSize - 1]);
        std::cout << "\n\n";
    }
}


void SaveGameConsoleText(int& userAnswer, player& currentPlayer, bool& isValidOption)
{
    std::cout << "Are you sure? if there is older save it will be overwritten." << std::endl
        << "[0] Save game and exit [1] Continue current game: " << std::endl;

    std::cin >> userAnswer;
    if (userAnswer == 0)
    {
        userAnswer = currentPlayer.handSize + 1;
        isValidOption = true;

    }
}

void StartNewGame(std::mt19937& gen)
{
    std::cout << "starting new game : D" << std::endl;


    do {
        std::cout << "How many players are gonna play the game? (form 2 to 4) ";
        std::cin >> numberOfPlayers;
    } while (!(numberOfPlayers > 1 && numberOfPlayers <= 4));

    fillUnoDeck(drawDeck);
    shuffleDeck(drawDeck, MAX_DECK_SIZE, gen);

    FillPlayersHands(numberOfPlayers);

    if (drawDeck[currentDrawDeckId].color == wildColor)
    {
        std::cout << "WIIIILD!!!" << std::endl;

        std::cout << "The starting card is Wild!" << std::endl;
        activeWildColor = ChooseColorForWild(currentPlayerId);


    }
    else
    {
        // Ако не е Wild, изчисти активния цвят
        activeWildColor = '\0';
    }
    discardDeck[topDiscardDeckId] = drawDeck[currentDrawDeckId++];
}




char ChooseColorForWild(int playerId)
{
    int colorChoice = -1;


    do {
        std::cout << "Player " << playerId << ", choose a color for the Wild card:" << std::endl;
        std::cout << "[0] ";
        PrintTextInColor("Red", RED_COLOR_CODE);
        std::cout << " [1] ";
        PrintTextInColor("Green", GREEN_COLOR_CODE);
        std::cout << " [2] ";
        PrintTextInColor("Yellow", YELLOW_COLOR_CODE);
        std::cout << " [3] ";
        PrintTextInColor("Blue", BLUE_COLOR_CODE);
        std::cout << std::endl;
        std::cout << "Your choice: ";
        std::cin >> colorChoice;
        if (colorChoice < 0 || colorChoice > 3)
        {
            ClearConsole();
            std::cout << "invalid choice, please choose again: \n \n";
            
        }
    } while (colorChoice < 0 || colorChoice > 3);

    return colors[colorChoice];  // Връща 'R', 'G', 'Y', или 'B'
}



void BuildCardText(card& c)
{
    c.text[0] = c.color;

    if (c.value[0] == '\0')
    {
        c.text[1] = '\0';
        return;
    }

    c.text[1] = ' ';
    int i = 0;
    while (c.value[i] != '\0')
    {
        c.text[2 + i] = c.value[i];
        i++;
    }
    c.text[2 + i] = '\0';
}

void SaveGameInFile()
{
    std::ofstream out(FILENAME, std::ios::trunc);
    if (!out)
    {
        std::cout << "Cannot open save file.\n";
        return;
    }

    out << numberOfPlayers << '\n';
    out << currentPlayerId << '\n';
    out << playerOrder << '\n';

    if (activeWildColor == '\0')
        out << "-\n";
    else
        out << activeWildColor << '\n';

    // PLAYERS
    for (int i = 0; i < numberOfPlayers; i++)
    {
        out << players[i].handSize << '\n';
        for (int j = 0; j < players[i].handSize; j++)
        {
            out << players[i].hand[j].color << '\n';

            // За Wild карти без value, пиши "-"
            if (players[i].hand[j].value[0] == '\0')
                out << "-\n";
            else
                out << players[i].hand[j].value << '\n';
        }
    }

    // DRAW DECK
    out << currentDrawDeckId << '\n';
    for (int i = currentDrawDeckId; i < MAX_DECK_SIZE; i++)
    {
        out << drawDeck[i].color << '\n';

        if (drawDeck[i].value[0] == '\0')
            out << "-\n";
        else
            out << drawDeck[i].value << '\n';
    }

    // DISCARD DECK
    out << topDiscardDeckId << '\n';
    for (int i = 0; i <= topDiscardDeckId; i++)
    {
        out << discardDeck[i].color << '\n';

        if (discardDeck[i].value[0] == '\0')
            out << "-\n";
        else
            out << discardDeck[i].value << '\n';
    }

    out.close();
    std::cout << "Game saved successfully.\n";
}

bool LoadGameFromFile()
{
    std::ifstream in(FILENAME);
    if (!in)
    {
        std::cout << "Save file not found.\n";
        return false;
    }

    currentDrawDeckId = 0;
    topDiscardDeckId = 0;

    in >> numberOfPlayers;
    in >> currentPlayerId;
    in >> playerOrder;

    char tempColor;
    in >> tempColor;
    if (tempColor == '-')
        activeWildColor = '\0';
    else
        activeWildColor = tempColor;
    // PLAYERS
    for (int i = 0; i < numberOfPlayers; i++)
    {
        in >> players[i].handSize;
        for (int j = 0; j < players[i].handSize; j++)
        {
            in >> players[i].hand[j].color;
            in >> players[i].hand[j].value;

            // Ако е "-", направи го '\0'
            if (players[i].hand[j].value[0] == '-' && players[i].hand[j].value[1] == '\0')
                players[i].hand[j].value[0] = '\0';

            BuildCardText(players[i].hand[j]);
        }
    }

    // DRAW DECK
    in >> currentDrawDeckId;
    for (int i = currentDrawDeckId; i < MAX_DECK_SIZE; i++)
    {
        in >> drawDeck[i].color;
        in >> drawDeck[i].value;

        if (drawDeck[i].value[0] == '-' && drawDeck[i].value[1] == '\0')
            drawDeck[i].value[0] = '\0';

        BuildCardText(drawDeck[i]);
    }

    // DISCARD DECK
    in >> topDiscardDeckId;
    for (int i = 0; i <= topDiscardDeckId; i++)
    {
        in >> discardDeck[i].color;
        in >> discardDeck[i].value;

        if (discardDeck[i].value[0] == '-' && discardDeck[i].value[1] == '\0')
            discardDeck[i].value[0] = '\0';

        BuildCardText(discardDeck[i]);
    }

    in.close();
    std::cout << "Game loaded successfully.\n";
    return true;
}


bool checkIfPlayerCanPlayCard(struct card currentCard, struct card playerCard) {

    if (playerCard.color==activeWildColor)
    {
        return true;
    }
    if (playerCard.color == wildColor)
    {
        return true;
    }

    // Ако текущата карта е Wild с избран цвят, използвай активния цвят
    char effectiveColor = currentCard.color;
    if (currentCard.color == wildColor && activeWildColor != '\0') {
        effectiveColor = activeWildColor;
    }

    if (effectiveColor == playerCard.color)
    {
        return true;
    }

    if (charEquals(currentCard.value, playerCard.value, 8))
    {
        return true;
    }

    return false;
}
void displayCurrentPlayerHand(player& currentPlayer)
{
    for (int i = 0; i < currentPlayer.handSize; i++)
    {
        std::cout << "[" << i << "] ";
        colorInCard(currentPlayer.hand[i]);
        std::cout << " ";
    }
}
void colorInCard(struct card currentCard) {
    char color = currentCard.color;

    for (int i = 0; i < COLORS_SIZE; i++)
    {
        if (color == colors[i])
        {
            PrintTextInColor(currentCard.text, colorCodes[i]);
            return;
        }
    }
    if (color == wildColor)
    {
        PrintTextInColor(currentCard.text, MAGENTA_COLOR_CODE);
    }
}

void colorInTopDiscardCard() {
    struct card currentCard = discardDeck[topDiscardDeckId];
    char displayColor = currentCard.color;

    // Ако топ картата е Wild и има избран цвят, покажи го
    if (currentCard.color == wildColor && activeWildColor != '\0') {
        displayColor = activeWildColor;
    }

    for (int i = 0; i < COLORS_SIZE; i++)
    {
        if (displayColor == colors[i])
        {
            PrintTextInColor(currentCard.text, colorCodes[i]);
            return;
        }
    }
    if (displayColor == wildColor)
    {
        PrintTextInColor(currentCard.text, MAGENTA_COLOR_CODE);
    }
}


void FillPlayersHands(int numberOfPlayers)
{
    for (int i = 0; i < numberOfPlayers; i++)
    {
        struct player currentPlayer;
        for (int i = 0; i < STARTING_NUMBER_OF_CARDS; i++)
        {
            currentPlayer.hand[i] = drawDeck[currentDrawDeckId++];
        }
        players[i] = currentPlayer;

    }
}



void fillUnoDeck(struct card drawDeck[MAX_DECK_SIZE]) {
    int cardIndex = 0;
    struct card currentCard;
    char cardValue[10] = {};
    for (int colorIndex = 0; colorIndex < COLORS_SIZE; colorIndex++)
    {
        for (int numberValue = 0; numberValue <= 9; numberValue++)
        {
            //cardValue = colors[colorIndex] + " " + (numberValue);
            currentCard.color = colors[colorIndex];
            currentCard.value[0] = (numberValue + '0');
            currentCard.value[1] = '\0';

            currentCard.text[0] = colors[colorIndex];
            currentCard.text[1] = ' ';
            currentCard.text[2] = (numberValue + '0');
            currentCard.text[3] = '\0';
            drawDeck[cardIndex++] = currentCard;

            if (numberValue != 0)
            {
                drawDeck[cardIndex++] = currentCard;

            }
            //std::cout << cardValue << "    ";
        }

        currentCard.color = colors[colorIndex];
        currentCard.value[0] = '+';
        currentCard.value[1] = '2';
        currentCard.value[2] = '\0';
        currentCard.text[0] = colors[colorIndex];
        currentCard.text[1] = ' ';
        currentCard.text[2] = '+';
        currentCard.text[3] = '2';
        currentCard.text[4] = '\0';
        drawDeck[cardIndex++] = currentCard;
        drawDeck[cardIndex++] = currentCard;

        currentCard.color = colors[colorIndex];
        currentCard.value[0] = 'S';
        currentCard.value[1] = 'k';
        currentCard.value[2] = 'i';
        currentCard.value[3] = 'p';
        currentCard.value[4] = '\0';
        currentCard.text[0] = colors[colorIndex];
        currentCard.text[1] = ' ';
        currentCard.text[2] = 'S';
        currentCard.text[3] = 'k';
        currentCard.text[4] = 'i';
        currentCard.text[5] = 'p';
        currentCard.text[6] = '\0';

        drawDeck[cardIndex++] = currentCard;
        drawDeck[cardIndex++] = currentCard;

        currentCard.color = colors[colorIndex];
        currentCard.value[0] = 'R';
        currentCard.value[1] = 'e';
        currentCard.value[2] = 'v';
        currentCard.value[3] = 'e';
        currentCard.value[4] = 'r';
        currentCard.value[5] = 's';
        currentCard.value[6] = 'e';
        currentCard.value[7] = '\0';
        currentCard.text[0] = colors[colorIndex];
        currentCard.text[1] = ' ';
        currentCard.text[2] = 'R';
        currentCard.text[3] = 'e';
        currentCard.text[4] = 'v';
        currentCard.text[5] = 'e';
        currentCard.text[6] = 'r';
        currentCard.text[7] = 's';
        currentCard.text[8] = 'e';
        currentCard.text[9] = '\0';
        drawDeck[cardIndex++] = currentCard;
        drawDeck[cardIndex++] = currentCard;

        

    }

    currentCard.color = wildColor;
    currentCard.value[0] = '\0';
    currentCard.text[0] = wildColor;
    currentCard.text[1] = '\0';
    drawDeck[cardIndex++] = currentCard;
    drawDeck[cardIndex++] = currentCard;
    drawDeck[cardIndex++] = currentCard;
    drawDeck[cardIndex++] = currentCard;

    currentCard.color = wildColor;
    currentCard.value[0] = '+';
    currentCard.value[1] = '4';
    currentCard.value[2] = '\0';
    currentCard.text[0] = wildColor;
    currentCard.text[1] = ' ';
    currentCard.text[2] = '+';
    currentCard.text[3] = '4';
    currentCard.text[4] = '\0';
    drawDeck[cardIndex++] = currentCard;
    drawDeck[cardIndex++] = currentCard;
    drawDeck[cardIndex++] = currentCard;
    drawDeck[cardIndex++] = currentCard;

}

void shuffleDeck(struct card drawDeck[MAX_DECK_SIZE], int arrSize,std::mt19937& gen) {
    std::shuffle(drawDeck, drawDeck+ arrSize, gen);
}


void ClearConsole() {
    system("CLS");
}
void ResetConsoleColor() { std::cout << "\033[0m"; }
void SetConsoleColor(int textColor)
{
    std::cout << "\033[" << textColor << "m";
}
void PrintTextInColor(const char text[], int color) {
    SetConsoleColor(color);
    std::cout << text;
    ResetConsoleColor();

}

bool charEquals(const char a[], const char b[], int size) {
    for (int i = 0; i < size; i++) {
        if (a[i] != b[i]) {
            return false; // веднага връщаме false, ако различни
        }
        if (a[i] == '\0' && b[i] == '\0') {
            return true; // края на двата стринга е достигнат
        }
    }
    // ако стигнем до края на масива без различия
    return true;
}

char toLower(char c)
{
    if (c >= 'A' && c <= 'Z')
        return c + ('a' - 'A');
    return c;
}

bool equalsIgnoreCase(const char* a, const char* b)
{
    while (*a && *b)
    {
        if (toLower(*a) != toLower(*b))
            return false;
        ++a;
        ++b;
    }
    return *a == *b;
}
