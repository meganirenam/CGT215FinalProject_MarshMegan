#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;

int main()
{
    RenderWindow window(VideoMode(800, 900), "Bounce");
    World world(Vector2f(0, 1)); // Gravity applied downward

    // Ball
    PhysicsCircle ball;
    ball.setCenter(Vector2f(250, 25));
    ball.setRadius(20);
    world.AddPhysicsBody(ball);
    ball.applyImpulse(Vector2f(0.3f, 0.3f));


    // Ceiling
    PhysicsRectangle ceiling;
    ceiling.setSize(Vector2f(800, 20));
    ceiling.setCenter(Vector2f(400, 10));
    ceiling.setStatic(true);
    world.AddPhysicsBody(ceiling);

    // Left wall
    PhysicsRectangle leftWall;
    leftWall.setSize(Vector2f(50, 900));
    leftWall.setCenter(Vector2f(10, 450));
    leftWall.setStatic(true);
    world.AddPhysicsBody(leftWall);

    // Pins
    PhysicsRectangle pinone;
    pinone.setSize(Vector2f(60, 60));
    pinone.setCenter(Vector2f(400, 370));
    pinone.setStatic(true);
    world.AddPhysicsBody(pinone);

    PhysicsRectangle pintwo;
    pintwo.setSize(Vector2f(30, 300));
    pintwo.setCenter(Vector2f(150, 400));
    pintwo.setStatic(true);
    world.AddPhysicsBody(pintwo);

    PhysicsRectangle pinthree;
    pinthree.setSize(Vector2f(30, 300));
    pinthree.setCenter(Vector2f(650, 400));
    pinthree.setStatic(true);
    world.AddPhysicsBody(pinthree);

    PhysicsRectangle pinfour;
    pinfour.setSize(Vector2f(60, 60));
    pinfour.setCenter(Vector2f(270, 150));
    pinfour.setStatic(true);
    world.AddPhysicsBody(pinfour);

    PhysicsRectangle pinfive;
    pinfive.setSize(Vector2f(60, 60));
    pinfive.setCenter(Vector2f(530, 150));
    pinfive.setStatic(true);
    world.AddPhysicsBody(pinfive);


    // Right wall
    PhysicsRectangle rightWall;
    rightWall.setSize(Vector2f(50, 900));
    rightWall.setCenter(Vector2f(790, 450));
    rightWall.setStatic(true);
    world.AddPhysicsBody(rightWall);

    // Flipper
    PhysicsRectangle paddle;
    paddle.setSize(Vector2f(200, 30));
    paddle.setCenter(Vector2f(400, 850));
    paddle.setStatic(true);
    world.AddPhysicsBody(paddle);

    // Points
    int thudCount(1);
    pinfive.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
        cout << " 5 Points " << endl;
        thudCount++;
        };
    pinfour.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
        cout << " 5 Points " << endl;
        thudCount++;
        };
    pinone.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
        cout << " 10 Points " << endl;
        thudCount++;
        };


    // Flipper collisions
    ball.onCollision = [&paddle](PhysicsBodyCollisionResult result) {
        if (&result.object2 == &paddle) {
            Vector2f ballVelocity = result.object1.getVelocity();
            result.object1.setVelocity(Vector2f(ballVelocity.x, -abs(ballVelocity.y)));
        }
        };

    Clock clock;
    Time lastTime(clock.getElapsedTime());

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        // Player flipper controls
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            Vector2f position = paddle.getCenter();
            if (position.x > 75)
                paddle.setCenter(Vector2f(position.x - 0.5f, position.y));
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            Vector2f position = paddle.getCenter();
            if (position.x < 725)
                paddle.setCenter(Vector2f(position.x + 0.5f, position.y));
        }

        // Game over
        Vector2f ballPosition = ball.getCenter();
        if (ballPosition.y > 900) {
            cout << "Game Over! " << endl;
            window.close();
        }

        Time currentTime = clock.getElapsedTime();
        Time deltaTime = currentTime - lastTime;
        int deltaTimeMS = deltaTime.asMilliseconds();
        if (deltaTimeMS > 0) {
            world.UpdatePhysics(deltaTimeMS);
            lastTime = currentTime;
        }

        window.clear(Color(0, 0, 0));
        window.draw(ball);
        window.draw(ceiling);
        window.draw(leftWall);
        window.draw(pinone);
        window.draw(pintwo);
        window.draw(pinthree);
        window.draw(pinfour);
        window.draw(pinfive);
        window.draw(rightWall);
        window.draw(paddle);
        window.display();
    }
}
