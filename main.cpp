#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <sstream>
#include <iostream>

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()



const int MAX_LIVES = 11;
int spentLives = 0;
int guessedAmount = 0;

int amountOfWords = 3;

std::string Word[] = {
	"filip",
	"olofsson",
	"abc"
};

char guessedLetters[26];

sf::RenderWindow window(sf::VideoMode(800, 600), "Hangman");

std::string getWord() {
	srand (time(NULL));
	int random = rand() % amountOfWords;
	return Word[random];
}

bool contains(char a) {
	for(int i = 0; i < guessedAmount; i++) {
		if(guessedLetters[i] == a) {
			return true;
		}
	}
	return false;
}

void addGuessed(char toAdd) {
	if(!contains(toAdd)) {
		guessedLetters[guessedAmount] = toAdd;
		guessedAmount++;
	}
}

int main() {

	std::string randomWord = getWord();

	char foundLetters [randomWord.length()];

	sf::Font font;
	sf::Text guessed;
	sf::Text found;
	sf::Texture man[MAX_LIVES];

	found.setCharacterSize(70);
	found.move(5, 300);
	found.setFont(font);
	found.setColor(sf::Color::Black);

	guessed.setCharacterSize(30);
	guessed.move(5, 400);
	guessed.setFont(font);
	guessed.setColor(sf::Color::Black);

	font.loadFromFile("fonts/BebasNeue.otf");

	for(int i = 0; i < randomWord.length(); i++) {
		foundLetters[i] = '_';
	}

	for(int i = spentLives; i <= MAX_LIVES; i++) {
		man[i].loadFromFile("img/man_" + SSTR(i) + ".png");
		std::cout << "Loading image img/man_" << i << ".png" << std::endl;
	}

	while(window.isOpen() && spentLives < MAX_LIVES) {

		std::string Found;
		for(int i = 0; i < randomWord.length(); i++) {
			Found = Found + foundLetters[i] + " ";
		}
		found.setString(Found);

		std::string Guessed = "Letters guessed: ";
		for(int i = 0; i < guessedAmount; i++) {
			Guessed = Guessed + guessedLetters[i] + ", ";
		}
		guessed.setString(Guessed);
		

		sf::Sprite sprite(man[spentLives]);

		sprite.setScale(1.5, 1.5);


		window.clear(sf::Color::White);
		window.draw(found);
		window.draw(guessed);
		window.draw(sprite);
		window.display();


		std::string input;
		std::cin >> input;
		if(input.length() <= 1) {
			if(randomWord.find(input) == -1 && !contains(input[0])) {
				addGuessed(input[0]);
				spentLives++;
			} else {
				for(int i = 0; i < randomWord.length(); i++) {
					if(randomWord[i] == input[0]) {
						foundLetters[i] = input[0];
					}
				}
				if(foundLetters == randomWord) {
					std::cout << "You win!" << std::endl;
					std::cout << "The word was " << randomWord << std::endl;
				return 0;
				}
			}
		} else {
			std::cout << "Input is longer than 1 so the user guessed a word" << std::endl;
			if(input == randomWord) {
				std::cout << "You win!" << std::endl;
				sf::sleep(sf::milliseconds(3000));
				return 0;
			}
		}
	}
	if(spentLives >= MAX_LIVES) {
		std::cout << "You lost." << std::endl;
		sf::sleep(sf::milliseconds(3000));
		return 0;
	}
}