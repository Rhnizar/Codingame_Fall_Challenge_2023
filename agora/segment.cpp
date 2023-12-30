#include <iostream>

struct Point
{
    int x;
    int y;
};

Point divideStraight(int beginX, int beginY, int endX, int endY, int segment, int SegmentCount)
{
    Point result;
    result.x = beginX + (endX - beginX) / SegmentCount;
    result.y = beginY + (endY - beginY)  / SegmentCount;
    return result;
}

int main()
{
    // Define the initial straight line
    int beginX = 0;
    int beginY = 500;
    int endX = 0;
    int endY = 1000;
    Point point;
    point.x = 0;
    point.y = 0;
    int i = 0;
    // Get the division point for the second segment (segment = 1)
    while(i < 10)
    {
        Point divisionPoint = divideStraight(point.x, point.y, endX, endY, 1, 2);
        point.x = divisionPoint.x;
        point.y = divisionPoint.y;
        // Display the division point
        std::cout << "Division Point for the second segment: (" << divisionPoint.x << ", " << divisionPoint.y << ")" << std::endl;
        i++;
    }


    return 0;
}
