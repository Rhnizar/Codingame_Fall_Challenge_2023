#include <iostream>
#include <cmath>

// Define a structure to represent coordinates (x, y)
struct Point {
    double x;
    double y;
};

// Function to calculate the position of the center of a circle given its radius
Point calculateCircleCenter(double radius) {
    Point center;
    
    // Assuming that the circle is centered at the origin (0, 0)
    center.x = 0.0;
    center.y = 0.0;

    return center;
}

int main() {
    double radius;

    // Get the radius from the user
    std::cout << "Enter the radius of the circle: ";
    std::cin >> radius;

    // Calculate the center of the circle
    Point center = calculateCircleCenter(radius);

    // Display the result
    std::cout << "The center of the circle with radius " << radius << " is at: (" << center.x << ", " << center.y << ")\n";

    return 0;
}
