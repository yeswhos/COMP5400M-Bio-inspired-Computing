// Vim users: for increased viewing pleasure :set ts=4

#include "animat.h"
#include "sensor.h"
#include "sensorbase.h"
#include "beast.h"
#include "simulation.h"
#include "population.h"
#include "neuralanimat.h"
#include "worldobject.h"

using namespace std;
using namespace BEAST;

int counterA = 0;
int counterB = 0;
bool inRangeA = true;
bool inRangeB = true;
bool temp = true;
bool tempB = true;
// For more information on this file, take a look at Tutorial 1 in the
// BEAST documentation.
class Circle : public WorldObject
{
public:
	Circle()
	{
		
		This.Radius = 200.0f;							 
		This.SetColour(ColourPalette[COLOUR_BLACK]);
		//This.InitRandom = true;						
		SetLocation(400, 300);
		This.Location = GetLocation();
	}
	virtual ~Circle(){}

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

class ZumoQueen;
class ZumoKing : public EvoFFNAnimat
{
public:

	ZumoKing():lines(0)
	{
		This.Add("lineSensor", ProximitySensor<circleCenter>(2 * PI, 200.0f, -PI));
		//Sensors["lineSensor"] -> SetMatchingFunction(new MatchExact<circleCenter>);
		This.Add("left", ProximitySensor<ZumoQueen>(PI/4, 200.0, -PI/20));
		This.Add("right", ProximitySensor<ZumoQueen>(PI/4, 200.0, PI/20));
		This.SetStartOrientation(PI);
		//This.SetInitRandom(true);	// Start in random locations
		This.InitRandom = false;
		This.SetStartLocation(Vector2D(500, 300));
		This.Radius = 25.0;
		SetMinSpeed(0.0);
		This.InitFFN(5);

	}

	// void setEnermy(EvoMouses *enermy) {
	// 	This.enermy = enermy;
	// }

	virtual void Control(){
		This.lines = This.Sensors["lineSensor"] ->GetOutput();
		if(This.lines < 0.015 && This.lines != 0){
			inRangeA = false;
			temp = false;
		}
		if (inRangeA == false){
			counterA++;
			This.SetLocation(Vector2D(500, 300));
			This.SetOrientation(PI);
			//This.SetStartOrientation(PI);
			inRangeA = true;
		}else if(tempB == false){
			This.SetLocation(Vector2D(500, 300));
			This.SetOrientation(PI);
			//This.SetStartOrientation(PI);
			tempB = true;
			inRangeA = true;
		}
		//cout << This.lines  << endl;
		// This.Controls["left"] = 0;
		// This.Controls["right"] = 0;
		
		EvoFFNAnimat::Control();
	}

	// void OnCollision(WorldObject* obj){
		
	// 	//setEnermy(enermy);
	// 	FFNAnimat::OnCollision(obj);
	// }

	virtual float GetFitness()const
	{	
		// return score;
		float score = 0.0;
		// if (counterB == 0){
		// 	score = 1;
		// }else{
		// 	score = counterB;
		// }
		float midValue = 0.0;
		if(counterB == 0){
			midValue = 7;
		}else{
			midValue = 1 / 5 * counterB;
		}
		score = 1 / (0.5 * counterA + midValue);
		if(score > 1){
			score = 1;
		}
		counterA = 0;
		//cout << score << endl;
		return score;
	}

	// Overloading the ToString method allows us to output a small amount of
	// information which is visible in the status bar of the GUI when a
	// mouse is clicked on.
	virtual string ToString()const
	{
		ostringstream out;
		//out << " Power used: " << This.PowerUsed;
		out << "current fitness for defence" << GetFitness();
		return out.str();
	}
private:
	double lines;

};

class ZumoQueen : public EvoFFNAnimat
{
public:
	//double lines;
	bool inRange = true;
	int counter = 0;
	
	//EvoMouses *enermy;
	ZumoQueen():lines(0)
	{
		This.Add("lineSensor", ProximitySensor<circleCenter>(2 * PI, 200.0f, -PI));
		//Sensors["lineSensor"] -> SetMatchingFunction(new MatchExact<circleCenter>);
		This.Add("left", ProximitySensor<ZumoKing>(PI/4, 200.0, -PI/20));
		This.Add("right", ProximitySensor<ZumoKing>(PI/4, 200.0, PI/20));

		//This.SetInitRandom(true);	// Start in random locations
		This.InitRandom = false;
		This.SetStartLocation(Vector2D(300, 300));
		
		This.Radius = 25.0;
		SetMinSpeed(0.0);
		This.InitFFN(5);

	}

	// void setEnermy(EvoMouses *enermy) {
	// 	This.enermy = enermy;
	// }

	virtual void Control(){
		This.lines = This.Sensors["lineSensor"] ->GetOutput();
		if(This.lines < 0.015 && This.lines != 0){
			inRangeB = false;
			tempB = false;
		}
		//cout << This.lines  << endl;
		// This.Controls["left"] = 0;
		// This.Controls["right"] = 0;
		
		EvoFFNAnimat::Control();
	}
	
	void reLocate(){
		This.SetLocation(Vector2D(300, 300));
		This.SetOrientation(0.0);
	}

	void OnCollision(WorldObject* obj){
		if (inRangeB == false){
			counterB++;
			reLocate();
			inRangeB = true;
		}else if(temp == false){
			reLocate();
			temp = true;
			inRangeB = true;
		}
		//setEnermy(enermy);
		FFNAnimat::OnCollision(obj);
	}

	virtual float GetFitness()const
	{	
		float score = 0.0;
		float midValue = 0.0;
		if(counterA == 0){
			midValue = 5;
		}else{
			midValue = 1 / counterA;
		}
		score = 1 / (counterB + midValue);
		if(score > 1){
			score = 1;
		}
		counterB = 0;
		//cout << score << endl;
		return score;

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
		//out << " Power used: " << This.PowerUsed;
		out << "current fitness for attack" << GetFitness();
		return out.str();
	}
private:
	double lines;

};

class ShrewSimulation : public Simulation
{
	GeneticAlgorithm<ZumoKing> gaKing;
	GeneticAlgorithm<ZumoQueen> gaQueen;
	Population<ZumoKing> popKing;
	Population<ZumoQueen> popQueen;
	// Group<EvoMouses> grpShrew;
	Group<Circle> theCircle;
	Group<circleCenter> theCircleCenter;

public:
	ShrewSimulation():
	gaKing(0.7f, 0.05f),
	gaQueen(0.7f, 0.05f),
	popKing(2, gaKing),
	popQueen(2, gaQueen),
	theCircle(1),
	theCircleCenter(1)
	{
		This.gaKing.SetSelection(GA_TOURNAMENT);
		This.gaKing.SetParameter(GA_TOURNAMENT_SIZE, 1);
		This.gaQueen.SetSelection(GA_TOURNAMENT);
		This.gaQueen.SetParameter(GA_TOURNAMENT_SIZE, 1);
		popKing.SetTeamSize(1);
		popQueen.SetTeamSize(1);
		SetAssessments(2);
		// if(inRangeA == false || inRangeB)
		This.Add("ZumoKing", This.popKing);
		This.Add("ZumoQueen", This.popQueen);
		
		This.Add("Circle", This.theCircle);
		This.Add("circleCenter", This.theCircleCenter);
		This.SetTimeSteps(500);
	}
};

