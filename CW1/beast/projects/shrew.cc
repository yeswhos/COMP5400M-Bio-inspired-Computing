// Vim users: for increased viewing pleasure :set ts=4

#include "animat.h"
#include "sensor.h"
#include "sensorbase.h"
#include "beast.h"
#include "simulation.h"
#include "bacteria.h"
#include<cstdlib>
#include <unistd.h>

using namespace std;
using namespace BEAST;

// For more information on this file, take a look at Tutorial 1 in the
// BEAST documentation.
class Circle : public WorldObject
{
public:
	Circle()
	{
		
		This.Radius = 200.0f;							 // Cheeses are quite small
		This.SetColour(ColourPalette[COLOUR_BLACK]);// Cheeses are yellow
		//This.InitRandom = true;						 // Cheases are scattered
		SetLocation(400, 300);
		This.Location = GetLocation();
	}
	virtual ~Circle(){}

	// When a Cheese is Eaten, it reappears in a random location.
	// void Eaten()
	// {
	// 	This.Location = This.MyWorld->RandomLocation();
	// }
};

class circleCenter : public WorldObject
{
public:
	circleCenter()
	{
		
		This.Radius = 1.1f;							 // Cheeses are quite small
		This.SetColour(ColourPalette[COLOUR_WHITE]);// Cheeses are yellow
		//This.InitRandom = true;						 // Cheases are scattered
		SetLocation(400, 300);
		This.Location = GetLocation();
	}
	virtual ~circleCenter(){}

	// When a Cheese is Eaten, it reappears in a random location.
	// void Eaten()
	// {
	// 	This.Location = This.MyWorld->RandomLocation();
	// }
};

class Shrew : public Animat // Shrew is derived from Animat
{
public:
	
	Shrew()
	{	
		
		//need to add area sensor
		This.Add("left", ProximitySensor<Shrew>(2 * PI, 300.0, -PI/20));
		//This.Add("right", ProximitySensor<Shrew>(PI/5, 200.0, PI/20));
		//This.Add("line", LineSensor<Shrew>(Vector2D(400.0, 300.0), 200.0f));
		Sensors["left"] -> SetMatchingFunction(new MatchExact<circleCenter>);

		This.SetInitRandom(true);	// Start in random locations
		//This.InitRandom = false;
		//SetStartLocation(Vector2D(300, 300));
		
		This.Radius = 28.0;			// Shrews are a little bigger than usual
		SetMinSpeed(0.0);
	}
	
	virtual ~Shrew(){
		
	}

	virtual void Control()
	{
		// double a = This.Sensors["right"]->GetOutput();
		double b = This.Sensors["left"]->GetOutput();
		//double c = This.Sensors["line"] ->GetOutput();
		//bool inRange = true;
		double num = rand()/double(RAND_MAX);
		//cout << num << endl;

		// if ((c >= 22) && (c <= 29)){
		// 	inRange = true;
		// }else{
		// 	inRange = false;
		// }
		// if (inRange){
		This.Controls["left"] = 0.5;
		This.Controls["right"] = num;
		cout << b << endl;
		// }else{
		// 	This.Controls["left"] = 0.0;
		// 	This.Controls["right"] = 0.5;
		// 	//sleep(1);
		// }

		// This.Controls["left"] = This.Sensors["right"]->GetOutput();
		// This.Controls["right"] = This.Sensors["left"]->GetOutput();
		
		//cout << c << endl;
		

	}
};



class ShrewSimulation : public Simulation
{
	Group<Shrew> grpShrew;
	Group<Circle> theCircle;
	Group<circleCenter> theCircleCenter;

public:
	ShrewSimulation():
	theCircle(1),
	theCircleCenter(1),
	grpShrew(1)
	{
		This.Add("Circle", This.theCircle);
		This.Add("circleCenter", This.theCircleCenter);
		This.Add("Shrews", This.grpShrew);
	}
};

