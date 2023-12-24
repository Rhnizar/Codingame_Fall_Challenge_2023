/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Drone2Movement.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 17:45:57 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/12/23 12:26:08 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */







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
        int    x;
        int    y;
        Fish(int creature_id, int color, int type)
        {
            this->creature_id = creature_id;
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
		My_drone(int drone_id, int drone_x, int drone_y, int emergency, int battery)
		{
			this->drone_id = drone_id;
			this->drone_x = drone_x;
			this->drone_y = drone_y;
			this->emergency= emergency;
			this->battery = battery;
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

int	TmpSize = 0;
int steps_x = 1000, steps_y = 1000;

string DroneMovement(int i, vector<Radar> RadarV, vector<My_drone> My_droneV, vector<int> My_drone_scan)
{
    int light = 0;
	string rad = Calculate_Numbers_Of_Radar(RadarV);
    cerr << "      " << rad << endl;
    if (My_droneV.at(i).drone_y > 3000)
        light = 1;
    if (My_drone_scan.size() > TmpSize + 4 && My_droneV[i].drone_y > 500)
        cout << "MOVE " << My_droneV[i].drone_x << " 500 0" << endl;
    else
    {
        if (My_droneV[i].drone_y < 600)
            TmpSize = My_drone_scan.size();
        if (rad == "TL")
        {
            // cerr << "TL" << endl;
            if (My_droneV.at(i).drone_x - steps_x > 0 && My_droneV.at(i).drone_y - steps_y > 0)
                cout << "MOVE " << My_droneV.at(i).drone_x - steps_x << " " << My_droneV.at(i).drone_y - steps_y << " " << light << endl;
            else
                cout << "MOVE " << My_droneV[i].drone_x << " 500 0" << endl;
        }
        else if(rad == "TR")
        {
            // cerr << "TR" << endl;
            if (My_droneV.at(i).drone_x + steps_x < 9999 && My_droneV.at(i).drone_y - steps_y > 0)
                cout << "MOVE " << My_droneV.at(i).drone_x + steps_x << " " << My_droneV.at(i).drone_y - steps_y << " " << light << endl;
            else
                cout << "MOVE " << My_droneV[i].drone_x << " 500 0" << endl;
		}
        else if(rad == "BL")
        {
            // cerr << "BL" << endl;
            if (My_droneV.at(i).drone_x - steps_x > 0 && My_droneV.at(i).drone_y + steps_y < 9999)
                cout << "MOVE " << My_droneV.at(i).drone_x - steps_x << " " << My_droneV.at(i).drone_y + steps_y << " " << light << endl;
            else
                cout << "WAIT 0" << endl;
        }
        else if(rad == "BR")
        {
            // cerr << "BR" << endl;
            if (My_droneV.at(i).drone_x + steps_x < 9999 && My_droneV.at(i).drone_y + steps_y < 9999)
                cout << "MOVE " << My_droneV.at(i).drone_x + steps_x << " " << My_droneV.at(i).drone_y + steps_y << " " << light << endl;
            else
                cout << "WAIT 0" << endl;
        }
    }
    return rad;
}

int typeCount = 0;
int TypeFish(int id, vector<Visible_creature> Visible_creatureV)
{
	for(size_t i=0; i<Visible_creatureV.size())
}
void Drone2Movement(int i, vector<Radar> RadarV, vector<My_drone> My_droneV, vector<int> My_drone_scan, vector<Visible_creature> Visible_creatureV)
{
	int type = -1;
	for(size_t i=0; i<RadarV.size(); i++)
	{
		type = TypeFish(RadarV[i].creature_id, Visible_creatureV);
		if ()
	}
}

void Drone2Movement(int i, vector<My_drone> My_droneV)
{
	if(My_droneV.at(i).drone_y < 10000)
		cout << "MOVE " << My_droneV.at(i).drone_x, " " << 9999 << " 1" << endl;
}

int main()
{
    int check = 1;
    int TmpSize = 0;
    int CheckValidation = 0;
    int creature_count;
    cin >> creature_count; cin.ignore();
    vector<Fish> FishV;
	vector<Visible_creature> Visible_creatureV;
    vector<int> My_drone_scan;
    
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
            // cerr << "heeeeeere  " << creature_id << endl;
            // scan_id.push_back(creature_id);
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
			My_droneV.push_back(My_drone(drone_id, drone_x, drone_y, emergency, battery));
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

            // cerr << "id Salim. " << creature_id << "     drone id    " << drone_id << endl;
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
            if (check_id(My_drone_scan, creature_id) == -1)
            {
                My_drone_scan.push_back(creature_id);
            }
            // cerr << "id Me    " << creature_id << endl;
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
		vector<Radar> RadarDrone1;
        vector<Radar> RadarDrone2;
        // cerr << "      " << radar_blip_count << endl;
        for (int i = 0; i < radar_blip_count; i++)
		{
            int drone_id;
            int creature_id;
			string radar;
            
            cin >> drone_id >> creature_id >> radar; cin.ignore();

            if (check_id(My_drone_scan, creature_id) == -1 && drone_id == My_droneV[0].drone_id)
			    RadarDrone1.push_back(Radar(radar, drone_id, creature_id));
            else if (check_id(My_drone_scan, creature_id) == -1 && drone_id == My_droneV[1].drone_id)
                RadarDrone2.push_back(Radar(radar, drone_id, creature_id));
        }
		int light = 0;
        if (My_droneV.at(0).drone_y > 3000)
            light = 1;

        // for (Radar rd : RadarDrone1)
        //     cerr << " radar  :  " << rd.radar << "   rd.creature_id :  " << rd.creature_id <<  "   rd.drone_id:  " << rd.drone_id << endl;
        // cerr << "\n-------------------------------------\n";
        // for (Radar rd : RadarDrone2)
        //     cerr << " radar  :  " << rd.radar << "   rd.creature_id :  " << rd.creature_id <<  "   rd.drone_id:  " << rd.drone_id << endl;
        for (int i = 0; i < my_drone_count; i++)
        {
            if(i == 0)
                DroneMovement(i, RadarDrone1, My_droneV, My_drone_scan);
            else
                // cout << "MOVE 6000 500 0" << endl;
                // cout << "WAIT 0" << endl;
                DroneMovement(i, RadarDrone2, My_droneV, My_drone_scan);
        }
	}
}