
#include <iostream>

std::string world_matrix[5][5] = {
    {"#", "#", "#", "#", "#"},
    {"#", " ", " ", " ", "#"},
    {"#", " ", " ", " ", "#"},
    {"#", " ", " ", " ", "#"},
    {"#", "#", "#", "#", "#"}
};

enum Heading {
    UP,
    DOWN,
    RIGHT,
    LEFT
};

std::string symbols[4] = { "^", "v", ">", "<" };

struct Robot {
    int currentX = 2;
    int currentY = 1;
    std::string robot_symbol = ">";
    
    Heading robot_heading = RIGHT;
};

Robot robot_character;

int check_distance() {
    int distance = 0;

    switch (robot_character.robot_heading) {
    case UP:
        for (int i = 1; (robot_character.currentX - i) >= 0; i++)
        {
            if (world_matrix[robot_character.currentX - i][robot_character.currentY] == "#") {
                distance = i - 1;
                break;
            }
        }
        break;

    case DOWN:
        for (int i = 0; i < 4; i++)
        {
            if (world_matrix[robot_character.currentX + i][robot_character.currentY] == "#") {
                distance = i - 1;
                break;
            }
        }
        break;

    case RIGHT:
        for (int i = 0; i < 4; i++)
        {
            if (world_matrix[robot_character.currentX][robot_character.currentY + i] == "#") {
                distance = i - 1;
                break;
            }
        }
        break;
     
    case LEFT:
        for (int i = 1; (robot_character.currentY - i) >= 0; i++)
        {
            if (world_matrix[robot_character.currentX][robot_character.currentY - i] == "#") {
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
    
    world_matrix[robot_character.currentX][robot_character.currentY] = robot_character.robot_symbol;

    while (true) {
        int distance_to_obstacle = check_distance();
        system("cls");

        robot_character.robot_symbol = symbols[robot_character.robot_heading];
        world_matrix[robot_character.currentX][robot_character.currentY] = robot_character.robot_symbol;
        
        draw_grid(world_matrix);
        
        std::cout << "1: Left | 2: Right | 3: Up | 4: Down \n";       
        std::cout << "Tiles until you hit obstacle: " << distance_to_obstacle << "\n";
        std::cout << "Where do you want to move?: ";
        std::cin >> userMovement;
        world_matrix[robot_character.currentX][robot_character.currentY] = " ";
        
        switch (userMovement) {
        case 1: // Left
            if (robot_character.currentY > 0 && world_matrix[robot_character.currentX][robot_character.currentY - 1] != "#")
            {
                robot_character.currentY--;
                robot_character.robot_heading = LEFT;
            } 
            break;

        case 2: // Right
            if (world_matrix[robot_character.currentX][robot_character.currentY + 1] != "#")
            {
                robot_character.currentY++;  
                robot_character.robot_heading = RIGHT;
            }
            break;

        case 3: //  Up
            if (robot_character.currentX > 0 && world_matrix[robot_character.currentX - 1][robot_character.currentY] != "#")
            {
                robot_character.currentX--;
                robot_character.robot_heading = UP;
            }
            break;

        case 4: // Down
            if (world_matrix[robot_character.currentX + 1][robot_character.currentY] != "#")
            {
                robot_character.currentX++;
                robot_character.robot_heading = DOWN;
            }
            break;
            
        }
    }
}
