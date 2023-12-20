/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Codingame_Fall_Challenge_2023.cpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:05:34 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/12/20 13:03:07 by rrhnizar         ###   ########.fr       */
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


int main()
{
    int creature_count;
    cin >> creature_count; cin.ignore();
    vector<Fish> FishV;
	vector<My_drone> My_droneV;
	vector<Visible_creature> Visible_creatureV;
    vector<int> scan_id;
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
            scan_id.push_back(creature_id);
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
        }
        int visible_creature_count;
        cin >> visible_creature_count; cin.ignore();

        for (int i = 0; i < visible_creature_count; i++)
		{
            int r = 0;

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
        int stepSize = 40;
        cin >> radar_blip_count; cin.ignore();
		vector<Radar> RadarV;
        for (int i = 0; i < radar_blip_count; i++)
		{
            int drone_id;
            int creature_id;
			string radar;
            
            cin >> drone_id >> creature_id >> radar; cin.ignore();
			RadarV.push_back(Radar(radar, drone_id, creature_id));
        }
		
        for (int i = 0; i < my_drone_count; i++) 
        {
			string rad = Calculate_Numbers_Of_Radar(RadarV);
			cout << "MOVE 500 8000" << endl;
			cout << "MOVE 8000 8000" << endl;
    	}
	}
}