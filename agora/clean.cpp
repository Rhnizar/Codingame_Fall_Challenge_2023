#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <random>
#include <map>

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

int Emergency = 0;

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
// std::vector<Point> divideLine(Point p1, Point p2, int numPoints)
std::vector<Point> divideLine(double x1, double y1, double x2, double y2, int n)
{
    // double x1, double y1, double x2, double y2, int n
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
    cerr << "Monster Count  " << drone.Monsters.size() << endl;
    cerr << "drone id  " << drone.drone_id << endl;
    for(size_t i=0; i<drone.Monsters.size(); i++)
    {
        cerr << "Monster_Id   " << drone.Monsters[i].creature_id << endl;
        // cerr << "Monster_X   " << drone.Monsters[i].creature_x << endl;
        // cerr << "Monster_Y   " << drone.Monsters[i].creature_y << endl;
        // cerr << "Monster_Vx   " << drone.Monsters[i].creature_vx << endl;
        // cerr << "Monster_Vy   " << drone.Monsters[i].creature_vy << endl;
        cerr << "\n-------------------------------------------------\n";
    }
    cerr << "Target :  x= " << Drone_NextX << " y= " << Drone_NextY << endl;

    cerr << "\n==========================================\n";
    
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
            // vector<Point> Dvp = divideLine(Point(drone.drone_x, drone.drone_y), Point(EstablishedPoints[i].x, EstablishedPoints[i].y), 100);
            // vector<Point> Mvp = divideLine(Point(Xmonster, Ymonster), Point(Next_Xmonster, Next_Ymonster), 100);

            vector<Point> Dvp = splitLine(drone.drone_x, drone.drone_y, EstablishedPoints[i].x, EstablishedPoints[i].y, 100);
            vector<Point> Mvp = splitLine(Xmonster, Ymonster, Next_Xmonster, Next_Ymonster, 100);

            int check = 0;
            double di = round(distance(EstablishedPoints[i].x, EstablishedPoints[i].y, Next_Xmonster, Next_Ymonster));
            double di2 = round(distance(EstablishedPoints[i].x, EstablishedPoints[i].y, Xmonster, Ymonster));
            double disDrone = 999999999;
            if(drone.Monsters[0].creature_id == 0)
            {
                disDrone = round(distance(EstablishedPoints[i].x, EstablishedPoints[i].y, drone.Monsters[0].creature_x, drone.Monsters[0].creature_y));
                // cerr << "yeeeeeeeeees\n";
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
        cerr << "size        =========   " << EstablishedPoints.size() << endl;
        if(EstablishedPoints.size() == 0)
        {
            // cerr << "size OldMonster " << OldMonster.size() << endl;
            int tmp = 0;
            // int tmp2 = 99999999;
            int NXM = 0, NYM = 0;
            int XM = 0, YM = 0;
            int VxM = 0, VyM = 0;
            vector<Point> Dvp2;
            double Tmpdis = 999999999;
            for(size_t i=0; i<OldMonster.size(); i++)
            {
                double dis = round(distance(drone.drone_x, drone.drone_y, OldMonster[i].x, OldMonster[i].y));
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
            Dvp2 = splitLine(drone.drone_x, drone.drone_y, x, y, 100);  
            for(size_t r=0; r<Dvp2.size(); r++)
            {
                int CheckOldMonster = 0;
                for(size_t i=0; i<OldMonster.size(); i++)
                {
                    if(round(distance(Dvp2[r].x, Dvp2[r].y, OldMonster[i].x, OldMonster[i].y)) <= 501 || round(distance(Dvp2[r].x, Dvp2[r].y, OldMonster[i].NextX, OldMonster[i].NextY)) <= 501)
                        CheckOldMonster = 1;
                }
                double dis = round(distance(Dvp2[r].x, Dvp2[r].y, Xmonster, Ymonster));
                if(CheckOldMonster == 0)
                {
                    // cerr << "heeeereeeee\n";
                    tmp = dis;
                    SavePoint.x = Dvp2[r].x;
                    SavePoint.y = Dvp2[r].y;
                }
            }
        }
        
    }
    cout << "MOVE " << SavePoint.x << " " << SavePoint.y << " " << drone.light << endl;
}

// int CheckType(int creature_id, vector<Fish> fish)
// {
//     for(size_t i=0; i<fish.size(); i++)
//     {
//         if(fish[i].creature_id == creature_id && fish[i].type == 2)
//             return 1;
//     }
//     return 0;
// }

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

// vector<Radar> RadarType2;
// string Calculate_Numbers_Of_Radar(My_drone drone, vector<Radar> RaV, vector<Fish> fish)
// {
// 	int tl = 0, tr = 0, bl = 0, br = 0;
//     RadarType2.clear();
//     for(size_t i = 0; i < RaV.size(); i++)
//     {
//         if(CheckType(RaV[i].creature_id, fish, 2) == 1)
//             RadarType2.push_back(RaV[i]);
//     }
//     cerr << "size radar type2  " << RadarType2.size() << endl;
//     if(RadarType2.size() != 0)
//     {
//         for(size_t i = 0; i < RadarType2.size(); i++)
// 	    {
// 	    	if(RadarType2.at(i).radar == "TL")
// 	    		tl++;
// 	    	else if(RadarType2.at(i).radar == "TR")
// 	    		tr++;
// 	    	else if(RadarType2.at(i).radar == "BL")
// 	    		bl++;
// 	    	else if(RadarType2.at(i).radar == "BR")
// 	    		br++;
// 	    }
// 	    int maxCount = tl;
// 	    std::string maxRadar = "TL";

// 	    if (tr > maxCount)
// 	    {
// 	        maxCount = tr;
// 	        maxRadar = "TR";
// 	    }

// 	    if (bl > maxCount)
// 	    {
// 	        maxCount = bl;
// 	        maxRadar = "BL";
// 	    }

// 	    if (br > maxCount)
// 	    {
// 	        maxCount = br;
// 	        maxRadar = "BR";
//         }
//         if((drone.drone_id == 0 || drone.drone_id == 3) && bl > 0)
//             return "BL";
//         if((drone.drone_id == 2 || drone.drone_id == 1) && br > 0)
//             return "BR";
// 	    return maxRadar;
//     }
//     else
//     {
//         for(size_t i = 0; i < RaV.size(); i++)
// 	    {
// 	    	if(RaV.at(i).radar == "TL")
// 	    		tl++;
// 	    	else if(RaV.at(i).radar == "TR")
// 	    		tr++;
// 	    	else if(RaV.at(i).radar == "BL")
// 	    		bl++;
// 	    	else if(RaV.at(i).radar == "BR")
// 	    		br++;
// 	    }
// 	    int maxCount = tl;
// 	    std::string maxRadar = "TL";

// 	    if (tr > maxCount)
// 	    {
// 	        maxCount = tr;
// 	        maxRadar = "TR";
// 	    }

// 	    if (bl > maxCount)
// 	    {
// 	        maxCount = bl;
// 	        maxRadar = "BL";
// 	    }

// 	    if (br > maxCount)
// 	    {
// 	        maxCount = br;
// 	        maxRadar = "BR";
//         }
// 	    return maxRadar;
//     }
// }

Point Target(2000, 8100);
Point Target2(8000, 8100);

void    UseRadar(My_drone drone, string rad, Point &Target)
{
    if(rad == "BR")
    {
        Target.x = drone.drone_x + 2400;
        Target.y = drone.drone_y + 2400;
        // Avoid_Monster(drone, 2500, 7500);
    }
    else if(rad == "BL")
    {
        Target.x = drone.drone_x - 2400;
        Target.y = drone.drone_y + 2400;
        // Avoid_Monster(drone, 2500, 7500);
    }
    else if(rad == "TR")
    {
        Target.x = drone.drone_x + 2400;
        Target.y = drone.drone_y - 2400;
        // Avoid_Monster(drone, 2500, 7500);
    }
    else if(rad == "TL")
    {
        Target.x = drone.drone_x - 2400;
        Target.y = drone.drone_x - 2400;
        // Avoid_Monster(drone, 2500, 7500);
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
    cerr << "RemainingFish = " << RemainingFish.size() << endl;
    cerr << "GlobalScan = " << GlobalScan << endl;
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

    // vector <int> RemainingFishType2;
    // cerr << "size = " << size1 << endl;
    // cerr << "GlobalScan = " << GlobalScan << endl;
    // cerr << "size RemainingFish  " << RemainingFish.size() << endl;
    // map<int, int>::iterator it = RemainingFish.begin();
    // for(; it != RemainingFish.end(); ++it)
    // {
    //     if(it->second == 2)
    //         RemainingFishType2.push_back(it->first);
    //         // size1++;
    // }
    // cerr << "RemainingFish =  " << RemainingFish.size() << endl;
    // || RadarType2.size() == 0 
    if(size1 > 0 || GlobalScan == 12)
    {
        cerr << "dkhal hna 1:      " << RadarType2.size() << endl;
        Target.y = 500;
        Target.x = drone.drone_x;
        // if(RadarType0.size() != 0 || RadarType1.size() != 0)
        drone.light = 0;
        // cerr << "faxe tla3 \n";
        // cerr << "drone.drone_y = " << drone.drone_y << "   Target.y " << Target.y << endl;
    }
    else if(size1 == 0 && drone.drone_y >= 6000)
    {
        cerr << "dkhal hna 2\n";
        // cerr << "here\n";
        rad = Calculate_Numbers_Of_Radar(drone, RadarType2, fish);
        cerr << "radar drone  " << drone.drone_id << "  is :  " << rad << endl;
        UseRadar(drone, rad, Target);
    }
    else if(Target.y == 3500 && size1 == 4)
    {
        cerr << "dkhal hna 3\n";
        if(drone.drone_y >= 3500)
        {
            Target.y = 500;
            Target.x = drone.drone_x;
        }
        else
            Target.y = 3500;
    }
    else
    {
        cerr << "dkhal hna 4\n";
        Target.y = 8100;
    }
    // cerr << "drone.drone_y = " << drone.drone_y << "   Target.y " << Target.y << endl;
    Avoid_Monster(drone, Target.x, Target.y);
}

void MoveDrone(My_drone drone, int &Check, vector<int> My_drone_scan, vector<Visible_creature> Visible_creature, int sep, vector<Fish> fish, \
    int &TmpSize, vector<int> foe_drone_scan, int GlobalScan, map<int, int> RemainingFish)
{
    cerr << "\n==========================================\n";
    cerr << "  x = " << drone.drone_x;
    cerr << "  y = " << drone.drone_y << endl;


    // string rad;
    if(drone.drone_id == 0 || drone.drone_id == 3)
    {
        // int c = 0;
        // rad = Calculate_Numbers_Of_Radar(drone.RadarDrone, fish, -1);
        // if(RadarType2.size() == 0 && drone.drone_y >= Target.y)
        //     Target.y = 3500;
        // for(size_t i=0; i<My_drone_scan.size(); i++)
        // {
        //     if(check_id(foe_drone_scan, My_drone_scan[i]) == -1)
        //     {
        //         cerr << "here drone 1" << endl;
        //         for(size_t j=0; j<Visible_creature.size(); j++)
        //         {
        //             if(Visible_creature[i].creature_id == My_drone_scan[i])
        //             {
        //                 drone.light = 1;
        //                 // Avoid_Monster(drone, Visible_creature[i].creature_x, Visible_creature[i].creature_y);
        //                 Avoid_Monster(drone, drone.drone_x + Visible_creature[i].creature_vx, drone.drone_y + Visible_creature[i].creature_vy);
        //                 c = 1;
        //                 break;
        //             }
        //         }
        //         break;
        //     }
        // }
        // if(c == 0)
        SepareteDrone(drone, My_drone_scan, fish, Target, GlobalScan, RemainingFish);
    }
    else
    {
        // int C = 0;
        // rad = Calculate_Numbers_Of_Radar(drone.RadarDrone, fish, 1);
        // if(RadarType2.size() == 0 && drone.drone_y >= Target.y)
        //     Target2.y = 3500;
        // for(size_t i=0; i<My_drone_scan.size(); i++)
        // {
        //     if(check_id(foe_drone_scan, My_drone_scan[i]) == -1)
        //     {
        //         cerr << "here drone 2" << endl;
        //         for(size_t j=0; j<Visible_creature.size(); j++)
        //         {
        //             if(Visible_creature[i].creature_id == My_drone_scan[i])
        //             {
        //                 Avoid_Monster(drone, Visible_creature[i].creature_x, Visible_creature[i].creature_y);
        //                 C = 1;
        //                 break;
        //             }
        //         }
        //         break;
        //     }
        // }
        // if(C == 0)
        SepareteDrone(drone, My_drone_scan, fish, Target2, GlobalScan, RemainingFish);
    }
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
    // cerr << "count Monster = " << Monsters.size();
    int Turn = 0;
    vector<int> My_drone1_scan;
	vector<int> My_drone2_scan;
    vector<int> foe_drone_scan;

    // vector<int> My_drone1_scanNew;
	// vector<int> My_drone2_scanNew;
    // game loop
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

        /**/

        // for(size_t i=0; i<My_drone1_scan.size(); i++)
        // {
        //     for(size_t j=0; j<My_drone1_scanNew.size(); j++)
        //     {
        //         if(My_drone1_scan[i] == My_drone1_scanNew[j] && my_drone[0].emergency == 0)
        //         {
        //             cerr << "here drone 1" << endl;
        //             My_drone1_scanNew.erase(My_drone1_scanNew.begin() + j);
        //         }
        //     }
        // }
        // for(size_t i=0; i<My_drone2_scan.size(); i++)
        // {
        //     for(size_t j=0; j<My_drone2_scanNew.size(); j++)
        //     {
        //         if(My_drone2_scan[i] == My_drone2_scanNew[j] && my_drone[1].emergency == 0)
        //         {
        //             cerr << "here drone 2" << endl;
        //             cerr << "before  " << My_drone2_scanNew.size() << endl;
        //             My_drone2_scanNew.erase(My_drone2_scanNew.begin() + j);
        //             cerr << "after   " << My_drone2_scanNew.size() << endl;
        //             cerr << "j= " << j << endl;
        //         }
        //     }
        // }
        /**/

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
        // cerr << "drone_scan_count.   " << drone_scan_count << endl;
        for (int i = 0; i < drone_scan_count; i++)
        {
            int drone_id;
            int creature_id;
            cin >> drone_id >> creature_id; cin.ignore();
            // hna kan3amro lkola drone lcreature liscanat
            // if(my_drone[0].drone_id == drone_id && check_id(My_drone1_scan, creature_id) == -1 && check_id(My_drone2_scan, creature_id) == -1)
            // {
			// 	My_drone1_scan.push_back(creature_id);
            // }
            // else if(my_drone[1].drone_id == drone_id && check_id(My_drone2_scan, creature_id) == -1 && check_id(My_drone1_scan, creature_id) == -1)
            // {
			// 	My_drone2_scan.push_back(creature_id);
            // }
            // else
            // {
            //     if(check_id(foe_drone_scan, creature_id) == -1)
            //         foe_drone_scan.push_back(creature_id);
            // }
            
            // if(my_drone[0].drone_id == drone_id && check_id(My_drone1_scanNew, creature_id) == -1 && check_id(My_drone2_scanNew, creature_id) == -1)
            // {
            //     My_drone1_scanNew.push_back(creature_id);
            // }
            // else if(my_drone[1].drone_id == drone_id && check_id(My_drone1_scanNew, creature_id) == -1 && check_id(My_drone2_scanNew, creature_id) == -1)
            // {
            //     My_drone2_scanNew.push_back(creature_id);
            // }


            if(my_drone[0].drone_id == drone_id)
            {
                My_drone1_scanNew.push_back(creature_id);
            }
            else if(my_drone[1].drone_id == drone_id)
            {
                My_drone2_scanNew.push_back(creature_id);
            }



            // if(my_drone[0].drone_id == drone_id)
            //     My_drone1_scanNew.push_back(creature_id);
            // else if(my_drone[1].drone_id == drone_id)
            //     My_drone2_scanNew.push_back(creature_id);
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

            // fill radar  the any drone .

            // if(my_drone[0].drone_id == drone_id && check_id(My_drone1_scan, creature_id) == -1 && check_id(My_drone2_scan, creature_id) == -1)
			// 	my_drone[0].RadarDrone.push_back(Radar(radar, drone_id, creature_id));
			// else if(my_drone[1].drone_id == drone_id && check_id(My_drone1_scan, creature_id) == -1 && check_id(My_drone2_scan, creature_id) == -1)
			// 	my_drone[1].RadarDrone.push_back(Radar(radar, drone_id, creature_id));

            if(check_id(My_drone1_scanNew, creature_id) != -1  || check_id(My_drone2_scanNew, creature_id) != -1 || check_id(Scan_Validated, creature_id) != -1)
            {
                continue;
            }

            if(my_drone[0].drone_id == drone_id)
				my_drone[0].RadarDrone.push_back(Radar(radar, drone_id, creature_id));
            else if(my_drone[1].drone_id == drone_id)
				my_drone[1].RadarDrone.push_back(Radar(radar, drone_id, creature_id));


            // int type;
            // if(radar_blip_count < 24)
            // {
            //     cerr << "here\n";
                // int type = -1;
                // for(size_t i=0; i<fish.size(); i++)
			    // {
				//     if(fish.at(i).creature_id == creature_id)
                //         type = fish.at(i).type;
                // }
                // if(type != -1)
                //     RemainingFish.insert({creature_id, type});
            // }
        }
        // RemainingFish.insert({1, 1});
        // cerr << "fish.size() " << fish.size() << endl;
        // cerr << "RemainingFish =  " << RemainingFish.size() << endl;
        
        int GlobalScan = My_drone1_scanNew.size() + My_drone2_scanNew.size() + Scan_Validated.size();
        for (int i = 0; i < my_drone_count; i++)
        {
            if(my_drone[i].drone_y >= 5600 && my_drone[i].drone_y <= 9000)
                my_drone[i].light = 1;
            if(Turn % 4  == 1 && my_drone[i].drone_y > 2000)
                my_drone[i].light = 1;
            if(my_drone[i].drone_y >= 1000 && my_drone[i].drone_y <= 1600)
                my_drone[i].light = 1;
            if(i == 0)
                MoveDrone(my_drone[i], CheckDrone1, My_drone1_scanNew, visible_creature, 0, fish, TmpSize1, foe_drone_scan, GlobalScan, RemainingFish);
            else
                MoveDrone(my_drone[i], CheckDrone2, My_drone2_scanNew, visible_creature, 1, fish, TmpSize2, foe_drone_scan, GlobalScan, RemainingFish);
        }
        Turn++;
    }
}