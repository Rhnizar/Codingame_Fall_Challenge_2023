#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
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


/*calculat number of radar */

string Calculate_Numbers_Of_Radar(vector<Radar> RaV)
{
	int tl = 0, tr = 0, bl = 0, br = 0;
	for(size_t i = 0; i < RaV.size(); i++)
	{
		if(RaV.at(i).radar == "TL")
			tl++;
		else if(RaV.at(i).radar == "TR")
			tr++;
		else if(RaV.at(i).radar == "BL")
			bl++;
		else if(RaV.at(i).radar == "BR")
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
	return maxRadar;
}

/* Drone Movement */
int steps_x = 600, steps_y = 600;
void DroneMovement(My_drone drone, vector<int> My_drone_scan, int	&TmpSize)
{
	string rad = Calculate_Numbers_Of_Radar(drone.RadarDrone);
	if (My_drone_scan.size() > TmpSize + 2 && drone.drone_y > 500)
        cout << "MOVE " << drone.drone_x << " 500 0" << endl;
	else
    {
		if (drone.drone_y < 600)
            TmpSize = My_drone_scan.size();
		if (rad == "TL" )
        {
            // cerr << "TL" << endl;
            if (drone.drone_x - steps_x > 0 && drone.drone_y - steps_y > 0)
                cout << "MOVE " << drone.drone_x - steps_x << " " << drone.drone_y - steps_y << " " << drone.light << endl;
            else
                cout << "MOVE " << drone.drone_x << " 500 0" << endl;
        }
        else if(rad == "TR")
        {
            // cerr << "TR" << endl;
            if (drone.drone_x + steps_x < 9999 && drone.drone_y - steps_y > 0)
                cout << "MOVE " << drone.drone_x + steps_x << " " << drone.drone_y - steps_y << " " << drone.light << endl;
            else
                cout << "MOVE " << drone.drone_x << " 500 0" << endl;
		}
        else if(rad == "BL")
        {
            // cerr << "BL" << endl;
            if (drone.drone_x - steps_x > 0 && drone.drone_y + steps_y < 9999)
                cout << "MOVE " << drone.drone_x - steps_x << " " << drone.drone_y + steps_y << " " << drone.light << endl;
            else
                cout << "WAIT 0" << endl;
        }
        else if(rad == "BR")
        {
            // cerr << "BR" << endl;
            if (drone.drone_x + steps_x < 9999 && drone.drone_y + steps_y < 9999)
                cout << "MOVE " << drone.drone_x + steps_x << " " << drone.drone_y + steps_y << " " << drone.light << endl;
            else
                cout << "WAIT 0" << endl;
        }
	}
}

void LightOnOff(My_drone drone)
{
	if(drone.drone_y == 3750 || drone.drone_y == 6250 || drone.drone_y == 8200)
		drone.light = 1;
}

int main()
{
	int	TmpSize_drone1 = 0;
	int	TmpSize_drone2 = 0;
    int creature_count;
    cin >> creature_count; cin.ignore();
    vector<Fish> FishV;
	vector<Visible_creature> Visible_creatureV;
    vector<int> My_drone_scan;
	vector<int> My_drone1_scan;
	vector<int> My_drone2_scan;
	int TmpSizeDrone1;
	int TmpSizeDrone2;
    
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
        vector<My_drone> My_droneV;

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
        }
        int radar_blip_count;
        cin >> radar_blip_count; cin.ignore();
        for (int i = 0; i < radar_blip_count; i++)
		{
            int drone_id;
            int creature_id;
			string radar;
            
            cin >> drone_id >> creature_id >> radar; cin.ignore();
			
			if(My_droneV[0].drone_id == drone_id && check_id(My_drone1_scan, creature_id) == -1 && check_id(My_drone2_scan, creature_id) == -1)
				My_droneV[0].RadarDrone.push_back(Radar(radar, drone_id, creature_id));
			else if(My_droneV[1].drone_id == drone_id && check_id(My_drone1_scan, creature_id) == -1 && check_id(My_drone2_scan, creature_id) == -1)
				My_droneV[1].RadarDrone.push_back(Radar(radar, drone_id, creature_id));
			
        }
		LightOnOff(My_droneV[0]);
		LightOnOff(My_droneV[1]);
        for (int i = 0; i < my_drone_count; i++)
        {
            if(i == 0)
                DroneMovement(My_droneV[0], My_drone1_scan, TmpSize_drone1);
            else
                DroneMovement(My_droneV[1], My_drone2_scan, TmpSize_drone2);
        }
	}
}