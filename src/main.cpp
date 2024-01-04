#include "imgui.h"
#include "imgui-SFML.h"

#include "SFML/Graphics.hpp"
#include <box2d/box2d.h>
int main()
{
    sf::RenderWindow window(sf::VideoMode(1366, 768), "Gator Engine");
    
  
    //Create world
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);
    //Create a body def for the ground
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(500, 500);
    //Create a body using the def for the ground
    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    //Create a polygon shape for the ground
    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);
    //Give the ground physical properties
    groundBody->CreateFixture(&groundBox, 0.0f);
    //Create the sprite for the ground
    sf::RectangleShape groundShape(sf::Vector2f(100.0f, 100.0f));
    groundShape.setPosition(500, window.getSize().y - groundBody->GetPosition().y);
    groundShape.setFillColor(sf::Color::Blue);

    //Create a body def for the rigid body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(500, 900);
    //Create a body using the def for the rigid body
    b2Body* body = world.CreateBody(&bodyDef);
    //Create a polygon shape for the rigid body
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);
    //Give the rigid body physical properties
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);

    //Create the sprite for the rigid body
    sf::RectangleShape boxShape(sf::Vector2f(10, 10));
    boxShape.setPosition(500, window.getSize().y - body->GetPosition().y);
    boxShape.setRotation(body->GetAngle());
    boxShape.setFillColor(sf::Color::Red);

    //Data for physics simulation steps
    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    window.setFramerateLimit(60);
    //Attach 

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //Run a physics step at 1/60 of a second
        world.Step(timeStep, velocityIterations, positionIterations);
        //Update sprite positions and rotations based on physics objects
        boxShape.setPosition(body->GetPosition().x, window.getSize().y - body->GetPosition().y);
        boxShape.setRotation(body->GetAngle());

        window.clear();
        window.draw(groundShape);
        window.draw(boxShape);
        window.display();
    }

    return 0;
}