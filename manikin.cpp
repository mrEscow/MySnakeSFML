#include <SFML/Graphics.hpp>

int SIZE = 30;

unsigned int GORIZONT = SIZE * SIZE;
unsigned int VERTIKAL = SIZE * SIZE / 2;

int lengthSnake = 3;

bool inMenu = true;

void menu(sf::RenderWindow &WIN)
{
	sf::Font font;//шрифт 
	font.loadFromFile("MetroplexShadow.ttf");//передаем нашему шрифту файл шрифта
	sf::Text menu("", font, 100);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)

	//text.setColor(sf::Color::Red);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	menu.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый	

	menu.setString("MENU");//задает строку тексту
	sf::FloatRect textRect = menu.getLocalBounds();
	menu.setOrigin(textRect.width / 2, textRect.height / 2);
	menu.setPosition(GORIZONT/2, 0);//задаем позицию текста, центр камеры
	
	int lightButton = 200;
	int hitgtButton = 50;

	sf::RectangleShape battonONE(sf::Vector2f(lightButton, hitgtButton));
	battonONE.setPosition((GORIZONT / 2)-(lightButton/2), (VERTIKAL / 3)-(hitgtButton /2));

	sf::RectangleShape battonTWO(sf::Vector2f(lightButton, hitgtButton));
	battonTWO.setPosition((GORIZONT / 2) - (lightButton / 2), (VERTIKAL / 2) - (hitgtButton / 2));

	sf::RectangleShape battonTHREE(sf::Vector2f(lightButton, hitgtButton));
	battonTHREE.setPosition((GORIZONT / 2) - (lightButton / 2), (VERTIKAL / 3 * 2) - (hitgtButton / 2));

	while (WIN.isOpen())
	{
		sf::Event e2;
		while (WIN.pollEvent(e2))
		{
			if (e2.type == sf::Event::Closed)
				WIN.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { inMenu = false; }
		}
		
		if (!inMenu) { break; }

		WIN.clear(sf::Color::Blue);
		WIN.draw(menu);//рисую этот текст
		WIN.draw(battonONE);
		WIN.draw(battonTWO);
		WIN.draw(battonTHREE);
		WIN.display();
	}

}


enum Direction
{
	Left,
	Right,
	Up,
	Down
}DIR;

struct Snake
{
	int x;
	int y;
}snake[100];

struct Apple
{
	int x;
	int y;
}apple;

void snakeDie()
{

}

void game()
{
	for (size_t i = lengthSnake; i > 0; i--)
	{
		snake[i].x = snake[i - 1].x;
		snake[i].y = snake[i - 1].y;
	}

	if (DIR == Right) { snake[0].x +=1 ; }
	if (DIR == Left) { snake[0].x -= 1; }
	if (DIR == Up) { snake[0].y -= 1; }
	if (DIR == Down) { snake[0].y += 1; }

	if ((apple.x == snake[0].x) && (apple.y == snake[0].y))
	{
		lengthSnake++;
		apple.x = std::rand() % GORIZONT / SIZE;
		apple.y = std::rand() % VERTIKAL / SIZE;
	}

	for (size_t i = 1; i < lengthSnake; i++)
	{
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) { lengthSnake = 3; snakeDie(); }
	}

	if (DIR == Right && snake[0].x >= (GORIZONT / SIZE)) { snake[0].x = 0;  }
	if (DIR == Left && snake[0].x < 0) { snake[0].x = (GORIZONT / SIZE)-1;  }
	if (DIR == Down && snake[0].y >= (VERTIKAL / SIZE)) { snake[0].y = 0;  }
	if (DIR == Up && snake[0].y < 0) { snake[0].y = (VERTIKAL / SIZE)-1;  }
}



int main()
{
	sf::RenderWindow WIN(sf::VideoMode(GORIZONT, VERTIKAL), "SNAKE", sf::Style::Default, sf::ContextSettings(0,0,8));

	menu(WIN);

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

	DIR = Right;

	sf::Clock clock;
	
	apple.x = std::rand() % GORIZONT / SIZE;
	apple.y = std::rand() % VERTIKAL / SIZE;

	while (WIN.isOpen())
	{

		float time = clock.getElapsedTime().asSeconds();
		float speedGame = 0.08;

		sf::Event e;

		while (WIN.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				WIN.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && DIR !=Left) { DIR = Right; }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && DIR !=Right){ DIR = Left; }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && DIR != Down) { DIR = Up; }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && DIR != Up) { DIR = Down; }

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { inMenu = true; }
		}

		if(inMenu){ menu(WIN); }

		if (time > speedGame)
		{
			game();
			clock.restart();
		}

		WIN.clear();

		for (size_t i = 0; i < GORIZONT / SIZE ; i++)
		{
			for (size_t j = 0; j < VERTIKAL / SIZE; j++)
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

		WIN.display();
	}

	return 0;
}