#include <string>
#include "Robot.h"

int check_distance(const Robot& robot, const std::vector<std::vector<char>>& grid) {
    int height = grid.size();
    int width = grid[0].size();
    int distance = 0;

    switch (robot.robot_heading) {
    case UP:
        for (int i = 1; (robot.currentX - i) >= 0; i++)
        {
            if (grid[robot.currentX - i][robot.currentY] == '#') {
                distance = i - 1;
                break;
            }
        }
        break;

    case DOWN:
        for (int i = 1; (robot.currentX + i) < height; i++)
        {
            if (grid[robot.currentX + i][robot.currentY] == '#') {
                distance = i - 1;
                break;
            }
        }
        break;

    case RIGHT:
        for (int i = 1; (robot.currentY + i) < width; i++)
        {
            if (grid[robot.currentX][robot.currentY + i] == '#') {
                distance = i - 1;
                break;
            }
        }
        break;

    case LEFT:
        for (int i = 1; (robot.currentY - i) >= 0; i++)
        {
            if (grid[robot.currentX][robot.currentY - i] == '#') {
                distance = i - 1;
                break;
            }
        }
        break;
    }

    return distance;
}

