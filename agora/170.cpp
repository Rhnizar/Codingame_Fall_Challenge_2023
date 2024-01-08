#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <random>
#include <map>

using namespace std;


double distance(int x1, int y1, int x2, int y2) 
{
    double deltaX = x2 - x1;
    double deltaY = y2 - y1;
    double distance = sqrt(deltaX * deltaX + deltaY * deltaY);
    return distance;
}

int check_id(vector<int> VId, int IdCheck)
{
    for(size_t i=0; i<VId.size(); i++)
    {
        if(VId.at(i) == IdCheck)
            return IdCheck;
    }
    return -1;
}

class Fish
{
    public :
        int creature_id;
        int color;
        int type;
        Fish(int creature_id, int color, int type)
        {
            this->creature_id = creature_id;
            this->color = color;
            this->type = type;
        }
};

class Visible_creature
{
	public:
		int creature_id;
        int creature_x;
        int creature_y;  
        int creature_vx;
        int creature_vy;

		int color;
        int type;
	Visible_creature(int creature_id, int creature_x, int creature_y, int creature_vx, int creature_vy, int color, int type)
	{
		this->creature_id = creature_id;
		this->creature_x = creature_x;
		this->creature_y = creature_y;
		this->creature_vx = creature_vx;
		this->creature_vy = creature_vy;

		this->color = color;
		this->type = type;
	}
};

class Radar
{
	public:
		string radar;
		int drone_id;
        int creature_id;
	Radar(string radar, int drone_id, int creature_id)
	{
		this->radar = radar;
		this->drone_id = drone_id;
		this->creature_id = creature_id;
	}
};

class My_drone
{
	public:
		int drone_id;
        int drone_x;
        int drone_y;
		int emergency;
        int battery;
        vector<Visible_creature> Monsters;
		vector<Radar> RadarDrone;
		int light;
		My_drone(int drone_id, int drone_x, int drone_y, int emergency, int battery, int light)
		{
			this->drone_id = drone_id;
			this->drone_x = drone_x;
			this->drone_y = drone_y;
			this->emergency= emergency;
			this->battery = battery;
			this->light = light;
		}
};

class Point
{
    public:
        int  x;
        int  y;
    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
};

class Point2
{
    public:
        int  x;
        int  y;
        int  NextX;
        int  NextY;
    Point2(int x, int y, int NextX, int NextY)
    {
        this->x = x;
        this->y = y;
        this->NextX = NextX;
        this->NextY = NextY;
    }
};

int Emergency = 0;

vector<Point> GeneratePoints(Point center, int radius)
{
    vector<Point> EstablishedPoints;
    EstablishedPoints.clear();

    for (size_t i = 0; i < 360; i++)
    {
        double angleInRadians = i * M_PI / 180.0;
        double x = center.x + radius * cos(angleInRadians);
        double y = center.y + radius * sin(angleInRadians);
        EstablishedPoints.push_back(Point(x, y));
    }
    return EstablishedPoints;
}

std::vector<Point> divideLine(double x1, double y1, double x2, double y2, int n)
{
    int move = 1;
    std::vector<Point> Vp;
    int Dx = x2 - x1;
    int Dy = y2 - y1;

    int StepX = Dx / n;
    int StepY = Dy / n;

    while(move <= n)
    {
        Point p(x1 + (move * StepX), y1 + (move * StepY));
        Vp.push_back(p);
        move++;
    }
    return Vp;
}


std::vector<Point> splitLine(double x1, double y1, double x2, double y2, int n)
{
    std::vector<Point> points;

    for (int i = 0; i <= n; ++i)
    {
        double t = static_cast<double>(i) / n;
        double x = x1 + t * (x2 - x1);
        double y = y1 + t * (y2 - y1);
        points.push_back(Point(x, y));
    }

    return points;
}

void    Avoid_Monster(My_drone drone, int Drone_NextX, int Drone_NextY)
{
    Point   SavePoint = Point(Drone_NextX, Drone_NextY);
    vector<Point> EstablishedPoints = GeneratePoints(Point(drone.drone_x, drone.drone_y), 600);
    vector<Point> ValidPoints;
    vector<Point2> OldMonster;
    for(size_t j=0; j<drone.Monsters.size(); j++)
    {
        int Xmonster = drone.Monsters[j].creature_x;
        int Ymonster = drone.Monsters[j].creature_y;
        int Next_Xmonster = drone.Monsters[j].creature_x + drone.Monsters[j].creature_vx;
        int Next_Ymonster = drone.Monsters[j].creature_y + drone.Monsters[j].creature_vy;

        OldMonster.push_back(Point2(Xmonster, Ymonster, Next_Xmonster, Next_Ymonster));
        double  TmpDist = 9999999999;
        ValidPoints.clear();
        for(size_t i = 0; i<EstablishedPoints.size(); i++)
        {

            vector<Point> Dvp = splitLine(drone.drone_x, drone.drone_y, EstablishedPoints[i].x, EstablishedPoints[i].y, 100);
            vector<Point> Mvp = splitLine(Xmonster, Ymonster, Next_Xmonster, Next_Ymonster, 100);

            int check = 0;
            double di = round(distance(EstablishedPoints[i].x, EstablishedPoints[i].y, Next_Xmonster, Next_Ymonster));
            double di2 = round(distance(EstablishedPoints[i].x, EstablishedPoints[i].y, Xmonster, Ymonster));
            double disDrone = 999999999;
            if(drone.Monsters[0].creature_id == 0)
            {
                disDrone = round(distance(EstablishedPoints[i].x, EstablishedPoints[i].y, drone.Monsters[0].creature_x, drone.Monsters[0].creature_y));
            }
            for(size_t r=0; r<Dvp.size(); r++)
            {
                
                if(round(distance(Dvp[r].x, Dvp[r].y, Mvp[r].x, Mvp[r].y)) <= 501 || di <= 501 || di2 <= 501 || disDrone <= 600 ||
                    EstablishedPoints[i].x < 0 || EstablishedPoints[i].x > 9999 || EstablishedPoints[i].y < 0 || EstablishedPoints[i].y > 9999)
                {
                    check = 1;
                    break;
                }
            }
            if(check == 0)
            {
                ValidPoints.push_back(EstablishedPoints[i]);
                double dist = round(distance(EstablishedPoints[i].x, EstablishedPoints[i].y, Drone_NextX, Drone_NextY));
                if(TmpDist > dist)
                {
                    TmpDist = dist;
                    SavePoint.x = EstablishedPoints[i].x;
                    SavePoint.y = EstablishedPoints[i].y;
                }
            }
        }
        EstablishedPoints = ValidPoints;
    }
    cout << "MOVE " << SavePoint.x << " " << SavePoint.y << " " << drone.light << endl;
}

int CheckType(int creature_id, vector<Fish> fish, int type)
{
    for(size_t i=0; i<fish.size(); i++)
    {
        if(fish[i].creature_id == creature_id && fish[i].type == type)
            return 1;
    }
    return 0;
}


string Calculate_Numbers_Of_Radar(My_drone drone, vector<Radar> RadarType, vector<Fish> fish)
{
	int tl = 0, tr = 0, bl = 0, br = 0;
    for(size_t i = 0; i < RadarType.size(); i++)
	{
		if(RadarType.at(i).radar == "TL")
			tl++;
		else if(RadarType.at(i).radar == "TR")
			tr++;
		else if(RadarType.at(i).radar == "BL")
			bl++;
		else if(RadarType.at(i).radar == "BR")
			br++;
	}
	int maxCount = tl;
	std::string maxRadar = "TL";
	if (tr > maxCount)
	{
	    maxCount = tr;
	    maxRadar = "TR";
	}
	if (bl > maxCount)
	{
	    maxCount = bl;
	    maxRadar = "BL";
	}
	if (br > maxCount)
	{
	    maxCount = br;
	    maxRadar = "BR";
    }
    if((drone.drone_id == 0 || drone.drone_id == 3) && bl > 0)
        return "BL";
    if((drone.drone_id == 2 || drone.drone_id == 1) && br > 0)
        return "BR";
	return maxRadar;
}

Point Target(2000, 8100);
Point Target2(8000, 8100);

void    UseRadar(My_drone drone, string rad, Point &Target)
{
    if(rad == "BR")
    {
        Target.x = drone.drone_x + 2400;
        Target.y = drone.drone_y + 2400;
    }
    else if(rad == "BL")
    {
        Target.x = drone.drone_x - 2400;
        Target.y = drone.drone_y + 2400;
    }
    else if(rad == "TR")
    {
        Target.x = drone.drone_x + 2400;
        Target.y = drone.drone_y - 2400;
    }
    else if(rad == "TL")
    {
        Target.x = drone.drone_x - 2400;
        Target.y = drone.drone_x - 2400;
    }
}

int size1 = 0;
void    SepareteDrone(My_drone drone, vector<int> My_drone_scan, vector<Fish> fish, Point &Target, int GlobalScan, map<int, int> RemainingFish)
{
    int size1 = 0;
    string rad;
    vector<Radar> RadarType0;
    vector<Radar> RadarType1;
    vector<Radar> RadarType2;

     if(RadarType2.size() == 0 && drone.drone_y >= Target.y)
        Target.y = 3500;
    for(size_t i = 0; i < drone.RadarDrone.size(); i++)
    {
        if(CheckType(drone.RadarDrone[i].creature_id, fish, 0) == 1)
            RadarType0.push_back(drone.RadarDrone[i]);
        if(CheckType(drone.RadarDrone[i].creature_id, fish, 1) == 1)
            RadarType1.push_back(drone.RadarDrone[i]);
        if(CheckType(drone.RadarDrone[i].creature_id, fish, 2) == 1)
            RadarType2.push_back(drone.RadarDrone[i]);
    }

    for(size_t i=0; i<My_drone_scan.size(); i++)
    {
        if(CheckType(My_drone_scan[i], fish, 2) == 1)
            size1++;
    }

    if(RadarType1.size() == 0 && drone.drone_y >= 5000 && drone.drone_y <= 6000)
        drone.light = 0;
    if(RadarType0.size() == 1 && drone.drone_y >= 2500 && drone.drone_y <= 5000)
        drone.light = 0;

    if(size1 > 0 || GlobalScan == 12)
    {
        Target.y = 500;
        Target.x = drone.drone_x;
        drone.light = 0;
    }
    else if(size1 == 0 && drone.drone_y >= 6000)
    {
        rad = Calculate_Numbers_Of_Radar(drone, RadarType2, fish);
        UseRadar(drone, rad, Target);
    }
    else if(Target.y == 3500 && size1 == 4)
    {
        if(drone.drone_y >= 3500)
        {
            Target.y = 500;
            Target.x = drone.drone_x;
        }
        else
            Target.y = 3500;
    }
    else
        Target.y = 8100;
    Avoid_Monster(drone, Target.x, Target.y);
}

void MoveDrone(My_drone drone, int &Check, vector<int> My_drone_scan, vector<Visible_creature> Visible_creature, int sep, vector<Fish> fish, \
    int &TmpSize, vector<int> foe_drone_scan, int GlobalScan, map<int, int> RemainingFish)
{

    if(drone.drone_id == 0 || drone.drone_id == 3)
        SepareteDrone(drone, My_drone_scan, fish, Target, GlobalScan, RemainingFish);
    else
        SepareteDrone(drone, My_drone_scan, fish, Target2, GlobalScan, RemainingFish);
}


int main()
{
    int CheckDrone1 = 0;
    int CheckDrone2 = 0;
    int TmpSize1 = 0;
    int TmpSize2 = 0;
    map<int, int> RemainingFish;
    vector <int> Monsters;
    vector <Visible_creature> MonstersV;
    vector<Fish> fish;
    
    vector<Visible_creature> visible_creature;
    int creature_count;
    cin >> creature_count; cin.ignore();
    for (int i = 0; i < creature_count; i++)
    {
        int creature_id;
        int color;
        int type;
        cin >> creature_id >> color >> type; cin.ignore();
        fish.push_back(Fish(creature_id, color, type));
        if(type == -1)
            Monsters.push_back(creature_id);
    }
    int Turn = 0;
    vector<int> My_drone1_scan;
	vector<int> My_drone2_scan;
    vector<int> foe_drone_scan;
    while (1)
    {
        vector<int> My_drone1_scanNew;
	    vector<int> My_drone2_scanNew;
        vector<int> Scan_Validated;


        vector<My_drone> my_drone;
        int my_score;
        cin >> my_score; cin.ignore();
        int foe_score;
        cin >> foe_score; cin.ignore();
        int my_scan_count;
        cin >> my_scan_count; cin.ignore();
        for (int i = 0; i < my_scan_count; i++)
        {
            int creature_id;
            cin >> creature_id; cin.ignore();
            Scan_Validated.push_back(creature_id);
        }
        int foe_scan_count;
        cin >> foe_scan_count; cin.ignore();
        for (int i = 0; i < foe_scan_count; i++) {
            int creature_id;
            cin >> creature_id; cin.ignore();
        }
        int my_drone_count;
        cin >> my_drone_count; cin.ignore();
        for (int i = 0; i < my_drone_count; i++)
        {
            int drone_id;
            int drone_x;
            int drone_y;
            int emergency;
            int battery;
            cin >> drone_id >> drone_x >> drone_y >> emergency >> battery; cin.ignore();
            my_drone.push_back(My_drone(drone_id, drone_x, drone_y, emergency, battery, 0));
        }


        int foe_drone_count;
        cin >> foe_drone_count; cin.ignore();
        vector<Point> foe_Point;
        for (int i = 0; i < foe_drone_count; i++)
        {
            int drone_id;
            int drone_x;
            int drone_y;
            int emergency;
            int battery;
            cin >> drone_id >> drone_x >> drone_y >> emergency >> battery; cin.ignore();
            foe_Point.push_back(Point(drone_x, drone_y));
        }
        int drone_scan_count;
        cin >> drone_scan_count; cin.ignore();
        for (int i = 0; i < drone_scan_count; i++)
        {
            int drone_id;
            int creature_id;
            cin >> drone_id >> creature_id; cin.ignore();


            if(my_drone[0].drone_id == drone_id)
            {
                My_drone1_scanNew.push_back(creature_id);
            }
            else if(my_drone[1].drone_id == drone_id)
            {
                My_drone2_scanNew.push_back(creature_id);
            }


        }
        int visible_creature_count;
        cin >> visible_creature_count; cin.ignore();
        for (int i = 0; i < visible_creature_count; i++)
        {
            int creature_id;
            int creature_x;
            int creature_y;
            int creature_vx;
            int creature_vy;

            int color;
			int type;
            cin >> creature_id >> creature_x >> creature_y >> creature_vx >> creature_vy; cin.ignore();
            for(size_t i=0; i<fish.size(); i++)
			{
				if(fish.at(i).creature_id == creature_id)
				{
					color = fish.at(i).color;
					type = fish.at(i).type;
					break;
				}
			}
            visible_creature.push_back(Visible_creature(creature_id, creature_x, creature_y, creature_vx, creature_vy, color, type));
            for(size_t i = 0; i<my_drone.size(); i++)
            {
                if(distance(my_drone[i].drone_x, my_drone[i].drone_y, creature_x, creature_y) < 2000 && type == -1)
                    my_drone[i].Monsters.push_back(Visible_creature(creature_id, creature_x, creature_y, creature_vx, creature_vy, color, type));
            }
        }

        
        if(distance(foe_Point[0].x, foe_Point[0].y, my_drone[0].drone_x, my_drone[0].drone_y) < 1000)
            my_drone[0].Monsters.push_back(Visible_creature(0, foe_Point[0].x, foe_Point[0].y, 0, 0, 0, 0));
        else if(distance(foe_Point[0].x, foe_Point[0].y, my_drone[1].drone_x, my_drone[1].drone_y) < 1000)
            my_drone[1].Monsters.push_back(Visible_creature(0, foe_Point[0].x, foe_Point[0].y, 0, 0, 0, 0));
        
        if(distance(foe_Point[1].x, foe_Point[1].y, my_drone[0].drone_x, my_drone[0].drone_y) < 1000)
            my_drone[0].Monsters.push_back(Visible_creature(0, foe_Point[1].x, foe_Point[1].y, 0, 0, 0, 0));
        else if(distance(foe_Point[1].x, foe_Point[1].y, my_drone[1].drone_x, my_drone[1].drone_y) < 1000)
            my_drone[1].Monsters.push_back(Visible_creature(0, foe_Point[1].x, foe_Point[1].y, 0, 0, 0, 0));


        if(my_drone[0].Monsters.size() > 1)
        {
            for(size_t i=0; i<my_drone[0].Monsters.size(); i++)
            {
                if(my_drone[0].Monsters[i].creature_id == 0)
                    my_drone[0].Monsters.erase(my_drone[0].Monsters.begin() + i);
            }
        }
        if(my_drone[1].Monsters.size() > 1)
        {
            for(size_t i=0; i<my_drone[1].Monsters.size(); i++)
            {
                if(my_drone[1].Monsters[i].creature_id == 0)
                    my_drone[1].Monsters.erase(my_drone[1].Monsters.begin() + i);
            }
        }
        int radar_blip_count;
        cin >> radar_blip_count; cin.ignore();
        for (int i = 0; i < radar_blip_count; i++)
        {
            int drone_id;
            int creature_id;
            string radar;
            cin >> drone_id >> creature_id >> radar; cin.ignore();

            if(check_id(My_drone1_scanNew, creature_id) != -1  || check_id(My_drone2_scanNew, creature_id) != -1 || check_id(Scan_Validated, creature_id) != -1)
            {
                continue;
            }

            if(my_drone[0].drone_id == drone_id)
				my_drone[0].RadarDrone.push_back(Radar(radar, drone_id, creature_id));
            else if(my_drone[1].drone_id == drone_id)
				my_drone[1].RadarDrone.push_back(Radar(radar, drone_id, creature_id));
        }
        int GlobalScan = My_drone1_scanNew.size() + My_drone2_scanNew.size() + Scan_Validated.size();
        for (int i = 0; i < my_drone_count; i++)
        {
            if(my_drone[i].drone_y >= 5600 && my_drone[i].drone_y <= 9000)
                my_drone[i].light = 1;
            if(Turn % 4  == 1 && my_drone[i].drone_y > 2000)
                my_drone[i].light = 1;
            if(i == 0)
            {
                if(my_drone[i].drone_y >= 1000 && my_drone[i].drone_y <= 1600 && Target.y != 500)
                    my_drone[i].light = 1;
                MoveDrone(my_drone[i], CheckDrone1, My_drone1_scanNew, visible_creature, 0, fish, TmpSize1, foe_drone_scan, GlobalScan, RemainingFish);
            }
            else
            {
                if(my_drone[i].drone_y >= 1000 && my_drone[i].drone_y <= 1600 && Target2.y != 500)
                    my_drone[i].light = 1;
                MoveDrone(my_drone[i], CheckDrone2, My_drone2_scanNew, visible_creature, 1, fish, TmpSize2, foe_drone_scan, GlobalScan, RemainingFish);
            }
        }
        Turn++;
    }
}