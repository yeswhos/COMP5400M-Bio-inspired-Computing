// Vim users: for increased viewing pleasure :set ts=4

#include "animat.h"
#include "sensor.h"

// For more information on this file, take a look at Tutorial 1 in the
// BEAST documentation.

using namespace BEAST;

class Shrew : public Animat // Shrew is derived from Animat
{
public:
	Shrew()
	{
		This.Add("left", ProximitySensor<Shrew>(PI/5, 200.0, -PI/20));
		This.Add("right", ProximitySensor<Shrew>(PI/5, 200.0, PI/20));

		This.SetInitRandom(true);	// Start in random locations

		This.Radius = 10.0;			// Shrews are a little bigger than usual
	}
	virtual ~Shrew(){}

	virtual void Control()
	{
		This.Controls["left"] = This.Sensors["right"]->GetOutput();
		This.Controls["right"] = This.Sensors["left"]->GetOutput();
	}
};

class ShrewSimulation : public Simulation
{
	Group<Shrew> grpShrew;

public:
	ShrewSimulation():
	grpShrew(30)
	{
		This.Add("Shrews", This.grpShrew);
	}
};

