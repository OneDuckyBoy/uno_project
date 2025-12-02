// uno_project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>


const int RED_COLOR_CODE = 91;
const int GREEN_COLOR_CODE = 92;
const int YELLOW_COLOR_CODE = 93;
const int BLUE_COLOR_CODE = 94;
const int MAGENTA_COLOR_CODE = 95;

const std::vector<std::string> colors = { "R", "G", "Y", "B", };
const std::vector<int> colorCodes = { RED_COLOR_CODE, GREEN_COLOR_CODE, YELLOW_COLOR_CODE, BLUE_COLOR_CODE };
const std::string wildColor = "W";
const int wildColorCode = MAGENTA_COLOR_CODE;
const int startingNumberOfCards = 7;



void SetConsoleColor(int);
void ResetConsoleColor();
void ClearConsole();

void PrintTextInColor(const std::string, int);

std::vector<std::string> FillUnoDeck(std::vector<std::string> colors, std::string wildColor);

void ShuffleVector(std::vector<std::string>& drawPile, std::mt19937& gen);

std::string drawCard();

std::string getCardColor(std::string card);

void ColorInCard(std::string cardValue);


void PrintVectorCards(std::vector<std::string>& drawPile, std::string separator);
void AddPlayers(const int numberOfPlayers);

std::vector<std::string> drawPile = FillUnoDeck(colors, wildColor);
std::vector<std::string> discardPile;


std::vector<std::vector<std::string>> players;
void PrintDefaultPlayersMenu(std::string currentCard, int currentPlayerId);

std::string getCardValue(const std::string card);
bool CanPlayCard(std::string card, std::string currentHand);

std::string playWildCard();
void playReverse();
void playSkip();
void playPlus2();

bool gameIsWon = false;
int currentPlayerIndex = 0;
int direction = 1;

int main()
{  
    std::random_device rd;
    std::mt19937 gen(rd());

    ShuffleVector(drawPile, gen);

     

    std::cout << CanPlayCard("R 4", "W");
    std::string newColor= playWildCard();
    std::cout << "New color: ";
    ColorInCard(newColor);

    return 0;
    int numberOfPlayers;

    do {
        std::cout << "How many players are gonna play the game? (form 2 to 4) ";
        std::cin >> numberOfPlayers;
    } while (!(numberOfPlayers > 1 && numberOfPlayers <= 4));
    AddPlayers(numberOfPlayers);
    //PrintVectorCards(drawPile);
    std::string currentCard = drawCard();
    discardPile.push_back(currentCard);
    
    PrintVectorCards(discardPile, " ");
    while (!gameIsWon)
    {
        PrintDefaultPlayersMenu(currentCard, currentPlayerIndex);
        currentCard = discardPile.back();
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();

        std::cout << "End game? [0] No [1] Yes "<<std::endl;
        int endGame;
        std::cin >> endGame;
        if (endGame) {
            break;
        }
    }
    

}


void playPlus2() {
    playSkip();
    players.at(currentPlayerIndex).push_back(drawCard());
    players.at(currentPlayerIndex).push_back(drawCard());
    

}
void playSkip() {
    currentPlayerIndex += 1 * direction;
    currentPlayerIndex %= players.size();
}

void playReverse() {
    direction *= -1;
}

std::string playWildCard() {
    
    int colorChosen;
    do
    {
        std::cout << "What Color Would you want to change the wild to? " << std::endl;
        for (int i = 0; i < colors.size(); i++)
        {
            std::cout << "[" << i << "] ";

            ColorInCard(colors.at(i));
            std::cout << " ";
        }
        std::cout << std::endl;

        std::cin >> colorChosen;
    } while (colorChosen < 0 || colorChosen >= colors.size());
    

    return colors.at(colorChosen);
}


void PrintDefaultPlayersMenu(std::string currentCard, int currentPlayerId) {

    /*
    current card: <currentCard>


    Current player: <currentPlayerId> 

    */

    std::cout << "Current card: " ;
    ColorInCard(currentCard);
    std::cout << std::endl << std::endl;
    std::cout << "Current player: " << currentPlayerId <<std::endl;

    std::cout << "Your current cards: " << std::endl;
    std::vector<std::string> currentHand = players.at(currentPlayerId);
    for (int i = 0; i < currentHand.size(); i++)
    {
        std::cout << "["<<i<<"] ";
        ColorInCard(currentHand.at(i));
        std::cout << " ";
    }
    std::cout << std::endl;
    bool canPlayCard = false;
    for (int i = 0; i < currentHand.size(); i++)
    {
        if (CanPlayCard(currentCard, currentHand.at(i))) {
            canPlayCard = true;
        }
    }
    if (canPlayCard)
    {
        int chosenCardIndex;
        bool invalidCardChosen = false;
        
        do {
        std::cout << "Choose index of card you want to play: ";

        std::cin >> chosenCardIndex;
        if (!(chosenCardIndex >= currentHand.size() || chosenCardIndex < 0))
        {
            invalidCardChosen = !CanPlayCard(currentCard, currentHand.at(chosenCardIndex));
            if (invalidCardChosen)
            {
                std::cout << "Can't play ";
                ColorInCard(currentHand.at(chosenCardIndex));
                std::cout << " on top of ";
                ColorInCard(currentCard);
                std::cout<<". "<<std::endl<<"Chose another." << std::endl;
            }
        }
        } while (chosenCardIndex>=currentHand.size() || chosenCardIndex<0 || invalidCardChosen);
        std::string playedCard = currentHand.at(chosenCardIndex);
        currentHand.erase(currentHand.begin() + chosenCardIndex);
        discardPile.push_back(playedCard);

    }
    else {
        std::cout << "No suitable cards. Automatically drawing card from deck..." << std::endl;
        std::string drawnCard = drawCard();
        players.at(currentPlayerId).push_back(drawnCard);
        std::cout << "Drawn card: " << drawnCard << std::endl;
        
        std::cout << "new hand: " <<std::endl;
        PrintVectorCards(players.at(currentPlayerId), ", ");
    }
        

    //PrintVectorCards(discardPile, "\n");
    //Choose index of card you want to play: <chosenIndex>
        

}
std::string getCardValue(const std::string card) {
    int pos = card.find(' ');

    if (pos == std::string::npos)
        return "";


    if (pos + 1 >= card.size())
        return "";

    // Return everything after the first space
    return card.substr(pos + 1);
}

bool CanPlayCard(std::string card, std::string currentCard) {
    std::string cardColor = getCardColor(card);
    std::string cardValue = getCardValue(card);

    std::string currentCardColor = getCardColor(currentCard);
    std::string currentCardValue = getCardValue(currentCard);
    
    if (!currentCardColor.compare(wildColor))
    {
        return true;
    }
    if (!cardColor.compare(wildColor)) {
        return true;
    }
    if (!cardColor.compare(currentCardColor) || !cardValue.compare(currentCardValue)) {
        return true;
    }

    return false;
}
void AddPlayers(const int numberOfPlayers) {
    for (int currentPlayerIndex = 0; currentPlayerIndex < numberOfPlayers; currentPlayerIndex++)
    {
        std::vector<std::string> currentPlayer;
        for (int i = 0; i < startingNumberOfCards; i++)
        {
            std::string currentCard = drawCard();
            currentPlayer.push_back(currentCard);
        }
        players.push_back(currentPlayer);

    }
}
void PrintVectorCards(std::vector<std::string>& vector, std::string separator)
{
    for (int i = 0; i < vector.size(); i++)
    {
        std::string cardValue = vector.at(i);
        ColorInCard(cardValue);
        std::cout << separator;

    }
}



void ColorInCard(std::string cardValue)
{
    std::string cardColor =  getCardColor(cardValue);

    auto it = std::find(colors.begin(), colors.end(), cardColor);

    if (it != colors.end())
    {
        int index = it - colors.begin();      // get index
        int code = colorCodes[index];        // matching code

        PrintTextInColor(cardValue, code);
    }
    else if (cardColor == "W") // wild cards
    {
        PrintTextInColor(cardValue, MAGENTA_COLOR_CODE);
    }
    /*if (!cardColor.compare("R"))
    {
        PrintTextInColor(cardValue, RED_COLOR_CODE);
    }
    else if (!cardColor.compare("B"))
    {
        PrintTextInColor(cardValue, BLUE_COLOR_CODE);
    }
    else if (!cardColor.compare("Y"))
    {
        PrintTextInColor(cardValue, YELLOW_COLOR_CODE);
    }
    else if (!cardColor.compare("G"))
    {
        PrintTextInColor(cardValue, GREEN_COLOR_CODE);
    }
    else if (!cardColor.compare("W"))
    {
        PrintTextInColor(cardValue, MAGENTA_COLOR_CODE);
    }*/

}



std::string getCardColor(std::string card) {
    /*size_t pos = card.find(' ');

    if (pos != std::string::npos && pos > 0) {
        char color = card[pos - 1];
        return std::string(1, color); // return "R", "G", "B", "Y"
    }

    return "";*/

    const char colors[] = { 'R', 'G', 'B', 'Y', 'W' };

    for (char ch : card) {
        char C = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
        for (char valid : colors) {
            if (C == valid) return std::string(1, C);
        }
    }

    return "";
}



std::string drawCard() {
    std::string card = drawPile.back();
    drawPile.pop_back();
    return card;
}



void ShuffleVector(std::vector<std::string>& drawPile, std::mt19937& gen)
{
    std::shuffle(drawPile.begin(), drawPile.end(), gen);
}



std::vector<std::string> FillUnoDeck(std::vector<std::string> colors, std::string wildColor) {
    std::vector<std::string>drawPile;
    std::string cardValue;
    for (int colorIndex = 0; colorIndex < colors.size(); colorIndex++)
    {
        for (int numberValue = 0; numberValue <= 9; numberValue++)
        {
            cardValue = colors[colorIndex] + " " + std::to_string(numberValue);

            if (numberValue != 0)
            {
                drawPile.push_back(cardValue);
                drawPile.push_back(cardValue);

            }
            else
            {
                drawPile.push_back(cardValue);
            }

            //std::cout << cardValue << "    ";
        }
        cardValue = colors[colorIndex] + " " + "+2";
        drawPile.push_back(cardValue);
        drawPile.push_back(cardValue);

        cardValue = colors[colorIndex] + " " + "Skip";
        drawPile.push_back(cardValue);
        drawPile.push_back(cardValue);

        cardValue = colors[colorIndex] + " " + "Reverse";
        drawPile.push_back(cardValue);
        drawPile.push_back(cardValue);

    }
    cardValue = wildColor;
    drawPile.push_back(cardValue);
    drawPile.push_back(cardValue);
    drawPile.push_back(cardValue);
    drawPile.push_back(cardValue);

    cardValue = wildColor + " " + "+4";
    drawPile.push_back(cardValue);
    drawPile.push_back(cardValue);
    drawPile.push_back(cardValue);
    drawPile.push_back(cardValue);

    return drawPile;
}




void PrintTextInColor(const std::string text, int color) {
    SetConsoleColor(color);
    std::cout << text;
    ResetConsoleColor();

}
void ClearConsole() {
    system("CLS");
}

void SetConsoleColor(int textColor)
{
    std::cout << "\033[" << textColor << "m";
}
void ResetConsoleColor() { std::cout << "\033[0m"; }