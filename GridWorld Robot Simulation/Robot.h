#pragma once
#include <vector>

enum Heading { UP, DOWN, RIGHT, LEFT };


struct Robot {
    int currentX = 2;
    int currentY = 1;
    char robot_symbol = '>';
    Heading robot_heading{};
};


int check_distance(const Robot& robot, const std::vector<std::vector<char>>& grid);