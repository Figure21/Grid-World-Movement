
#include <iostream>
#include <vector>
#include <thread>
#include "Robot.h"
#include <fstream>

void setDimensions(int &height, int &width) {
    std::ifstream configFile("config.txt");

    if (configFile.is_open()) {
        configFile >> height >> width;
    }
    else {
        height = 5;
        width = 15;
    }
    
}

void draw_grid_v2(std::vector<std::vector<char>>& grid) {

    std::string frame = "\x1B[H";
    int height = grid.size();
    int width = grid[0].size();


    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                grid[i][j] = '#';
            }
            frame += grid[i][j]; 
        }
        frame += '\n';
    }
    std::cout << frame << std::flush;
}

char symbols[4] = { '^', 'v', '>', '<' };

Robot robot_character;

int main()
{
    int height = 5;
    int width = 15;

    setDimensions(height, width);
    std::vector<std::vector<char>> grid(height, std::vector<char>(width, ' '));
    int userMovement;
     
    char moveChar;

    grid[robot_character.currentX][robot_character.currentY] = robot_character.robot_symbol;

    while (true) {
        
        robot_character.robot_symbol = symbols[robot_character.robot_heading];
        grid[robot_character.currentX][robot_character.currentY] = robot_character.robot_symbol;
        
        draw_grid_v2(grid);
        int distance_to_obstacle = check_distance(robot_character, grid);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        std::cout << "A: Left | D: Right | W: Up | S: Down \n";       
        std::cout << "Tiles until you hit obstacle: " << distance_to_obstacle << "         \n";
        std::cout << "Where do you want to move?: \x1B[J";
        std::cin >> moveChar;

        grid[robot_character.currentX][robot_character.currentY] = ' ';
        
        switch (moveChar) {
        case 'a': // Left
            if (robot_character.currentY > 0 && grid[robot_character.currentX][robot_character.currentY - 1] != '#')
            {
                robot_character.currentY--;
                robot_character.robot_heading = LEFT;
            } 
            break;

        case 'd': // Right
            if (grid[robot_character.currentX][robot_character.currentY + 1] != '#')
            {
                robot_character.currentY++;  
                robot_character.robot_heading = RIGHT;
            }
            break;

        case 'w': //  Up
            if (robot_character.currentX > 0 && grid[robot_character.currentX - 1][robot_character.currentY] != '#')
            {
                robot_character.currentX--;
                robot_character.robot_heading = UP;
            }
            break;

        case 's': // Down
            if (grid[robot_character.currentX + 1][robot_character.currentY] != '#')
            {
                robot_character.currentX++;
                robot_character.robot_heading = DOWN;
            }
            break;
            
        }
    }
}
