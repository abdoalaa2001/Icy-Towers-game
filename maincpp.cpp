#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include<iostream>
#include<sstream>
#include<fstream>
using namespace sf;
using namespace std;

RenderWindow window(VideoMode(800, 600), "Icy Tower");

//variable
bool move_tower = 0, on_stair = 0, move_left = 0, move_right = 0, fall = 0, firstback = true, soundisplay = true, pause = true, death = false, stop = false, about_fall = 0, sp = false;
float  m_sprite_up = 0, m_sprite_right = 0, m_sprite_left = 0, m_stair = float(0.5), m_tower = m_stair / 6, Gravity = 0;
Vector2f PosStair, PosSprite, Pospole_right, Pospole_right1, Pospole_left, Pospole_left1, Posrec_background, Posrec_background1, stair_size;
IntRect player(0, 0, 75, 76);
int  minutes = 0, counter = 0;
unsigned long long  currentScore = 0;
RectangleShape rec_background1;
RectangleShape right_pole;
RectangleShape right_pole1;
RectangleShape left_pole;
RectangleShape left_pole1;
RectangleShape rec_background;
RectangleShape recStair(Vector2f(200.0f, 50.0f));
RectangleShape platform(Vector2f(620.0f, 50.0f));
Sprite sprite;
Texture pole_right;
Texture pole_left;
Texture back;
Texture tstairs;
Texture texture;
Texture arrowtexture;
Clock c;
Time clocktime;
Time clockfirst;

//sound---------
SoundBuffer buffer;
Sound sound;
//------------


Text scoresave;
Text selectarr[4];
Texture texturebackground[6];
Sprite background2;
Texture texturesound[2];
Sprite soundicon;
Text textarr[3];
Sprite arrowsprite;
Texture watchtex;
Sprite watchsprite;
RectangleShape hourhandline;
CircleShape circle;
Text scoreCurrent;
Text score;
Text clocktext;
String playerInput = " ";
Text playerText;
Text setname;




void drawifl_s() {

	if (death)
	{
		window.draw(textarr[0]);
		sp = false;
		score.setPosition(300, 340);
		scoreCurrent.setPosition(450, 340);
		score.setCharacterSize(45);
		scoreCurrent.setCharacterSize(45);
		window.draw(playerText);
		window.draw(setname);
		window.draw(scoresave);
	}
	if (stop)
	{
		textarr[1].setString("continue");

		for (int i = 1; i < 3; i++)
		{
			window.draw(textarr[i]);
		}

	}


}
void setarrow()
{
	arrowtexture.loadFromFile("graphics/arrow.png");
	arrowsprite.setTexture(arrowtexture);
	arrowsprite.setPosition(20, 20);

}
void sound_stop()
{
	soundicon.setTexture(texturesound[1]);
	soundisplay = false;

}
void sound_play()
{
	soundicon.setTexture(texturesound[0]);
	soundisplay = true;
}
struct st
{
	RectangleShape s;
	unsigned long long n;
}stair[6];
void start()
{
	tstairs.loadFromFile("graphics/stair.png");
	back.loadFromFile("graphics/background.jpg");
	pole_right.loadFromFile("graphics/right pole.png");
	pole_left.loadFromFile("graphics/left pole.png");
	hourhandline.setOrigin(circle.getOrigin());
	clocktext.setPosition(680, 550);
	scoreCurrent.setPosition(120, 550);
	score.setPosition(10, 550);
	clocktext.setPosition(647, 550);

	hourhandline.setRotation(-90);
	minutes = 0;
	clocktime = seconds(0);
	hourhandline.setPosition(174 + 230 + 363, 101 - 48);

	score.setCharacterSize(35);
	scoreCurrent.setCharacterSize(35);
	sp = false;
	float StairSpace = 570;
	fall = 0;
	move_tower = 0;
	right_pole.setPosition(800 - 100, 0);
	right_pole1.setPosition(800 - 100, -600);
	left_pole.setPosition(0, 0);
	left_pole1.setPosition(0, -600);
	rec_background.setPosition(90, 0);
	rec_background1.setPosition(90, -600);
	platform.setPosition(90, 600 - 30);
	sprite.setPosition(380, 550 - 76);
	m_sprite_left = 0;
	m_sprite_right = 0;
	m_sprite_up = 0;
	Gravity = 0;
	m_stair = float(0.5);
	m_tower = m_stair / 6;
	currentScore = 0;
	for (unsigned long long i = 0; i < 6; i++)
	{
		stair[i].s = recStair;
		stair[i].s.setSize(Vector2f((rand() % 200) + 100.0f, 50.0f));
		stair_size = stair[i].s.getSize();
		stair[i].s.setPosition(float((rand() % int(600 - stair_size.x))) + 100, StairSpace -= 100);
		stair[i].n = unsigned long long(i + 1);
	}
}
void tower()
{
	Posrec_background1 = rec_background1.getPosition();
	Posrec_background = rec_background.getPosition();
	Pospole_left1 = left_pole1.getPosition();
	Pospole_left = left_pole.getPosition();
	Pospole_right1 = right_pole1.getPosition();
	Pospole_right = right_pole.getPosition();
	if (Posrec_background1.y >= 600)
	{
		rec_background1.setPosition(90, Posrec_background1.y - 1200);
	}
	if (Posrec_background.y >= 600)
	{
		rec_background.setPosition(90, Posrec_background.y - 1200);
	}
	if (Pospole_left1.y >= 600)
	{
		left_pole1.setPosition(0, Pospole_left1.y - 1200);
	}
	if (Pospole_left.y >= 600)
	{
		left_pole.setPosition(0, Pospole_left.y - 1200);
	}
	if (Pospole_right1.y >= 600)
	{
		right_pole1.setPosition(700, Pospole_right1.y - 1200);
	}
	if (Pospole_right.y >= 600)
	{
		right_pole.setPosition(700, Pospole_right.y - 1200);
	}
	window.draw(rec_background);
	window.draw(left_pole);
	window.draw(right_pole);
	window.draw(rec_background1);
	window.draw(left_pole1);
	window.draw(right_pole1);
	if (stop || death)
	{
		window.draw(arrowsprite);
	}
}
void game()
{
	string s, m;
	stringstream ss, sm, s2;

	Text stair_num;
	Font font;
	font.loadFromFile("fonts/FORTE.ttf");
	stair_num.setFont(font);
	stair_num.setCharacterSize(20);

	if (move_tower) {
		sp = true;

	}
	for (int i = 0; i < 6; i++)
	{
		window.draw(stair[i].s);

		if (PosSprite.y <= 150 && PosSprite.y != 0 && !stop)
		{
			stair[i].s.move(0, abs(m_stair * 250 / PosSprite.y));
			sprite.move(0, abs(m_stair * 250 / PosSprite.y / 6));
			if (!stop) {
				right_pole.move(0, abs(m_tower * 250 / PosSprite.y));
				right_pole1.move(0, abs(m_tower * 250 / PosSprite.y));
				left_pole.move(0, abs(m_tower * 250 / PosSprite.y));
				left_pole1.move(0, abs(m_tower * 250 / PosSprite.y));
				rec_background.move(0, abs(m_tower * 250 / PosSprite.y));
				rec_background1.move(0, abs(m_tower * 250 / PosSprite.y));
			}
			fall = 1;
		}
		if (move_tower == 1)
		{
			if (!stop)
			{
				right_pole.move(0, m_tower);
				right_pole1.move(0, m_tower);
				left_pole.move(0, m_tower);
				left_pole1.move(0, m_tower);
				rec_background.move(0, m_tower);
				rec_background1.move(0, m_tower);
				stair[i].s.move(0, m_stair);

				sprite.move(0, m_stair / 6);
			}
		}
		stair_size = stair[i].s.getSize();
		PosStair = stair[i].s.getPosition();
		if (on_stair == 0)
		{
			if ((PosSprite.y + 35 >= PosStair.y && PosSprite.y + 25 < PosStair.y) && (PosSprite.x > PosStair.x&& PosSprite.x < PosStair.x + stair_size.x))
			{
				if (stair[i].n >= 6)
				{
					move_tower = 1;
				}
				currentScore = stair[i].n * 10;
				stair_size = stair[i].s.getSize();
				Gravity = 0;
				m_sprite_up = 0;
				if (PosSprite.x - 10 < PosStair.x)
				{
					about_fall = 1;
					if (c.getElapsedTime().asMilliseconds() > 150.0f) {
						if (player.left == 75 * 14 || (player.left < 75 * 13 || player.left > 75 * 14))
							player.left = 75 * 13;
						else
							player.left += 75;
						sprite.setTextureRect(player);
						c.restart();
					}
				}
				if (PosSprite.x + 10 > PosStair.x + stair_size.x)
				{
					about_fall = 1;
					if (c.getElapsedTime().asMilliseconds() > 150.0f) {
						if (player.left == 75 * 12 || (player.left < 75 * 11 || player.left > 75 * 12))
							player.left = 75 * 11;
						else
							player.left += 75;
						sprite.setTextureRect(player);
						c.restart();
					}
				}
			}
		}


		if (PosStair.y >= 600)
		{
			stair[i].n += 6;
			if (stair[i].n % 200 == 0)
			{
				stair[i].s.setSize(Vector2f(620.0f, 50.0f));
				stair[i].s.setPosition(90, PosStair.y - 600);
				tstairs.loadFromFile("graphics/stair.png");
				back.loadFromFile("graphics/background.jpg");
				pole_right.loadFromFile("graphics/right pole.png");
				pole_left.loadFromFile("graphics/left pole.png");
			}
			else if (stair[i].n % 100 == 0)
			{
				stair[i].s.setSize(Vector2f(620.0f, 50.0f));
				stair[i].s.setPosition(90, PosStair.y - 600);
				tstairs.loadFromFile("graphics/stair2.png");
				back.loadFromFile("graphics/background2.jpg");
				pole_right.loadFromFile("graphics/right pole2.png");
				pole_left.loadFromFile("graphics/left pole2.png");
			}
			else
			{
				stair[i].s.setSize(Vector2f((rand() % 200) + 100.0f, 50.0f));
				stair_size = stair[i].s.getSize();
				stair[i].s.setPosition(float((rand() % int(600 - stair_size.x))) + 100, PosStair.y - 600);
			}
		}
		if ((stair[i].n) % 10 == 0)
		{
			ss << stair[i].n << endl;
			s = ss.str();
			ss.clear();
			ss.str("");
			stair_num.setOrigin(sf::Vector2f((s.length() * 20) / 4, 12));
			stair_num.setString(s);
			stair_num.setFillColor(Color::Black);
			stair_num.setPosition(PosStair.x + stair_size.x / 2, PosStair.y + 25);
			window.draw(stair_num);
		}
	}
	if (!death && !stop) {
		window.draw(watchsprite);
		window.draw(circle);
		window.draw(hourhandline);
	}
}
void rp()
{
	pole_right.loadFromFile("graphics/right pole.png");
	right_pole.setSize(Vector2f(100, 610));
	right_pole.setTexture(&pole_right);
	right_pole1.setSize(Vector2f(100, 610));
	right_pole1.setTexture(&pole_right);
}
void lp()
{
	pole_left.loadFromFile("graphics/left pole.png");
	left_pole.setSize(Vector2f(100, 610));
	left_pole.setTexture(&pole_left);
	left_pole1.setSize(Vector2f(100, 610));
	left_pole1.setTexture(&pole_left);
}
void bk()
{
	back.loadFromFile("graphics/background.JPG");
	rec_background.setSize(Vector2f(620, 610));
	rec_background.setTexture(&back);
	rec_background1.setSize(Vector2f(620, 610));
	rec_background1.setTexture(&back);
}
void setwatch() {
	watchtex.loadFromFile("graphics/watch.png");
	watchsprite.setTexture(watchtex);
	watchsprite.setPosition(100 + 230 + 360, 20 + 30 - 70);


}
void sethourhand1() {
	hourhandline.setFillColor(Color::Black);
	hourhandline.setPosition(174 + 230 + 3603, 101 - 33);
	hourhandline.setSize(Vector2f(25, 5));
	hourhandline.setRotation(-90);
	hourhandline.setOrigin(circle.getOrigin());


}
void setcircle() {

	circle.setFillColor(Color::Black);
	circle.setRadius(7);
	circle.setPosition(170 + 593, 50);
	circle.setOrigin(3.5, 2);

}
void stairs()
{
	tstairs.loadFromFile("graphics/stair.PNG");
	recStair.setTexture(&tstairs);
	platform.setTexture(&tstairs);
}
void character()
{
	texture.loadFromFile("graphics/player.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(player);
	sprite.setOrigin(75 / 2, 76 / 2);
}
void soundGame()
{
	buffer.loadFromFile("sounds/s.ogg");
	sound.setBuffer(buffer);
	sound.setVolume(30);
	sound.play();
	sound.setLoop(1);
}

void drawifpause()
{

	window.draw(background2);
	window.draw(soundicon);
	if (firstback)
	{
		for (int i = 0; i < 4; i++)
		{
			window.draw(selectarr[i]);
		}
	}
	if (!firstback)
	{
		window.draw(arrowsprite);

	}
}
void setoutbackground()
{

	texturebackground[2].loadFromFile("graphics/background1.gif");

	texturebackground[1].loadFromFile("graphics/develop1.gif");
	texturebackground[0].loadFromFile("graphics/how to play.png");
	background2.setTexture(texturebackground[2]);

}
void setsound()
{
	texturesound[0].loadFromFile("graphics/soundicon_on.gif");
	texturesound[1].loadFromFile("graphics/soundicon_off.gif");
	soundicon.setTexture(texturesound[0]);
	soundicon.setPosition(735, 21);
}
void outerselectifup()
{
	for (int i = 1; i < 4; i++)
	{

		if (selectarr[i].getFillColor() == Color::Red)
		{
			selectarr[i - 1].setFillColor(Color::Red);
			selectarr[i].setFillColor(Color::White);
			break;

		}
	}
}
void  outerselectifdown()
{
	for (int i = 0; i < 3; i++)
	{

		if (selectarr[i].getFillColor() == Color::Red)
		{

			selectarr[i + 1].setFillColor(Color::Red);
			selectarr[i].setFillColor(Color::White);
			break;
		}
	}

}
void ifselect()
{

	for (int i = 0; i < 2; i++)
	{
		if (selectarr[i].getFillColor() == Color::Red)
		{
			background2.setTexture(texturebackground[i]);
			firstback = false;

		}
	}



	if (selectarr[2].getFillColor() == Color::Red)
	{
		pause = false;
		start();


	}
}
void innerup_down()
{
	if (textarr[1].getFillColor() == Color::Red)
	{
		textarr[2].setFillColor(Color::Red);
		textarr[1].setFillColor(Color::White);
	}
	else if (textarr[2].getFillColor() == Color::Red)
	{
		textarr[1].setFillColor(Color::Red);
		textarr[2].setFillColor(Color::White);
	}
}
void ifselectinner()
{
	if (textarr[1].getFillColor() == Color::Red && stop)
	{
		stop = false;
	}
	if (textarr[2].getFillColor() == Color::Red)
	{
		stop = false;
		start();
	}
}




int main()
{
	window.setFramerateLimit(144);


	Font font;
	font.loadFromFile("fonts/FORTE.ttf");

	//name------
	setname.setFont(font);
	setname.setCharacterSize(40);
	setname.setFillColor(Color::White);
	setname.setPosition(300, 400);
	setname.setString("name:");

	//score save------
	scoresave.setFont(font);
	scoresave.setCharacterSize(40);
	scoresave.setFillColor(Color::Cyan);
	scoresave.setPosition(150, 500);
	scoresave.setString("Press Enter to save the score");

	playerText.setFont(font);
	playerText.setCharacterSize(40);
	playerText.setFillColor(Color::White);
	playerText.setPosition(400, 400);

	//-----------------

	score.setFont(font);
	score.setFillColor(sf::Color::White);
	score.setString("Score:");
	score.setCharacterSize(35);
	score.setPosition(320, 0);
	//score-------
	scoreCurrent.setFont(font);
	scoreCurrent.setFillColor(Color::White);
	scoreCurrent.setCharacterSize(35);
	scoreCurrent.setPosition(120, 590);
	//------------

	clocktext.setFont(font);
	clocktext.setFillColor(Color::White);
	clocktext.setCharacterSize(30);
	clocktext.setPosition(780, 590);




	//outertext----
	for (int i = 0; i < 4; i++)
	{
		selectarr[i].setFont(font);
		selectarr[i].setFillColor(Color::White);
		selectarr[i].setCharacterSize(42);
	}

	selectarr[0].setString("How to play");
	selectarr[0].setPosition(150, 320);
	selectarr[0].setFillColor(Color::Red);


	selectarr[1].setString("developers");
	selectarr[1].setPosition(387, 370);

	selectarr[2].setString("Start");
	selectarr[2].setFillColor(Color::White);
	selectarr[2].setCharacterSize(46);
	selectarr[2].setPosition(338, 456);

	selectarr[3].setString("Exit");
	selectarr[3].setPosition(520, 530);
	//-----------------------


	//innertext--------------------
	textarr[0].setString("Game over");
	textarr[0].setFillColor(Color::Red);
	textarr[0].setCharacterSize(100);
	textarr[0].setPosition(175, 208);

	textarr[1].setString("Continue");
	textarr[1].setCharacterSize(80);
	textarr[1].setPosition(265, 250);
	textarr[1].setFillColor(Color::Red);

	textarr[2].setString("new game");
	textarr[2].setCharacterSize(52);
	textarr[2].setPosition(292, 365);
	for (int i = 0; i < 3; i++)
	{
		textarr[i].setFont(font);
	}
	//---------------------------
	//ifpause--------
	setoutbackground();

	setsound();

	//-----------------


	setarrow();
	////////shapes
	//right pole
	rp();

	//left pole
	lp();

	//backgound
	bk();

	//stairs
	stairs();

	setwatch();
	sethourhand1();
	setcircle();
	//Character
	character();

	//song
	//soundGame();
	soundGame();

	start();

	//int score = 0;

	//game loop
	Clock clock;
	while (window.isOpen())
	{
		Time clockfirst = clock.restart();

		Event evnt;
		while (window.pollEvent(evnt))
		{

			//soundoff_on---------
			if (evnt.type == Event::KeyPressed)
			{
				if (evnt.key.code == Keyboard::M && !death)
				{
					if (soundisplay)
					{
						sound.pause();
						sound_stop();

					}
					else if (!soundisplay)
					{
						sound.play();
						sound_play();

					}
				}
			}

			if (!pause && death) {
				if (evnt.type == Event::TextEntered)
				{
					if (Keyboard::isKeyPressed(Keyboard::BackSpace))
					{
						playerInput = " ";
						counter = 0;
					}
					else if (Keyboard::isKeyPressed(Keyboard::Enter))
					{
						ofstream scorefile("score.txt", ios::app);
						scorefile << string(playerInput) << "   " << currentScore << "   " << minutes << " m    " << clocktime.asSeconds() << " s" << endl;
						scorefile.close();
					}
					else if (counter < 7)
					{
						playerInput += evnt.text.unicode;
						counter++;
					}
					playerText.setString(playerInput);
				}
			}
			//innerselect--------------
			if ((evnt.type == Event::KeyPressed) && !pause && stop)
			{
				if ((evnt.key.code == Keyboard::Up) ||
					(evnt.key.code == Keyboard::Down))
					innerup_down();
			}

			if ((evnt.type == Event::KeyPressed) && !pause && (death || stop))
			{
				if (evnt.key.code == Keyboard::Left)
				{
					pause = true;
					stop = false;
					death = false;
				}
			}
			//outerselect-----------
			if (pause)
			{


				if (evnt.type == Event::KeyPressed)
				{
					if (evnt.key.code == Keyboard::Up)
					{
						outerselectifup();
					}
					if (evnt.key.code == Keyboard::Down)
						outerselectifdown();
				}
			}
		}

		//outerselectyes------------
		if (Keyboard::isKeyPressed(Keyboard::Enter) && pause)
		{
			ifselect();

			if (selectarr[3].getFillColor() == Color::Red) {
				window.close();
			}
		}
		//changebackground--------------
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			background2.setTexture(texturebackground[2]);
			firstback = true;
		}
		//-------------------------
		if (Keyboard::isKeyPressed(Keyboard::Escape) && !pause && !death)
		{
			stop = true;
		}

		if (Keyboard::isKeyPressed(Keyboard::Enter) && stop)
		{
			ifselectinner();
		}



		if (!pause) {
			window.clear();


			if (!death && !stop) {


				if (sp) {
					clocktime += clockfirst;
				}


				if (clocktime <= seconds(60) && sp)
				{

					hourhandline.rotate(float(0.042));
					hourhandline.setOrigin(circle.getOrigin());

				}
				//clocktime += clockfirst;
				if (clocktime.asSeconds() >= 60) {
					clocktime = seconds(0);
					minutes += 1;
					m_stair += float(0.2);
					m_tower = m_stair / 6;
				}
			}
			tower();

			PosSprite = sprite.getPosition();
			game();

			if (fall == 0)
			{
				window.draw(platform);
				if (PosSprite.y + 10 >= 550 && PosSprite.y < 550)
				{
					Gravity = 0;
					m_sprite_up = 0;
					currentScore = 0;
				}
			}
			else if (PosSprite.y - 35 >= 600)
			{
				move_tower = 0;
				death = true;
			}
			if (!stop && !death) {
				if (Gravity < 0.2 && on_stair == 0)
				{
					if (Keyboard::isKeyPressed(Keyboard::Key::Space) || Keyboard::isKeyPressed(Keyboard::Key::Up))
					{
						on_stair = 1;
						m_sprite_up = -5;
					}
				}
				move_left = 0;
				move_right = 0;
				if (Keyboard::isKeyPressed(Keyboard::Key::Right) && PosSprite.x + 15 < 700 && !Keyboard::isKeyPressed(Keyboard::Key::Left))
				{
					move_left = 1;
					m_sprite_right += float(0.05);
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::Left) && PosSprite.x - 15 > 100 && !Keyboard::isKeyPressed(Keyboard::Key::Right))
				{
					move_right = 1;
					m_sprite_left -= float(0.05);
				}
				//animation-----------------------------------------------------------------------------------------------------------------
				if (about_fall == 0)
				{
					if (m_sprite_up <= -9)
					{
						player.left = 75 * 10;
						sprite.setTextureRect(player);
						sprite.rotate(5);
					}
					else if (m_sprite_up < 0 && Keyboard::isKeyPressed(Keyboard::Key::Right) && !Keyboard::isKeyPressed(Keyboard::Key::Left))
					{
						player.left = 75 * 15;
						sprite.setTextureRect(player);
					}
					else if (m_sprite_up < 0 && !Keyboard::isKeyPressed(Keyboard::Key::Right) && Keyboard::isKeyPressed(Keyboard::Key::Left))
					{
						player.left = 75 * 16;
						sprite.setTextureRect(player);
					}
					else if (m_sprite_up < 0)
					{
						player.left = 75 * 6;
						sprite.setTextureRect(player);
					}
					else if (m_sprite_right > -m_sprite_left)
					{
						if (c.getElapsedTime().asMilliseconds() > 100.0f) {
							if (player.left == 75 * 5 || (player.left < 75 * 3 || player.left > 75 * 5))
								player.left = 75 * 3;
							else
								player.left += 75;
							sprite.setTextureRect(player);
							c.restart();
						}
					}
					else if (-m_sprite_left > m_sprite_right)
					{
						if (c.getElapsedTime().asMilliseconds() > 100.0f) {
							if (player.left == 75 * 9 || (player.left < 75 * 7 || player.left > 75 * 9))
								player.left = 75 * 7;
							else
								player.left += 75;
							sprite.setTextureRect(player);
							c.restart();
						}
					}
					else
					{
						if (c.getElapsedTime().asMilliseconds() > 150.0f) {
							if (player.left == 75 * 2 || (player.left < 75 * 0 || player.left > 75 * 2))
								player.left = 75 * 0;
							else
								player.left += 75;
							sprite.setTextureRect(player);
							c.restart();
						}
					}
				}
				about_fall = 0;
				//-------------------------------------------------------------------------------------------------------------------
				if (PosSprite.x - 15 <= 100)
				{
					m_sprite_right += -1 * m_sprite_left / 2;
					m_sprite_left = 0;
				}
				if (PosSprite.x + 15 >= 700)
				{
					m_sprite_left -= m_sprite_right / 2;
					m_sprite_right = 0;
				}
				if (move_left == 0)
				{
					if (m_sprite_right > 0)
					{
						m_sprite_right -= float(0.1);
					}
				}
				if (move_right == 0)
				{
					if (m_sprite_left < 0)
					{
						m_sprite_left += float(0.1);
					}
				}
				if (m_sprite_right < 0)
				{
					m_sprite_right = 0;
				}
				if (m_sprite_left > 0)
				{
					m_sprite_left = 0;
				}
				//superjump------------------------------------------------------------------------
				if ((m_sprite_left <= -6 || m_sprite_right >= 6) && on_stair == 1 && Gravity == 0)
				{
					m_sprite_up = -10;
				}
				else if ((m_sprite_left <= -5 || m_sprite_right >= 5) && on_stair == 1 && Gravity == 0)
				{
					m_sprite_up = -8;
				}
				else if ((m_sprite_left <= -4 || m_sprite_right >= 4) && on_stair == 1 && Gravity == 0)
				{
					m_sprite_up = -7;
				}
				if (m_sprite_up > -10)
				{
					sprite.setRotation(0);
				}
				//-----------------------------------------------------------------------------------------
				sprite.move(0, Gravity);
				sprite.move(0, m_sprite_up);
				sprite.move(m_sprite_left, 0);
				sprite.move(m_sprite_right, 0);
				Gravity += float(0.1);
				if (Gravity >= -m_sprite_up)
				{
					on_stair = 0;
				}
			}
			window.draw(sprite);
		}
		if (pause)
		{
			drawifpause();
		}
		if (!pause)
		{
			drawifl_s();
			if (!stop) {
				window.draw(score);
				window.draw(scoreCurrent);
				window.draw(clocktext);
			}
		}
		//----> Convert score to string
		stringstream s;
		s << currentScore;
		scoreCurrent.setString(s.str());

		stringstream s2;
		s2 << minutes << ":" << clocktime.asSeconds();
		clocktext.setString(s2.str());
		//------------------------
		window.display();
	}

	return 0;
}