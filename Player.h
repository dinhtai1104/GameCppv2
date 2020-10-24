#pragma once
#include "Entity.h"
#include "Animation.h"

class Player : public Entity {
private:
	Sprite s;
	
	View view;

	Animation currentAnimation; // animation hien tai
	Animation die, nhay;
	float angle = -20;

	bool isPressed = false;

public:
	Player() {
		view.setSize(500, 500);
		currentAnimation = Animation(5, "", 1);
		currentAnimation.setTexture(s);
		this->body.setSize((Vector2f)s.getTexture()->getSize());
		this->body.setOrigin((Vector2f)s.getTexture()->getSize() * 0.5f);

		s.setPosition(250, 250);
	}

	void Update() {
		Entity::Update();
		// update animation
		currentAnimation.Update();
		currentAnimation.setTexture(s);
		
		// Handle Input
		Input();

		Move(this->velocity);
		
	}


	bool isRight = true;

	void Flip() {
		Vector2f localScale = s.getScale();
		localScale.x *= -1;
		isRight = !isRight;

		s.setScale(localScale);
	}

	void setView(RenderWindow& rd) {
		rd.setView(view);
	}

	void setCenterView() {
		view.setCenter(this->body.getPosition());
	}

	void recognizeEvent(Event evt) {
		if (evt.type == Event::KeyReleased) {
			isPressed = false;
		}
	}

	void Input() {
		angle += 3;
		if (this->isGround) {
			angle = 0;
		}
		s.setRotation(angle);

		if (Keyboard::isKeyPressed(Keyboard::Space) && !isPressed) {
			this->velocity.y = -5;
			this->angle = -40;
			isPressed = true;
		}
		///*else isPressed = fals*/e;

		if (Keyboard::isKeyPressed(Keyboard::Left) && isRight) {
			Flip();
		}
		if (Keyboard::isKeyPressed(Keyboard::Right) && !isRight) {
			Flip();
		}
	}

	void Move(Vector2f velocity) {
		s.move(velocity);
		this->view.move(velocity);
		this->body.setPosition(s.getPosition());
	}

	void Draw(RenderWindow& rd) {
		Entity::Draw(rd);
		rd.draw(s);
	}


};