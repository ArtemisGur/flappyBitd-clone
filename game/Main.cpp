#include <stdio.h>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include "MainWindow.cpp"
#include "Bird.cpp"
#include <sstream>


using namespace sf;

const int WEIGHT = 1500;
const int HEIGHT = 1000;
int random(int min, int max)
{
	return (rand() % (max - min + 1) + min);
}

int main() {
	srand((unsigned int)time(NULL));   
	MainWindow::setBackground();
	Bird *bird = new Bird();
	bool isJump = 0;

	const int countPipes = 4;
	Pipe pipes[countPipes];
	int firstPipe = 0;

	bool isGameOver = false;

	std::ostringstream text;

	int score = 0;
	int oldScore = 0;
	Font font;
	font.loadFromFile("..\\font\\font.ttf");
	Text gameOverWrite;
	Text scoreToWrite;

	gameOverWrite.setFont(font);
	gameOverWrite.setPosition(420, 400);
	gameOverWrite.setString("Game over!");
	gameOverWrite.setCharacterSize(150);
	gameOverWrite.setFillColor(Color::Cyan);
	gameOverWrite.setOutlineThickness(8);
	gameOverWrite.setOutlineColor(Color::Red);
	gameOverWrite.setStyle(Text::Bold);

	scoreToWrite.setFont(font);
	scoreToWrite.setPosition(700, 850);
	scoreToWrite.setCharacterSize(60);
	scoreToWrite.setFillColor(Color::Cyan);
	scoreToWrite.setOutlineThickness(3);
	scoreToWrite.setOutlineColor(Color::Red);
	scoreToWrite.setStyle(Text::Bold);

	for (int i = 0; i < countPipes; i++)
	{
		pipes[i].setDefaultValues("..\\img\\Tower.png", 0.7, 0.7);

		pipes[i].position.x = WEIGHT;
		pipes[i].position.y = random(HEIGHT - (int)pipes[i].height, HEIGHT - 120);
	}

	pipes[firstPipe].moving = true;

	RenderWindow window(VideoMode(MainWindow::width,MainWindow::height), "Flappy Bird");
	while (window.isOpen()) {
		Event event;

		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close(); 
		}
		if (event.key.code == Keyboard::Space) {
			isJump = 0; 
		}
		if (GetAsyncKeyState(VK_SPACE) && isJump == 0) {
			bird->jump();
			isJump = 1;
		}
		if (!isGameOver)
		{
			if (score == 0) {
				std::ostringstream playerScoreString;
				playerScoreString << 0;
				scoreToWrite.setString(playerScoreString.str());
				window.draw(scoreToWrite);
			}
			if (oldScore < score) {
				std::ostringstream playerScoreString;
				playerScoreString << score;
				scoreToWrite.setString(playerScoreString.str());
				oldScore = score;
			}

			bird->animateBird();
			bird->fallDown();
			pipes->ControllTowers(pipes, countPipes, 500, &firstPipe, 250, pipes->vy_tower, &score);
			isGameOver = bird->isCollide(*bird, &pipes[firstPipe]);
			
			

			window.clear(sf::Color::White);
			window.draw(MainWindow::background);
			for (int i = 0; i < countPipes; i++) {
				window.draw(pipes[i].towerUp);
				window.draw(pipes[i].towerDown);
			}
			window.draw(scoreToWrite);
			window.draw(bird->image);
			window.display();
		}
		else {
			window.draw(gameOverWrite);
			window.display();
		}
	}
}
	