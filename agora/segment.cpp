#include <iostream>
#include <vector>



// Point divideStraight(int beginX, int beginY, int endX, int endY, int segment, int SegmentCount)
// {
//     Point result;
//     result.x = beginX + (endX - beginX) / SegmentCount;
//     result.y = beginY + (endY - beginY)  / SegmentCount;
//     return result;
// }


class Point
{
    public:
        int x;
        int y;
    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
};

std::vector<Point> divideLine(Point p1, Point p2, int numPoints)
{
    int move = 1;
    std::vector<Point> Vp;
    int Dx = p2.x - p1.x;
    int Dy = p2.y - p1.y;

    int StepX = Dx / numPoints;
    int StepY = Dy / numPoints;

    while(move <= numPoints)
    {
        Point p(p1.x + (move * StepX), p1.y + (move * StepY));
        Vp.push_back(p);
        move++;
    }
    return Vp;
}


int main()
{
    Point p1(6767, 5238);
    Point p2(7500, 9600);

    Point p3(6913, 5814);
    Point p4(6780, 5291);

    std::vector<Point> vec1 = divideLine(p1, p2, 10);
    std::vector<Point> vec2 = divideLine(p3, p4, 10);

    std::cout << "line 1 \n";
    for(size_t i=0; i<vec1.size();i++)
        std::cout << "x = " << vec1[i].x << "  y =  " << vec1[i].y << std::endl;

    std::cout << "line 2 \n";
    for(size_t i=0; i<vec2.size();i++)
        std::cout << "x = " << vec2[i].x << "  y =  " << vec2[i].y << std::endl;


    return 0;
}


