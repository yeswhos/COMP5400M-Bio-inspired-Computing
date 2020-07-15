// Vim users: for increased viewing pleasure :set ts=4

#include "animat.h"
#include "sensor.h"
#include "sensorbase.h"
#include "beast.h"
#include "simulation.h"
#include "bacteria.h"

using namespace std;
using namespace BEAST;

// For more information on this file, take a look at Tutorial 1 in the
// BEAST documentation.

class Shrew : public Animat // Shrew is derived from Animat
{
public:
	Shrew()
	{
		//need to add area sensor
		This.Add("left", ProximitySensor<Shrew>(PI/5, 200.0, -PI/20));
		This.Add("right", ProximitySensor<Shrew>(PI/5, 200.0, PI/20));
		This.Add("line", LineSensor<Shrew>(Vector2D(400.0, 300.0), 200.0f));

		//This.SetInitRandom(true);	// Start in random locations
		This.InitRandom = false;
		SetStartLocation(Vector2D(300, 300));
		//SetLocation(4.0, 2.5);
		//This.Location = GetLocation();
		//This.Location = Vector2D(400, 400);
		// This.Location = Vector2D(400, 300);
		This.Radius = 29.0;			// Shrews are a little bigger than usual
		SetMaxSpeed(0.0);
	}
	virtual ~Shrew(){}

	virtual void Control()
	{
		double a = This.Sensors["right"]->GetOutput();
		double b = This.Sensors["left"]->GetOutput();

		// if((a == 0.0) && (b == 0)){
		// This.Controls["left"] = 0;
		// This.Controls["right"] = 0;
		// }
		// else{
		// 	This.Controls["left"] = This.Sensors["right"]->GetOutput();
		// 	This.Controls["right"] = This.Sensors["left"]->GetOutput();
		// }
		// This.Controls["left"] = This.Sensors["right"]->GetOutput();
		// This.Controls["right"] = This.Sensors["left"]->GetOutput();
		double c = This.Sensors["line"] ->GetOutput();
		cout << c << endl;
		//cout << a << endl;
		//cout << "------------------------" << endl;
		// This.Controls["left"] = 0.0;
		// This.Controls["right"] = 0.0;

	}
};

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

class ShrewSimulation : public Simulation
{
	Group<Shrew> grpShrew;
	Group<Circle> theCircle;

public:
	ShrewSimulation():
	theCircle(1),
	grpShrew(1)
	{
		This.Add("Circle", This.theCircle);
		This.Add("Shrews", This.grpShrew);
	}
};

