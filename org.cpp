
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;


string& Calculate_Numbers_Of_Radar(vector<Radar> RaV, )
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
    int check = 0;
    int checkX = 0;
    int CheckUp = 0;
    int FinalCheck = 0;
    int FirstCheck = 0;
    int creature_count;
    cin >> creature_count; cin.ignore();
    vector<Fish> FishV;
    vector<int> scan_id;
    for (int i = 0; i < creature_count; i++) {
        int creature_id;
        int color;
        int type;
        cin >> creature_id >> color >> type; cin.ignore();
        FishV.push_back(Fish(creature_id , color , type, -1 , -1));
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
        double     dist = 90000000;
        double     min = 0;
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
        int drone_id;
        int drone_x;
        int drone_y;
        int my_drone_x;
        int my_drone_y;
        for (int i = 0; i < my_drone_count; i++) {
            
            int emergency;
            int battery;
            cin >> drone_id >> drone_x >> drone_y >> emergency >> battery; cin.ignore();
            my_drone_x = drone_x;
            my_drone_y = drone_y;
        }
        int foe_drone_count;
        cin >> foe_drone_count; cin.ignore();
        for (int i = 0; i < foe_drone_count; i++) {
            int drone_id;
            int drone_x;
            int drone_y;
            int emergency;
            int battery;
            cin >> drone_id >> drone_x >> drone_y >> emergency >> battery; cin.ignore();
        }
        int drone_scan_count;
        cin >> drone_scan_count; cin.ignore();
        for (int i = 0; i < drone_scan_count; i++) {
            int drone_id;
            int creature_id;
            cin >> drone_id >> creature_id; cin.ignore();
        }
        int visible_creature_count;
        cin >> visible_creature_count; cin.ignore();

        int tmp_x = 4000;
        int tmp_y = 7000;
        int    id = 0;
        vector<int> visible_creatureID;
        visible_creatureID.reserve(visible_creature_count);
        for (int i = 0; i < visible_creature_count; i++) {
            int r = 0;

            int creature_id;
            int creature_x;
            int creature_y;
            int creature_vx;
            int creature_vy;
            cin >> creature_id >> creature_x >> creature_y >> creature_vx >> creature_vy; cin.ignore();

            visible_creatureID.push_back(creature_id);
        }
        int radar_blip_count;
        string radar;
        int stepSize = 40;
        cin >> radar_blip_count; cin.ignore();
        for (int i = 0; i < radar_blip_count; i++)
		{
            int drone_id;
            int creature_id;
            
            cin >> drone_id >> creature_id >> radar; cin.ignore();
        }
        visible_creatureID.clear();
        for (int i = 0; i < my_drone_count; i++) 
        {
            if (i == 1)
            {
                if((drone_x == 2000 && drone_y == 500) || FirstCheck == 1)
                {
                    if(check != 14)
                    {
                        if(FirstCheck == 0)
                            drone_x = 300;
                        if(CheckUp == 1)
                        {
                            cout << "MOVE " << drone_x << " " << drone_y - 1000 << " 1" << endl;
                        }
                        else
                            cout << "MOVE " << drone_x << " " << drone_y + 1000 << " 1" << endl;
                        check++;
                        FirstCheck = 1;
                    }
                    else if(check == 14 && checkX != 10)
                    {
                        cout << "MOVE " << drone_x + 1000 << " " << drone_y << " 1" << endl;
                        check = 0;
                        if(CheckUp == 0)
                            CheckUp = 1;
                        else
                            CheckUp = 0;
                        checkX++;
                    }
                    else
                        cout << "WAIT 0" << endl;
                    FirstCheck = 1;
                }
                else
                {
                    if(check != 14)
                    {
                        if(FirstCheck == 0)
                            drone_x = 10000;
                        if(CheckUp == 1)
                            cout << "MOVE " << drone_x << " " << drone_y - 1000 << " 1" << endl;
                        else
                            cout << "MOVE " << drone_x << " " << drone_y + 1000 << " 1" << endl;
                        check++;
                        FirstCheck = 1;
                    }
                    else if(check == 14 && checkX != 10)
                    {
                        cout << "MOVE " << drone_x - 1000 << " " << drone_y << " 1" << endl;
                        check = 0;
                        if(CheckUp == 0)
                            CheckUp = 1;
                        else
                            CheckUp = 0;
                        checkX++;
                    }
                }
            }
            else
            {
                cout << "MOVE " << drone_x << " " << drone_y << " 1" << endl;
            }
    }
}
}