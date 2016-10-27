#ifndef FOOTEST_H
#define FOOTEST_H

class FooTest : public Test
{
public:
	FooTest() { 
		b2BodyDef myBodyDef;
		myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
		myBodyDef.position.Set(0, 20); //set the starting position
		myBodyDef.angle = 0; //set the starting angle

		b2Body* dynamicBody = m_world->CreateBody(&myBodyDef);

		b2PolygonShape boxShape;
		boxShape.SetAsBox(1, 1);

		b2FixtureDef boxFixtureDef;
		boxFixtureDef.shape = &boxShape;
		boxFixtureDef.density = 1;
		dynamicBody->CreateFixture(&boxFixtureDef);

		#define DEGTORAD 0.0174532925199432957f
		#define RADTODEG 57.295779513082320876f

		dynamicBody->SetTransform(b2Vec2(10, 20), 45 * DEGTORAD); //45 degrees counter-clockwise

		dynamicBody->SetLinearVelocity(b2Vec2(-5, 5)); //moving up and left 5 units per second
		dynamicBody->SetAngularVelocity(-90 * DEGTORAD); //90 degrees per second clockwise

		myBodyDef.type = b2_staticBody; //this will be a static body
		myBodyDef.position.Set(0, 10); //slightly lower position
		b2Body* staticBody = m_world->CreateBody(&myBodyDef); //add body to world
		staticBody->CreateFixture(&boxFixtureDef); //add fixture to body


	
	} //do nothing, no scene yet

	void Step(Settings* settings)
	{
		//run the default physics and rendering
		Test::Step(settings);

		//show some text in the main screen
		g_debugDraw.DrawString(5, m_textLine, "Now we have a foo test");
		m_textLine += 15;
	}

	static Test* Create()
	{
		return new FooTest;
	}
};

#endif