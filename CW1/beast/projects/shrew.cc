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

list<int> l1;

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
		
		This.Radius = 3.1f;							 // Cheeses are quite small
		This.SetColour(ColourPalette[COLOUR_WHITE]);// Cheeses are yellow
		//This.InitRandom = true;						 // Cheases are scattered
		SetLocation(400, 300);
		This.Location = GetLocation();
	}
	virtual ~circleCenter(){}
};

class EvoMouses : public EvoFFNAnimat
{
public:
	//double lines;
	bool inRange = true;
	int counter = 0;
	
	//EvoMouses *enermy;
	EvoMouses():lines(0)
	{
		This.Add("lineSensor", ProximitySensor<circleCenter>(2 * PI, 200.0f, -PI));
		//Sensors["lineSensor"] -> SetMatchingFunction(new MatchExact<circleCenter>);
		This.Add("left", ProximitySensor<EvoMouses>(PI/5, 200.0, -PI/20));
		This.Add("right", ProximitySensor<EvoMouses>(PI/5, 200.0, PI/20));

		//This.SetInitRandom(true);	// Start in random locations
		This.InitRandom = false;
		This.SetStartLocation(Vector2D(500, 300));
		This.Radius = 28.0;
		SetMinSpeed(0.0);
		This.InitFFN(5);

	}

	// void setEnermy(EvoMouses *enermy) {
	// 	This.enermy = enermy;
	// }

	virtual void Control(){
		This.lines = This.Sensors["lineSensor"] ->GetOutput();
		if(This.lines < 0.015 && This.lines != 0){
			inRange = false;
		}
		//cout << This.lines  << endl;
		// This.Controls["left"] = 0;
		// This.Controls["right"] = 0;
		
		EvoFFNAnimat::Control();
	}

	void OnCollision(WorldObject* obj){
		if (inRange == false){
			counter++;
			This.SetLocation(Vector2D(500, 300));
		}
		l1.push_back(counter);
		
		//setEnermy(enermy);
		FFNAnimat::OnCollision(obj);
	}

	virtual float GetFitness()const
	{
		//cout << l1.empty() << endl;
		cout << "-------------" << endl;
		// int c = l1.front();
		int c = l1.size();
		cout << c << endl;
		if (inRange){
			return 1.0;
		}
		else{
			return 0.0;
		}
		// int score;
		// if (counter == 0){
		// 	score = 1;
		// 	return score;
		// }else{
		// 	float score = 1 / counter;
		// 	cout << score << endl;
		// 	return score;
		// }

		// int score = enermy -> counter;
		// float fitness = score - This.counter;
		// return fitness;
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
	// Group<EvoMouses> grpShrew;
	Group<Circle> theCircle;
	Group<circleCenter> theCircleCenter;

public:
	ShrewSimulation():
	theGA(0.7f, 0.05f),
	theMice(2, theGA),
	theCircle(1),
	theCircleCenter(1)
	{
		This.Add("EvoMouses", This.theMice);
		//theMice[0] -> SetLocation(500, 300);
		//theMice[1] -> SetStartOrientation(PI);
		// grpShrew[1] -> changeControlMode(2);
		// grpShrew[0] -> changeControlMode(1);
		// theMice[0] -> Add("left", ProximitySensor<EvoMouses>(PI/5, 200.0, -(21 * PI)/20));
		// theMice[0] -> Add("right", ProximitySensor<EvoMouses>(PI/5, 200.0, (21 * PI)/20));
		// tes = theMice[1] -> inRange;
		// cout << tes << endl;
		//theMice.setEnermy()
		This.Add("Circle", This.theCircle);
		This.Add("circleCenter", This.theCircleCenter);
		
		This.theGA.SetSelection(GA_TOURNAMENT);
		This.theGA.SetParameter(GA_TOURNAMENT_SIZE, 2);
		//This.Add("Shrews", This.grpShrew);
		//This.Add("Shrews_opponent", This.grpShrew_opponent);
		This.SetTimeSteps(200);
	}
};

