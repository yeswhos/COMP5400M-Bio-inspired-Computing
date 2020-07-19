// Vim users: for increased viewing pleasure :set ts=4

#include "animat.h"
#include "sensor.h"
#include "sensorbase.h"
#include "beast.h"
#include "simulation.h"
#include "bacteria.h"
#include<cstdlib>
#include <unistd.h>
#include "neuralanimat.h"
#include "population.h"

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

// class Shrew : public Animat // Shrew is derived from Animat
// {
// public:
// 	int controlMode;
// 	Shrew()
// 	{	
		
// 		This.Add("lineSensor", ProximitySensor<Shrew>(2 * PI, 300.0, -PI/20));
// 		Sensors["lineSensor"] -> SetMatchingFunction(new MatchExact<circleCenter>);
// 		This.Add("left", ProximitySensor<Shrew>(PI/5, 200.0, -PI/20));
// 		This.Add("right", ProximitySensor<Shrew>(PI/5, 200.0, PI/20));
		
// 		Sensors["left"] -> SetMatchingFunction(new MatchExact<Shrew>);
// 		Sensors["right"] -> SetMatchingFunction(new MatchExact<Shrew>);

// 		//This.SetInitRandom(true);	// Start in random locations
// 		This.InitRandom = false;
// 		This.Radius = 28.0;			// Shrews are a little bigger than usual
// 		SetMinSpeed(0.0);
// 	}
	
// 	virtual ~Shrew(){
		
// 	}

// 	void changeControlMode(int controlMode) {
// 		This.controlMode = controlMode;
// 	}

// 	virtual void Control()
// 	{
// 		if(This.controlMode == 1) {
// 			Mode1();
// 		} else {
// 			Mode2();
// 		}

// 	}
	
// 	void Mode1() {
// 		// write mode 1
// 		double right_a = This.Sensors["right"]->GetOutput();
// 		double left_a = This.Sensors["left"]->GetOutput();
// 		//double line = This.Sensors["line"] ->GetOutput();
// 		//bool inRange = true;
// 		//double num = rand()/double(RAND_MAX);
// 		//cout << num << endl;

// 		// if ((c >= 22) && (c <= 29)){
// 		// 	inRange = true;
// 		// }else{
// 		// 	inRange = false;
// 		// }
// 		// if (inRange){
// 		// This.Controls["left"] = -left_a;
// 		// This.Controls["right"] = -right_a;
// 		This.Controls["left"] = -right_a;
// 		This.Controls["right"] = -left_a;
// 		//cout << b << endl;
// 		// }else{
// 		// 	This.Controls["left"] = 0.0;
// 		// 	This.Controls["right"] = 0.5;
// 		// 	//sleep(1);
// 		// }

// 		// This.Controls["left"] = This.Sensors["right"]->GetOutput();
// 		// This.Controls["right"] = This.Sensors["left"]->GetOutput();
		
// 		//cout << c << endl;
// 	}

// 	void Mode2() {
// 		// write mode 2
// 		//double line = This.Sensors["line"] ->GetOutput();
// 		double num = rand()/double(RAND_MAX);
// 		double num_plus = rand()/double(RAND_MAX);
// 		This.Controls["left"] = num;
// 		This.Controls["right"] = num_plus;
		
// 	}
// };

class EvoMouses : public EvoFFNAnimat
{
public:
	//double lines;
	EvoMouses()
	{
		This.Add("lineSensor", ProximitySensor<EvoMouses>(2 * PI, 500.0f, -PI));
		Sensors["lineSensor"] -> SetMatchingFunction(new MatchExact<circleCenter>);
		This.Add("left", ProximitySensor<EvoMouses>(PI/5, 200.0, -PI/20));
		This.Add("right", ProximitySensor<EvoMouses>(PI/5, 200.0, PI/20));
		
		Sensors["left"] -> SetMatchingFunction(new MatchExact<EvoMouses>);
		Sensors["right"] -> SetMatchingFunction(new MatchExact<EvoMouses>);

		//This.SetInitRandom(true);	// Start in random locations
		This.InitRandom = false;
		This.Radius = 28.0;
		SetMinSpeed(0.0);
		This.InitFFN(4);
		// This.lines = This.Sensors["lineSensor"] ->GetOutput();
		// cout << lines << endl;
	}
	// double lines = This.Sensors["lineSensor"] ->GetOutput();
	// void setLines()
	virtual void getLines(){
		lines = This.Sensors["lineSensor"] ->GetOutput();

		//EvoFFNAnimat::getLines();
	}
	virtual float GetFitness()const
	{
		//double lines = setLine();
		cout << This.lines << endl;
		// double right_a = This.Sensors["right"]->GetOutput();
		if (lines < 200.0f){
			return 0.0;
		}
		else{
			return 1.0;
		}
	}

	// Overloading the ToString method allows us to output a small amount of
	// information which is visible in the status bar of the GUI when a
	// mouse is clicked on.
	virtual string ToString()const
	{
		
		ostringstream out;
		out << " Power used: " << This.PowerUsed;
		return out.str();
	}
private:
	double lines;

};

class ShrewSimulation : public Simulation
{
	GeneticAlgorithm<EvoMouses> theGA;
	Population<EvoMouses> theMice;
	// Group<Shrew> grpShrew;
	//Group<Shrew_opponent> grpShrew_opponent;
	Group<Circle> theCircle;
	Group<circleCenter> theCircleCenter;

public:
	ShrewSimulation():
	theGA(0.7f, 0.05f),
	theMice(2, theGA),
	theCircle(1),
	theCircleCenter(1)
	//grpShrew_opponent(1),
	// grpShrew(2)
	{
		This.Add("Mice", This.theMice);
		theMice[0] -> SetStartLocation(Vector2D(500, 300));
		theMice[1] -> SetStartLocation(Vector2D(300, 300));
		// grpShrew[1] -> changeControlMode(2);
		// grpShrew[0] -> changeControlMode(1);
		theMice[0] -> Add("left", ProximitySensor<EvoMouses>(PI/5, 200.0, -(21 * PI)/20));
		theMice[0] -> Add("right", ProximitySensor<EvoMouses>(PI/5, 200.0, (21 * PI)/20));
		This.Add("Circle", This.theCircle);
		This.Add("circleCenter", This.theCircleCenter);
		
		This.theGA.SetSelection(GA_TOURNAMENT);
		This.theGA.SetParameter(GA_TOURNAMENT_SIZE, 2);
		//This.Add("Shrews", This.grpShrew);
		//This.Add("Shrews_opponent", This.grpShrew_opponent);
		This.SetTimeSteps(200);
	}
};

