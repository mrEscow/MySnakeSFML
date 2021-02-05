#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <ctime>

int SIZE = 30;

int score = 0;
int BestScore = 0;

unsigned int GORIZONT = SIZE * SIZE;
unsigned int VERTIKAL = SIZE * SIZE / 2;

int lengthSnake = 3;

bool inMenu = true;

enum MENU
{
	BATTnewGame,
	BATTresumeGame,
	BATTexitGame,
	BATTnotBatton

}MENU;

enum Direction
{
	Left,
	Right,
	Up,
	Down
}DIR;

struct Snake
{
	int x = GORIZONT / SIZE / 2;
	int y = VERTIKAL / SIZE / 2;
}snake[100];

void menu(sf::RenderWindow &WIN, sf::Music &musicGame, sf::Music &musicMenu)
{
	musicGame.pause();
	musicMenu.play();

	int lightButton = 200;
	int hitgtButton = 50;

	sf::Font fontMenu;
	fontMenu.loadFromFile("MetroplexShadow.ttf");
	sf::Text menu("", fontMenu, 100);

	menu.setFillColor(sf::Color::Red);
	menu.setStyle(sf::Text::Bold | sf::Text::Underlined);

	menu.setString("MENU");
	sf::FloatRect textRect = menu.getLocalBounds();
	menu.setOrigin(textRect.width / 2, textRect.height / 2);
	menu.setPosition(GORIZONT/2, 0);

	sf::Font batton;
	batton.loadFromFile("aSignboardCpsNrBoldItalic.ttf");

	sf::Text fontNewGame("", batton, 30);
	fontNewGame.setStyle(sf::Text::Bold);
	fontNewGame.setString("  NEW GAME ");
	fontNewGame.setFillColor(sf::Color::Black);
	fontNewGame.setPosition((GORIZONT / 2) - (lightButton / 2), (VERTIKAL / 3) - (hitgtButton / 2));

	sf::Text fontResumeGame("", batton, 30);
	fontResumeGame.setStyle(sf::Text::Bold);
	fontResumeGame.setString("   RESUME  ");
	fontResumeGame.setFillColor(sf::Color::Black);
	fontResumeGame.setPosition((GORIZONT / 2) - (lightButton / 2), (VERTIKAL / 2) - (hitgtButton / 2));

	sf::Text fontExitGame("", batton, 30);
	fontExitGame.setStyle(sf::Text::Bold);
	fontExitGame.setString("     EXIT    ");
	fontExitGame.setFillColor(sf::Color::Black);
	fontExitGame.setPosition((GORIZONT / 2) - (lightButton / 2), (VERTIKAL / 3 * 2) - (hitgtButton / 2));

	sf::RectangleShape battonONE(sf::Vector2f(lightButton, hitgtButton));
	battonONE.setFillColor(sf::Color::Yellow);
	battonONE.setPosition((GORIZONT / 2)-(lightButton/2), (VERTIKAL / 3)-(hitgtButton /2));

	sf::RectangleShape battonTWO(sf::Vector2f(lightButton, hitgtButton));
	battonTWO.setFillColor(sf::Color::Yellow);
	battonTWO.setPosition((GORIZONT / 2) - (lightButton / 2), (VERTIKAL / 2) - (hitgtButton / 2));

	sf::RectangleShape battonTHREE(sf::Vector2f(lightButton, hitgtButton));
	battonTHREE.setFillColor(sf::Color::Yellow);
	battonTHREE.setPosition((GORIZONT / 2) - (lightButton / 2), (VERTIKAL / 3 * 2) - (hitgtButton / 2));

	while (WIN.isOpen())
	{
		sf::Event e2;
		while (WIN.pollEvent(e2))
		{
			if (e2.type == sf::Event::Closed)
				WIN.close();

			if (sf::IntRect((GORIZONT / 2) - (lightButton / 2 ), (VERTIKAL / 3) - (hitgtButton / 2), lightButton, hitgtButton).contains(sf::Mouse::getPosition(WIN)))
			{ 
				battonONE.setFillColor(sf::Color::Red); MENU = BATTnewGame;
			}else 
			{ battonONE.setFillColor(sf::Color::Yellow); }

			if (sf::IntRect((GORIZONT / 2) - (lightButton / 2), (VERTIKAL / 2) - (hitgtButton / 2), lightButton, hitgtButton).contains(sf::Mouse::getPosition(WIN)))
			{
				battonTWO.setFillColor(sf::Color::Red);  MENU = BATTresumeGame;
			}else 
			{ battonTWO.setFillColor(sf::Color::Yellow); }

			if (sf::IntRect((GORIZONT / 2) - (lightButton / 2), (VERTIKAL / 3 * 2) - (hitgtButton / 2), lightButton, hitgtButton).contains(sf::Mouse::getPosition(WIN)))
			{
				battonTHREE.setFillColor(sf::Color::Red);  MENU = BATTexitGame;
			}
			else 
			{ battonTHREE.setFillColor(sf::Color::Yellow); }

			if (!(sf::IntRect((GORIZONT / 2) - (lightButton / 2), (VERTIKAL / 3) - (hitgtButton / 2), lightButton, hitgtButton).contains(sf::Mouse::getPosition(WIN))) &&
				!(sf::IntRect((GORIZONT / 2) - (lightButton / 2), (VERTIKAL / 2) - (hitgtButton / 2), lightButton, hitgtButton).contains(sf::Mouse::getPosition(WIN))) &&
				!(sf::IntRect((GORIZONT / 2) - (lightButton / 2), (VERTIKAL / 3 * 2) - (hitgtButton / 2), lightButton, hitgtButton).contains(sf::Mouse::getPosition(WIN))))
			{
				battonONE.setFillColor(sf::Color::Yellow); MENU = BATTnotBatton;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { inMenu = false; }

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && MENU == BATTnewGame)
			{ 
				lengthSnake = 0;
				score = 0; 
				BestScore = 0; 	
				DIR = Right;
				snake[0].x = GORIZONT / SIZE / 2;
				snake[0].y = VERTIKAL / SIZE / 2;
				lengthSnake = 3;
				inMenu = false;
				musicGame.stop();
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && MENU == BATTresumeGame) { inMenu = false;}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && MENU == BATTexitGame) { WIN.close();}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && MENU == BATTnotBatton) {  }
		}

		if (!inMenu) { break; }

		WIN.clear(sf::Color::Blue);

		WIN.draw(menu);

		WIN.draw(battonONE);
		WIN.draw(fontNewGame);

		WIN.draw(battonTWO);
		WIN.draw(fontResumeGame);

		WIN.draw(battonTHREE);
		WIN.draw(fontExitGame);

		WIN.display();
	}

	musicMenu.stop();
	musicGame.play();
}

struct Apple
{
	int x ;
	int y ;
}apple;

void snakeDie()
{

}

void game(sf::Sound &soundEat, sf::Sound &soundUps)
{


	for (size_t i = lengthSnake; i >= 1; i--)
	{
		snake[i].x = snake[i - 1].x;
		snake[i].y = snake[i - 1].y;
	}

	if (DIR == Right) { snake[0].x +=1 ; }
	if (DIR == Left) { snake[0].x -= 1; }
	if (DIR == Up) { snake[0].y -= 1; }
	if (DIR == Down) { snake[0].y += 1; }

	if (DIR == Right && snake[0].x >= (GORIZONT / SIZE)) { snake[0].x = 0; }
	if (DIR == Left && snake[0].x < 0) { snake[0].x = (GORIZONT / SIZE) - 1; }
	if (DIR == Down && snake[0].y >= (VERTIKAL / SIZE) + 1) { snake[0].y = 1; }
	if (DIR == Up && snake[0].y < 1) { snake[0].y = (VERTIKAL / SIZE); }

	if ((apple.x == snake[0].x) && (apple.y == snake[0].y))
	{
		soundEat.play();
		lengthSnake++;
		apple.x = std::rand() % GORIZONT / SIZE;
		apple.y = 1 + std::rand() % (VERTIKAL / SIZE);
		score++;
	}

	for (size_t i = 1; i < lengthSnake; i++)
	{
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) { soundUps.play(); lengthSnake = 3; snakeDie(); score = 0; }
	}
}

int main()
{
	sf::RenderWindow WIN(sf::VideoMode(GORIZONT, VERTIKAL+SIZE+SIZE), "", sf::Style::None, sf::ContextSettings(0,0,8));

	sf::Music musicGame;
	musicGame.openFromFile("8-Bit Universe - Jingle Bells_(Inkompmusic.ru).ogg");
	musicGame.play();
	musicGame.setVolume(30);
	musicGame.setLoop(true);

	sf::Music musicMenu;
	musicMenu.openFromFile("8-Bit Universe - Teenage Mutant Ninja Turtles Theme_(Inkompmusic.ru).ogg");
	musicMenu.setVolume(30);
	musicMenu.setLoop(true);

	sf::SoundBuffer AppleEat;
	AppleEat.loadFromFile("AppleEat.wav");
	sf::Sound soundEat;
	soundEat.setBuffer(AppleEat);

	sf::SoundBuffer SoundUps;
	SoundUps.loadFromFile("ups.wav");
	sf::Sound soundUps;
	soundUps.setBuffer(SoundUps);

	srand(time(NULL));

	menu(WIN, musicGame, musicMenu);

	sf::RectangleShape block(sf::Vector2f(SIZE, SIZE));
	block.setFillColor(sf::Color::Yellow);
	block.setOutlineThickness(2.f);
	block.setOutlineColor(sf::Color::Blue);

	sf::RectangleShape snakeBlock(sf::Vector2f(SIZE, SIZE));
	snakeBlock.setFillColor(sf::Color::Red);
	snakeBlock.setOutlineThickness(1.f);
	snakeBlock.setOutlineColor(sf::Color::Blue);

	sf::RectangleShape appleBlock(sf::Vector2f(SIZE, SIZE));
	appleBlock.setFillColor(sf::Color::Magenta);
	appleBlock.setOutlineThickness(1.f);
	appleBlock.setOutlineColor(sf::Color::Blue);	

	sf::Clock clock;
	
	apple.x = std::rand() % GORIZONT / SIZE;
	apple.y = 1 + std::rand() % (VERTIKAL / SIZE);
	
	sf::Font font1;
	font1.loadFromFile("aSignboardCpsNrBoldItalic.ttf");

	sf::Text fontscore("", font1, 30);
	fontscore.setStyle(sf::Text::Bold);
	fontscore.setPosition(0, VERTIKAL + SIZE );

	sf::Text fontBestScore("", font1, 30);
	fontBestScore.setStyle(sf::Text::Bold);	

	sf::Text fontESC("", font1, 25);
	fontESC.setStyle(sf::Text::Bold);
	fontESC.setString("--ESC = MENU--");
	fontESC.setPosition(GORIZONT - fontESC.getLocalBounds().width, 0 );

	sf::Text fontSNAKE("", font1, 25);
	fontSNAKE.setStyle(sf::Text::Bold);
	fontSNAKE.setString("--SNAKE--");
	fontSNAKE.setPosition(0, 0);

	while (WIN.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		float speedGame = 0.08;

		sf::Event e;

		while (WIN.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				WIN.close();

			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && DIR !=Left) { DIR = Right; }
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && DIR !=Right){ DIR = Left; }
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && DIR != Down) { DIR = Up; }
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && DIR != Up) { DIR = Down; }

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { inMenu = true; }
		}

		if(inMenu){ menu(WIN, musicGame, musicMenu); }

		if (time > speedGame)
		{
			game(soundEat, soundUps);
			clock.restart();
		}

		if (score >= BestScore) { BestScore = score; }

		WIN.clear();

		for (size_t i = 0; i < GORIZONT / SIZE ; i++)
		{
			for (size_t j = 1; j <= VERTIKAL / SIZE; j++)
			{
				WIN.draw(block);
				block.setPosition(i * SIZE, j * SIZE);
			}
		}

			appleBlock.setPosition(apple.x * SIZE, apple.y * SIZE);
			WIN.draw(appleBlock);

		for (size_t i = 0; i < lengthSnake; i++)
		{
			snakeBlock.setPosition(snake[i].x * SIZE, snake[i].y * SIZE);
			WIN.draw(snakeBlock);
		}

		WIN.draw(fontESC);
		WIN.draw(fontSNAKE);

		std::ostringstream Score;   
		Score << score;		
		fontscore.setString("Score: " + Score.str());
		WIN.draw(fontscore);
		
		std::ostringstream bestScore;  
		bestScore << ( BestScore );		
		fontBestScore.setPosition(GORIZONT - fontBestScore.getLocalBounds().width, VERTIKAL + SIZE);
		fontBestScore.setString("Best score: " + bestScore.str());
		WIN.draw(fontBestScore);

		WIN.display();
	}

	return 0;
}