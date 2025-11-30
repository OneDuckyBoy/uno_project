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
void SetConsoleColor(int);
void ResetConsoleColor();
void ClearConsole();

void PrintTextInColor(const std::string, int);

std::vector<std::string> FillUnoDeck(std::vector<std::string> colors, std::string wildColor);

void ShuffleVector(std::vector<std::string>& drawPile, std::mt19937& gen);


int main()
{  
    std::random_device rd;
    std::mt19937 gen(rd());
    int startingNumberOfCards = 6;

    std::vector<std::string> colors = { "R", "G", "Y", "B", };
    std::vector<int> colorsCodes = { RED_COLOR_CODE, GREEN_COLOR_CODE, YELLOW_COLOR_CODE, BLUE_COLOR_CODE };
    std::string wildColor = "W";
    int wildColorCode = MAGENTA_COLOR_CODE;

    std::vector<std::string> drawPile = FillUnoDeck(colors, wildColor);
    ShuffleVector(drawPile, gen);

    std::vector<std::string> discardPile;


    
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