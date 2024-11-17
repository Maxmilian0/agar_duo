#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <random>
int main()
{
	int gigantCounter = 0;

	int player1Score = 0;
	int player2Score = 0;
	int numOfGames = 1;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, 1000);

	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Agar duo V.1.0", sf::Style::Close);
	window.setFramerateLimit(60);

	sf::CircleShape player1;
	float player1Speed = 20.f;
	player1.setRadius(15.f);
	player1.setFillColor(sf::Color(10, 10, 100, 200));
	player1.setOutlineThickness(2);
	player1.setOutlineColor(sf::Color(20, 20, 200, 200));
	player1.setPosition(sf::Vector2f(window.getSize().x / 2 - window.getSize().x / 4, window.getSize().y / 2 - player1.getRadius() / 2));

	sf::CircleShape player2;
	float player2Speed = 5.f;
	player2.setRadius(15.f);
	player2.setFillColor(sf::Color(100, 10, 10, 200));
	player2.setOutlineThickness(2);
	player2.setOutlineColor(sf::Color(200, 20, 20, 200));
	player2.setPosition(sf::Vector2f(window.getSize().x / 2 + window.getSize().x / 4, window.getSize().y / 2 - player2.getRadius() / 2));

	sf::CircleShape meal;
	meal.setRadius(10.f);
	meal.setFillColor(sf::Color(10, 100, 10, 250));
	meal.setPosition(sf::Vector2f(distrib(gen), distrib(gen)));

	sf::CircleShape weapon;
	weapon.setRadius(10.f);
	weapon.setFillColor(sf::Color(5, 5, 5, 250));
	weapon.setPosition(sf::Vector2f(distrib(gen), distrib(gen)));

	sf::CircleShape gigant;
	gigant.setRadius(10.f);
	gigant.setFillColor(sf::Color(100, 5, 100, 250));
	gigant.setPosition(1105.f, 1105.f);

	while (window.isOpen()) {
		sf::Event windowEvent;
		while (window.pollEvent(windowEvent)) {
			if (windowEvent.type == sf::Event::Closed) {
				window.close();
			}
			if (windowEvent.KeyPressed && windowEvent.key.code == sf::Keyboard::Escape) {
				window.close();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player1.getPosition().x > 0) {
			player1.move(-player1Speed, 0);
			window.setPosition(sf::Vector2i(window.getPosition().x + player1Speed, window.getPosition().y));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player1.getPosition().x < window.getSize().x - player1.getRadius() * 2) {
			player1.move(player1Speed, 0);
			window.setPosition(sf::Vector2i(window.getPosition().x - player1Speed, window.getPosition().y));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && player1.getPosition().y > 0) {
			player1.move(0, -player1Speed);
			window.setPosition(sf::Vector2i(window.getPosition().x, window.getPosition().y + player1Speed));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && player1.getPosition().y < window.getSize().y - player1.getRadius() * 2) {
			player1.move(0, player1Speed);
			window.setPosition(sf::Vector2i(window.getPosition().x, window.getPosition().y - player1Speed));
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player2.getPosition().x > 0) {
			player2.move(-player2Speed, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && player2.getPosition().x < window.getSize().x - player2.getRadius() * 2) {
			player2.move(player2Speed, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player2.getPosition().y > 0) {
			player2.move(0, -player2Speed);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && player2.getPosition().y < window.getSize().y - player2.getRadius() * 2) {
			player2.move(0, player2Speed);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {

			player2.setRadius(200);
			player2.setPosition(0, 0);
			player2Speed = 15.f;

		}


		if (player1.getGlobalBounds().intersects(meal.getGlobalBounds())) {
			meal.setPosition(distrib(gen), distrib(gen));
			player1.setRadius(player1.getRadius() + 5);
			//player1Speed = player1Speed - player1Speed / 10;
		}
		if (player2.getGlobalBounds().intersects(meal.getGlobalBounds())) {
			meal.setPosition(distrib(gen), distrib(gen));
			player2.setRadius(player2.getRadius() + 5);
			//player2Speed = player2Speed - player2Speed / 10;
		}

		if (player1.getGlobalBounds().intersects(weapon.getGlobalBounds())) {
			weapon.setPosition(distrib(gen), distrib(gen));
			player2.setRadius(player2.getRadius() - 5);
			//player2Speed = player2Speed + player2Speed / 10;
		}
		if (player2.getGlobalBounds().intersects(weapon.getGlobalBounds())) {
			weapon.setPosition(distrib(gen), distrib(gen));
			player1.setRadius(player1.getRadius() - 5);
			//player1Speed = player1Speed + player1Speed / 10;
		}

		if (player1.getGlobalBounds().intersects(gigant.getGlobalBounds()) && gigantCounter < 2) {
			player1.setRadius(player1.getRadius() + 100.f);
			gigantCounter++;
			//player1Speed = 1.f;
			gigant.setPosition(1105.f, 1105.f);
		}
		if (player2.getGlobalBounds().intersects(gigant.getGlobalBounds()) && gigantCounter < 2) {
			player2.setRadius(player2.getRadius() + 100.f);
			gigantCounter++;
			//player2Speed = 1.f;
			gigant.setPosition(1105.f, 1105.f);
		}





		if (player1.getGlobalBounds().intersects(player2.getGlobalBounds())) {
			if (player1.getRadius() > player2.getRadius()) {
				player2.setPosition(sf::Vector2f(window.getSize().x / 2 + window.getSize().x / 4, window.getSize().y / 2 - player2.getRadius() / 2));
				player2.setRadius(15);
				player2Speed = 5.f;
				player1.setPosition(sf::Vector2f(window.getSize().x / 2 - window.getSize().x / 4, window.getSize().y / 2 - player1.getRadius() / 2));
				player1.setRadius(15);
				player1Speed = 1.f;
				gigant.setPosition(distrib(gen), distrib(gen));

				player1Score++; 
				std::cout << numOfGames << ".\t" << player1Score << " : " << player2Score << std::endl;
				numOfGames++;
			}
			if (player2.getRadius() > player1.getRadius()) {
				player1.setPosition(sf::Vector2f(window.getSize().x / 2 - window.getSize().x / 4, window.getSize().y / 2 - player1.getRadius() / 2));
				player1.setRadius(15);
				player1Speed = 1.f;
				gigant.setPosition(distrib(gen), distrib(gen));
				player2.setPosition(sf::Vector2f(window.getSize().x / 2 + window.getSize().x / 4, window.getSize().y / 2 - player2.getRadius() / 2));
				player2.setRadius(15);
				player2Speed = 5.f;
				player2Score++;
				std::cout << numOfGames << ".\t" << player1Score << " : " << player2Score << std::endl;
				numOfGames++;
			}
			if (numOfGames == 11)
			{
				if (player1Score < player2Score) {
					std::cout << "Red wind! Score: " << player1Score << " : " << player2Score << std::endl;
				}
					
				else {
					std::cout << "Blue wind! Score: " << player1Score << " : " << player2Score << std::endl;
				}
			}
		}
		window.clear(sf::Color(50, 50, 50));
		window.draw(player1);
		window.draw(player2);
		window.draw(meal);
		window.draw(weapon);
		if (gigantCounter < 2)
			window.draw(gigant);
		window.display();
	}
	return 0;
}