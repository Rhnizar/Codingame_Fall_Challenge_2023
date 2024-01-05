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
    for(size_t j=0; j<drone.Monsters.size(); j++)
    {
        int Xmonster = drone.Monsters[j].creature_x;
        int Ymonster = drone.Monsters[j].creature_y;
        int Next_Xmonster = drone.Monsters[j].creature_x + drone.Monsters[j].creature_vx;
        int Next_Ymonster = drone.Monsters[j].creature_y + drone.Monsters[j].creature_vy;

        double  TmpDist = 9999999999;
        ValidPoints.clear();
        for(size_t i = 0; i<EstablishedPoints.size(); i++)
        {
            vector<Point> Dvp = divideLine(Point(drone.drone_x, drone.drone_y), Point(EstablishedPoints[i].x, EstablishedPoints[i].y), 10);
            vector<Point> Mvp = divideLine(Point(Xmonster, Ymonster), Point(Next_Xmonster, Next_Ymonster), 10);

            int check = 0;
            for(size_t r=0; r<Dvp.size(); r++)
            {
                if(distance(Dvp[r].x, Dvp[r].y, Mvp[r].x, Mvp[r].y) <= 550)
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
            int tmp = 0;
            int tmp2 = 0;
            vector<Point> Dvp2;
            int x, y;
            if(drone.Monsters[j].creature_vx > 0)
                x = drone.drone_x + drone.Monsters[j].creature_vx + 60;
            else
                x = drone.drone_x + drone.Monsters[j].creature_vx - 60;
            
            if(drone.Monsters[j].creature_vy > 0)
                y = drone.drone_y + drone.Monsters[j].creature_vy + 60;
            else
                y = drone.drone_y + drone.Monsters[j].creature_vy - 60;
            
            Dvp2 = divideLine(Point(drone.drone_x, drone.drone_y), Point(x, y), 30);
            
            for(size_t r=0; r<Dvp2.size(); r++)
            {
                double dis = distance(Dvp2[r].x, Dvp2[r].y, Xmonster, Ymonster);
                if(dis > 550 && tmp < dis)
                {
                    cerr << "heeeereeeee\n";
                    tmp = dis;
                    SavePoint.x = Dvp2[r].x;
                    SavePoint.y = Dvp2[r].y;
                }
            }
        }
        cerr << "size        =========   " << EstablishedPoints.size() << endl;
    }
    cout << "MOVE " << SavePoint.x << " " << SavePoint.y << " " << drone.light << endl;
}

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
Point GenerateRandomPoint(My_drone drone, int sep)
{
    Point point(-1, -1);
    std::uniform_int_distribution<int> distributionX;
    std::uniform_int_distribution<int> distributionY;
    random_device rd;
    mt19937 gen(rd());

    int DroneX = 0;
    int DroneY = 0;
    if(sep == 0)
        distributionX = std::uniform_int_distribution<int>(0, 4000);
    else
        distributionX = std::uniform_int_distribution<int>(6000, 9000);

    if(allreadyCheckId.size() != 4)
        distributionY = std::uniform_int_distribution<int>(7500, 9000);
    else
        distributionY = std::uniform_int_distribution<int>(3500, 7500);

    DroneX = distributionX(gen);
    DroneY = distributionY(gen);

    Avoid_Monster(drone, DroneX, DroneY);
}

int tmp1 = 0;
int tmp2 = 0;
int size1 = 0;
int size2 = 0;
void MoveDrone(My_drone drone, int &Check, vector<int> My_drone_scan, vector<Visible_creature> Visible_creature, int sep)
{
    cerr << "\n==========================================\n";
    cerr << "  x = " << drone.drone_x;
    cerr << "  y = " << drone.drone_y << endl;

    // for(size_t i=0;i<My_drone_scan.size();i++)
    // {
    //     if(CheckType(My_drone_scan[i], Visible_creature) == 1 && find(allreadyCheckId.begin(), allreadyCheckId.end(), My_drone_scan[i]) == allreadyCheckId.end())
    //         allreadyCheckId.push_back(My_drone_scan[i]);
    // }
    // // allreadyCheckId.size() < 4 ||
    // if(sep == 0)
    // {
    //     if(My_drone_scan.size() + size1 < 4 || tmp1 == 1)
    //         GenerateRandomPoint(drone, sep);
    //     else
    //     {
    //         Avoid_Monster(drone, drone.drone_x, 500);
    //         if(drone.drone_y <= 500)
    //         {
    //             tmp1 = 1;
    //             size1 = 1;
    //         }
    //     }
    // }
    // else
    // {
    //     if(My_drone_scan.size() + size2  < 5 || tmp2 == 1)
    //         GenerateRandomPoint(drone, sep);
    //     else
    //     {
    //         Avoid_Monster(drone, drone.drone_x, 500);
    //         if(drone.drone_y <= 500)
    //         {
    //             tmp2 = 1;
    //             size2 = 1;
    //         }
    //     }
    // }
        // cout << "MOVE " << drone.drone_x << " " << 500 << " " << drone.light << endl;
    
    if(sep == 0)
    {
        if(drone.drone_y < 8000 && Check == 0)
        {
            Avoid_Monster(drone, 2000, 9600);
        }
        else if(drone.drone_y >= 8000 || Check == 1)
        {
            Check = 1;
            Avoid_Monster(drone, drone.drone_x, 500);
            if(drone.drone_y <= 500)
                Check = 0;
        }
    }
    else
    {
        if(drone.drone_y < 8000 && Check == 0)
        {
            Avoid_Monster(drone, 8000, 9600);
        }
        else if(drone.drone_y >= 8000 || Check == 1)
        {
            Check = 1;
            Avoid_Monster(drone, drone.drone_x, 500);
            if(drone.drone_y <= 500)
                Check = 0;
        }
    }
}


int main()
{
    int CheckDrone1 = 0;
    int CheckDrone2 = 0;
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
        
        for (int i = 0; i < my_drone_count; i++)
        {
            if((my_drone[i].drone_y >= 2000 && my_drone[i].drone_y <= 5000) || (my_drone[i].drone_y >= 7500 && my_drone[i].drone_y <= 9000))
                my_drone[i].light = 1;
            // if(my_drone[i].drone_y >= 7500)
            //     my_drone[i].light = 1;
            if(i == 0)
                MoveDrone(my_drone[i], CheckDrone1, My_drone1_scan, visible_creature, 0);
            else
                MoveDrone(my_drone[i], CheckDrone2, My_drone2_scan, visible_creature, 1);
        }
    }
}