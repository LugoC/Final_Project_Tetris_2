#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;

//FUNCTION TO DRAW THE ENTIRE PLAYABLE AREA TO CLEAN UP CODE 
//void DrawPlayArea(RenderWindow& window, PhysicsRectangle& Floor, PhysicsRectangle& LeftWall, PhysicsRectangle& RightWall, PhysicsRectangle& Ceiling)
//    {
//        window.draw(Floor);
//        window.draw(LeftWall);
//        window.draw(RightWall);
//        window.draw(Ceiling);
//    }

//Array for creating the game pieces 
int GamePieces[7][4][4] =
{
    {1,0,0,0,
    1,0,0,0,
    1,0,0,0,
    1,0,0,0},

    {1,0,0,0,
    1,1,0,0,
    0,1,0,0,
    0,0,0,0},

    {0,1,0,0,
    1,1,0,0,
    1,0,0,0,
    0,0,0,0},

    {1,1,0,0,
    1,1,0,0,
    0,0,0,0,
    0,0,0,0},

    {1,0,0,0,
    1,1,0,0,
    1,0,0,0,
    0,0,0,0},

    {1,0,0,0,
    1,0,0,0,
    1,1,0,0,
    0,0,0,0},

    {0,1,0,0,
    0,1,0,0,
    1,1,0,0,
    0,0,0,0}
};

//array for setting piece color 
const Color GamePieceColor[] =
{
    Color::Green, Color::Blue, Color::Red, Color::Yellow, Color::Black, Color::Magenta, Color::Cyan
};

const int cell_size = 20;

int main()
{
    //creates the window (1000 x 1000)
    RenderWindow window(VideoMode(800, 800), "Tetris");
    World world(Vector2f(0, 0));
    RectangleShape cell(Vector2f(cell_size, cell_size));
    int score(0);
    int highscore(0);
    time_t t;

    //Type of Game Piece 
    int GamePieceType;
    //Game Piece X Position 
    int GamePieceX;
    //Game Piece Y Position 
    int GamePieceY;

    auto new_GamePiece = [&]()
    {
        srand(time(0));
        GamePieceType = rand() % 7;
        GamePieceX = 260;
        GamePieceY = 260;
    };
    new_GamePiece();

    auto GamePieceCollision = [&]()
    {
        for (int y = 0; y < 4; y++)
            for (int x = 0; x < 4; x++)
            {
                if (GamePieces[GamePieceType][y][x] == 0)
                {
                    continue;

                }
                if (x + GamePieceX < 0 || x + GamePieceX >= 422 || x + GamePieceX <= 99 || y + GamePieceY >= 658)
                {
                    return false;
                }
            }
    };

    Clock clock;
    Time lastTime(clock.getElapsedTime());
    Time currentTime(lastTime);

    //create the playable area

    //create the floor
    PhysicsRectangle Floor;
    Floor.setSize(Vector2f(323, 10));
    Floor.setCenter(Vector2f(260, 700));
    Floor.setStatic(true);
    Floor.setFillColor(Color::Black);
    world.AddPhysicsBody(Floor);

    //create the left wall
    PhysicsRectangle LeftWall;
    LeftWall.setSize(Vector2f(10, 480));
    LeftWall.setCenter(Vector2f(95, 465));
    LeftWall.setStatic(true);
    LeftWall.setFillColor(Color::Black);
    world.AddPhysicsBody(LeftWall);

    //create the right wall
    PhysicsRectangle RightWall;
    RightWall.setSize(Vector2f(10, 480));
    RightWall.setCenter(Vector2f(425, 465));
    RightWall.setStatic(true);
    RightWall.setFillColor(Color::Black);
    world.AddPhysicsBody(RightWall);

    //create the ceiling 
    PhysicsRectangle Ceiling;
    Ceiling.setSize(Vector2f(323, 10));
    Ceiling.setCenter(Vector2f(260, 230));
    Ceiling.setStatic(true);
    Ceiling.setFillColor(Color::Black);
    world.AddPhysicsBody(Ceiling);

    //create the score section 

    //create the floor
    PhysicsRectangle ScoreFloor;
    ScoreFloor.setSize(Vector2f(200, 10));
    ScoreFloor.setCenter(Vector2f(600, 580));
    ScoreFloor.setStatic(true);
    ScoreFloor.setFillColor(Color::Black);
    world.AddPhysicsBody(ScoreFloor);

    //create the left wall
    PhysicsRectangle ScoreLeftWall;
    ScoreLeftWall.setSize(Vector2f(10, 100));
    ScoreLeftWall.setCenter(Vector2f(495, 535));
    ScoreLeftWall.setStatic(true);
    ScoreLeftWall.setFillColor(Color::Black);
    world.AddPhysicsBody(ScoreLeftWall);

    //create the right wall
    PhysicsRectangle ScoreRightWall;
    ScoreRightWall.setSize(Vector2f(10, 100));
    ScoreRightWall.setCenter(Vector2f(705, 535));
    ScoreRightWall.setStatic(true);
    ScoreRightWall.setFillColor(Color::Black);
    world.AddPhysicsBody(ScoreRightWall);

    //create the ceiling 
    PhysicsRectangle ScoreCeiling;
    ScoreCeiling.setSize(Vector2f(200, 10));
    ScoreCeiling.setCenter(Vector2f(600, 490));
    ScoreCeiling.setStatic(true);
    ScoreCeiling.setFillColor(Color::Black);
    world.AddPhysicsBody(ScoreCeiling);

    //create the highscore section 

    //create the floor
    PhysicsRectangle HighScoreFloor;
    HighScoreFloor.setSize(Vector2f(200, 10));
    HighScoreFloor.setCenter(Vector2f(600, 700));
    HighScoreFloor.setStatic(true);
    HighScoreFloor.setFillColor(Color::Black);
    world.AddPhysicsBody(HighScoreFloor);

    //create the left wall
    PhysicsRectangle HighScoreLeftWall;
    HighScoreLeftWall.setSize(Vector2f(10, 100));
    HighScoreLeftWall.setCenter(Vector2f(495, 655));
    HighScoreLeftWall.setStatic(true);
    HighScoreLeftWall.setFillColor(Color::Black);
    world.AddPhysicsBody(HighScoreLeftWall);

    //create the right wall
    PhysicsRectangle HighScoreRightWall;
    HighScoreRightWall.setSize(Vector2f(10, 100));
    HighScoreRightWall.setCenter(Vector2f(705, 655));
    HighScoreRightWall.setStatic(true);
    HighScoreRightWall.setFillColor(Color::Black);
    world.AddPhysicsBody(HighScoreRightWall);

    //create the ceiling 
    PhysicsRectangle HighScoreCeiling;
    HighScoreCeiling.setSize(Vector2f(200, 10));
    HighScoreCeiling.setCenter(Vector2f(600, 610));
    HighScoreCeiling.setStatic(true);
    HighScoreCeiling.setFillColor(Color::Black);
    world.AddPhysicsBody(HighScoreCeiling);

    //Setting Custom Font
    Font fnt;
    if (!fnt.loadFromFile("fonts/Tetris.ttf")) {
        cout << "Could not load font." << endl;
        exit(3);
    }

    //Create Title
    Text Tetris_Title;
    Tetris_Title.setString("Tetris");
    Tetris_Title.setFont(fnt);
    Tetris_Title.setFillColor(Color::Black);
    Tetris_Title.setCharacterSize(72);
    Tetris_Title.setPosition(130, 140);

    //Create Score Text
    Text ScoreText;
    ScoreText.setString("Score");
    ScoreText.setFont(fnt);
    ScoreText.setFillColor(Color::Black);
    ScoreText.setCharacterSize(32);
    ScoreText.setPosition(550, 490);

    //Create Score Counter
    Text ScoreDisplay;
    ScoreDisplay.setString(to_string(score));
    ScoreDisplay.setFont(fnt);
    ScoreDisplay.setFillColor(Color::Black);
    ScoreDisplay.setCharacterSize(28);
    ScoreDisplay.setPosition(593, 530);


    //Create High Score Text
    Text HighScoreText;
    HighScoreText.setString("High Score");
    HighScoreText.setFont(fnt);
    HighScoreText.setFillColor(Color::Black);
    HighScoreText.setCharacterSize(32);
    HighScoreText.setPosition(510, 610);

    //Create High Score Counter
    Text HighScoreDisplay;
    HighScoreDisplay.setString(to_string(GamePieceType));
    HighScoreDisplay.setFont(fnt);
    HighScoreDisplay.setFillColor(Color::Black);
    HighScoreDisplay.setCharacterSize(28);
    HighScoreDisplay.setPosition(593, 650);

    //allows for the window to remain open with a black background
    while (window.isOpen())
    {
        Event start;
        while (window.pollEvent(start))
        {
            if (start.type == Event::KeyPressed)
            {
                if (start.key.code == Keyboard::Left)
                {
                    GamePieceX -= 40;
                }
                else if (start.key.code == Keyboard::Right)
                {
                    GamePieceX += 40;
                }
                else if (start.key.code == Keyboard::Down)
                {
                    GamePieceY += 40;
                }
            }
            if (start.type == Event::Closed)
            {
                window.close();
            }
        }
        window.clear(Color::White);

        auto draw_GamePieces = [&]()
        {
            cell.setFillColor(GamePieceColor[GamePieceType]);
            for (int y = 0; y < 4; y++)
                for (int x = 0; x < 4; x++)
                    if (GamePieces[GamePieceType][x][y])
                    {
                        cell.setPosition(Vector2f((GamePieceX + (x * cell_size)), ((GamePieceY + (y * cell_size)))));
                        window.draw(cell);
                    }
        };

        currentTime = clock.getElapsedTime();
        Time deltaTime = currentTime - lastTime;
        long deltaMS = deltaTime.asMilliseconds();

        auto GamePieceGravity = [&]()
        {
            if (deltaMS >= 1000)
            {
                GamePieceY++;
                deltaMS = 0;
                if (deltaMS < 1000)
                {
                    GamePieceY--;
                }
            }
            else if (GamePieceCollision() == false)
            {
                GamePieceY--;
            }
        };

        GamePieceGravity();

        //draws the playable area
        window.draw(Floor);
        window.draw(LeftWall);
        window.draw(RightWall);
        window.draw(Ceiling);

        //draw the score section
        window.draw(ScoreFloor);
        window.draw(ScoreLeftWall);
        window.draw(ScoreRightWall);
        window.draw(ScoreCeiling);

        //draw the high score section
        window.draw(HighScoreFloor);
        window.draw(HighScoreLeftWall);
        window.draw(HighScoreRightWall);
        window.draw(HighScoreCeiling);

        //draw title
        window.draw(Tetris_Title);

        //draw score text
        window.draw(ScoreText);
        window.draw(ScoreDisplay);

        //draw high score text
        window.draw(HighScoreText);
        window.draw(HighScoreDisplay);

        draw_GamePieces();
        window.display();

    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file