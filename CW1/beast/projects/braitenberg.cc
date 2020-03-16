// Vim users: for increased viewing pleasure :set ts=4

#include "beast.h"
#include "animat.h"
#include "sensor.h"

using namespace BEAST;

// Dots are just WorldObjects with the colour set to yellow and the
// radius set to 10. The constructor just allows you to specify a
// location. Dot relies on the default non-solid setting for 
// WorldObject, which means that instead of bumping into Dots, Animats
// slide over them.
class Dot : public WorldObject
{
public:
	Dot(Vector2D l = Vector2D()):WorldObject(l, 0.0, 10.0){SetColour(ColourPalette[COLOUR_YELLOW]);}
	virtual ~Dot(){}

	// This simply adjusts the standard serialisation (save to file) code
	// so that the object remembers it's a 'Dot', rather than a
	// 'WorldObject' - since there are no properties in Dot which
	// WorldObject doesn't have, it's not necessary to add any new
	// serialisation code.
	IMPLEMENT_SERIALISATION("Dot", WorldObject)
};

// Braitenberg is a basic bot inherited from the Animat class, with two
// sensors representing the Braitenberg's left and right light sensors,
// a radius of 10 and a minimum speed of 0, ensuring that the Braitenberg
// does not go backwards when its control output is 0.
class Braitenberg : public Animat
{
public:
	Braitenberg()
	{
		This.Add("left", ProximitySensor<Dot>(PI/2, 75.0, -1));
		This.Add("right", ProximitySensor<Dot>(PI/2, 75.0, 1));

		This.SetInitRandom(true);

		This.SetMinSpeed(0.0);
		This.SetMaxSpeed(95.0);

		This.Radius = 10.0;
	}
};

// This is a Braitenberg with the control function overloaded so that the
// left sensor feeds the left motor, and the right sensor feeds the right
// motor.
class Braitenberg2a : public Braitenberg
{
public:
	virtual void Control()
	{
		This.Controls["left"] = This.Sensors["left"]->GetOutput();
		This.Controls["right"] = This.Sensors["right"]->GetOutput();
	}
};
#include <map>
// This is a Braitenberg with the control function overloaded so that the
// left sensor feeds the right motor, and the right sensor feeds the left
// motor.
class Braitenberg2b : public Braitenberg
{
public:
	virtual void Control()
	{
		This.Controls["left"] = This.Sensors["right"]->GetOutput();
		This.Controls["right"] = This.Sensors["left"]->GetOutput();
	}
};

// Sets up a simple simulation with a series of positioned dots and two
// Braitenberg vehicles.
class BraitenbergSimulation : public Simulation
{
	Group<WorldObject> ExampleWorld;

public:
	BraitenbergSimulation()
	{
		// We set up the ExampleWorld by filling it with instances of
		// the two types of Braitenbergs.
		ExampleWorld.push_back(new Braitenberg2a);
		ExampleWorld.push_back(new Braitenberg2b);

		// Now the Dots are added, initialised with their locations in
		// the world.
		ExampleWorld.push_back(new Dot(Vector2D(150.0, 100.0)));
		ExampleWorld.push_back(new Dot(Vector2D(200.0, 100.0)));
		ExampleWorld.push_back(new Dot(Vector2D(250.0, 100.0)));
		ExampleWorld.push_back(new Dot(Vector2D(300.0, 100.0)));
		ExampleWorld.push_back(new Dot(Vector2D(350.0, 100.0)));
		ExampleWorld.push_back(new Dot(Vector2D(400.0, 100.0)));
		ExampleWorld.push_back(new Dot(Vector2D(400.0, 150.0)));
		ExampleWorld.push_back(new Dot(Vector2D(400.0, 200.0)));
		ExampleWorld.push_back(new Dot(Vector2D(400.0, 250.0)));
		ExampleWorld.push_back(new Dot(Vector2D(400.0, 300.0)));
		ExampleWorld.push_back(new Dot(Vector2D(400.0, 350.0)));
		ExampleWorld.push_back(new Dot(Vector2D(350.0, 350.0)));
		ExampleWorld.push_back(new Dot(Vector2D(300.0, 350.0)));
		ExampleWorld.push_back(new Dot(Vector2D(250.0, 350.0)));
		ExampleWorld.push_back(new Dot(Vector2D(200.0, 350.0)));
		ExampleWorld.push_back(new Dot(Vector2D(200.0, 400.0)));
		ExampleWorld.push_back(new Dot(Vector2D(200.0, 450.0)));
		ExampleWorld.push_back(new Dot(Vector2D(200.0, 500.0)));
		ExampleWorld.push_back(new Dot(Vector2D(200.0, 550.0)));
		ExampleWorld.push_back(new Dot(Vector2D(250.0, 550.0)));
		ExampleWorld.push_back(new Dot(Vector2D(300.0, 550.0)));
		ExampleWorld.push_back(new Dot(Vector2D(350.0, 550.0)));
		ExampleWorld.push_back(new Dot(Vector2D(400.0, 550.0)));
		ExampleWorld.push_back(new Dot(Vector2D(450.0, 550.0)));
		ExampleWorld.push_back(new Dot(Vector2D(500.0, 550.0)));
		ExampleWorld.push_back(new Dot(Vector2D(550.0, 550.0)));
		ExampleWorld.push_back(new Dot(Vector2D(600.0, 550.0)));
		ExampleWorld.push_back(new Dot(Vector2D(600.0, 500.0)));
		ExampleWorld.push_back(new Dot(Vector2D(600.0, 450.0)));
		ExampleWorld.push_back(new Dot(Vector2D(600.0, 400.0)));
		ExampleWorld.push_back(new Dot(Vector2D(600.0, 350.0)));
		ExampleWorld.push_back(new Dot(Vector2D(550.0, 350.0)));
		ExampleWorld.push_back(new Dot(Vector2D(500.0, 350.0)));
		ExampleWorld.push_back(new Dot(Vector2D(500.0, 300.0)));
		ExampleWorld.push_back(new Dot(Vector2D(500.0, 250.0)));
		ExampleWorld.push_back(new Dot(Vector2D(500.0, 200.0)));
		ExampleWorld.push_back(new Dot(Vector2D(500.0, 150.0)));
		ExampleWorld.push_back(new Dot(Vector2D(500.0, 100.0)));
		ExampleWorld.push_back(new Dot(Vector2D(500.0,  50.0)));

		// All the objects in our ExampleWorld Group have now been
		// configured and can now be added to the World.
		Add("ExampleWorld", ExampleWorld);

		// Because we just want the braitenbergs to go on indefinitely,
		// the time limit is set to -1.
		SetTimeSteps(-1);
	}
};

