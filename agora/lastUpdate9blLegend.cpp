#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <random>

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

vector<Point> GeneratePoints(Point center, int radius)
{
    vector<Point> EstablishedPoints;
    // Clear existing points
    EstablishedPoints.clear();

    for (size_t i = 0; i < 360; i++)
    {
        double angleInRadians = i * M_PI / 180.0;

        // Calculate coordinates using polar coordinates
        double x = center.x + radius * cos(angleInRadians);
        double y = center.y + radius * sin(angleInRadians);

        // Point point = {x, y};
        EstablishedPoints.push_back(Point(x, y));
    }
    return EstablishedPoints;
}

// divide Line to segments
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

void    Avoid_Monster(My_drone drone, int Drone_NextX, int Drone_NextY)
{
    // cerr << "Monster Count  " << drone.Monsters.size() << endl;
    // cerr << "drone id  " << drone.drone_id << endl;
    // for(size_t i=0; i<drone.Monsters.size(); i++)
    // {
    //     cerr << "Monster_Id   " << drone.Monsters[i].creature_id << endl;
    //     // cerr << "Monster_X   " << drone.Monsters[i].creature_x << endl;
    //     // cerr << "Monster_Y   " << drone.Monsters[i].creature_y << endl;
    //     // cerr << "Monster_Vx   " << drone.Monsters[i].creature_vx << endl;
    //     // cerr << "Monster_Vy   " << drone.Monsters[i].creature_vy << endl;
    //     cerr << "\n-------------------------------------------------\n";
    // }
    // cerr << "Target :  x= " << Drone_NextX << " y= " << Drone_NextY << endl;

    // cerr << "\n==========================================\n";
    
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
            vector<Point> Dvp = divideLine(Point(drone.drone_x, drone.drone_y), Point(EstablishedPoints[i].x, EstablishedPoints[i].y), 10);
            vector<Point> Mvp = divideLine(Point(Xmonster, Ymonster), Point(Next_Xmonster, Next_Ymonster), 10);

            int check = 0;
            double di = distance(EstablishedPoints[i].x, EstablishedPoints[i].y, Next_Xmonster, Next_Ymonster);
            for(size_t r=0; r<Dvp.size(); r++)
            {
                if(distance(Dvp[r].x, Dvp[r].y, Mvp[r].x, Mvp[r].y) <= 508 || di <= 501)
                {
                    check = 1;
                    break;
                }
            }
            if(check == 0)
            {
                ValidPoints.push_back(EstablishedPoints[i]);
                double dist = distance(EstablishedPoints[i].x, EstablishedPoints[i].y, Drone_NextX, Drone_NextY);
                if(TmpDist > dist)
                {
                    TmpDist = dist;
                    SavePoint.x = EstablishedPoints[i].x;
                    SavePoint.y = EstablishedPoints[i].y;
                }
            }
        }
        EstablishedPoints = ValidPoints;
        if(EstablishedPoints.size() == 0)
        {
            cerr << "size OldMonster " << OldMonster.size() << endl;
            int tmp = 0;
            // int tmp2 = 99999999;
            int NXM = 0, NYM = 0;
            int XM = 0, YM = 0;
            int VxM = 0, VyM = 0;
            vector<Point> Dvp2;
            double Tmpdis = 999999999;
            for(size_t i=0; i<OldMonster.size(); i++)
            {
                double dis = distance(drone.drone_x, drone.drone_y, OldMonster[i].x, OldMonster[i].y);
                if(dis < Tmpdis)
                {
                    Tmpdis = dis;
                    NXM = OldMonster[i].NextX;
                    NYM = OldMonster[i].NextY;
                    XM = OldMonster[i].x;
                    YM = OldMonster[i].y;
                    VxM = OldMonster[i].NextX - OldMonster[i].x;
                    VyM = OldMonster[i].NextY - OldMonster[i].y;
                    // cerr << "monster x.  =  " << OldMonster[i].x << endl;
                }
            }
            int x, y;
            if(VxM > 0)
                x = drone.drone_x + VxM + 60;
            else
                x = drone.drone_x + VxM - 60;
            if(VyM > 0)
                y = drone.drone_y + VyM + 60;
            else
                y = drone.drone_y + VyM - 60;
            
            Dvp2 = divideLine(Point(drone.drone_x, drone.drone_y), Point(x, y), 70);
            
            for(size_t r=0; r<Dvp2.size(); r++)
            {
                int CheckOldMonster = 0;
                for(size_t i=0; i<OldMonster.size(); i++)
                {
                    if(distance(Dvp2[r].x, Dvp2[r].y, OldMonster[i].x, OldMonster[i].y) <= 501 || distance(Dvp2[r].x, Dvp2[r].y, OldMonster[i].NextX, OldMonster[i].NextY) <= 500)
                        CheckOldMonster = 1;
                }
                double dis = distance(Dvp2[r].x, Dvp2[r].y, Xmonster, Ymonster);
                if(CheckOldMonster == 0)
                {
                    // cerr << "heeeereeeee\n";
                    tmp = dis;
                    SavePoint.x = Dvp2[r].x;
                    SavePoint.y = Dvp2[r].y;
                }
            }
        }
        // cerr << "size        =========   " << EstablishedPoints.size() << endl;
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


vector<Radar> RadarType2;
string Calculate_Numbers_Of_Radar(My_drone drone, vector<Radar> RadarType2, vector<Fish> fish)
{
	int tl = 0, tr = 0, bl = 0, br = 0;
    // RadarType2.clear();
    // for(size_t i = 0; i < RaV.size(); i++)
    // {
    //     if(CheckType(RaV[i].creature_id, fish, type) == 1)
    //         RadarType2.push_back(RaV[i]);
    // }
    // cerr << "size radar type  " << type << "  is    " << RadarType2.size() << endl;
    // if(RadarType2.size() != 0)
    // {
        for(size_t i = 0; i < RadarType2.size(); i++)
	    {
	    	if(RadarType2.at(i).radar == "TL")
	    		tl++;
	    	else if(RadarType2.at(i).radar == "TR")
	    		tr++;
	    	else if(RadarType2.at(i).radar == "BL")
	    		bl++;
	    	else if(RadarType2.at(i).radar == "BR")
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
    // }
    // else
    // {
    //     for(size_t i = 0; i < RaV.size(); i++)
	//     {
	//     	if(RaV.at(i).radar == "TL")
	//     		tl++;
	//     	else if(RaV.at(i).radar == "TR")
	//     		tr++;
	//     	else if(RaV.at(i).radar == "BL")
	//     		bl++;
	//     	else if(RaV.at(i).radar == "BR")
	//     		br++;
	//     }
	//     int maxCount = tl;
	//     std::string maxRadar = "TL";

	//     if (tr > maxCount)
	//     {
	//         maxCount = tr;
	//         maxRadar = "TR";
	//     }

	//     if (bl > maxCount)
	//     {
	//         maxCount = bl;
	//         maxRadar = "BL";
	//     }

	//     if (br > maxCount)
	//     {
	//         maxCount = br;
	//         maxRadar = "BR";
    //     }
	//     return maxRadar;
    // }
}

Point Target(1500, 7000);
Point Target2(8500, 7000);

void    UseRadar(My_drone drone, string rad, Point &Target)
{
    if(rad == "BR")
    {
        Target.x = drone.drone_x + 500;
        Target.y = drone.drone_y + 2400;
        // Avoid_Monster(drone, 2500, 7500);
    }
    else if(rad == "BL")
    {
        Target.x = drone.drone_x - 500;
        Target.y = drone.drone_y + 2400;
        // Avoid_Monster(drone, 2500, 7500);
    }
    else if(rad == "TR")
    {
        Target.x = drone.drone_x + 500;
        Target.y = drone.drone_y - 2400;
        // Avoid_Monster(drone, 2500, 7500);
    }
    else if(rad == "TL")
    {
        Target.x = drone.drone_x - 500;
        Target.y = drone.drone_x - 2400;
        // Avoid_Monster(drone, 2500, 7500);
    }
}

int size1 = 0;
void    SepareteDrone(My_drone drone, vector<int> My_drone_scan, vector<Fish> fish, Point Target, int GlobalScan)
{
    int SizeScanType2 = 0;
    int SizeScanType1 = 0;
    int SizeScanType0 = 0;
    string rad;
    vector<Radar> RadarType0;
    vector<Radar> RadarType1;
    vector<Radar> RadarType2;
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
            SizeScanType2++;
        if(CheckType(My_drone_scan[i], fish, 1) == 1)
            SizeScanType1++;
        if(CheckType(My_drone_scan[i], fish, 0) == 1)
            SizeScanType0++;
    }
    cerr << "SizeScanType0  =  " << SizeScanType0 << "  SizeScanType1  =  " << SizeScanType1 << "   SizeScanType2  =  " << SizeScanType2;
    cerr << "     drone id  = " << drone.drone_id << endl;
    if(SizeScanType2 > 0 || GlobalScan == 12)
    {
        Target.y = 500;
        Target.x = drone.drone_x;
        if(RadarType0.size() <= 0 || RadarType1.size() <= 1)
            drone.light = 0;
    }
    else
    {
        if(drone.drone_y >= 2500 && drone.drone_y <= 4000 && RadarType0.size() < 1 && RadarType0.size() != 0)
        {
            rad = Calculate_Numbers_Of_Radar(drone, RadarType0, fish);
            UseRadar(drone, rad, Target);
            // target type 0
        }
        else if(drone.drone_y > 4000 && drone.drone_y <= 7000 && RadarType1.size() < 1 && RadarType1.size() != 0)
        {
            rad = Calculate_Numbers_Of_Radar(drone, RadarType1, fish);
            UseRadar(drone, rad, Target);
            // target type 1
        }
        else if(RadarType2.size() != 0)
        {
            rad = Calculate_Numbers_Of_Radar(drone, RadarType2, fish);
            UseRadar(drone, rad, Target);
            // target type 2
        }
    }
    Avoid_Monster(drone, Target.x, Target.y);

    // else if(drone.drone_y >= Target.y)
    // {
    //     rad = Calculate_Numbers_Of_Radar(drone, drone.RadarDrone, fish);
    //     cerr << "radar drone  " << drone.drone_id << "  is :  " << rad << endl;
    //     UseRadar(drone, rad, Target);
    // }
    // Avoid_Monster(drone, Target.x, Target.y);
}

void MoveDrone(My_drone drone, int &Check, vector<int> My_drone_scan, vector<Visible_creature> Visible_creature, int sep, vector<Fish> fish, int &TmpSize, vector<int> foe_drone_scan, int GlobalScan)
{
    // cerr << "\n==========================================\n";
    // cerr << "  x = " << drone.drone_x;
    // cerr << "  y = " << drone.drone_y << endl;

    if(drone.drone_id == 0 || drone.drone_id == 3)
    {
        // if(RadarType2.size() == 0 && drone.drone_y >= Target.y)
        //     Target.y = 3500;
        SepareteDrone(drone, My_drone_scan, fish, Target, GlobalScan);
    }
    else
    {
        // if(RadarType2.size() == 0 && drone.drone_y >= Target.y)
        //     Target2.y = 3500;
        SepareteDrone(drone, My_drone_scan, fish, Target2, GlobalScan);
    }
}


int main()
{
    int CheckDrone1 = 0;
    int CheckDrone2 = 0;
    int TmpSize1 = 0;
    int TmpSize2 = 0;
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
    }

    int Turn = 0;
    vector<int> My_drone1_scan;
	vector<int> My_drone2_scan;
    vector<int> foe_drone_scan;
    // game loop
    while (1)
    {
        vector<int> My_drone1_scanNew;
	    vector<int> My_drone2_scanNew;

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
        // cerr << "drone_scan_count.   " << drone_scan_count << endl;
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
            else
            {
                if(check_id(foe_drone_scan, creature_id) == -1)
                    foe_drone_scan.push_back(creature_id);
            }
            if(my_drone[0].drone_id == drone_id)
                My_drone1_scanNew.push_back(creature_id);
            else if(my_drone[1].drone_id == drone_id)
                My_drone2_scanNew.push_back(creature_id);
        }
        int visible_creature_count;
        cin >> visible_creature_count; cin.ignore();
        // cerr << "VC  " << visible_creature_count << endl;
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
        
        int GlobalScan = My_drone1_scan.size() + My_drone2_scan.size();
        for (int i = 0; i < my_drone_count; i++)
        {
            if((my_drone[i].drone_y >= 6000 && my_drone[i].Monsters.size() == 0) || my_drone[i].drone_y >= 7500)
                my_drone[i].light = 1;
            if(Turn % 4  == 1 && my_drone[i].drone_y > 2700 && my_drone[i].Monsters.size() == 0)
                my_drone[i].light = 1;
            if(i == 0)
                MoveDrone(my_drone[i], CheckDrone1, My_drone1_scanNew, visible_creature, 0, fish, TmpSize1, foe_drone_scan, GlobalScan);
            else
                MoveDrone(my_drone[i], CheckDrone2, My_drone2_scanNew, visible_creature, 1, fish, TmpSize2, foe_drone_scan, GlobalScan);
        }
        Turn++;
    }
}