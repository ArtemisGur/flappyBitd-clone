#include <SFML/Graphics.hpp>
#include "Pipes.cpp"

using namespace sf;

class Entity {
protected:
	int curFrame = 0;
	float duration = float();
	sf::Texture arrayBirds[4];  
	sf::Clock clock;
	sf::Clock clock1;
	const double boostDown = 0.0000006;
	float vectorY = 0;
	const float velocityUp = 0.009;
};

class Bird:Entity {
public:
	const int WEIGHT = 1500;
	const int HEIGHT = 1000;
	sf::Sprite image;
	float xBird;
	float yBird;
	Bird(float x = 70, float y = 500) {
		arrayBirds[0].loadFromFile("..\\img\\1.png");
		arrayBirds[1].loadFromFile("..\\img\\2.png");
		arrayBirds[2].loadFromFile("..\\img\\1.png");
		arrayBirds[3].loadFromFile("..\\img\\3.png");
		image.setPosition(x, y);
		image.setScale(2, 2);
		xBird = x;
		yBird = y;
	}
	float getCoordX(){
		return xBird;
	}

	float getCoordsY() {
		return yBird;
	}

	void animateBird() {
		sf::Time dt = clock.restart();
		duration += dt.asSeconds();
		if (duration > 0.1f) {
			duration = 0;
			if (curFrame < 3) {
				curFrame += 1;
			}
			else {
				curFrame = 0;
			}
			image.setTexture(arrayBirds[curFrame]);
		}

	}
	
	void fallDown() {
		const float dt = 250;
		clock1.restart();
		vectorY += boostDown * dt;
		yBird += vectorY * dt;
		image.setPosition(getCoordX(), getCoordsY());
	}

	void jump() {
		vectorY = 0;
		vectorY -= velocityUp;
		yBird += vectorY;
		image.setPosition(getCoordX(), getCoordsY());
	}

	bool isCollide(Bird bird, Pipe *tower) {
		bool collision = 0;

		if (bird.yBird < 0) {
			bird.yBird = 0;
		}
		else if (bird.yBird + 24 > HEIGHT) {
			bird.yBird = HEIGHT - 24;
		}

		if (bird.yBird <= tower->towerUp.getPosition().y ||
			bird.yBird + 46 >= tower->towerDown.getPosition().y)
		{
			if (bird.xBird + 50 >= tower->position.x &&
				bird.xBird <= tower->position.x + tower->weight)
			{
				collision = 1;
			}
		}

		return collision;
	}

};


