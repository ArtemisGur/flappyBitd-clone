#include <SFML/Graphics.hpp>
#include <windows.h>
#include <ctime>

class Pipe {
private:
	sf::Texture texture;

public:
	const int WEIGHT = 1500;
	const int HEIGHT = 1000;

	sf::Sprite towerDown;
	sf::Sprite towerUp;

	float height;
	float weight;

	float scaleX;
	float scaleY;

	float vy_tower = 0.004; 

	sf::Vector2f position;

	bool moving;

	static int random(int min, int max)
	{
		return (rand() % (max - min + 1) + min);
	}

	void setDefaultValues(const char path[], float _scaleX, float _scaleY)
	{
		texture.loadFromFile(path);

		sf::Vector2u size = texture.getSize();

		towerUp.setTexture(texture);
		towerDown.setTexture(texture);

		scaleX = _scaleX;
		scaleY = _scaleY;

		towerUp.setScale(scaleX, -scaleY);
		towerDown.setScale(scaleX, scaleY);

		height = size.y * scaleY;
		weight = size.x * scaleX;

		moving = false;
	}


	void ControllTowers(Pipe pipes[], int count, float distance, int* firstTower, float dt, float vy, int *score)
	{
		static int lastTower = 0;	
		for (int i = 0; i < count; i++)
		{
			if (pipes[i].moving)
			{
				float posX = pipes[i].position.x;
				float posY = pipes[i].position.y;

				pipes[i].towerUp.setPosition(posX, posY - 170);
				pipes[i].towerDown.setPosition(posX, posY);

				posX -= vy * dt;

				pipes[i].position.x = posX;
				
			}
		}

		if (WEIGHT - (pipes[lastTower].position.x + pipes[lastTower].weight) >= distance)
		{
			if (lastTower == count - 1) {
				lastTower = 0;
			}
			else {
				lastTower++;
			}

			pipes[lastTower].position.x = WEIGHT;
			pipes[lastTower].moving = true;

			pipes[lastTower].position.y = random(HEIGHT - (int)pipes[lastTower].height, HEIGHT - 120);
			
		}

		if (pipes[*firstTower].position.x + pipes[*firstTower].weight <= 0)
		{
			if (*firstTower == count - 1) {
				(*firstTower) = 0;
			}
			else {
				(*firstTower)++;
			} 
		*score += 1;
		}
	}
};