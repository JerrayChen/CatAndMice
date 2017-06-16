#include <SFML/Graphics.hpp>
#include "ResourcePath.h"
#include "Overlap.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <sstream>

void showScore(int &, sf::Text &);

void showScore(int &intScore, sf::Text &score){
    std::stringstream sStream;
    std::string strScore;
    sStream << "Total score: " << intScore;
    strScore = sStream.str();
    score.setString(strScore);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(700, 600), "SFML Works!");
    
    //window.setVerticalSyncEnabled(true);
    
    window.setFramerateLimit(60);
	//sf::CircleShape shape(100.f);
    
	//shape.setFillColor(sf::Color::Green);

    // Load a sprite to display
    sf::Texture catT;
    if (!catT.loadFromFile(resourcePath() + "assets/cat.jpg"))
        return EXIT_FAILURE;
    sf::Sprite catS(catT);
    catS.setScale(0.75,0.75);
    catS.setOrigin(catS.getLocalBounds().width/2, catS.getLocalBounds().height/2);
    catS.setPosition(300.0, 300.0);
    
    sf::Texture catcanT;
    if (!catcanT.loadFromFile(resourcePath() + "assets/catcan.jpeg"))
        return EXIT_FAILURE;
    sf::Sprite catcanS(catcanT);
    catcanS.setScale(0.25,0.25);
    catcanS.setOrigin(catcanS.getLocalBounds().width/2, catcanS.getLocalBounds().height/2);
    catcanS.setPosition(200.0, 200.0);
    srand(time(NULL));

    
    sf::Texture miceT;
    if (!miceT.loadFromFile(resourcePath() + "assets/mice.jpeg"))
        return EXIT_FAILURE;
    sf::Sprite miceS(miceT);
    miceS.setScale(0.25,0.25);
    miceS.setOrigin(miceS.getLocalBounds().width/2, miceS.getLocalBounds().height/2);
    miceS.setPosition(400.0, 400.0);
    
    sf::Font font1;
    font1.loadFromFile(resourcePath() + "assets/Roboto-Regular.ttf");
    sf::Text score;
    std::string strScore;
    score.setFont(font1);
    score.setCharacterSize(16);
    int intScore = 0;
    
    
    
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
            
		}
        /*
        if (event.key.code == sf::Keyboard::Up){
            catS.move(0.0, -2.0);
        }
        if (event.key.code == sf::Keyboard::Down){
            catS.move(0.0, 2.0);
        }
        if (event.key.code == sf::Keyboard::Right){
            catS.move(2.0, 0.0);
        }
        if (event.key.code == sf::Keyboard::Left){
            catS.move(-2.0, 0.0);
        }
        */
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            catS.move(0.0, -2.0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            catS.move(0.0, 2.0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            catS.move(2.0, 0.0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            catS.move(-2.0, 0.0);
        }
        //catS.move(1.0, 0.0);
        /*
        std::stringstream sStream;
        sStream << "Total score: " << intScore;
        strScore = sStream.str();
        score.setString(strScore);
        */
        showScore(intScore, score);
        
        if (overlap(catS, catcanS)){
            
            if (catS.getScale().x < 1 and catS.getScale().y < 1){
                
                catS.setScale(catS.getScale().x * 1.1, catS.getScale().y * 1.1);
            }
            do{
                catcanS.setPosition(rand()%700+1, rand()%600+1);
            }while(overlap(catS, catcanS));
            intScore += 1;
            /*std::stringstream sStream;
            sStream << "Total score: " << intScore;
            strScore = sStream.str();
            score.setString(strScore);
             */
            showScore(intScore, score);
        }
        
        if (overlap(catS, miceS)){
            
            catS.setScale(catS.getScale().x / 1.1, catS.getScale().y / 1.1);
            
            do{
                miceS.setPosition(rand()%700+1, rand()%600+1);
            }while(overlap(catS, miceS));
            intScore -= 1;
            showScore(intScore, score);
        }
		window.clear();
		//window.draw(shape);
        
        // Draw the sprite
        window.draw(catS);
        window.draw(catcanS);
        window.draw(miceS);

        window.draw(score);
        
		window.display();
	}

	return 0;
}

