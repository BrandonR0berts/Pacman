#include "DotsHandler.h"

#include "GameManager.h"
#include "Constants.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// ----------------------------------------------------------------- //

DotsHandler::DotsHandler()
{
	LoadInDotData();

	mSmallDotSpriteSheet = new S2D::Texture2D();
	mSmallDotSpriteSheet->Load("Textures/Dots/SmallDot.png", false);

	mLargeDotSpriteSheet = new S2D::Texture2D();
	mLargeDotSpriteSheet->Load("Textures/Dots/LargeDot.png", false);

	if (!mLargeDotSpriteSheet || !mSmallDotSpriteSheet)
	{
		std::cout << "Failed to load in the dot sprite sheets." << std::endl;
		return;
	}

	mSourceRectLargeDot = new S2D::Rect(0, 0, SPRITE_RESOLUTION, SPRITE_RESOLUTION);
	mSourceRectSmallDot = new S2D::Rect(0, 0, SPRITE_RESOLUTION, SPRITE_RESOLUTION);
}

// ----------------------------------------------------------------- //

DotsHandler::~DotsHandler()
{
	for (unsigned int i = 0; i < mDots.size(); i++)
	{
		delete mDots[i];
		mDots[i] = nullptr;
	}

	mDots.clear();

	delete mLargeDotSpriteSheet;
		mLargeDotSpriteSheet = nullptr;

	delete mSmallDotSpriteSheet;
		mSmallDotSpriteSheet = nullptr;

	delete mSourceRectLargeDot;
		mSourceRectLargeDot = nullptr;

	delete mSourceRectSmallDot;
		mSourceRectSmallDot = nullptr;
}

// ----------------------------------------------------------------- //

void DotsHandler::Render(unsigned int currentFrameCount)
{
	// Setup the flashing animations
	/*
	if (currentFrameCount > 30)
	{

	}
	else
	{

	}
	*/

	// Loop through all dots and render them in the correct position using the correct sprite sheet
	for (unsigned int i = 0; i < mDots.size(); i++)
	{
		if (mDots[i]->GetDotType() == DOT_TYPE::SMALL)
			S2D::SpriteBatch::Draw(mSmallDotSpriteSheet, mDots[i]->GetPosition(), mSourceRectSmallDot);
		else
			S2D::SpriteBatch::Draw(mLargeDotSpriteSheet, mDots[i]->GetPosition(), mSourceRectLargeDot);
	}
}

// ----------------------------------------------------------------- //

void DotsHandler::LoadInDotData()
{
	// Open the file and load in the positions for this specific level
	std::ifstream file;
	file.open("DotPositions/Positions" + to_string(GameManager::Instance()->GetCurrentLevel()) + ".txt");
	if(!file.is_open())
	{
		std::cout << "Failed to open the file containing the dot positional data." << std::endl;
		return;
	}

	// Now we know the file is open loop through and read in the data
	char*             charLine = new char[100];
	std::string       sLine = "";
	std::stringstream ssLine;
	int xPos, yPos, typeOfDot;

	// Get each line of the file
	while (file.getline(charLine, 100))
	{
		// Convert to a string for checks
		sLine = charLine;

		// See if it is the end of the file
		if (sLine == "END" || sLine == "")
			break;

		// Reset the variables so values do not carry over
		xPos = 0; yPos = 0; typeOfDot = -1;

		// Convert the line to a string stream to simplify the process of extracting the data
		ssLine = std::stringstream(sLine);

		// Now get the data in
		ssLine >> xPos >> yPos >> typeOfDot;

		if (typeOfDot == 1)
		{
			mDots.push_back(new Dot(new S2D::Vector2(GameManager::Instance()->GetGridOffset().X + float((xPos * SPRITE_RESOLUTION)), GameManager::Instance()->GetGridOffset().Y + float((yPos * SPRITE_RESOLUTION))), DOT_TYPE::SMALL));
			continue;
		}
		else if (typeOfDot == 2)
		{
			mDots.push_back(new Dot(new S2D::Vector2(GameManager::Instance()->GetGridOffset().X + float(xPos * SPRITE_RESOLUTION), GameManager::Instance()->GetGridOffset().Y + float(yPos * SPRITE_RESOLUTION)), DOT_TYPE::LARGE));
			continue;
		}
		else
			continue;
	}

	delete[] charLine;
}

// ----------------------------------------------------------------- //

void DotsHandler::Update(S2D::Vector2* pacmanPosition, const unsigned int pacmanDimensions)
{
	// Loop through all positions and check if pacman has come into contact with them - only one can be in contact with 
	for (unsigned int i = 0; i < mDots.size(); i++)
	{
		// The X lines up correctly
		if (mDots[i]->GetPosition()->X > pacmanPosition->X && mDots[i]->GetPosition()->X < pacmanPosition->X + pacmanDimensions)
		{
			if (mDots[i]->GetPosition()->Y > pacmanPosition->Y && mDots[i]->GetPosition()->Y < pacmanPosition->Y - pacmanDimensions)
			{
				// Add score to the player's score based on the type of dot it is
				if (mDots[i]->GetDotType() == DOT_TYPE::SMALL)
				{
					GameManager::Instance()->AddToScore(100);
				}
				else
				{
					GameManager::Instance()->AddToScore(300);
					GameManager::Instance()->SetPlayerPoweredUp(true);
				}

				Dot* placeholder = mDots[mDots.size() - 1];
				mDots[mDots.size() - 1] = mDots[i];
				mDots[i] = placeholder;
				mDots.pop_back();

				return;
			}
		}
	}
}

// ----------------------------------------------------------------- //