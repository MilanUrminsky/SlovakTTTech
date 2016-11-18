#include <stdio.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265
#define ACCURACY 2


//�trukt�ra pre bod na mape
struct nav_point{  

    double longitude;
    double latitude;
};

nav_point nav_map [3] = 
{
    {1, 1 },
    {3, 1 },
    {3, 3 }
};

//
// Funkcia na n�jdenie najbli��ieho bodu mapu
// @longtitude, zemepisna sirka
// @latitude, zemepisna dlzka
//

int find_closest_point(double longitude,double latitude)
{
  int min_index = 0;
  long double min= sqrt(pow(longitude - nav_map[0].longitude,2)+pow(latitude - nav_map[0].latitude,2));

  for(int i=1;i<5;i++)
  {
	long double dist= sqrt(pow(longitude - nav_map[i].longitude,2)+pow(latitude - nav_map[i].latitude,2));
	if(min > dist)
	{
		min=dist;
		min_index = i;
	}
  }
  return min_index;
}

//
// Funkcia na prepo��tanie hodnoty stup�a pod�a kvadrant v ktorom sa nach�dza
// @x, rozdiel medzi xovymi suradnic bodu zaciatku a konca
// @y, rozdiel medzi ynovymi suradnic bodu zaciatku a konca
// @degree, uhol vypo��tany pre prv� kvadrant
//
int degree_based_on_sector(double x,double y,double degree)
{
	if(x>=0 && y>=0) //1.st sector
	{
		return degree;
	}else if(x>=0 && y<=0) //2.nd sector
	{
		return 180-degree;
	}else if(x<=0 && y<=0) //3.rd sector
	{
		return 180-degree;
	}else //4.th sector
	{
		return 360-degree;
	}
}

//
// Funkcia na vypo��ta uhol potrebn� na dosiahnutie bodu end z bodu start
// @start, za�iato�n� bod
// @end, koncov� bod
//
double calculate_compass_degree(nav_point start,nav_point end)
{
	double x = end.longitude-start.latitude;
	double y = end.latitude-start.latitude;
	return degree_based_on_sector(x,y,atan(abs(x)/abs(y)) * (180/PI));
}

//
// Funkcia zist�, �i sa nach�dza bod actual v bl�zkosti bodu dest
// @actual, aktu�lny bod
// @dest, cie�ov� bod
//
bool is_in_node(nav_point actual,nav_point dest)
{
	if(sqrt(pow(actual.longitude - dest.longitude,2)+pow(actual.latitude - dest.latitude,2)) <= ACCURACY)
	{
		return true;
	}
	return false;
}

int main()
{
	double lon = 4;
	double lat = 2;
	int i = find_closest_point(lon,lat);

	printf("Closest point: %lf %lf\n",nav_map[i].longitude,nav_map[i].latitude);
	printf("Compass degree: %lf\n",calculate_compass_degree(nav_map[0],nav_map[2]));
	printf("%d",is_in_node(nav_map[0],nav_map[2]));

	getchar();
	return 0;
}