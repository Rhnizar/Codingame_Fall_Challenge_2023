/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CalculateStep.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 21:18:54 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/12/23 11:56:29 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cmath>

// struct Position {
//     int x;
//     int y;
// };

// struct Steps {
//     int x;
//     int y;
// };

int steps_x, steps_y;
void calculate_steps(int drone_positionX, int drone_positionY,  std::string target_direction, int map_width, int map_height)
{
    // int target_x = drone_position.x;
    // int target_y = drone_position.y;
	int target_x = drone_positionX;
    int target_y = drone_positionY;

    // Adjust target position based on direction
    if (target_direction == "TL")
	{
        target_x = 0;
        target_y = 0;
    }
	else if (target_direction == "TR")
	{
        target_x = map_width;
        target_y = 0;
    }
	else if (target_direction == "BL")
	{
        target_x = 0;
        target_y = map_height;
    }
	else if (target_direction == "BR")
	{
        target_x = map_width;
        target_y = map_height;
    }
	else
	{
        std::cerr << "Invalid target direction.\n";
        // return {0, 0};
    }

    // Calculate relative position
	int Relative_positionX = target_x - drone_positionX;
	int Relative_positionY = target_y - drone_positionY;
    // Position relative_position = {target_x - drone_position.x, target_y - drone_position.y};

    // Calculate distances
    int x_distance = std::abs(Relative_positionX);
    int y_distance = std::abs(Relative_positionY);

    // Decide which direction to move first
    
    if (x_distance > y_distance)
	{
        steps_x = std::min(x_distance, map_width - x_distance);
        steps_y = std::min(y_distance, map_height - y_distance);
    } 
	else
	{
        steps_y = std::min(y_distance, map_height - y_distance);
        steps_x = std::min(x_distance, map_width - x_distance);
    }
}

int main()
{
    // Position drone_position = {5000, 8000};  // Assuming the drone is at the center of the map
    std::string target_direction = "BR";  // Replace with "TL", "TR", "BL", or "BR"
    int map_width = 10000;
    int map_height = 10000;
	int x = 5000;
	int y = 9000;
    calculate_steps(x, y, target_direction, map_width, map_height);

    std::cout << "Move " << steps_x << " steps in the X direction and " << steps_y << " steps in the Y direction.\n";

    return 0;
}









/*    initial steps    way 1*/


int StepSizeY = 1000;
int StepSizeX = 1000;

void initSteps(int i, vector<My_drone> My_droneV, string rad)
{
    /*initial the StepSizeX */
    if(My_droneV[i].drone_x <= 2500)
    {
        if(rad == "TL" || rad == "BL")
            StepSizeX = 200;
        else
            StepSizeX = 1000;
    }
    else if(My_droneV[i].drone_x > 2500 && My_droneV[i].drone_x < 5000)
    {
        if(rad == "TL" || rad == "BL")
            StepSizeX = 300;
        else
            StepSizeX = 600;
    }
    else if(My_droneV[i].drone_x >= 5000 && My_droneV[i].drone_x < 7500)
    {
        if(rad == "TR" || rad == "BR")
            StepSizeX = 300;
        else
            StepSizeX = 600;
    }
    else if(My_droneV[i].drone_x >= 7500)
    {
        if(rad == "TR" || rad == "BR")
            StepSizeX = 200;
        else
            StepSizeX = 1000;
    }
    /*initial the StepSizeY */
    if(My_droneV[i].drone_y <= 2500)
    {
        if (rad == "TL" || rad == "TR")
            StepSizeY = 200;
        else
            StepSizeY = 1000;
    }
    else if(My_droneV[i].drone_y > 2500 && My_droneV[i].drone_y < 5000)
    {
        if (rad == "TL" || rad == "TR")
            StepSizeY = 300;
        else
            StepSizeY = 600;
    }
    else if(My_droneV[i].drone_y >= 5000 && My_droneV[i].drone_y < 7500)
    {
        if (rad == "BL" || rad == "BR")
            StepSizeY = 300;
        else
            StepSizeY = 600;
    }
    else if(My_droneV[i].drone_y >= 7500)
    {
        if (rad == "BL" || rad == "BR")
            StepSizeY = 200;
        else
            StepSizeY = 1000;
    }
}



/*    initial steps    way 2*/


void calculate_steps(int drone_positionX, int drone_positionY,  std::string target_direction, int map_width, int map_height)
{
    // int target_x = drone_position.x;
    // int target_y = drone_position.y;
	int target_x = drone_positionX;
    int target_y = drone_positionY;

    // Adjust target position based on direction
    if (target_direction == "TL")
	{
        target_x = 0;
        target_y = 0;
    }
    else if (target_direction == "TR")
	{
        target_x = map_width;
        target_y = 0;
    }
    else if (target_direction == "BL")
	{
        target_x = 0;
        target_y = map_height;
    }
    else if (target_direction == "BR")
	{
        target_x = map_width;
        target_y = map_height;
    }

    // Calculate relative position
	int Relative_positionX = target_x - drone_positionX;
	int Relative_positionY = target_y - drone_positionY;
    // Position relative_position = {target_x - drone_position.x, target_y - drone_position.y};

    // Calculate distances
    int x_distance = std::abs(Relative_positionX);
    int y_distance = std::abs(Relative_positionY);

    // Decide which direction to move first
    
    if (x_distance > y_distance)
	{
        steps_x = std::min(x_distance, map_width - x_distance);
        steps_y = std::min(y_distance, map_height - y_distance);
    }
    else
	{
        steps_y = std::min(y_distance, map_height - y_distance);
        steps_x = std::min(x_distance, map_width - x_distance);
    }
}