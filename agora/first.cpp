#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

/**
 * Score points by scanning valuable fish faster than your opponent.
 **/


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

void    Avoid_Monster(My_drone drone, int Drone_NextX, int Drone_NextY)
{
    cerr << "\n-------------------------------------------------\n";
    cerr << "Monster Count  " << drone.Monsters.size() << endl;
    cerr << "The drone that scanned this monster " << drone.drone_id << endl;
    for(size_t i=0; i<drone.Monsters.size(); i++)
    {
        cerr << "Monster_Id   " << drone.Monsters[i].creature_id << endl;
        cerr << "Monster_X   " << drone.Monsters[i].creature_x << endl;
        cerr << "Monster_Y   " << drone.Monsters[i].creature_y << endl;
        cerr << "Monster_Vx   " << drone.Monsters[i].creature_vx << endl;
        cerr << "Monster_Vy   " << drone.Monsters[i].creature_vy << endl;
        cerr << "\n-------------------------------------------------\n";
    }
    cerr << "Target :  x= " << Drone_NextX << " y= " << Drone_NextY << endl;
    
    double  TmpDist = 124000000;
    int y = 10000;
    Point   SavePoint = Point(-1, -1, -1);
    for(size_t j=0; j<drone.Monsters.size(); j++)
    {
        vector<Point> EstablishedPoints = GeneratePoints(Point(drone.drone_x, drone.drone_y, -1), 600);
        for(size_t i=0; i<EstablishedPoints.size(); i++)
        {
            double CheckDis = distance(EstablishedPoints[i].x, EstablishedPoints[i].y, drone.Monsters[j].creature_x, drone.Monsters[j].creature_y);
            double CheckDis2 = distance(EstablishedPoints[i].x, EstablishedPoints[i].y, drone.Monsters[j].creature_x + drone.Monsters[j].creature_vx, drone.Monsters[j].creature_y + drone.Monsters[j].creature_vy);
            if(CheckDis > 800 && CheckDis2 > 800)
            {
                EstablishedPoints[i].dist = distance(EstablishedPoints[i].x, EstablishedPoints[i].y, Drone_NextX, Drone_NextY);
                int DisDrone = distance(drone.drone_x, drone.drone_y, EstablishedPoints[i].x, EstablishedPoints[i].y);
                int DisMonster = distance(drone.Monsters[i].creature_x, drone.Monsters[i].creature_y, drone.Monsters[j].creature_x + drone.Monsters[j].creature_vx, drone.Monsters[j].creature_y + drone.Monsters[j].creature_vy);
                if(TmpDist > EstablishedPoints[i].dist)
                {
                    TmpDist = EstablishedPoints[i].dist;
                    SavePoint.x = EstablishedPoints[i].x;
                    SavePoint.y = EstablishedPoints[i].y;
                    SavePoint.dist = EstablishedPoints[i].dist;
                }
            }
        }
    }
    cout << "MOVE " << (int)SavePoint.x << " " << (int)SavePoint.y << " " << drone.light << endl;
}

int Check = 0;
void MoveDrone(My_drone drone)
{
    if(drone.drone_y < 8000 && Check == 0)
    {
        cout << "MOVE " << drone.drone_x << " 8600 0" << endl;
    }
    else if(drone.drone_y >= 8000 || Check == 1)
    {
        Check = 1;
        cout << "MOVE " << drone.drone_x << " 500 0" << endl;
        if(drone.drone_y <= 500)
            Check = 0;
    }
}

int main()
{
    vector<Fish> fish;
    vector<int> My_drone1_scan;
	vector<int> My_drone2_scan;
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
    }

    // game loop
    while (1)
    {
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
        for (int i = 0; i < foe_drone_count; i++)
        {
            int drone_id;
            int drone_x;
            int drone_y;
            int emergency;
            int battery;
            cin >> drone_id >> drone_x >> drone_y >> emergency >> battery; cin.ignore();
        }
        int drone_scan_count;
        cin >> drone_scan_count; cin.ignore();
        for (int i = 0; i < drone_scan_count; i++)
        {
            int drone_id;
            int creature_id;
            cin >> drone_id >> creature_id; cin.ignore();
            // hna kan3amro lkola drone lcreature liscanat 
            if(my_drone[0].drone_id == drone_id && check_id(My_drone1_scan, creature_id) == -1 && check_id(My_drone2_scan, creature_id) == -1)
				My_drone1_scan.push_back(creature_id);
			else if(my_drone[1].drone_id == drone_id && check_id(My_drone2_scan, creature_id) == -1 && check_id(My_drone1_scan, creature_id) == -1)
				My_drone2_scan.push_back(creature_id);
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
            // this loop for add color and type Lvisible_creature;
            for(size_t i=0; i<fish.size(); i++)
			{
				if(fish.at(i).creature_id == creature_id)
				{
					color = fish.at(i).color;
					type = fish.at(i).type;
					break;
				}
			}
            // fill vector the Visible_creature
            visible_creature.push_back(Visible_creature(creature_id, creature_x, creature_y, creature_vx, creature_vy, color, type));
            //hna ghadi njm3o lmonster l9rab lkola drone
            for(size_t i = 0; i<my_drone.size(); i++)
            {
                if(distance(my_drone[i].drone_x, my_drone[i].drone_y, creature_x, creature_y) < 2000 && type == -1)
                    my_drone[i].Monsters.push_back(Visible_creature(creature_id, creature_x, creature_y, creature_vx, creature_vy, color, type));
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

            // fill radar  the any drone .
            if(my_drone[0].drone_id == drone_id && check_id(My_drone1_scan, creature_id) == -1 && check_id(My_drone2_scan, creature_id) == -1)
				my_drone[0].RadarDrone.push_back(Radar(radar, drone_id, creature_id));
			else if(my_drone[1].drone_id == drone_id && check_id(My_drone1_scan, creature_id) == -1 && check_id(My_drone2_scan, creature_id) == -1)
				my_drone[1].RadarDrone.push_back(Radar(radar, drone_id, creature_id));
        }
        for (int i = 0; i < my_drone_count; i++)
        {

            // Write an action using cout. DON'T FORGET THE "<< endl"
            // To debug: cerr << "Debug messages..." << endl;
            MoveDrone(my_drone[i]);
            // cout << "WAIT 1" << endl; // MOVE <x> <y> <light (1|0)> | WAIT <light (1|0)>
        }
    }
}