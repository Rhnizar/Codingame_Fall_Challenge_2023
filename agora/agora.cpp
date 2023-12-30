#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>
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



/* Drone Movement */

// int steps_x = 600, steps_y = 600;
int CountType2 = 0;
int CountType22 = 0;
int r = 0;
int Light = 0;

int CheckType(int creature_id, vector<Visible_creature> Visible_creatureV)
{
    for(size_t i=0; i<Visible_creatureV.size(); i++)
    {
        if(Visible_creatureV[i].creature_id == creature_id && Visible_creatureV[i].type == 2)
            return 1;
    }
    return 0;
}

vector<int> allreadyCheckId;

void MoveDrone(My_drone drone, vector<int> My_drone_scan, int &TmpSize, int sep, vector<Visible_creature> Visible_creatureV, int CheckType2, int GSC, int SizeRemainingFish, int &CheckMon)
{
    cerr << "drone.Monsters.size()      " << drone.Monsters.size() << "       drone.drone_id      " << drone.drone_id << endl;
    if(drone.Monsters.size() > 0 || CheckMon == 1)
    {
        CheckMon = 1;
        drone.light = 0;
        if(drone.drone_y < drone.Monsters[0].creature_y)
            cout << "MOVE " << drone.drone_x << " 500 " << drone.light << endl;
        else
            cout << "MOVE " << drone.drone_x << " 9999 " << drone.light << endl;
        if(drone.drone_y < 600)
            CheckMon = 0;
    }
    else
    {
        int SRF = 0;
        int si;
        for(size_t i=0;i<My_drone_scan.size();i++)
        {
            if(CheckType(My_drone_scan[i], Visible_creatureV) == 1 && find(allreadyCheckId.begin(), allreadyCheckId.end(), My_drone_scan[i]) == allreadyCheckId.end())
            {
                allreadyCheckId.push_back(My_drone_scan[i]);
                CountType2++;
            }
        }
        // if(CountType2 == CheckType2)
        //     si = 0;
        
        // cerr << "\n--------------------- " << si << "-------------------------\n";
        // cerr << "CountType2   " << CountType2 << "   CheckType2    " << CheckType2 << endl;
        // cerr << "GSC   " << GSC << "   SizeRemainingFish    " << SizeRemainingFish << endl;

        // cerr << "Light  " << Light  << " is " << drone.light << endl;
        if(SizeRemainingFish > 0)
            SRF = 12 - SizeRemainingFish;
        if(SRF + GSC < 8)
            si = 1;
        else
            si = 0;
        if((CountType2 == CheckType2 && drone.drone_y > 500) || (My_drone_scan.size() > TmpSize + 7 && drone.drone_y > 500)
        || (GSC > SizeRemainingFish && SizeRemainingFish > 0 && drone.drone_y > 500))
        {
            cout << "MOVE " << drone.drone_x << " 500 " << drone.light << endl;
            CountType22 = -1;
        }
        else
        {
            std::uniform_int_distribution<int> distributionX;
            std::uniform_int_distribution<int> distributionY;
            
            if (drone.drone_y < 600)
            {
                if(CountType2 == CheckType2)
                {
                    if(r % 2 == 1)
                    {
                        cerr << "Here\n";
                        CountType2 = 0;
                        Light = -1;
                    }
                    r++;
                }
                else
                    TmpSize = My_drone_scan.size();
            }
            random_device rd;
            mt19937 gen(rd());
            // Generate random x and y coordinates for the player within the map
            if(sep == 0)
                distributionX = std::uniform_int_distribution<int>(0, 4000);
            else
                distributionX = std::uniform_int_distribution<int>(6000, 9000);
            if(CountType22 != -1)
                distributionY = std::uniform_int_distribution<int>(7500, 9000);
            else
                distributionY = std::uniform_int_distribution<int>(3500, 7500);
            int playerX = distributionX(gen);
            int playerY = distributionY(gen);
            cout << "MOVE " << playerX << " " << playerY << " " << drone.light << endl;
        }
    }
}

void LightOnOff(My_drone &drone, int PosLightOn)
{
	if(drone.drone_y > PosLightOn)
		drone.light = 1;
}

int main()
{
    int GlobalScanCount= 0;
	int	TmpSize_drone1 = 0;
	int	TmpSize_drone2 = 0;
    int CheckMonD1 = 0;
    int CheckMonD2 = 0;
    int creature_count;
    cin >> creature_count; cin.ignore();
    vector<Fish> FishV;
	vector<Visible_creature> Visible_creatureV;
    vector<int> My_drone_scan;
	vector<int> My_drone1_scan;
	vector<int> My_drone2_scan;

	// int TmpSizeDrone1;
	// int TmpSizeDrone2;
    
    for (int i = 0; i < creature_count; i++)
	{
        
        int creature_id;
        int color;
        int type;
        cin >> creature_id >> color >> type; cin.ignore();
        FishV.push_back(Fish(creature_id , color , type));
    }

    // game loop

    while (1)
	{
        
        int CheckType2 = 4;
        vector<My_drone> My_droneV;
        // vector<int> RemainingFish;
        map<int, int> RemainingFish;

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
        for (int i = 0; i < foe_scan_count; i++)
		{
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
			My_droneV.push_back(My_drone(drone_id, drone_x, drone_y, emergency, battery, 0));
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
			if(My_droneV[0].drone_id == drone_id && check_id(My_drone1_scan, creature_id) == -1 && check_id(My_drone2_scan, creature_id) == -1)
				My_drone1_scan.push_back(creature_id);
			else if(My_droneV[1].drone_id == drone_id && check_id(My_drone2_scan, creature_id) == -1 && check_id(My_drone1_scan, creature_id) == -1)
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
			for(size_t i=0; i<FishV.size(); i++)
			{
				if(FishV.at(i).creature_id == creature_id)
				{
					color = FishV.at(i).color;
					type = FishV.at(i).type;
					break;
				}
			}
			Visible_creatureV.push_back(Visible_creature(creature_id, creature_x, creature_y, creature_vx, creature_vy, color, type));
            // if(type == -1)
            // {
                for(size_t i = 0; i<My_droneV.size(); i++)
                {
                    if(distance(My_droneV[i].drone_x, My_droneV[i].drone_y, creature_x, creature_y) < 2000 && type == -1)
                        My_droneV[i].Monsters.push_back(Visible_creature(creature_id, creature_x, creature_y, creature_vx, creature_vy, -1, -1));
                }
            // }
        }
        int radar_blip_count;
        cin >> radar_blip_count; cin.ignore();
        for (int i = 0; i < radar_blip_count; i++)
		{
            int drone_id;
            int creature_id;
            int type;
			string radar;
            
            cin >> drone_id >> creature_id >> radar; cin.ignore();
			
			if(My_droneV[0].drone_id == drone_id && check_id(My_drone1_scan, creature_id) == -1 && check_id(My_drone2_scan, creature_id) == -1)
				My_droneV[0].RadarDrone.push_back(Radar(radar, drone_id, creature_id));
			else if(My_droneV[1].drone_id == drone_id && check_id(My_drone1_scan, creature_id) == -1 && check_id(My_drone2_scan, creature_id) == -1)
				My_droneV[1].RadarDrone.push_back(Radar(radar, drone_id, creature_id));
			
            
            if(radar_blip_count < 24)
            {
                CheckType2 = 0;
                for(size_t i=0; i<FishV.size(); i++)
			    {
				    if(FishV.at(i).creature_id == creature_id)
                        type = FishV.at(i).type;
                }
                RemainingFish.insert({creature_id, type});
            }
        }
        map<int, int>::iterator it = RemainingFish.begin();
        for(; it != RemainingFish.end(); ++it)
        {
            if(it->second == 2)
                CheckType2++;
            // cerr << "Remaining Fish id   " << it->first << "   Remaining Fish type   " << it->second << endl;
        }
        // cerr << "\n------------------   " << CheckType2 << "     ------------------------\n";
        if(Light != -1)
        {
		    LightOnOff(My_droneV[0], 7000);
		    LightOnOff(My_droneV[1], 7000);
        }
        else
        {
            LightOnOff(My_droneV[0], 3500);
		    LightOnOff(My_droneV[1], 3500);
        }
        GlobalScanCount = My_drone1_scan.size() + My_drone2_scan.size();
        // cerr << "global Scan " << GlobalScanCount << endl;
        for (int i = 0; i < my_drone_count; i++)
        {
            if(i == 0)
                MoveDrone(My_droneV[0], My_drone1_scan, TmpSize_drone1, 0, Visible_creatureV, CheckType2, GlobalScanCount, RemainingFish.size(), CheckMonD1);
            else
                MoveDrone(My_droneV[1], My_drone2_scan, TmpSize_drone2, 1, Visible_creatureV, CheckType2, GlobalScanCount, RemainingFish.size(), CheckMonD2);
        }
	}
}
