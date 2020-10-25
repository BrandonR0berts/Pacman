#include "Pacman.h"
#include "GameManager.h"
#include "Constants.h"

#include <sstream>

// -------------------------------------------------------------------------------------------------------------- //

Pacman::Pacman(int argc, char* argv[]) : Game(argc, argv)
{
	_frameCount = 0;

	//Initialise important Game aspects
	Graphics::Initialise(argc, argv, this, SCREEN_WIDTH, SCREEN_HEIGHT, false, 25, 25, "Pacman", 60);
	Input::Initialise();

	// Start the Game Loop - This calls Update and Draw in game loop
	Graphics::StartGameLoop();
}

// -------------------------------------------------------------------------------------------------------------- //

Pacman::~Pacman()
{
	delete mBackground;
	delete mPlayer;
	delete mDotHandler;
	delete _stringPosition;

	delete mPauseMenu;
	delete mStartMenu;
	delete mHighScoreMenu;

	delete mCollectable;
}

// -------------------------------------------------------------------------------------------------------------- //

void Pacman::LoadContent()
{
	// Set string position
	_stringPosition  = new Vector2(10.0f, 25.0f);

	mBackground      = new Background(2);

	mPlayer          = new PacmanCharacter(mBackground->GetCollisionMap());
	mDotHandler      = new DotsHandler();

	mPauseMenu       = new PauseMenu();
	mStartMenu       = new StartMenu();
	mHighScoreMenu   = new HighScoresMenu();

	// Default into the start menu
	mInStartMenu     = true;
	mInHighscoreMenu = false;
	mInMainGame      = false;

	mTimeTillNextCollectableSpawn = 10.0f;
}

// -------------------------------------------------------------------------------------------------------------- //

void Pacman::Update(int elapsedTime)
{
	float deltaTime = ((float)elapsedTime / 1000.0f);

	StartMenuUpdate(deltaTime);
	HighScoreMenuUpdate();
	PauseMenuUpdate(deltaTime);

	InGameUpdate(deltaTime);

}

// -------------------------------------------------------------------------------------------------------------- //

void Pacman::Draw(int elapsedTime)
{
	// Allows us to easily create a string
	//std::stringstream stream;
	//stream << "Pacman X: " << mPlayer->GetPosition()->X << " Y: " << mPlayer->GetPosition()->Y;

	// Starts Drawing
	SpriteBatch::BeginDraw();

		// Make sure we are rendering the correct content
		if (mInMainGame)
		{
			// Draw the background first
			if(mBackground)
				mBackground->Render();

			// Render the dots onto the screen
			if(mDotHandler)
				mDotHandler->Render(_frameCount);

			// Render the player
			if(mPlayer)
				mPlayer->Render(_frameCount);

			if (mCollectable)
				mCollectable->Render();
		}
		else
		{
			if (mInStartMenu)
			{
				mStartMenu->Render(_frameCount);
			}
			else if (mInHighscoreMenu)
			{
				mHighScoreMenu->Render();
			}
			else if (GameManager::Instance()->GetGameIsPaused())
			{
				mPauseMenu->Render();
			}
		}

		// Increment the frame count
		_frameCount++;

		if (_frameCount >= 60)
			_frameCount = 0;

	SpriteBatch::EndDraw(); // Ends Drawing
}

// -------------------------------------------------------------------------------------------------------------- //

void Pacman::StartMenuUpdate(const float deltaTime)
{
	if (mInStartMenu)
	{
		mInMainGame = false;

		SELECTION_OPTIONS returnOption = mStartMenu->Update(deltaTime);
		if (returnOption == SELECTION_OPTIONS::START_GAME)
		{
			mInMainGame = true;
			mInStartMenu = false;
			mInHighscoreMenu = false;
		}
		else if (returnOption == SELECTION_OPTIONS::HIGHSCORES)
		{
			// Selected to go into the highscores menu
			mInMainGame = false;
			mInStartMenu = false;
			mInHighscoreMenu = true;
		}
		else if (returnOption == SELECTION_OPTIONS::CHANGE_PLAYER)
		{
			GameManager::Instance()->SetPlayerCharacter(PLAYER_CHARACTER_TYPE::BLUE_GHOST);
			mInMainGame = false;
		}
		else if (returnOption == SELECTION_OPTIONS::QUIT)
		{
			std::cout << "Quitting the program." << std::endl;
		}
	}
}

// -------------------------------------------------------------------------------------------------------------- //

void Pacman::PauseMenuUpdate(const float deltaTime)
{
	if (GameManager::Instance()->GetGameIsPaused() && mPauseMenu)
	{
		mInMainGame = mPauseMenu->Update(deltaTime);
	}
}

// -------------------------------------------------------------------------------------------------------------- //

void Pacman::HighScoreMenuUpdate()
{
	if (mInHighscoreMenu)
	{
		mInMainGame = false;

		if (!mHighScoreMenu->Update())
		{
			mInHighscoreMenu = false;
			mInStartMenu = true;
		}
	}
}

// -------------------------------------------------------------------------------------------------------------- //

void Pacman::InGameUpdate(const float deltaTime)
{
	if (mInMainGame)
	{
		mTimeTillNextCollectableSpawn -= deltaTime;

		if (mTimeTillNextCollectableSpawn <= 0.0f && mCollectable == nullptr)
		{
			// Spawn the collectable
			SpawnNextCollectable();

			// Reset the time to a random amount
			mTimeTillNextCollectableSpawn = (rand() % 40) + 15;
		}

		//mDotHandler->Update(new S2D::Vector2(mPlayer->GetPosition()), 2 * SPRITE_RESOLUTION);
		mPlayer->Update(deltaTime);

		// Update the background to see if it should change colour
		mBackground->Update();

		// Update the dots in the level
		if (mDotHandler->Update(mPlayer->GetCentrePosition(), 9))
		{
			mPlayer->ResetPosition();

			return;
		}

		// Update the game manager
		GameManager::Instance()->Update(deltaTime);

		if (mCollectable && mCollectable->CheckForCollision(mPlayer->GetCentrePosition(), 8))
		{
			// Add the relevent score
			GameManager::Instance()->AddToScore((int)mCollectable->GetType() * 100);

			// Delete this collectable
			delete mCollectable;
			mCollectable = nullptr;
		}

		// Check if the player has paused the game
		if (S2D::Input::Keyboard::GetState()->IsKeyDown(S2D::Input::Keys::P) && !GameManager::Instance()->GetIsAlreadySettingGamePaused())
		{
			GameManager::Instance()->SetGameIsPaused(true);
			GameManager::Instance()->SetIsPausedButtonPressed(true);
			return;
		}
		else if (S2D::Input::Keyboard::GetState()->IsKeyUp(S2D::Input::Keys::P))
		{
			GameManager::Instance()->SetIsPausedButtonPressed(false);
		}

		// If we want to return back to the start menu then the player must press escape
		if (S2D::Input::Keyboard::GetState()->IsKeyDown(S2D::Input::Keys::ESCAPE))
		{
			mInStartMenu = true;
			return;
		}
	}
}

// -------------------------------------------------------------------------------------------------------------- //

void Pacman::SpawnNextCollectable()
{
	// Spawn in a new random collectable
	mCollectable = new PickUps((PICKUP_TYPES) (rand() % 8));
}

// -------------------------------------------------------------------------------------------------------------- //