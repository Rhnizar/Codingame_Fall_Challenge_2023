#include <iostream>
#include <random>

int main() {
    // Define the width and height of the map
    const int mapWidth = 10000;
    const int mapHeight = 10000;

    // Seed for random number generation
    std::random_device rd;
    std::mt19937 gen(rd());

    // Generate random x and y coordinates for the player within the map
    std::uniform_int_distribution<int> distributionX(0, mapWidth);
    std::uniform_int_distribution<int> distributionY(0, mapHeight);

    int playerX = distributionX(gen);
    int playerY = distributionY(gen);

    // Display the player's random position
    std::cout << "Player's position: X = " << playerX << ", Y = " << playerY << std::endl;

    return 0;
}
