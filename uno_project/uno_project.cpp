// uno_project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>


const int RED_COLOR_CODE = 91;
const int GREEN_COLOR_CODE = 92;
const int YELLOW_COLOR_CODE = 93;
const int BLUE_COLOR_CODE = 94;
const int MAGENTA_COLOR_CODE = 95;
void SetConsoleColor(int);
void ResetConsoleColor();
void ClearConsole();

void PrintTextInColor(const std::string, int);


int main()
{  
    
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