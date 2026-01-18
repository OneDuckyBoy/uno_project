/**
*
* Solution to course project # 4
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2025/2026
*
* @author Stilian Milenov Matev
* @idnumber 7MI0600671
* @compiler VC
*
* <File with the full game logic and all the needed helper functions>
*
*/


#include <iostream>
#include <algorithm>
#include <random>
#include <fstream>
const int MAX_CHAR_ARRAY_SIZE = 1000;

const char FILENAME_1[MAX_CHAR_ARRAY_SIZE] = "UnoSaveState.txt";
const char FILENAME_2[MAX_CHAR_ARRAY_SIZE] = "UnoSaveState2.txt";
const char FILENAME_3[MAX_CHAR_ARRAY_SIZE] = "UnoSaveState3.txt";
const int MAX_VALUE_LENGTH = 10;
const int MAX_TEXT_LENGTH = 20;
const int ZERO_NUMBER_CARD = 0;
const int LAST_NUMBER_CARD = 9;
const int MAX_PLAYERS = 4;
const int RED_COLOR_CODE = 91;
const int GREEN_COLOR_CODE = 92;
const int YELLOW_COLOR_CODE = 93;
const int BLUE_COLOR_CODE = 94;
const int MAGENTA_COLOR_CODE = 95;
const int MAX_DECK_SIZE = 108;
const char COLORS[] = { 'R', 'G', 'Y', 'B', };
const int COLORS_SIZE = 4;
const int COLOR_CODES[] = { RED_COLOR_CODE, GREEN_COLOR_CODE, YELLOW_COLOR_CODE, BLUE_COLOR_CODE };
const char WILD_COLOR = 'W';
const int WILD_COLOR_CODE = MAGENTA_COLOR_CODE;
const char UNO_STR[] = "uno";
const int SKIP_STRING_SIZE = 5;
const int REVERSE_STRING_SIZE = 8;
const int PLUS_2_STRING_SIZE = 3;
const int PLUS_4_STRING_SIZE = 3;
const int STARTING_NUMBER_OF_CARDS = 7;

const int numberOfSaveFiles = 3;
const char* SAVEFILE_NAMES[] = { FILENAME_1, FILENAME_2, FILENAME_3 };

struct card
{
    char color;
    char value[MAX_VALUE_LENGTH];
    char text[MAX_TEXT_LENGTH];
};
struct player
{
    struct card hand[MAX_DECK_SIZE] = {};
    int handSize = STARTING_NUMBER_OF_CARDS;
};
const struct savestate {
    struct card discardDeck[MAX_DECK_SIZE];
    struct card drawDeck[MAX_DECK_SIZE];
    struct player players[MAX_PLAYERS];
    char activeWildColor = '\0';
    int currentDrawDeckId = 0;
    int topDiscardDeckId = 0;
    int numberOfPlayers = 0;
    int currentPlayerId = 0;
    int playerOrder = 1;
    int currentSaveFileId = -1;
};

struct SaveFileInfo
{
    bool exists;
    bool isEmpty;
    int numPlayers;
    int currentPlayer;
    card topCard;
    char activeColor;

};


int GameLoop(savestate& unoSavestate, std::mt19937& gen);

int main();


void GameBegining(int& userAnswer, struct savestate& unoSavestate, std::mt19937& gen);

void FillUnoDeck(struct card drawDeck[MAX_DECK_SIZE]);
int GameFlow(savestate& uss, int& userAnswer, bool& retFlag, std::mt19937& gen);
void ChooseActionToPlay(savestate& uss, int& userAnswer, const card& currentCard);
void PlayAction(int& userAnswer, savestate& uss, bool& isValidOption, const card& currentCard);
void PlayDrawnCard(const card& drawnCard, int& userAnswer, std::mt19937& gen, savestate& uss);
void SayUnoAction(int currPlayerIdBeforePlay, std::mt19937& gen, savestate& uss);
void MoveToNextPlayer(savestate& uss);
void DrawCard(savestate& uss, int prevUserId, std::mt19937& gen);
void SaveGameConsoleText(int& userAnswer, player& currentPlayer, bool& isValidOption);
void StartNewGame(savestate& unoSavestate, std::mt19937& gen);
void SaveGameInFile(savestate& uss, char filename[MAX_CHAR_ARRAY_SIZE]);
void ChooseSaveFIleForSaveGame(savestate uss);
void DisplayCurrentPlayerHand(player& currentPlayer);
void FillPlayersHands(player players[MAX_PLAYERS], int numberOfPlayers, card drawDeck[MAX_DECK_SIZE], int currentDrawDeckId);
void ShuffleDeck(struct card drawDeck[MAX_DECK_SIZE], int arrSize, std::mt19937& gen);
void ClearConsole();
void ResetConsoleColor();
void SetConsoleColor(int textColor);
void PrintTextInColor(const char text[], int color);
void ColorInCard(struct card currentCard, char activeWildColor = '\0');
bool CheckIfPlayerCanPlayCard(char activeWildColor, struct card currentCard, struct card playerCard);
void BuildCardText(card& c);
bool LoadGameFromFile(savestate& uss);
char ChooseColorForWild(savestate& uss);
void PlayCard(int cardIndex, player& currentPlayer, std::mt19937& gen, savestate& uss);
void Draw4CardAction(std::mt19937& gen, savestate& uss);
void Draw2CardAction(std::mt19937& gen, savestate& uss);
void ReverseCardAction(savestate& uss);
void SkipCardAction(savestate& uss);
void CheckIfPlayerIsWinner(player& currentPlayer, int currentPlayerId);
void ReshuffleDiscardPile(savestate& uss, std::mt19937& gen);
bool CharEquals(const char a[], const char b[], int size);
char ToLower(char c);
bool EqualsIgnoreCase(const char* a, const char* b);
bool ReadIntFromConsole(int& outValue);
int ReadValidInteger(const char* prompt, int minValue, int maxValue);
int DrawMultipleCards(int playerId, int numCards, std::mt19937& gen, savestate& uss);
void MyStrCopy(const char src[MAX_CHAR_ARRAY_SIZE], char dest[MAX_CHAR_ARRAY_SIZE]);
int chooseSaveFile(char textForCancel[MAX_CHAR_ARRAY_SIZE], int currentSaveFileId);
SaveFileInfo GetSaveFileInfo(const char* filename);
void DisplaySaveSlot(int slotNumber, const SaveFileInfo& info, bool IsCurrentFile);
bool ReadValidIntegerWhileCycle(int minValue, int maxValue, int& value);

int main()
{

    //starting the random generator
    std::random_device rd;
    unsigned int seed = rd();
    std::mt19937 gen(seed);

    
    //initializing save state
    savestate unoSavestate;
    int userAnswer=-1;

    GameBegining(userAnswer, unoSavestate, gen);


    return GameLoop(unoSavestate, gen);
}

int GameLoop(savestate& unoSavestate, std::mt19937& gen)
{
    int userAnswer = -1;

    while (true)
    {
        bool retFlag;
        int retVal = GameFlow(unoSavestate, userAnswer, retFlag, gen);

        if (retFlag)
        {
            return retVal;
        }

        ClearConsole();
        std::cout << "give pc to next player: player " << unoSavestate.currentPlayerId << std::endl;
        std::cout << "and press enter...";
        //std::cin.ignore();
        std::cin.get();
    }
}


void DisplaySaveSlot(int slotNumber, const SaveFileInfo& info, bool isCurrentSaveFile = false)
{
    std::cout << "[" << slotNumber << "] Slot " << slotNumber << ": ";

    if (!info.exists || info.isEmpty)
    {
        std::cout << "EMPTY\n";
        return;
    }

    std::cout << info.numPlayers << " players, Player " << info.currentPlayer << ", Top: ";

    ColorInCard(info.topCard, info.activeColor);
    if (isCurrentSaveFile)
    {
        std::cout << " (current save file)";
    }
    std::cout << "\n";
}
 SaveFileInfo GetSaveFileInfo(const char* filename)
{
    SaveFileInfo info;
    info.exists = false;
    info.isEmpty = true;
    info.numPlayers = 0;
    info.currentPlayer = 0;
    info.activeColor = '\0';

    std::ifstream in(filename);
    if (!in)
    {
        return info;
    }

    info.exists = true;

    in.seekg(0, std::ios::end);
    if (in.tellg() == 0)
    {
        in.close();
        return info;
    }

    info.isEmpty = false;
    in.seekg(0, std::ios::beg);

    in >> info.numPlayers;
    in >> info.currentPlayer;

    int playerOrder;
    in >> playerOrder;

    char tempColor;
    in >> tempColor;
    if (tempColor == '-')
        info.activeColor = '\0';
    else
        info.activeColor = tempColor;

    
    for (int i = 0; i < info.numPlayers; i++)
    {
        int handSize;
        in >> handSize;

        for (int j = 0; j < handSize; j++)
        {
            char color, value[10];
            in >> color >> value;
        }
    }

    int drawDeckId;
    in >> drawDeckId;

    for (int i = drawDeckId; i < MAX_DECK_SIZE; i++)
    {
        char color, value[10];
        in >> color >> value;
    }

    int topDiscardId;
    in >> topDiscardId;

    for (int i = 0; i < topDiscardId; i++)
    {
        char color, value[10];
        in >> color >> value;
    }

    in >> info.topCard.color;
    in >> info.topCard.value;

    if (info.topCard.value[0] == '-' && info.topCard.value[1] == '\0')
        info.topCard.value[0] = '\0';

    BuildCardText(info.topCard);

    in.close();
    return info;
}



void GameBegining(int& userAnswer, savestate& unoSavestate, std::mt19937& gen)
{
    std::cout << "Welcome to Uno tm console edition :D" << std::endl
        << "Do you want to start a new game or continue the game from last time?" << std::endl
        << "(if no previous game exists new game will start)" << std::endl;
    char tempAnsw[MAX_CHAR_ARRAY_SIZE];
    bool validUserAnswer = false;
    do {
        std::cout << "[0] start new game    [1] continue last game" << std::endl;
        std::cin >> tempAnsw;
        if (tempAnsw[0] == '0' && tempAnsw[1] == '\0')
        {
            userAnswer = 0;
            validUserAnswer = true;
        }
        else if (tempAnsw[0] == '1' && tempAnsw[1] == '\0')
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
        StartNewGame(unoSavestate, gen);
    }
    else if (userAnswer == 1)
    {
        if (!LoadGameFromFile(unoSavestate))
        {
            std::cout << "Starting new game instead...\n\n";
            StartNewGame(unoSavestate, gen);
        }
        else {
            std::cout << "Loading successful\n";
        }
    }
}


void StartNewGame(savestate& uss, std::mt19937& gen)
{
    std::cout << "starting new game : D" << std::endl;
    uss.numberOfPlayers = ReadValidInteger(
        "How many players are gonna play the game? (from 2 to 4): ",
        2,
        4
    );
    FillUnoDeck(uss.drawDeck);
    ShuffleDeck(uss.drawDeck, MAX_DECK_SIZE, gen);
    FillPlayersHands(uss.players, uss.numberOfPlayers, uss.drawDeck, uss.currentDrawDeckId);
    if (uss.drawDeck[uss.currentDrawDeckId].color == WILD_COLOR)
    {
        std::cout << "The starting card is Wild!" << std::endl;
        uss.activeWildColor = ChooseColorForWild(uss);
    }
    else
    {
        // Ако не е Wild, изчисти активния цвят
        uss.activeWildColor = '\0';
    }
    uss.discardDeck[uss.topDiscardDeckId] = uss.drawDeck[uss.currentDrawDeckId++];
}


bool LoadGameFromFile(savestate& uss)
{
    char newGameText[MAX_CHAR_ARRAY_SIZE] = "start new game instead";
    int gameFileId = -1;
    
    do
    {
        gameFileId = chooseSaveFile(newGameText, uss.currentSaveFileId);
    } while (gameFileId<0||gameFileId>numberOfSaveFiles);
    uss.currentSaveFileId = gameFileId;
    if (gameFileId == numberOfSaveFiles)
    {
        return false;
    }

    
    std::ifstream in(SAVEFILE_NAMES[gameFileId]);
    if (!in)
    {
        std::cout << "Save file not found.\n";
        return false;
    }

    uss.currentDrawDeckId = 0;
    uss.topDiscardDeckId = 0;

    in >> uss.numberOfPlayers;
    in >> uss.currentPlayerId;
    in >> uss.playerOrder;

    char tempColor;
    in >> tempColor;
    if (tempColor == '-')
        uss.activeWildColor = '\0';
    else
        uss.activeWildColor = tempColor;
    // PLAYERS
    for (int i = 0; i < uss.numberOfPlayers; i++)
    {
        in >> uss.players[i].handSize;
        for (int j = 0; j < uss.players[i].handSize; j++)
        {
            in >> uss.players[i].hand[j].color;
            in >> uss.players[i].hand[j].value;

            // Ако е "-" -> '\0'
            if (uss.players[i].hand[j].value[0] == '-' && uss.players[i].hand[j].value[1] == '\0')
                uss.players[i].hand[j].value[0] = '\0';

            BuildCardText(uss.players[i].hand[j]);
        }
    }

    // DRAW DECK
    in >> uss.currentDrawDeckId;
    for (int i = uss.currentDrawDeckId; i < MAX_DECK_SIZE; i++)
    {
        in >> uss.drawDeck[i].color;
        in >> uss.drawDeck[i].value;

        if (uss.drawDeck[i].value[0] == '-' && uss.drawDeck[i].value[1] == '\0')
            uss.drawDeck[i].value[0] = '\0';

        BuildCardText(uss.drawDeck[i]);
    }

    // DISCARD DECK
    in >> uss.topDiscardDeckId;
    for (int i = 0; i <= uss.topDiscardDeckId; i++)
    {
        in >> uss.discardDeck[i].color;
        in >> uss.discardDeck[i].value;

        if (uss.discardDeck[i].value[0] == '-' && uss.discardDeck[i].value[1] == '\0')
            uss.discardDeck[i].value[0] = '\0';

        BuildCardText(uss.discardDeck[i]);
    }

    in.close();
    std::cout << "Game loaded successfully.\n";
    return true;
}


int GameFlow(savestate& uss, int& userAnswer, bool& retFlag, std::mt19937& gen)
{
    retFlag = false;  
    struct card currentCard = uss.discardDeck[uss.topDiscardDeckId];
    ChooseActionToPlay(uss, userAnswer, currentCard);
    if (userAnswer == uss.players[uss.currentPlayerId].handSize)
    {
        DrawCard(uss,uss.currentPlayerId, gen);
        card drawnCard = uss.players[uss.currentPlayerId].hand[uss.players[uss.currentPlayerId].handSize - 1];
        bool canPlayDrawnCard = CheckIfPlayerCanPlayCard(uss.activeWildColor, uss.discardDeck[uss.topDiscardDeckId], drawnCard);
        if (canPlayDrawnCard)
        {
            PlayDrawnCard(drawnCard, userAnswer, gen, uss);
        }
        else
        {
            std::cout << "can't play ";
            ColorInCard(drawnCard);
            std::cout << " on top card ";
            card topDiscardCard = uss.discardDeck[uss.topDiscardDeckId];
            ColorInCard(topDiscardCard, uss.activeWildColor);
            std::cout << std::endl;
        }
        std::cout << "Press Enter to continue...";
        std::cin.ignore();
        std::cin.get();
        MoveToNextPlayer(uss);
    }
    else if (userAnswer == uss.players[uss.currentPlayerId].handSize + 1)
    {
        ChooseSaveFIleForSaveGame(uss);
        retFlag = true;
        return 0;
    }
    else
    {
        int currPlayerIdBeforePlay = uss.currentPlayerId;
        PlayCard(userAnswer, uss.players[uss.currentPlayerId], gen, uss);
        SayUnoAction(currPlayerIdBeforePlay, gen, uss);
    }
    return 0;
}



void ChooseActionToPlay(savestate& uss, int& userAnswer, const card& currentCard)
{
    bool isValidOption = false;
    ClearConsole();
    do {
        do
        {
            std::cout << "Current player: " << uss.currentPlayerId << std::endl;
            std::cout << "Current card: ";
            card topDiscardCard = uss.discardDeck[uss.topDiscardDeckId];
            ColorInCard(topDiscardCard, uss.activeWildColor);
            std::cout << std::endl << "Your hand: " << std::endl;
            DisplayCurrentPlayerHand(uss.players[uss.currentPlayerId]);
            std::cout << "[" << uss.players[uss.currentPlayerId].handSize << "] Draw card" << std::endl;
            std::cout << "[" << uss.players[uss.currentPlayerId].handSize + 1 << "] Save game and exit" << std::endl;
            std::cout << "What do you want to do?" << std::endl;
            if (!ReadIntFromConsole(userAnswer))
            {
                ClearConsole();
                userAnswer = -1;
                std::cout << "Invalid input! Please enter a number." << std::endl;
                std::cin.clear();
                continue;
            }
            if (userAnswer < 0 || userAnswer > uss.players[uss.currentPlayerId].handSize + 1)
            {
                ClearConsole();
                std::cout << "Invalid choice! Please choose between 0 and "
                    << uss.players[uss.currentPlayerId].handSize + 1 << std::endl;
                continue;
            }
            break;
        } while (true);
        PlayAction(userAnswer, uss, isValidOption, currentCard);
    } while (!isValidOption);
}

void PlayAction(int& userAnswer, savestate& uss, bool& isValidOption, const card& currentCard)
{
    if (userAnswer == uss.players[uss.currentPlayerId].handSize)
    {
        isValidOption = true;
    }
    else if (userAnswer == uss.players[uss.currentPlayerId].handSize + 1)
    {
        SaveGameConsoleText(userAnswer, uss.players[uss.currentPlayerId], isValidOption);
    }
    else {
        struct card playerCard = uss.players[uss.currentPlayerId].hand[userAnswer];
        isValidOption = CheckIfPlayerCanPlayCard(uss.activeWildColor, currentCard, playerCard);
    }
    if (!isValidOption && userAnswer < uss.players[uss.currentPlayerId].handSize)
    {
        ClearConsole();
        std::cout << "Invalid choice - you cannot play this card!\n\n";
    }
}

bool ReadIntFromConsole(int& outValue) {
    char buffer[MAX_CHAR_ARRAY_SIZE];
    std::cin >> buffer;

    // Check if all characters are digits
    int i = 0;
    if (buffer[0] == '\0') return false;
    while (buffer[i] != '\0') {
        if (buffer[i] < '0' || buffer[i] > '9') return false;
        i++;
    }

    // Convert to int
    outValue = 0;
    i = 0;
    while (buffer[i] != '\0') {
        outValue = outValue * 10 + (buffer[i] - '0');
        i++;
    }
    return true;
}


void DisplayCurrentPlayerHand(player& currentPlayer)
{
    for (int i = 0; i < currentPlayer.handSize; i++)
    {
        std::cout << "[" << i << "] ";
        ColorInCard(currentPlayer.hand[i]);
        std::cout << " ";
    }
}

bool CheckIfPlayerCanPlayCard(char activeWildColor, struct card currentCard, struct card playerCard) {
    if (playerCard.color == activeWildColor)
    {
        return true;
    }
    if (playerCard.color == WILD_COLOR)
    {
        return true;
    }
    char effectiveColor = currentCard.color;
    if (currentCard.color == WILD_COLOR && activeWildColor != '\0') {
        effectiveColor = activeWildColor;
    }
    if (effectiveColor == playerCard.color)
    {
        return true;
    }
    if (CharEquals(currentCard.value, playerCard.value, 8))
    {
        return true;
    }
    return false;
}


void ReshuffleDiscardPile(savestate& uss, std::mt19937& gen)
{
    if (uss.topDiscardDeckId == 0)
    {
        std::cout << "\n>>> Cannot reshuffle - only top card in discard pile. <<<\n";
        std::cout << ">>> Continuing without reshuffling... <<<\n\n";
        return;  
    }
    std::cout << "\n>>> Reshuffling discard pile into draw deck! <<<\n\n";  
    struct card topCard = uss.discardDeck[uss.topDiscardDeckId];
    int cardsToShuffle = uss.topDiscardDeckId;
    for (int i = 0; i < cardsToShuffle; i++)
    {
        uss.drawDeck[uss.currentDrawDeckId + i] = uss.discardDeck[i];
    }
    ShuffleDeck(uss.drawDeck + uss.currentDrawDeckId, cardsToShuffle, gen);
    uss.discardDeck[0] = topCard;
    uss.topDiscardDeckId = 0;
    std::cout << "Reshuffled " << cardsToShuffle << " cards back into draw deck!\n\n";
}

void PlayCard(int cardIndex, player& currentPlayer, std::mt19937& gen, savestate& uss)
{
    // 1. ВЗЕМИ КАРТАТА
    struct card playedCard = currentPlayer.hand[cardIndex];
    // 2. ДОБАВИ В DISCARD PILE
    uss.topDiscardDeckId++;
    uss.discardDeck[uss.topDiscardDeckId] = playedCard;

    // 3. ПРЕМАХНИ ОТ РЪКАТА
    for (int i = cardIndex; i < currentPlayer.handSize - 1; i++)
    {
        currentPlayer.hand[i] = currentPlayer.hand[i + 1];
    }
    currentPlayer.handSize--;

    // 4. АКО Е WILD, ИЗБЕРИ ЦВЯТ
    if (playedCard.color == WILD_COLOR)
    {
        std::cout << "You played a Wild card!\n";
        uss.activeWildColor = ChooseColorForWild(uss);
    }
    else
    {
        uss.activeWildColor = '\0';
    }

    // 5. ПРОВЕРИ ЗА ПОБЕДИТЕЛ
    CheckIfPlayerIsWinner(currentPlayer, uss.currentPlayerId);
    

    // 6. ОБРАБОТИ СПЕЦИАЛНИ КАРТИ
    if (CharEquals(playedCard.value, "Skip", SKIP_STRING_SIZE))
    {
        SkipCardAction(uss);
        return;
    }
    else if (CharEquals(playedCard.value, "Reverse", REVERSE_STRING_SIZE))
    {
        ReverseCardAction(uss);

        return;

    }
    else if (CharEquals(playedCard.value, "+2", PLUS_2_STRING_SIZE))
    {
        Draw2CardAction(gen, uss);
        return;
    }
    else if (CharEquals(playedCard.value, "+4", PLUS_4_STRING_SIZE))
    {
        Draw4CardAction(gen, uss);
        return;
    }
    // 7. ОБИКНОВЕНА КАРТА - ПРЕМИНИ КЪМ СЛЕДВАЩ ИГРАЧ
    MoveToNextPlayer(uss);
}

void Draw4CardAction(std::mt19937& gen, savestate& uss)
{
    std::cout << "\n>>> WILD +4! <<<\n";
    MoveToNextPlayer(uss);
    int nextPlayerId = uss.currentPlayerId;// = (uss.currentPlayerId + uss.playerOrder + uss.numberOfPlayers) % uss.numberOfPlayers;
    std::cout << "Player " << nextPlayerId << " must draw 4 cards!\n";

    int cardsDrawn = DrawMultipleCards(nextPlayerId, 4, gen, uss);

    std::cout << "Player " << nextPlayerId << " drew " << cardsDrawn << " card(s) and skips their turn!\n\n";

    // Прескочи следващия играч
    MoveToNextPlayer(uss);
    MoveToNextPlayer(uss);
}

void Draw2CardAction(std::mt19937& gen, savestate& uss)
{
    std::cout << "\n>>> DRAW +2! <<<\n";
    MoveToNextPlayer(uss);
    int nextPlayerId = uss.currentPlayerId;
    std::cout << "Player " << nextPlayerId << " must draw 2 cards!\n";

    int cardsDrawn = DrawMultipleCards(nextPlayerId, 2, gen, uss);

    std::cout << "Player " << nextPlayerId << " drew " << cardsDrawn << " card(s) and skips their turn!\n\n";

    // Прескочи следващия играч
    MoveToNextPlayer(uss);
    MoveToNextPlayer(uss);
}

void ReverseCardAction(savestate& uss)
{
    std::cout << "\n>>> REVERSE! Direction changed! <<<\n\n";
    uss.playerOrder *= -1;  
    if (uss.numberOfPlayers == 2)
    {
        std::cout << ">>> (In 2-player game, Reverse acts as Skip) <<<\n\n";
        MoveToNextPlayer(uss);
        MoveToNextPlayer(uss);
    }
    else
    {
        MoveToNextPlayer(uss);
    }
}

void SkipCardAction(savestate& uss)
{
    std::cout << "\n>>> SKIP! Player " << ((uss.currentPlayerId + uss.playerOrder + uss.numberOfPlayers) % uss.numberOfPlayers) << " is skipped! <<<\n\n";
    MoveToNextPlayer(uss);
    MoveToNextPlayer(uss);
}

void CheckIfPlayerIsWinner(player& currentPlayer, int currentPlayerId)
{
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
}

void PlayDrawnCard(const card& drawnCard, int& userAnswer, std::mt19937& gen, savestate& uss)
{
    std::cout << "can play ";
    ColorInCard(drawnCard);
    std::cout << " on top card ";
    card topDiscardCard = uss.discardDeck[uss.topDiscardDeckId];
    ColorInCard(topDiscardCard, uss.activeWildColor);
    
    std::cout << std::endl;
    std::cout << "Do you want to play ";
    ColorInCard(drawnCard);
    std::cout << "?" << std::endl;
    std::cout << "[1] play card   [2/anyting else] don't play card" << std::endl;
    if (!ReadIntFromConsole(userAnswer))
    {
        std::cout << "Invalid input - keeping the card.\n";
        userAnswer = 2;
    }
    if (userAnswer == 1)
    {
        PlayCard(uss.players[uss.currentPlayerId].handSize - 1, uss.players[uss.currentPlayerId], gen,uss);
    }
    else
    {
        std::cout << "Keeping the card." << std::endl;
    }
}

void SayUnoAction(int currPlayerIdBeforePlay, std::mt19937& gen, savestate& uss)
{
    char unoInput[MAX_CHAR_ARRAY_SIZE];
    std::cout << "enter Uno, or something else to continue(entering Uno means you are saying it)" << std::endl;
    std::cin.ignore();
    std::cin.getline(unoInput, MAX_CHAR_ARRAY_SIZE);
    if (EqualsIgnoreCase(unoInput, UNO_STR))
    {
        std::cout << "You Said Uno!" << std::endl;
    }

    if (uss.players[currPlayerIdBeforePlay].handSize == 1)
    {
        if (EqualsIgnoreCase(unoInput, UNO_STR))
        {
            std::cout << "You Said Uno Correctly!\nNo need to draw cards as penalty\n";
        }
        else
        {
            std::cout << "You Forgot to say Uno! Draw 1 card as penalty.\n";
            DrawCard(uss, currPlayerIdBeforePlay, gen); // твоя функция за теглене
            std::cout << "Press Enter to continue...";
            std::cin.get();
        }
    }
    else
    {
        if (EqualsIgnoreCase(unoInput, UNO_STR))
        {
            std::cout << "You Said Uno incorrectly!\nDraw 1 card as penalty.\n";
            std::cout << "current player: " << uss.currentPlayerId << "\ncurrPlayerIdBeforePlay: " << currPlayerIdBeforePlay << "\n";
            DrawCard(uss, currPlayerIdBeforePlay, gen);
        }
    }
    std::cout << unoInput << std::endl;
    if (EqualsIgnoreCase(unoInput, UNO_STR)) {

        std::cout << "Press Enter to continue...";
        std::cin.get();
    }
}

void MoveToNextPlayer(savestate& uss)
{
    uss.currentPlayerId = (uss.currentPlayerId + uss.playerOrder + uss.numberOfPlayers) % uss.numberOfPlayers;
}

void DrawCard(savestate& uss, int prevUserId, std::mt19937& gen)
{
    int currentPlayerId = prevUserId;
    std::cout << "Drawing a card...\n";
    if (uss.currentDrawDeckId >= MAX_DECK_SIZE - 1)
    {
        
        ReshuffleDiscardPile(uss, gen);
    }
    uss.players[currentPlayerId].hand[uss.players[currentPlayerId].handSize] = uss.drawDeck[uss.currentDrawDeckId++];
    uss.players[currentPlayerId].handSize++;
    std::cout << "You drew: ";
    ColorInCard(uss.players[currentPlayerId].hand[uss.players[currentPlayerId].handSize - 1]);
    std::cout << "\n\n";
    
}


void SaveGameConsoleText(int& userAnswer, player& currentPlayer, bool& isValidOption)
{
    userAnswer= ReadValidInteger("Are you sure?\n[0] Save game and exit [1] Continue current game: ", 0-1, 1);
    if (userAnswer == 0)
    {
        userAnswer = currentPlayer.handSize + 1;
        isValidOption = true;

    }
}

char ChooseColorForWild(savestate& uss)
{
    int colorChoice = -1;
    bool validInput = false;
    ClearConsole();
    do {
        std::cout << "player " << uss.currentPlayerId << " please choose color for wild card"<<std::endl;
        DisplayCurrentPlayerHand(uss.players[uss.currentPlayerId]);
        std::cout << std::endl;
        std::cout << "Player " << uss.currentPlayerId << ", choose a color for the Wild card:" << std::endl;
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
        if (!ReadIntFromConsole(colorChoice))
        {
            ClearConsole();
            std::cout << "Invalid input, please enter a number.\n\n";
            continue;
        }
        if (colorChoice < 0 || colorChoice > COLORS_SIZE)
        {
            ClearConsole();
            std::cout << "Invalid choice, please choose again.\n\n";
            continue;
        }
        validInput = true;
    } while (!validInput);
    return COLORS[colorChoice];  
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



void MyStrCopy(const char src[MAX_CHAR_ARRAY_SIZE], char dest[MAX_CHAR_ARRAY_SIZE]) {
    int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}
void SaveGameInFile(savestate& uss, char filename[MAX_CHAR_ARRAY_SIZE])
{
    std::ofstream out(filename, std::ios::trunc);
    if (!out)
    {
        std::cout << "Cannot open save file.\n";
        return;
    }
    out << uss.numberOfPlayers << '\n';
    out << uss.currentPlayerId << '\n';
    out << uss.playerOrder << '\n';
    if (uss.activeWildColor == '\0')
        out << "-\n";
    else
        out << uss.activeWildColor << '\n';
    // PLAYERS
    for (int i = 0; i < uss.numberOfPlayers; i++)
    {
        out << uss.players[i].handSize << '\n';
        for (int j = 0; j < uss.players[i].handSize; j++)
        {
            out << uss.players[i].hand[j].color << '\n';

            // За Wild карти без value "-"
            if (uss.players[i].hand[j].value[0] == '\0')
                out << "-\n";
            else
                out << uss.players[i].hand[j].value << '\n';
        }
    }
    // DRAW DECK
    out << uss.currentDrawDeckId << '\n';
    for (int i = uss.currentDrawDeckId; i < MAX_DECK_SIZE; i++)
    {
        out << uss.drawDeck[i].color << '\n';

        if (uss.drawDeck[i].value[0] == '\0')
            out << "-\n";
        else
            out << uss.drawDeck[i].value << '\n';
    }
    // DISCARD DECK
    out << uss.topDiscardDeckId << '\n';
    for (int i = 0; i <= uss.topDiscardDeckId; i++)
    {
        out << uss.discardDeck[i].color << '\n';

        if (uss.discardDeck[i].value[0] == '\0')
            out << "-\n";
        else
            out << uss.discardDeck[i].value << '\n';
    }
    out.close();
    std::cout << "Game saved successfully.\n";
}


void ChooseSaveFIleForSaveGame(savestate uss)
{
    std::cout << "Choose a save file: "<<std::endl;
    char textForCancel[MAX_CHAR_ARRAY_SIZE] = "exit game without saving";

    int choice = chooseSaveFile(textForCancel, uss.currentSaveFileId);
    if (choice==numberOfSaveFiles)
    {
        return;
    }
    
    char filename[MAX_CHAR_ARRAY_SIZE] ;
    MyStrCopy(SAVEFILE_NAMES[choice], filename);
    SaveGameInFile(uss, filename);
}

int chooseSaveFile(char textForCancel[MAX_CHAR_ARRAY_SIZE], int currentSaveFileId= -1) {
    
    int choice = -1;
    bool isValid = false;
    do
    {
        for (int i = 0; i < numberOfSaveFiles; i++)
        {
            SaveFileInfo info = GetSaveFileInfo(SAVEFILE_NAMES[i]);bool isCurrentSaveFile = false;
            if (currentSaveFileId == i)
            {
                isCurrentSaveFile = true;
            }

            DisplaySaveSlot(i, info, isCurrentSaveFile);

        }
        std::cout << "[" << numberOfSaveFiles << "] " << textForCancel << std::endl;
        isValid = ReadValidIntegerWhileCycle(0, numberOfSaveFiles , choice);
    } while (!isValid);
    return choice;
}

void ColorInCard(struct card currentCard, char activeWildColor) {
    char color = currentCard.color;

    for (int i = 0; i < COLORS_SIZE; i++)
    {
        if (color == COLORS[i])
        {
            PrintTextInColor(currentCard.text, COLOR_CODES[i]);
            return;
        }
    }
    if (color == WILD_COLOR && activeWildColor == '\0')
    {
        PrintTextInColor(currentCard.text, MAGENTA_COLOR_CODE);
    }
    else {
        for (int i = 0; i < COLORS_SIZE; i++)
        {
            if (activeWildColor == COLORS[i])
            {
                PrintTextInColor(currentCard.text, COLOR_CODES[i]);
                return;
            }
        }
    }
}

void FillPlayersHands(player players[MAX_PLAYERS], int numberOfPlayers, card drawDeck[MAX_DECK_SIZE], int currentDrawDeckId)
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


void FillUnoDeck(struct card drawDeck[MAX_DECK_SIZE]) {
    int cardIndex = 0;
    struct card currentCard;
    char cardValue[10] = {};
    for (int colorIndex = 0; colorIndex < COLORS_SIZE; colorIndex++)
    {
        for (int numberValue = ZERO_NUMBER_CARD; numberValue <= LAST_NUMBER_CARD; numberValue++)
        {
            currentCard.color = COLORS[colorIndex];
            currentCard.value[0] = (numberValue + '0');
            currentCard.value[1] = '\0';

            currentCard.text[0] = COLORS[colorIndex];
            currentCard.text[1] = ' ';
            currentCard.text[2] = (numberValue + '0');
            currentCard.text[3] = '\0';
            drawDeck[cardIndex++] = currentCard;

            if (numberValue != ZERO_NUMBER_CARD)
            {
                drawDeck[cardIndex++] = currentCard;

            }
        }

        currentCard.color = COLORS[colorIndex];
        currentCard.value[0] = '+';
        currentCard.value[1] = '2';
        currentCard.value[2] = '\0';
        currentCard.text[0] = COLORS[colorIndex];
        currentCard.text[1] = ' ';
        currentCard.text[2] = '+';
        currentCard.text[3] = '2';
        currentCard.text[4] = '\0';
        drawDeck[cardIndex++] = currentCard;
        drawDeck[cardIndex++] = currentCard;

        currentCard.color = COLORS[colorIndex];
        currentCard.value[0] = 'S';
        currentCard.value[1] = 'k';
        currentCard.value[2] = 'i';
        currentCard.value[3] = 'p';
        currentCard.value[4] = '\0';
        currentCard.text[0] = COLORS[colorIndex];
        currentCard.text[1] = ' ';
        currentCard.text[2] = 'S';
        currentCard.text[3] = 'k';
        currentCard.text[4] = 'i';
        currentCard.text[5] = 'p';
        currentCard.text[6] = '\0';

        drawDeck[cardIndex++] = currentCard;
        drawDeck[cardIndex++] = currentCard;

        currentCard.color = COLORS[colorIndex];
        currentCard.value[0] = 'R';
        currentCard.value[1] = 'e';
        currentCard.value[2] = 'v';
        currentCard.value[3] = 'e';
        currentCard.value[4] = 'r';
        currentCard.value[5] = 's';
        currentCard.value[6] = 'e';
        currentCard.value[7] = '\0';
        currentCard.text[0] = COLORS[colorIndex];
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

    currentCard.color = WILD_COLOR;
    currentCard.value[0] = '\0';
    currentCard.text[0] = WILD_COLOR;
    currentCard.text[1] = '\0';
    drawDeck[cardIndex++] = currentCard;
    drawDeck[cardIndex++] = currentCard;
    drawDeck[cardIndex++] = currentCard;
    drawDeck[cardIndex++] = currentCard;

    currentCard.color = WILD_COLOR;
    currentCard.value[0] = '+';
    currentCard.value[1] = '4';
    currentCard.value[2] = '\0';
    currentCard.text[0] = WILD_COLOR;
    currentCard.text[1] = ' ';
    currentCard.text[2] = '+';
    currentCard.text[3] = '4';
    currentCard.text[4] = '\0';
    drawDeck[cardIndex++] = currentCard;
    drawDeck[cardIndex++] = currentCard;
    drawDeck[cardIndex++] = currentCard;
    drawDeck[cardIndex++] = currentCard;

}

void ShuffleDeck(struct card drawDeck[MAX_DECK_SIZE], int arrSize,std::mt19937& gen) {
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

bool CharEquals(const char a[], const char b[], int size) {
    for (int i = 0; i < size; i++) {
        if (a[i] != b[i]) {
            return false; 
        }
        if (a[i] == '\0' && b[i] == '\0') {
            return true; 
        }
    }
    return true;
}

char ToLower(char c)
{
    if (c >= 'A' && c <= 'Z')
        return c + ('a' - 'A');
    return c;
}

bool EqualsIgnoreCase(const char* a, const char* b)
{
    while (*a && *b)
    {
        if (ToLower(*a) != ToLower(*b))
            return false;
        ++a;
        ++b;
    }
    return *a == *b;
}


bool ReadValidIntegerWhileCycle(int minValue, int maxValue, int &value){

    if (!ReadIntFromConsole(value))
    {
        std::cout << "Invalid input! Please enter a number between "
            << minValue << " and " << maxValue << ".\n";
        return false;
    }

    if (value < minValue || value > maxValue)
    {
        std::cout << "Invalid choice! Please enter a number between "
            << minValue << " and " << maxValue << ".\n";
        return false;
    }

    return true;
}

int ReadValidInteger(const char* prompt, int minValue, int maxValue)
{
    int value;
    bool validInput = false;

    do {
        std::cout << prompt;

        validInput = ReadValidIntegerWhileCycle(minValue, maxValue, value);

    } while (!validInput);

    return value;
}


int DrawMultipleCards(int playerId, int numCards, std::mt19937& gen, savestate& uss)
{
    int cardsDrawn = 0;

    for (int i = 0; i < numCards; i++)
    {
        if (uss.currentDrawDeckId >= MAX_DECK_SIZE)
        {
            ReshuffleDiscardPile(uss, gen);
        }

        if (uss.currentDrawDeckId < MAX_DECK_SIZE)
        {
            uss.players[playerId].hand[uss.players[playerId].handSize++] = uss.drawDeck[uss.currentDrawDeckId++];
            cardsDrawn++;
        }
        else
        {
            break;
        }
    }

    return cardsDrawn;
}