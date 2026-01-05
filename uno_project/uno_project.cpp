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
    struct card hand[MAX_DECK_SIZE];
    int handSize = 7;
};
const int MAX_PLAYERS = 4;
struct player players[MAX_PLAYERS];
int numberOfPlayers = 0;
int currentPlayerId = 0;
int playerOrder = 1;
void fillUnoDeck(struct card drawDeck[MAX_DECK_SIZE]);
int main();
void SaveGameInFile();
void displayCurrentPlayerHand(player& currentPlayer);
void FillPlayersHands(int numberOfPlayers);
void shuffleDeck(struct card drawDeck[MAX_DECK_SIZE], int arrSize, std::mt19937& gen);

void ClearConsole();

void ResetConsoleColor();

void SetConsoleColor(int textColor);

void PrintTextInColor(const char text[], int color);
const char colors[] = { 'R', 'G', 'Y', 'B', };
const int COLORS_SIZE = 4;
const int colorCodes[] = { RED_COLOR_CODE, GREEN_COLOR_CODE, YELLOW_COLOR_CODE, BLUE_COLOR_CODE };
const char wildColor = 'W';
const int wildColorCode = MAGENTA_COLOR_CODE;
const int STARTING_NUMBER_OF_CARDS = 7;
          

void colorInCard(struct card currentCard);

bool checkIfPlayerCanPlayCard(struct card currentCard, struct card playerCard);
bool charEquals(const char a[], const char b[], int size);


void BuildCardText(card& c);

bool LoadGameFromFile();
int main()
{
    std::random_device rd;
    unsigned int seed = rd();
    
    std::mt19937 gen(seed);
    //       597823264      //wild card is top discard card when 2 players (reshuffles deck and chooses new card)
    //gen.seed(8);
    //std::cout << "seed: "<<seed << std::endl;
    //std::cout << "Hello World!\n";

    std::cout << "Welcome to Uno tm console edition :D" << std::endl
        << "Do you want to start a new game or continue the game from last time?" << std::endl
        << "(if no previous game exists new game will start)" << std::endl;
    int userAnswer;
    bool validUserAnswer = false;
    do {
        std::cout << "[0] start new game    [1] continue last game" << std::endl;
        std::cin >> userAnswer;
        if (userAnswer == 0 || userAnswer == 1)
        {
            validUserAnswer = true;


        }
        else
        {
            std::cout << "Invalid answer. Choose from the valid options : )" << std::endl;
        }
    } while (validUserAnswer == false);

    if (userAnswer == 0)
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
            do
                shuffleDeck(drawDeck + currentDrawDeckId, MAX_DECK_SIZE - currentDrawDeckId, gen);
            while (drawDeck[currentDrawDeckId].color == wildColor);

        }
        discardDeck[topDiscardDeckId] = drawDeck[currentDrawDeckId++];

    }
    else if (userAnswer == 1)
    {

        if (!LoadGameFromFile())
        {
            std::cout << "Starting new game instead...\n";
            // тук стартираш нова игра
        }
        else {
            std::cout << "loading somewhat successful\n";

        }
        //std::ifstream UnoSaveState(FILENAME);
        //if (!UnoSaveState) {
        //    // File does not exist or could not be opened
        //    std::cout << "File does not exist or cannot be opened." << std::endl;
        //}
        //else {
        //    // Move to the end to check file size
        //    UnoSaveState.seekg(0, std::ios::end);
        //    if (UnoSaveState.tellg() == 0) {
        //        // File is empty
        //        std::cout << "File exists but is empty." << std::endl;
        //    }
        //    else {
        //        // File has content
        //        std::cout << "File exists and has content." << std::endl;
        //        //const int MAX_LINE_LENGTH = 1256; // Adjust as needed
        //        //char line[MAX_LINE_LENGTH];
        //        //UnoSaveState.seekg(0, std::ios::beg);
        //        //while (UnoSaveState.getline(line, MAX_LINE_LENGTH)) {
        //        //    std::cout << line << std::endl;
        //        //}
        //    }

        //}
        //UnoSaveState.close();




    }


    std::cout << "Current player: " << currentPlayerId << std::endl;
    std::cout << "Current card: ";

    

    struct card currentCard = discardDeck[topDiscardDeckId];
    colorInCard(currentCard);
    std::cout << std::endl << "Your hand: " << std::endl;
    struct player currentPlayer = players[currentPlayerId];
    bool isValidOption = false;
    do {
        do
        {
            displayCurrentPlayerHand(currentPlayer);
            std::cout << "[" << currentPlayer.handSize << "] Draw card" << std::endl;
            std::cout << "[" << currentPlayer.handSize + 1 << "] Save game and exit" << std::endl;
            std::cout << "What do you want to do?" << std::endl;
            std::cin >> userAnswer;
        } while (!(userAnswer >= 0 && userAnswer <= currentPlayer.handSize + 1));
        if (userAnswer == currentPlayer.handSize)
        {
            isValidOption = true;
        }
        else if (userAnswer == currentPlayer.handSize + 1)
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
        else {
            struct card playerCard = currentPlayer.hand[userAnswer];
            isValidOption = checkIfPlayerCanPlayCard(currentCard, playerCard);
        }
    } while (!isValidOption);

    if (userAnswer == currentPlayer.handSize + 1)
    {
        //save progress and exit game

        SaveGameInFile();

        return 0;

    }



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

bool LoadGameFromFile()
{
    std::ifstream in(FILENAME);
    if (!in)
    {
        std::cout << "Save file not found.\n";
        return false;
    }

    // RESET
    currentDrawDeckId = 0;
    topDiscardDeckId = 0;

    in >> numberOfPlayers;
    in >> currentPlayerId;
    in >> playerOrder;

    // PLAYERS
    for (int i = 0; i < numberOfPlayers; i++)
    {
        in >> players[i].handSize;
        for (int j = 0; j < players[i].handSize; j++)
        {
            in >> players[i].hand[j].color;
            in >> players[i].hand[j].value;
            BuildCardText(players[i].hand[j]);
        }
    }

    // DRAW DECK
    in >> currentDrawDeckId;
    for (int i = currentDrawDeckId; i < MAX_DECK_SIZE; i++)
    {
        in >> drawDeck[i].color;
        in >> drawDeck[i].value;
        BuildCardText(drawDeck[i]);
    }

    // DISCARD DECK ← ТУК БЕШЕ ПРОБЛЕМЪТ
    in >> topDiscardDeckId;
    for (int i = 0; i <= topDiscardDeckId; i++)
    {
        in >> discardDeck[i].color;
        in >> discardDeck[i].value;
        BuildCardText(discardDeck[i]);
    }

    in.close();
    std::cout << "Game loaded successfully.\n";
    return true;
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

    // PLAYERS
    for (int i = 0; i < numberOfPlayers; i++)
    {
        out << players[i].handSize << '\n';
        for (int j = 0; j < players[i].handSize; j++)
        {
            out << players[i].hand[j].color << '\n';
            out << players[i].hand[j].value << '\n';
        }
    }

    // DRAW DECK
    out << currentDrawDeckId << '\n';
    for (int i = currentDrawDeckId; i < MAX_DECK_SIZE; i++)
    {
        out << drawDeck[i].color << '\n';
        out << drawDeck[i].value << '\n';
    }

    // DISCARD DECK
    out << topDiscardDeckId << '\n';   // ← ИНДЕКС
    for (int i = 0; i <= topDiscardDeckId; i++)
    {
        out << discardDeck[i].color << '\n';
        out << discardDeck[i].value << '\n';
    }

    out.close();
    std::cout << "Game saved successfully.\n";
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
bool checkIfPlayerCanPlayCard(struct card currentCard, struct card playerCard) {
    if (playerCard.color==wildColor)
    {
        return true;
    }
    if (currentCard.color == playerCard.color)
    {
        return true;
    }
    if (charEquals(currentCard.value, playerCard.value,8))
    {
        return true;
    }return false;
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