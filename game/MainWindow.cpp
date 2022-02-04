#pragma once

class MainWindow {
public:
	static const int width = 1500;
	static const int height = 1000;
	static sf::Texture texture;
	static sf::Sprite background;
	static void setBackground();
};

sf::Texture MainWindow::texture;
sf::Sprite MainWindow::background;

void MainWindow::setBackground() {
	texture.loadFromFile("..\\img\\bg1.png");
	background.setTexture(texture);
	background.setScale(5.3f, 2.8f);
}