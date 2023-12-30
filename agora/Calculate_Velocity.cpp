

// float magnitude() {return (sqrt(x * x + y * y));}
// Vector normalize()
// {
//     float m = magnitude();
//     return (Vector(x / m, y / m));
// }


#include <iostream>

int main()
{
    int x1 = 0;
    int y1 = 0;
    int x2 = 500;
    int y2 = 250;
    double m = sqrt(x2 * x2 + y2 * y2);
    std::cout << "Velocity x (Vx): " << ((x2 / m) * 600) + x1 << std::endl;
    std::cout << "Velocity y (Vy): " << ((y2 / m) * 600) + y1 << std::endl;


    return 0;
}