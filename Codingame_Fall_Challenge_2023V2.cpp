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

/* Move Drone */

void DroneMovement(int i, vector<Radar> RadarV, vector<My_drone> My_droneV, vector<int> My_drone_scan)
{
	int light = 0;
	int	TmpSize = 0;
	int stepSizeY = 1000;
    int StepSizeX = 1000;
	string rad = Calculate_Numbers_Of_Radar(RadarV);
    if (My_droneV.at(i).drone_y > 3000)
        light = 1;
    cerr << My_drone_scan.size() << "  " << TmpSize << endl;
    if (My_drone_scan.size() > TmpSize + 2 && My_droneV[i].drone_y > 600)
        cout << "MOVE " << My_droneV[i].drone_x << " 500 0" << endl;
    else
    {
        if (My_droneV[i].drone_y < 600)
            TmpSize = My_drone_scan.size();
        if (rad == "TL")
        {
            cerr << "TL" << endl;
            if (My_droneV.at(i).drone_x - StepSizeX > 0 && My_droneV.at(i).drone_y - stepSizeY > 0)
                cout << "MOVE " << My_droneV.at(i).drone_x - StepSizeX << " " << My_droneV.at(i).drone_y - stepSizeY << " " << light << endl;
            else
                cout << "MOVE " << My_droneV[i].drone_x << " 500 0" << endl;
        }
        else if(rad == "TR")
        {
            cerr << "TR" << endl;
            if (My_droneV.at(i).drone_x + StepSizeX < 9999 && My_droneV.at(i).drone_y - stepSizeY > 0)
                cout << "MOVE " << My_droneV.at(i).drone_x + StepSizeX << " " << My_droneV.at(i).drone_y - stepSizeY << " " << light << endl;
            else
                cout << "MOVE " << My_droneV[i].drone_x << " 500 0" << endl;
		}
        else if(rad == "BL")
        {
            cerr << "BL" << endl;
            if (My_droneV.at(i).drone_x - StepSizeX > 0 && My_droneV.at(i).drone_y + stepSizeY < 9999)
                cout << "MOVE " << My_droneV.at(i).drone_x - StepSizeX << " " << My_droneV.at(i).drone_y + stepSizeY << " " << light << endl;
            else
                cout << "WAIT 0" << endl;
        }
        else if(rad == "BR")
        {
            cerr << "BR" << endl;
            if (My_droneV.at(i).drone_x + StepSizeX < 9999 && My_droneV.at(i).drone_y + stepSizeY < 9999)
                cout << "MOVE " << My_droneV.at(i).drone_x + StepSizeX << " " << My_droneV.at(i).drone_y + stepSizeY << " " << light << endl;
            else
                cout << "WAIT 0" << endl;
        }
    }
}

int main()
{
    vector<Point> points;
    points.push_back(Point(2000, 500));
    points.push_back(Point(2000, 8000));
    points.push_back(Point(8000, 500));
    points.push_back(Point(8000, 7500));

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
            // cerr << "heeeeeere\n";
            int creature_id;
            cin >> creature_id; cin.ignore();
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

            // cerr << "id Salim. " << creature_id << endl;
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
		vector<Radar> RadarV;
        cerr << "      " << radar_blip_count << endl;
        for (int i = 0; i < radar_blip_count; i++)
		{
            int drone_id;
            int creature_id;
			string radar;
            
            cin >> drone_id >> creature_id >> radar; cin.ignore();

            if (check_id(My_drone_scan, creature_id) == -1)
			    RadarV.push_back(Radar(radar, drone_id, creature_id));
        }
		int light = 0;
        if (My_droneV.at(0).drone_y > 3000)
            light = 1;
        int stepSize = 1000;
        int Slow_StepSize = 1000;

        for (Radar rd : RadarV)
            cerr << " radar  :  " << rd.radar << "   rd.creature_id :  " << rd.creature_id <<  "   rd.drone_id:  " << rd.drone_id << endl;
        for (int i = 0; i < my_drone_count; i++) 
        {
            if(i == 0)
            {
			    string rad = Calculate_Numbers_Of_Radar(RadarV);
                if (My_droneV.at(i).drone_y > 3000)
                    light = 1;
                cerr << My_drone_scan.size() << "  " << TmpSize << endl;
                if (My_drone_scan.size() > TmpSize + 2 && My_droneV[i].drone_y > 600)
                    cout << "MOVE " << My_droneV[i].drone_x << " 500 0" << endl;
                else
                {
                    if (My_droneV[i].drone_y < 600)
                        TmpSize = My_drone_scan.size();
                    if (rad == "TL")
                    {
                        cerr << "TL" << endl;
                        if (My_droneV.at(i).drone_x - Slow_StepSize > 0 && My_droneV.at(i).drone_y - stepSize > 0)
                            cout << "MOVE " << My_droneV.at(i).drone_x - Slow_StepSize << " " << My_droneV.at(i).drone_y - stepSize << " " << light << endl;
                        else
                            cout << "MOVE " << My_droneV[i].drone_x << " 500 0" << endl;
                            // cout << "WAIT 0" << endl;
                    }
                    else if(rad == "TR")
                    {
                        cerr << "TR" << endl;
                        if (My_droneV.at(i).drone_x + Slow_StepSize < 9999 && My_droneV.at(i).drone_y - stepSize > 0)
                            cout << "MOVE " << My_droneV.at(i).drone_x + Slow_StepSize << " " << My_droneV.at(i).drone_y - stepSize << " " << light << endl;
                        else
                            cout << "MOVE " << My_droneV[i].drone_x << " 500 0" << endl;
                            // cout << "WAIT 0" << endl;
                    }

                    else if(rad == "BL")
                    {
                        cerr << "BL" << endl;
                        if (My_droneV.at(i).drone_x - Slow_StepSize > 0 && My_droneV.at(i).drone_y + stepSize < 9999)
                            cout << "MOVE " << My_droneV.at(i).drone_x - Slow_StepSize << " " << My_droneV.at(i).drone_y + stepSize << " " << light << endl;
                        else
                            cout << "WAIT 0" << endl;
                            // cout << "MOVE " << My_droneV[i].drone_x << " 500 0" << endl;
                    }
                    else if(rad == "BR")
                    {
                        cerr << "BR" << endl;
                        if (My_droneV.at(i).drone_x + Slow_StepSize < 9999 && My_droneV.at(i).drone_y + stepSize < 9999)
                            cout << "MOVE " << My_droneV.at(i).drone_x + Slow_StepSize << " " << My_droneV.at(i).drone_y + stepSize << " " << light << endl;
                        else
                            cout << "WAIT 0" << endl;
                            // cout << "MOVE " << My_droneV[i].drone_x << " 500 0" << endl;
                    }
                }
            }
            else
            {
                cout << "MOVE 6000 500 0" << endl;
            }

        }
        // CheckValidation++;
	}
}