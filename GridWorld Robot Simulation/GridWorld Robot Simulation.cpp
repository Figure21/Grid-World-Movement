
#include <iostream>
#include <vector>
#include <thread>

int height = 5;
int width = 15;

std::vector<std::vector<char>> grid(height, std::vector<char>(width, ' '));

void draw_grid_v2() {

    std::string frame = "\x1B[H";

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

enum Heading {
    UP,
    DOWN,
    RIGHT,
    LEFT
};

char symbols[4] = { '^', 'v', '>', '<' };

struct Robot {
    int currentX = 2;
    int currentY = 1;
    char robot_symbol = '>';
    
    Heading robot_heading = RIGHT;
};

Robot robot_character;

int check_distance() {
    int distance = 0;

    switch (robot_character.robot_heading) {
    case UP:
        
        for (int i = 1; (robot_character.currentX - i) >= 0; i++)
        {
            if (grid[robot_character.currentX - i][robot_character.currentY] == '#') {
                distance = i - 1;
                break;
            }
        }
        break;

    case DOWN:
        for (int i = 1; (robot_character.currentX + i) < height; i++)
        {
            if (grid[robot_character.currentX + i][robot_character.currentY] == '#') {
                distance = i - 1;
                break;
            }
        }
        break;

    case RIGHT:
        for (int i = 1; (robot_character.currentY + i) < width; i++)
        {
            if (grid[robot_character.currentX][robot_character.currentY + i] == '#') {
                distance = i - 1;
                break;
            }
        }
        break;
     
    case LEFT:
        for (int i = 1; (robot_character.currentY - i) >= 0; i++)
        {
            if (grid[robot_character.currentX][robot_character.currentY - i] == '#') {
                distance = i - 1;
                break; 
            }
        }
        break;  
    }
    
    return distance;
}

void draw_grid(std::string matrix[5][5]) {
    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < 5; j++)
        {
            std::cout << matrix[i][j] << "";
        }
        std::cout << std::endl;
    }
}

int main()
{
    int userMovement;
     
    char moveChar;


    grid[robot_character.currentX][robot_character.currentY] = robot_character.robot_symbol;

    while (true) {
        
        robot_character.robot_symbol = symbols[robot_character.robot_heading];
        grid[robot_character.currentX][robot_character.currentY] = robot_character.robot_symbol;
        
        draw_grid_v2();
        int distance_to_obstacle = check_distance();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        std::cout << "1: Left | 2: Right | 3: Up | 4: Down \n";       
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
