#include "SFML/Graphics.hpp"
#include <iostream>
#include "Animation.h"
#include <vector>
#include "Entity.h"
#include "Player.h"
#include "Ground.h"
#include "Pipe.h"
using namespace std;
using namespace sf;


enum STATE {ATTACK, DEFENSE, BEAMSATTACK};

int main() {

	/*
		Animation: loat cac anh.
	
	*/
	RenderWindow window(VideoMode(500, 500), "Hello World");
	window.setFramerateLimit(60);

	Entity* player = new Player();
	Entity* ground = new Ground();
	Entity* pipe = new Pipe(Vector2f(50, 400), Vector2f(700, 0), 100, 3);
	Entity* pipe2 = new Pipe(Vector2f(50, 400), Vector2f(300, 0), 100, 3);



	View view(Vector2f(0, 0), Vector2f(500, 500));
	//view.setViewport(FloatRect(00, 0, 500, 500));
	player->setView(window);
	//cout << "OK";
	bool isPressed = false;
	player->setCenterView();

	RectangleShape p(Vector2f(16, 16));
	p.setPosition(300, 300);
	view.setCenter(p.getPosition());



	Image img;
	if (img.loadFromFile("Map.png")) {
		cout << "Load successfull!";
	}
	// Load map
	vector<RectangleShape> mapGame;

	for (int y = 0; y < img.getSize().y; y++) {
		for (int x = 0; x < img.getSize().x; x++) {
			if (img.getPixel(x, y).a == 255) { // so sánh màu trên pixel map rồi generate nó ra
				RectangleShape shape(Vector2f(16, 16));
				shape.setPosition(16 * x, 16 * y);
				shape.setFillColor(Color::Red);
				mapGame.push_back(shape);
			}
		}
	}



	while (window.isOpen()) {
		
		// Nhận sự kiện
		Event evt;
		view.setCenter(p.getPosition());

		while (window.pollEvent(evt)) {
			switch (evt.type)
			{
			case Event::Closed:
				window.close();
				break;
			
			case Event::MouseButtonReleased:
				cout << "Mouse Released\n";
				break;
			//case Event::KeyReleased:
			//	//velocity.x = 0;
			//	isPressed = false;
			//	break;
			/*case Event::KeyPressed:
				cout << "OK\n";
				break;*/

			default:
				break;
			}
			player->recognizeEvent(evt);
		}
		
		if (Mouse::isButtonPressed(Mouse::Left)) p.move(-1, 0);
		if (Mouse::isButtonPressed(Mouse::Right)) p.move(1, 0);
		if (Keyboard::isKeyPressed(Keyboard::Up)) p.move(0, -1);
		if (Keyboard::isKeyPressed(Keyboard::Down)) p.move(0, 1);
		window.setView(view);

		/*if (Keyboard::isKeyPressed(Keyboard::Space) && !isPressed) {
			isPressed = true;
			cout << "OK\n";
		}*/

		//player->isCollision(ground);
		//pipe->isCollision(player);
		//pipe2->isCollision(player);
		//player->Update();
		//pipe->Update();
		//pipe2->Update();
		 //Xóa màn hình
		window.clear();


		//// Vẽ
		window.draw(p);
		for (auto z : mapGame) {
			window.draw(z);
		}

		//pipe->Draw(window);
		//pipe2->Draw(window);
		//player->Draw(window);
		//ground->Draw(window);
		window.display();


	}


	return 0;
}