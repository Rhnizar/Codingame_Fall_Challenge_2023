// #include <iostream>
// #include <string>
// #include <vector>
// #include <algorithm>
// #include <math.h>

// using namespace std;

// /**
//  * Score points by scanning valuable fish faster than your opponent.
//  **/

// // calc distance 
//     // prioritize 
//          // if not scanned by opponent
         

//          // if u have more entities different color
//          // same color 

// double distance(int x1, int y1, int x2, int y2) 
// {
//     double deltaX = x2 - x1;
//     double deltaY = y2 - y1;

//     // Use the Pythagorean theorem to calculate the distance
//     double distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

//     return distance;
// }

// int check_id(vector<int> VId, int IdCheck)
// {
//     for(size_t i=0; i<VId.size(); i++)
//     {
//         cerr << "Check      " << " VId  " << VId.at(i) << "  IdCheck.  " << IdCheck << endl;
//         if(VId.at(i) == IdCheck)
//         {
//             cerr << "\n ----------------------------- \n";
//             return IdCheck;
//         }
//     }
//     return -1;
// }

// class Fish
// {
//     public :
//         int creature_id;
//         int color;
//         int type;
//         int    x;
//         int    y;
//         Fish(int creature_idd, int coloer, int typee, int x , int y)
//         {
//             creature_id = creature_idd;
//             color = coloer;
//             type = typee;
//             this->x = x;
//             this->y = y;
//         }
// };      

// int main()
// {
//     int check = 0;
//     int checkX = 0;
//     int CheckUp = 0;
//     int FinalCheck = 0;
//     int FirstCheck = 0;
//     int creature_count;
//     cin >> creature_count; cin.ignore();
//     vector<Fish> v;
//     vector<int> scan_id;
//     for (int i = 0; i < creature_count; i++) {
//         int creature_id;
//         int color;
//         int type;
//         cin >> creature_id >> color >> type; cin.ignore();
//         v.push_back(Fish(creature_id , color , type, -1 , -1));
//     }

//     // game loop
//     while (1) {
//         int my_score;
//         cin >> my_score; cin.ignore();
//         int foe_score;
//         cin >> foe_score; cin.ignore();
//         int my_scan_count;
//         cin >> my_scan_count; cin.ignore();
//         double     dist = 90000000;
//         double     min = 0;
//         // cerr << "===>. " << my_scan_count << endl;
//         for (int i = 0; i < my_scan_count; i++) {
//             int creature_id;
//             cin >> creature_id; cin.ignore();
//             scan_id.push_back(creature_id);
//         }
        
        
//         int foe_scan_count;
//         cin >> foe_scan_count; cin.ignore();
//         for (int i = 0; i < foe_scan_count; i++) {
//             int creature_id;
//             cin >> creature_id; cin.ignore();
//         }
//         int my_drone_count;
//         cin >> my_drone_count; cin.ignore();
//         int drone_id;
//         int drone_x;
//         int drone_y;
//         int my_drone_x;
//         int my_drone_y;
//         for (int i = 0; i < my_drone_count; i++) {
            
//             int emergency;
//             int battery;
//             cin >> drone_id >> drone_x >> drone_y >> emergency >> battery; cin.ignore();
//             my_drone_x = drone_x;
//             my_drone_y = drone_y;
//         }
//         int foe_drone_count;
//         cin >> foe_drone_count; cin.ignore();
//         for (int i = 0; i < foe_drone_count; i++) {
//             int drone_id;
//             int drone_x;
//             int drone_y;
//             int emergency;
//             int battery;
//             cin >> drone_id >> drone_x >> drone_y >> emergency >> battery; cin.ignore();
//         }
//         int drone_scan_count;
//         cin >> drone_scan_count; cin.ignore();
//         for (int i = 0; i < drone_scan_count; i++) {
//             int drone_id;
//             int creature_id;
//             cin >> drone_id >> creature_id; cin.ignore();
//         }
//         int visible_creature_count;
//         cin >> visible_creature_count; cin.ignore();

//         int tmp_x = 4000;
//         int tmp_y = 7000;
//         int    id = 0;
//         vector<int> visible_creatureID;
//         visible_creatureID.reserve(visible_creature_count);
//         // cerr << "     VCC.   " << visible_creature_count << endl;
//         for (int i = 0; i < visible_creature_count; i++) {
//             int r = 0;

//             int creature_id;
//             int creature_x;
//             int creature_y;
//             int creature_vx;
//             int creature_vy;
//             cin >> creature_id >> creature_x >> creature_y >> creature_vx >> creature_vy; cin.ignore();

//             visible_creatureID.push_back(creature_id);
//             // v[i].x = creature_x;
//             // v[i].y = creature_y;
//             // cerr << "i =   " << i << "   creature_id   " << creature_id << endl;
//             // min = distance(drone_x, drone_y, v[i].x, v[i].y);
//             // if (check_id(scan_id, creature_id) == 0 && min < dist)
//             // {
//             //     dist = min;
//             //     id = creature_id;
//             //     tmp_x = v[i].x;
//             //     tmp_y = v[i].y;
//             // }
//         }
//         // cerr << " VC.  " << visible_creature_count << "    C   " << creature_count << "  size  creature id "  << visible_creatureID.size() << endl;
//         int radar_blip_count;
//         string radar;
//         int stepSize = 40;
//         cin >> radar_blip_count; cin.ignore();
//         cerr << "radar_blip_count               " << radar_blip_count << endl;
//         for (int i = 0; i < radar_blip_count; i++) {
//             int drone_id;
//             int creature_id;
            
//             cin >> drone_id >> creature_id >> radar; cin.ignore();

//             cerr << "drone id.     " << drone_id << "          creature_id             " << creature_id  << "      radar:      " << radar << endl;
//         }
//         visible_creatureID.clear();
//         for (int i = 0; i < my_drone_count; i++) 
//         {
//             if (i == 1)
//             {
//                 if(drone_x == 2000 && drone_y == 500 || FirstCheck == 1)
//                 {
//                     if(check != 14)
//                     {
//                         if(FirstCheck == 0)
//                             drone_x = 300;
//                         if(CheckUp == 1)
//                         {
//                             cout << "MOVE " << drone_x << " " << drone_y - 1000 << " 1" << endl;
//                         }
//                         else
//                             cout << "MOVE " << drone_x << " " << drone_y + 1000 << " 1" << endl;
//                         check++;
//                         FirstCheck = 1;
//                     }
//                     else if(check == 14 && checkX != 10)
//                     {
//                         cout << "MOVE " << drone_x + 1000 << " " << drone_y << " 1" << endl;
//                         check = 0;
//                         if(CheckUp == 0)
//                             CheckUp = 1;
//                         else
//                             CheckUp = 0;
//                         checkX++;
//                     }
//                     else
//                         cout << "WAIT 0" << endl;
//                     FirstCheck = 1;
//                 }
//                 else
//                 {
//                     if(check != 14)
//                     {
//                         if(FirstCheck == 0)
//                             drone_x = 10000;
//                         if(CheckUp == 1)
//                             cout << "MOVE " << drone_x << " " << drone_y - 1000 << " 1" << endl;
//                         else
//                             cout << "MOVE " << drone_x << " " << drone_y + 1000 << " 1" << endl;
//                         check++;
//                         FirstCheck = 1;
//                     }
//                     else if(check == 14 && checkX != 10)
//                     {
//                         cout << "MOVE " << drone_x - 1000 << " " << drone_y << " 1" << endl;
//                         check = 0;
//                         if(CheckUp == 0)
//                             CheckUp = 1;
//                         else
//                             CheckUp = 0;
//                         checkX++;
//                     }
//                 }
//             }
//             else
//             {
//                 cout << "MOVE " << drone_x << " " << drone_y << " 1" << endl;
//             }
//             // if(drone_x == 3333 && drone_y == 500 || FirstCheck == 1)
//             // {
//             //     if(check != 15)
//             //     {
//             //         if(FirstCheck == 0)
//             //             drone_x = 300;
//             //         if(CheckUp == 1)
//             //         {
//             //             cout << "MOVE " << drone_x << " " << drone_y - 1000 << " 1" << endl;
//             //         }
//             //         else
//             //             cout << "MOVE " << drone_x << " " << drone_y + 1000 << " 1" << endl;
//             //         check++;
//             //         FirstCheck = 1;
//             //     }
//             //     else if(check == 15 && checkX != 10)
//             //     {
//             //         cout << "MOVE " << drone_x + 1000 << " " << drone_y << " 1" << endl;
//             //         check = 0;
//             //         if(CheckUp == 0)
//             //             CheckUp = 1;
//             //         else
//             //             CheckUp = 0;
//             //         checkX++;
//             //     }
//             //     else
//             //         cout << "WAIT 0" << endl;
//             //     FirstCheck = 1;
//             // }
//             // else
//             // {
//             //     if(check != 15)
//             //     {
//             //         if(FirstCheck == 0)
//             //             drone_x = 10000;
//             //         if(CheckUp == 1)
//             //             cout << "MOVE " << drone_x << " " << drone_y - 1000 << " 1" << endl;
//             //         else
//             //             cout << "MOVE " << drone_x << " " << drone_y + 1000 << " 1" << endl;
//             //         check++;
//             //         FirstCheck = 1;
//             //     }
//             //     else if(check == 15 && checkX != 10)
//             //     {
//             //         cout << "MOVE " << drone_x - 1000 << " " << drone_y << " 1" << endl;
//             //         check = 0;
//             //         if(CheckUp == 0)
//             //             CheckUp = 1;
//             //         else
//             //             CheckUp = 0;
//             //         checkX++;
//             //     }
//             // }
//             //     else
//             //         cout << "WAIT 0" << endl;
//             //     FirstCheck = 2;
//             // }
//     }
// }
// }












/*--------------------------------------------------------------------------*/

// #include <iostream>
// #include <string>
// #include <vector>
// #include <algorithm>
// #include <math.h>
// #include <map>

// using namespace std;

// /**
//  * Score points by scanning valuable fish faster than your opponent.
//  **/



// double distance(int x1, int y1, int x2, int y2) 
// {
//     double deltaX = x2 - x1;
//     double deltaY = y2 - y1;
//     double distance = sqrt(deltaX * deltaX + deltaY * deltaY);
//     return distance;
// }

// int check_id(vector<int> VId, int IdCheck)
// {
//     for(size_t i=0; i<VId.size(); i++)
//     {
//         if(VId.at(i) == IdCheck)
//             return IdCheck;
//     }
//     return -1;
// }

// class Fish
// {
//     public :
//         int creature_id;
//         int color;
//         int type;
//         Fish(int creature_id, int color, int type)
//         {
//             this->creature_id = creature_id;
//             this->color = color;
//             this->type = type;
//         }
// };

// class My_drone
// {
// 	public:
// 		int drone_id;
//         int drone_x;
//         int drone_y;
// 		int emergency;
//         int battery;
// 		My_drone(int drone_id, int drone_x, int drone_y, int emergency, int battery)
// 		{
// 			this->drone_id = drone_id;
// 			this->drone_x = drone_x;
// 			this->drone_y = drone_y;
// 			this->emergency= emergency;
// 			this->battery = battery;
// 		}
// };

// class Visible_creature
// {
// 	public:
// 		int creature_id;
//         int creature_x;
//         int creature_y;  
//         int creature_vx;
//         int creature_vy;

// 		int color;
//         int type;
// 	Visible_creature(int creature_id, int creature_x, int creature_y, int creature_vx, int creature_vy, int color, int type)
// 	{
// 		this->creature_id = creature_id;
// 		this->creature_x = creature_x;
// 		this->creature_y = creature_y;
// 		this->creature_vx = creature_vx;
// 		this->creature_vy = creature_vy;

// 		this->color = color;
// 		this->type = type;
// 	}
// };

// class Radar
// {
// 	public:
// 		string radar;
// 		int drone_id;
//         int creature_id;
// 	Radar(string radar, int drone_id, int creature_id)
// 	{
// 		this->radar = radar;
// 		this->drone_id = drone_id;
// 		this->creature_id = creature_id;
// 	}
// };


// /*calculat number of radar */

// string Calculate_Numbers_Of_Radar(vector<Radar> RaV)
// {
// 	int tl = 0, tr = 0, bl = 0, br = 0;
// 	for(size_t i = 0; i < RaV.size(); i++)
// 	{
// 		if(RaV.at(i).radar == "TL")
// 			tl++;
// 		else if(RaV.at(i).radar == "TR")
// 			tr++;
// 		else if(RaV.at(i).radar == "BL")
// 			bl++;
// 		else if(RaV.at(i).radar == "BR")
// 			br++;
// 	}
// 	int maxCount = tl;
// 	std::string maxRadar = "TL";

// 	if (tr > maxCount)
// 	{
// 	    maxCount = tr;
// 	    maxRadar = "TR";
// 	}

// 	if (bl > maxCount)
// 	{
// 	    maxCount = bl;
// 	    maxRadar = "BL";
// 	}

// 	if (br > maxCount)
// 	{
// 	    maxCount = br;
// 	    maxRadar = "BR";
// 	}
// 	return maxRadar;
// }

// /* Drone Movement */

// int	TmpSize = 0;
// int steps_x = 600, steps_y = 600;

// string DroneMovement(int i, vector<Radar> RadarV, vector<My_drone> My_droneV, vector<int> My_drone_scan)
// {
//     int light = 0;
// 	string rad = Calculate_Numbers_Of_Radar(RadarV);
//     cerr << "      " << rad << endl;
//     if (My_droneV.at(i).drone_y > 3000)
//         light = 1;
//     if (My_drone_scan.size() > TmpSize + 2 && My_droneV[i].drone_y > 500)
//         cout << "MOVE " << My_droneV[i].drone_x << " 500 0" << endl;
//     else
//     {
//         if (My_droneV[i].drone_y < 600)
//             TmpSize = My_drone_scan.size();
//         if (rad == "TL")
//         {
//             // cerr << "TL" << endl;
//             if (My_droneV.at(i).drone_x - steps_x > 0 && My_droneV.at(i).drone_y - steps_y > 0)
//                 cout << "MOVE " << My_droneV.at(i).drone_x - steps_x << " " << My_droneV.at(i).drone_y - steps_y << " " << light << endl;
//             else
//                 cout << "MOVE " << My_droneV[i].drone_x << " 500 0" << endl;
//         }
//         else if(rad == "TR")
//         {
//             // cerr << "TR" << endl;
//             if (My_droneV.at(i).drone_x + steps_x < 9999 && My_droneV.at(i).drone_y - steps_y > 0)
//                 cout << "MOVE " << My_droneV.at(i).drone_x + steps_x << " " << My_droneV.at(i).drone_y - steps_y << " " << light << endl;
//             else
//                 cout << "MOVE " << My_droneV[i].drone_x << " 500 0" << endl;
// 		}
//         else if(rad == "BL")
//         {
//             // cerr << "BL" << endl;
//             if (My_droneV.at(i).drone_x - steps_x > 0 && My_droneV.at(i).drone_y + steps_y < 9999)
//                 cout << "MOVE " << My_droneV.at(i).drone_x - steps_x << " " << My_droneV.at(i).drone_y + steps_y << " " << light << endl;
//             else
//                 cout << "WAIT 0" << endl;
//         }
//         else if(rad == "BR")
//         {
//             // cerr << "BR" << endl;
//             if (My_droneV.at(i).drone_x + steps_x < 9999 && My_droneV.at(i).drone_y + steps_y < 9999)
//                 cout << "MOVE " << My_droneV.at(i).drone_x + steps_x << " " << My_droneV.at(i).drone_y + steps_y << " " << light << endl;
//             else
//                 cout << "WAIT 0" << endl;
//         }
//     }
//     return rad;
// }

// int check = 0;
// void Drone2Movement(int i, vector<My_drone> My_droneV)
// {
// 	if(My_droneV.at(i).drone_y != 8500 && check == 0)
//     {
// 		cout << "MOVE " << 5000 << " " << 8500 << " 1" << endl;
//     }
//     else if(My_droneV.at(i).drone_y != 8500 && check == 2)
// 		cout << "MOVE " << 8000 << " " << 8500 << " 1" << endl;
//     else
//     {
//         check = 1;
//         cout << "MOVE " << 500 << " 500 0" << endl;
//         if (My_droneV[i].drone_y == 500)
//             check++;
//     }
// }

// int check2 = 0;
// void Drone3Movement(int i, vector<My_drone> My_droneV)
// {
// 	if(My_droneV.at(i).drone_y != 8500 && check2 == 0)
// 		cout << "MOVE " << 2100 << " " << 8500 << " 1" << endl;
//     else if(My_droneV.at(i).drone_y != 6500 && check2 == 2)
// 		cout << "MOVE " << 2100 << " " << 6500 << " 1" << endl;
//     else
//     {
//         check2 = 1;
//         cout << "MOVE " << My_droneV[i].drone_x << " 500 0" << endl;
//         if (My_droneV[i].drone_y == 500)
//             check2++;
//     }
// }

// int main()
// {
//     int check = 1;
//     int TmpSize = 0;
//     int CheckValidation = 0;
//     int creature_count;
//     cin >> creature_count; cin.ignore();
//     vector<Fish> FishV;
// 	vector<Visible_creature> Visible_creatureV;
//     vector<int> My_drone_scan;
    
//     for (int i = 0; i < creature_count; i++)
// 	{
//         int creature_id;
//         int color;
//         int type;
//         cin >> creature_id >> color >> type; cin.ignore();
//         FishV.push_back(Fish(creature_id , color , type));
//     }

//     // game loop

//     while (1) 
// 	{
//         vector<My_drone> My_droneV;
//         int my_score;
//         cin >> my_score; cin.ignore();
//         int foe_score;
//         cin >> foe_score; cin.ignore();
//         int my_scan_count;
//         cin >> my_scan_count; cin.ignore();
//         for (int i = 0; i < my_scan_count; i++)
// 		{
//             int creature_id;
//             cin >> creature_id; cin.ignore();
//             cerr << "heeeeeere  " << creature_id << endl;
//             // scan_id.push_back(creature_id);
//         }
        
        
//         int foe_scan_count;
//         cin >> foe_scan_count; cin.ignore();
//         for (int i = 0; i < foe_scan_count; i++)
// 		{
//             int creature_id;
//             cin >> creature_id; cin.ignore();
//         }
//         int my_drone_count;
//         cin >> my_drone_count; cin.ignore();
//         for (int i = 0; i < my_drone_count; i++)
// 		{
// 			int drone_id;
//         	int drone_x;
//         	int drone_y;
//             int emergency;
//             int battery;
//             cin >> drone_id >> drone_x >> drone_y >> emergency >> battery; cin.ignore();
// 			My_droneV.push_back(My_drone(drone_id, drone_x, drone_y, emergency, battery));
//         }
//         int foe_drone_count;
//         cin >> foe_drone_count; cin.ignore();
//         for (int i = 0; i < foe_drone_count; i++)
// 		{
//             int drone_id;
//             int drone_x;
//             int drone_y;
//             int emergency;
//             int battery;
//             cin >> drone_id >> drone_x >> drone_y >> emergency >> battery; cin.ignore();
//         }
//         int drone_scan_count;
//         cin >> drone_scan_count; cin.ignore();
//         for (int i = 0; i < drone_scan_count; i++)
// 		{
//             int drone_id;
//             // My_droneV[i].drone_id == drone_id
//             int creature_id;
//             cin >> drone_id >> creature_id; cin.ignore();

//             cerr << "id Salim. " << creature_id << "     drone id    " << drone_id << endl;
//         }
//         int visible_creature_count;
//         cin >> visible_creature_count; cin.ignore();
//         for (int i = 0; i < visible_creature_count; i++)
// 		{
//             int creature_id;
//             int creature_x;
//             int creature_y;
//             int creature_vx;
//             int creature_vy;
            

// 			int color;
// 			int type;
//             cin >> creature_id >> creature_x >> creature_y >> creature_vx >> creature_vy; cin.ignore();
//             if (check_id(My_drone_scan, creature_id) == -1)
//             {
//                 My_drone_scan.push_back(creature_id);
//             }
//             // cerr << "id Me    " << creature_id << endl;
// 			for(size_t i=0; i<FishV.size(); i++)
// 			{
// 				if(FishV.at(i).creature_id == creature_id)
// 				{
// 					color = FishV.at(i).color;
// 					type = FishV.at(i).type;
// 					break;
// 				}
// 			}
// 			Visible_creatureV.push_back(Visible_creature(creature_id, creature_x, creature_y, creature_vx, creature_vy, color, type));
//         }
//         int radar_blip_count;
//         cin >> radar_blip_count; cin.ignore();
// 		vector<Radar> RadarDrone1;
//         vector<Radar> RadarDrone2;
//         // cerr << "      " << radar_blip_count << endl;
//         for (int i = 0; i < radar_blip_count; i++)
// 		{
//             int drone_id;
//             int creature_id;
// 			string radar;
            
//             cin >> drone_id >> creature_id >> radar; cin.ignore();
//             // cerr << "id drone ==>>   " << drone_id << endl;

//             if (check_id(My_drone_scan, creature_id) == -1 && drone_id == My_droneV[0].drone_id)
// 			    RadarDrone1.push_back(Radar(radar, drone_id, creature_id));
//             else if (check_id(My_drone_scan, creature_id) == -1 && drone_id == My_droneV[1].drone_id)
//                 RadarDrone2.push_back(Radar(radar, drone_id, creature_id));
//         }
// 		int light = 0;
//         if (My_droneV.at(0).drone_y > 3000)
//             light = 1;

//         // for (Radar rd : RadarDrone1)
//         //     cerr << " radar  :  " << rd.radar << "   rd.creature_id :  " << rd.creature_id <<  "   rd.drone_id:  " << rd.drone_id << endl;
//         // cerr << "\n-------------------------------------\n";
//         // for (Radar rd : RadarDrone2)
//         //     cerr << " radar  :  " << rd.radar << "   rd.creature_id :  " << rd.creature_id <<  "   rd.drone_id:  " << rd.drone_id << endl;
//         for (int i = 0; i < my_drone_count; i++)
//         {
//             if(i == 0)
//                 // Drone3Movement(i, My_droneV);
//                 DroneMovement(i, RadarDrone1, My_droneV, My_drone_scan);
//             else
//                 // cout << "MOVE 6000 500 0" << endl;
//                 // cout << "WAIT 0" << endl;
//                 Drone2Movement(i, My_droneV);
//         }
// 	}
// }







/*-----------------------*/




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

class Point
{
    public:
        double  x;
        double  y;
        double dist;
    Point(double x, double y, double dist)
    {
        this->x = x;
        this->y = y;
        this->dist = dist;
    }
};


// void GeneratePoints(Point center, int radius)
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
        EstablishedPoints.push_back(Point(x, y, -1));
    }
    return EstablishedPoints;
}
// void   GeneratePoint(Point point, int radius)
// {
//     for(size_t i=0; i<359; i++)
//     {
//         Point point;
//         EstablishedPoints.push_back(point);
//     }
// }
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
                // for(size_t i=0; i<DisDrone; i+=3)
                // {

                // }
                if(TmpDist > EstablishedPoints[i].dist)
                {
                    TmpDist = EstablishedPoints[i].dist;
                    SavePoint.x = EstablishedPoints[i].x;
                    SavePoint.y = EstablishedPoints[i].y;
                    SavePoint.dist = EstablishedPoints[i].dist;
                }
            }
        }
        // cerr << "Point :  x=  " << EstablishedPoints[i].x << "  y=  " << EstablishedPoints[i].y << endl;
    }
    // if(drone.Monsters.size() > 0)
        cout << "MOVE " << (int)SavePoint.x << " " << (int)SavePoint.y << " " << drone.light << " tal3a o l9at monster drone_id " + to_string(drone.drone_id) << endl;
    // else
    //     cout << "MOVE " << Drone_NextX << " " << Drone_NextY << " " << drone.light << endl;


    // cerr << "\n---------------------- All Information about Monster -----------------------------------\n";
    // cerr << "count The Monster :  " << drone.Monsters.size() << endl;
    // for(size_t i=0; i<drone.Monsters.size(); i++)
    // {
        // double dist = distance(Drone_NextX, Drone_NextY, drone.Monsters[0].creature_x + drone.Monsters[0].creature_vx, drone.Monsters[0].creature_y + drone.Monsters[0].creature_vy);
        // double distWithCurentposition = distance(drone.drone_x, drone.drone_y, drone.Monsters[0].creature_x, drone.Monsters[0].creature_y);
        // if(dist < 1000 || distWithCurentposition < 1000)
        // {
    //         cerr << "Yes Avoid Monster now \n";
    //         if(drone.drone_x > drone.Monsters[i].creature_x && drone.drone_y < drone.Monsters[i].creature_y && Drone_NextY > drone.drone_y)
    //         {
    //             cerr << "condition 1\n";
    //             cout << "MOVE " << drone.drone_x + 500 << " " << drone.Monsters[i].creature_y << " 0" << endl;
    //         }
    //         else if(drone.drone_x > drone.Monsters[i].creature_x && drone.drone_y >= drone.Monsters[i].creature_y && Drone_NextY > drone.drone_y)
    //         {
    //             cerr << "condition 2\n";
    //             cout << "MOVE " << drone.drone_x - 200 << " " << drone.Monsters[i].creature_y + 700 << " 0" << endl;
    //         }
    //         else if(drone.drone_x >= drone.Monsters[i].creature_x && drone.drone_y >= drone.Monsters[i].creature_y && Drone_NextY < drone.drone_y)
    //         {
    //             cerr << "condition 3\n";
    //             cout << "MOVE " << drone.drone_x + 500 << " " << drone.Monsters[i].creature_y - 500 << " 0" << endl;
    //         }
    //         else if(drone.drone_x < drone.Monsters[i].creature_x && drone.drone_y >= drone.Monsters[i].creature_y && Drone_NextY < drone.drone_y)
    //         {
    //             cerr << "condition 4\n";
    //             cout << "MOVE " << drone.drone_x - 500 << " " << drone.Monsters[i].creature_y - 500 << " 0" << endl;
    //         }


    //         // else if(drone.drone_x >= drone.Monsters[i].creature_x && drone.drone_y > drone.Monsters[i].creature_y)
    //         // {
    //         //     cerr << "condition 5\n";
    //         //     cout << "MOVE " << drone.drone_x - 500 << " " << drone.Monsters[i].creature_y + 500 << " 0" << endl;
    //         // }
    //         // else if(drone.drone_x > drone.Monsters[i].creature_x && drone.drone_y < drone.Monsters[i].creature_y)
    //         // {
    //         //     cerr << "condition 6\n";
    //         //     cout << "MOVE " << drone.drone_x - 500 << " " << drone.Monsters[i].creature_y + 500 << " 0" << endl;
    //         // }
    //         else
    //             cout << "WAIT 0" << endl;
    //     }
        // else
        //     cout << "MOVE " << Drone_NextX << " " << Drone_NextY << " 0" << endl;     
    //     cerr << "Drone_NextX " << Drone_NextX << "  Drone_NextY  " << Drone_NextY << endl;
    //     cerr << " creature_XVX  " << drone.Monsters[i].creature_x + drone.Monsters[i].creature_vx;
    //     cerr << " creature_YVY  " << drone.Monsters[i].creature_y + drone.Monsters[i].creature_vy << endl;
    //     cerr << " Distance. " << dist << endl;
    //     cerr << " Distance2 " << distWithCurentposition << endl;
    // }
    // cerr << "\n-----------------------------------------------------------------------------\n";
    // if(dist < 1000 || distWithCurentposition < 2000)
    // {
    //     if(drone.drone_y > drone.Monsters[0].creature_y && drone.Monsters[0].creature_x < drone.drone_x)
    //     {
    //         cerr << "kayn lt7t o lmonster 3la lisre\n";
    //         cout << "MOVE " << drone.drone_x + 2000 << " " << drone.drone_y + 500 << " " << drone.light << endl;
    //     }
    //     else if(drone.drone_y > drone.Monsters[0].creature_y && drone.Monsters[0].creature_x >= drone.drone_x)
    //     {
    //         cerr << "kayn lt7t o lmonster 3la limen \n";
    //         cout << "MOVE " << drone.drone_x - 2000 << " " << drone.drone_y - 500 << " " << drone.light << endl;
    //     }
    //     else
    //     {
    //         cerr << "kayn lfoo9\n";
    //         cout << "MOVE " << drone.drone_x << " 500 " << drone.light << endl;
    //     }
    // }
    // else
        // cout << "MOVE " << Drone_NextX << " " << Drone_NextY << " 0" << endl;
        

        // cout << "MOVE " << drone.drone_x << " 500 " << drone.light << endl;

}
// void    GenerateRandomPoint(int sep)
// Point    GenerateRandomPoint(My_drone drone, int sep)
// {
//     Point point(-1, -1, -1);
//     std::uniform_int_distribution<int> distributionX;
//     std::uniform_int_distribution<int> distributionY;
//     random_device rd;
//     mt19937 gen(rd());
//     // Generate random x and y coordinates for the player within the map
//     if(sep == 0)
//         distributionX = std::uniform_int_distribution<int>(0, 4000);
//     else
//         distributionX = std::uniform_int_distribution<int>(6000, 9000);
//     if(CountType22 != -1)
//         distributionY = std::uniform_int_distribution<int>(7500, 9000);
//     else
//         distributionY = std::uniform_int_distribution<int>(3500, 7500);

//     int DroneX = distributionX(gen);
//     int DroneY = distributionY(gen);
//     point.x = DroneX;
//     point.y = DroneY;

//     int check = 0;
//     for(size_t i=0; i<drone.Monsters.size(); i++)
//     {
//         double dis = distance(point.x, point.y, drone.Monsters[i].creature_x, drone.Monsters[i].creature_y);
//         if(dis < 700)
//             check++;
//     }
//     if(check != 0)
//         point = GenerateRandomPoint(drone, sep);
//     return point;
// }


Point GenerateRandomPoint(My_drone drone, int sep)
{
    Point point(-1, -1, -1);
    std::uniform_int_distribution<int> distributionX;
    std::uniform_int_distribution<int> distributionY;
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

    int maxAttempts = 50000;  // Maximum attempts to find a valid point
    int attempts = 0;


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

    while (attempts < maxAttempts)
    {
        int DroneX = distributionX(gen);
        int DroneY = distributionY(gen);

        point.x = DroneX;
        point.y = DroneY;

        // Check if the point is within a certain distance of existing points
        bool isValid = true;
        for (size_t i = 0; i < drone.Monsters.size(); i++)
        {
            double m = sqrt(point.x * point.x + point.y * point.y);
            double Vx = ((point.x / m) * 600) + drone.drone_x;
            double Vy = ((point.y / m) * 600) + drone.drone_y;
            double dis = distance(point.x, point.y, drone.Monsters[i].creature_x, drone.Monsters[i].creature_y);
            double dis2 = distance(drone.Monsters[i].creature_x + drone.Monsters[i].creature_vx, drone.Monsters[i].creature_y + drone.Monsters[i].creature_vy,
                drone.drone_x + Vx, drone.drone_y + Vy);
            // double dis3 = distance(drone.Monsters[i].creature_x + drone.Monsters[i].creature_vx, drone.Monsters[i].creature_y + drone.Monsters[i].creature_vy,
            //     drone.drone_x, drone.drone_y);
            if (dis < 800 || dis2 < 800)
            {
                isValid = false;
                break;
            }
        }
        if (isValid)
        {
            return point;  // Found a valid point, exit the loop
        }
        attempts++;
    }
    vector<Point> EstablishedPoints = GeneratePoints(Point(drone.drone_x, drone.drone_y, -1), 600);
    cerr << "     heere      " << attempts << endl;
    // If we couldn't find a valid point after maximum attempts, return the original point
    return point;
}


vector<int> allreadyCheckId;
void MoveDrone(My_drone drone, vector<int> My_drone_scan, int &TmpSize, int sep, vector<Visible_creature> Visible_creatureV, int CheckType2, int GSC, int SizeRemainingFish, int &CheckMon)
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
        if(drone.Monsters.size() > 0)
            Avoid_Monster(drone, drone.drone_x, 500);
        else
            cout << "MOVE " << drone.drone_x << " 500 " << drone.light << " ghadi tla3 lfo9 drone_id " + to_string(drone.drone_id) << endl;
        CountType22 = -1;
    }
    else
    {   
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
        // std::uniform_int_distribution<int> distributionX;
        // std::uniform_int_distribution<int> distributionY;
        // random_device rd;
        // mt19937 gen(rd());
        // // Generate random x and y coordinates for the player within the map
        // if(sep == 0)
        //     distributionX = std::uniform_int_distribution<int>(0, 4000);
        // else
        //     distributionX = std::uniform_int_distribution<int>(6000, 9000);
        // if(CountType22 != -1)
        //     distributionY = std::uniform_int_distribution<int>(7500, 9000);
        // else
        //     distributionY = std::uniform_int_distribution<int>(3500, 7500);
        // int playerX = distributionX(gen);
        // int playerY = distributionY(gen);
        Point point = GenerateRandomPoint(drone, sep);
        // if(drone.Monsters.size() > 0)
        // {
        //     for(size_t i=0; i<drone.Monsters.size(); i++)
        //     {
        //         double dis = distance(point.x, point.y, drone.Monsters[i].creature_x, drone.Monsters[i].creature_y);
        //         if(dis < 700)
        //             point = GenerateRandomPoint(sep);
        //     }
        //     Avoid_Monster(drone, point.x, point.y);
        // }
        // else
        cout << "MOVE " << point.x << " " << point.y << " " << drone.light << " mazal kat9alb drone_id " + to_string(drone.drone_id) << endl;
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
        cerr << "                        " << visible_creature_count << endl;
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

// moxkil kaytbdl CheckType2  o ana jm3t 4 dyal type2 o 9bl manvalidihom tbdl type 2
