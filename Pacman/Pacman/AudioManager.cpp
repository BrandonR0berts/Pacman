#include "AudioManager.h"

#include <iostream>

AudioManager* AudioManager::mInstance = nullptr;

// -------------------------------------------------------------------------- //

AudioManager::AudioManager()
{
	static AudioManager* mInstance;

	mDotCollectionSFX       = new S2D::SoundEffect();
	mDotCollectionSFX->Load("Audio/credit.wav");

	if (!mDotCollectionSFX)
		std::cout << "Failed to load the dot collection SFX" << std::endl;
	mDotCollectionSFX->SetLooping(false);

	mEatingFruitSFX         = new S2D::SoundEffect();
	mEatingFruitSFX->Load("Audio/eat_fruit.wav");

	if (!mEatingFruitSFX)
		std::cout << "Failed to load the eating friut SFX" << std::endl;
	mEatingFruitSFX->SetLooping(false);

	mExtraLifeAllocationSFX = new S2D::SoundEffect();
	mExtraLifeAllocationSFX->Load("Audio/extend.wav");

	if (!mExtraLifeAllocationSFX)
		std::cout << "Failed to load the extra life allocation SFX" << std::endl;
	mExtraLifeAllocationSFX->SetLooping(false);


	mDeathSFX_1             = new S2D::SoundEffect();
	mDeathSFX_1->Load("Audio/death_1.wav");

	if (!mDeathSFX_1)
		std::cout << "Failed to load the death 2 SFX" << std::endl;
	mDeathSFX_1->SetLooping(false);


	mDeathSFX_2             = new S2D::SoundEffect();
	mDeathSFX_2->Load("Audio/death_2.wav");

	if (!mDeathSFX_2)
		std::cout << "Failed to load the death 2 SFX" << std::endl;
	mDeathSFX_2->SetLooping(false);

	mEatingGhostSFX         = new S2D::SoundEffect();
	mEatingGhostSFX->Load("Audio/eat_ghost.wav");

	if (!mEatingGhostSFX)
		std::cout << "Failed to load the eating ghost SFX" << std::endl;
	mEatingGhostSFX->SetLooping(false);


	mGhostGoingToHomeSFX    = new S2D::SoundEffect();
	mGhostGoingToHomeSFX->Load("Audio/retreating.wav");

	if (!mGhostGoingToHomeSFX)
		std::cout << "Failed to load the ghost going home SFX" << std::endl;
	mGhostGoingToHomeSFX->SetLooping(true);


	mGhostFleeingSFX_1      = new S2D::SoundEffect();
	mGhostFleeingSFX_1->Load("Audio/siren_1.wav");

	if (!mGhostFleeingSFX_1)
		std::cout << "Failed to load the ghost fleeing 1 SFX" << std::endl;
	mGhostFleeingSFX_1->SetLooping(true);


	mGhostFleeingSFX_2      = new S2D::SoundEffect();
	mGhostFleeingSFX_2->Load("Audio/siren_2.wav");

	if (!mGhostFleeingSFX_2)
		std::cout << "Failed to load the ghost fleeing 2 SFX" << std::endl;
	mGhostFleeingSFX_2->SetLooping(true);


	mGhostFleeingSFX_3      = new S2D::SoundEffect();
	mGhostFleeingSFX_3->Load("Audio/siren_3.wav");

	if (!mGhostFleeingSFX_3)
		std::cout << "Failed to load the ghost fleeing 3 SFX" << std::endl;
	mGhostFleeingSFX_3->SetLooping(true);


	mGhostFleeingSFX_4      = new S2D::SoundEffect();
	mGhostFleeingSFX_4->Load("Audio/siren_4.wav");

	if (!mGhostFleeingSFX_4)
		std::cout << "Failed to load the ghost fleeing 4 SFX" << std::endl;
	mGhostFleeingSFX_4->SetLooping(true);


	mGhostFleeingSFX_5      = new S2D::SoundEffect();
	mGhostFleeingSFX_5->Load("Audio/siren_5.wav");

	if (!mGhostFleeingSFX_5)
		std::cout << "Failed to load the ghost fleeing 5 SFX" << std::endl;
	mGhostFleeingSFX_5->SetLooping(true);


	mGameStartSFX           = new S2D::SoundEffect();
	mGameStartSFX->Load("Audio/game_start.wav");

	if (!mGameStartSFX)
		std::cout << "Failed to load the game start SFX" << std::endl;
	mGameStartSFX->SetLooping(false);
}

// -------------------------------------------------------------------------- //

AudioManager::~AudioManager()
{
	delete mDotCollectionSFX;
	mDotCollectionSFX = nullptr;

	delete mEatingFruitSFX;
	mEatingFruitSFX = nullptr;

	delete mExtraLifeAllocationSFX;
	mExtraLifeAllocationSFX = nullptr;

	delete mDeathSFX_1;
	mDeathSFX_1 = nullptr;

	delete mDeathSFX_2;
	mDeathSFX_2 = nullptr;

	delete mEatingGhostSFX;
	mEatingGhostSFX = nullptr;

	delete mGhostGoingToHomeSFX;
	mGhostGoingToHomeSFX = nullptr;

	delete mGhostFleeingSFX_1;
	mGhostFleeingSFX_1 = nullptr;

	delete mGhostFleeingSFX_2;
	mGhostFleeingSFX_2 = nullptr;

	delete mGhostFleeingSFX_3;
	mGhostFleeingSFX_3 = nullptr;

	delete mGhostFleeingSFX_4;
	mGhostFleeingSFX_4 = nullptr;

	delete mGhostFleeingSFX_5;
	mGhostFleeingSFX_5 = nullptr;

	delete mGameStartSFX;
	mGameStartSFX = nullptr;

	mCurrentlyPlayingSounds.clear();
}

// -------------------------------------------------------------------------- //

AudioManager* AudioManager::GetInstance()
{
	if (!mInstance)
		mInstance = new AudioManager;

	return mInstance;
}

// -------------------------------------------------------------------------- //

void AudioManager::PlayDotCollectionSFX()
{
	if (mDotCollectionSFX->GetState() != S2D::SoundEffectState::PLAYING && mDotCollectionSFX)
	{
		S2D::Audio::Play(mDotCollectionSFX);
		mCurrentlyPlayingSounds.push_back(mDotCollectionSFX);
	}
}

// -------------------------------------------------------------------------- //

void AudioManager::PlayEatingFruitSFX()
{
	if (mEatingFruitSFX->GetState() != S2D::SoundEffectState::PLAYING && mEatingFruitSFX)
	{
		S2D::Audio::Play(mEatingFruitSFX);
		mCurrentlyPlayingSounds.push_back(mEatingFruitSFX);
	}
}

// -------------------------------------------------------------------------- //

void AudioManager::PlayExtraLifeSFX()
{
	if (mExtraLifeAllocationSFX->GetState() != S2D::SoundEffectState::PLAYING && mExtraLifeAllocationSFX)
	{
		S2D::Audio::Play(mExtraLifeAllocationSFX);
		mCurrentlyPlayingSounds.push_back(mExtraLifeAllocationSFX);
	}
}

// -------------------------------------------------------------------------- //

void AudioManager::PlayPacmanDeathSFX_1()
{
	if (mDeathSFX_1->GetState() != S2D::SoundEffectState::PLAYING && mDeathSFX_1)
	{
		S2D::Audio::Play(mDeathSFX_1);	
		mCurrentlyPlayingSounds.push_back(mDeathSFX_1);
	}
}

// -------------------------------------------------------------------------- //

void AudioManager::PlayPacmanDeathSFX_2()
{
	if (mDeathSFX_2->GetState() != S2D::SoundEffectState::PLAYING && mDeathSFX_2)
	{
		S2D::Audio::Play(mDeathSFX_2);
		mCurrentlyPlayingSounds.push_back(mDeathSFX_2);
	}
}

// -------------------------------------------------------------------------- //

void AudioManager::PlayEatingGhostSFX()
{
	if (mEatingGhostSFX)
	{
		S2D::Audio::Play(mEatingGhostSFX);
		mCurrentlyPlayingSounds.push_back(mEatingFruitSFX);
	}
}

// -------------------------------------------------------------------------- //

void AudioManager::PlayGhostGoingToHomeSFX()
{
	if (mGhostGoingToHomeSFX->GetState() != S2D::SoundEffectState::PLAYING && mGhostGoingToHomeSFX)
	{
		S2D::Audio::Play(mGhostGoingToHomeSFX);
		mCurrentlyPlayingSounds.push_back(mGhostGoingToHomeSFX);
	}
}

// -------------------------------------------------------------------------- //

void AudioManager::PlayGhostFleeingSFX_1()
{
	if (mGhostFleeingSFX_1 && mGhostFleeingSFX_1->GetState() != S2D::SoundEffectState::PLAYING)
	{
		S2D::Audio::Play(mGhostFleeingSFX_1);

		mCurrentlyPlayingSounds.push_back(mGhostFleeingSFX_1);

		// Pause all other fleeing SFX
		for (unsigned int i = 0; i < mCurrentlyPlayingSounds.size(); i++)
		{
			if (mCurrentlyPlayingSounds[i] == mGhostFleeingSFX_2 || 
				mCurrentlyPlayingSounds[i] == mGhostFleeingSFX_3 ||
				mCurrentlyPlayingSounds[i] == mGhostFleeingSFX_4 ||
				mCurrentlyPlayingSounds[i] == mGhostFleeingSFX_5)
				mCurrentlyPlayingSounds.erase(mCurrentlyPlayingSounds.begin() + i);
		}

		PauseGhostFleeingSFX_2();
		PauseGhostFleeingSFX_3();
		PauseGhostFleeingSFX_4();
		PauseGhostFleeingSFX_5();
	}
}

// -------------------------------------------------------------------------- //

void AudioManager::PlayGhostFleeingSFX_2()
{
	if (mGhostFleeingSFX_2 && mGhostFleeingSFX_2->GetState() != S2D::SoundEffectState::PLAYING)
	{
		S2D::Audio::Play(mGhostFleeingSFX_2);

		// Pause all other fleeing SFX
		for (unsigned int i = 0; i < mCurrentlyPlayingSounds.size(); i++)
		{
			if (mCurrentlyPlayingSounds[i] == mGhostFleeingSFX_1 ||
				mCurrentlyPlayingSounds[i] == mGhostFleeingSFX_3 ||
				mCurrentlyPlayingSounds[i] == mGhostFleeingSFX_4 ||
				mCurrentlyPlayingSounds[i] == mGhostFleeingSFX_5)
				mCurrentlyPlayingSounds.erase(mCurrentlyPlayingSounds.begin() + i);
		}

		// Pause all other fleeing SFX
		PauseGhostFleeingSFX_1();
		PauseGhostFleeingSFX_3();
		PauseGhostFleeingSFX_4();
		PauseGhostFleeingSFX_5();
	}
}

// -------------------------------------------------------------------------- //

void AudioManager::PlayGhostFleeingSFX_3()
{
	if (mGhostFleeingSFX_3 && mGhostFleeingSFX_3->GetState() != S2D::SoundEffectState::PLAYING)
	{
		S2D::Audio::Play(mGhostFleeingSFX_3);

		// Pause all other fleeing SFX
		for (unsigned int i = 0; i < mCurrentlyPlayingSounds.size(); i++)
		{
			if (mCurrentlyPlayingSounds[i] == mGhostFleeingSFX_1 ||
				mCurrentlyPlayingSounds[i] == mGhostFleeingSFX_2 ||
				mCurrentlyPlayingSounds[i] == mGhostFleeingSFX_4 ||
				mCurrentlyPlayingSounds[i] == mGhostFleeingSFX_5)
				mCurrentlyPlayingSounds.erase(mCurrentlyPlayingSounds.begin() + i);
		}

		// Pause all other fleeing SFX
		PauseGhostFleeingSFX_1();
		PauseGhostFleeingSFX_2();
		PauseGhostFleeingSFX_4();
		PauseGhostFleeingSFX_5();
	}
}

// -------------------------------------------------------------------------- //

void AudioManager::PlayGhostFleeingSFX_4()
{
	if (mGhostFleeingSFX_4 && mGhostFleeingSFX_4->GetState() != S2D::SoundEffectState::PLAYING)
	{
		S2D::Audio::Play(mGhostFleeingSFX_4);

		// Pause all other fleeing SFX
		for (unsigned int i = 0; i < mCurrentlyPlayingSounds.size(); i++)
		{
			if (mCurrentlyPlayingSounds[i] == mGhostFleeingSFX_1 ||
				mCurrentlyPlayingSounds[i] == mGhostFleeingSFX_2 ||
				mCurrentlyPlayingSounds[i] == mGhostFleeingSFX_3 ||
				mCurrentlyPlayingSounds[i] == mGhostFleeingSFX_5)
				mCurrentlyPlayingSounds.erase(mCurrentlyPlayingSounds.begin() + i);
		}

		// Pause all other fleeing SFX
		PauseGhostFleeingSFX_1();
		PauseGhostFleeingSFX_2();
		PauseGhostFleeingSFX_3();
		PauseGhostFleeingSFX_5();
	}
}

// -------------------------------------------------------------------------- //

void AudioManager::PlayGhostFleeingSFX_5()
{
	if (mGhostFleeingSFX_5 && mGhostFleeingSFX_5->GetState() != S2D::SoundEffectState::PLAYING)
	{
		S2D::Audio::Play(mGhostFleeingSFX_5);

		// Pause all other fleeing SFX
		for (unsigned int i = 0; i < mCurrentlyPlayingSounds.size(); i++)
		{
			if (mCurrentlyPlayingSounds[i] == mGhostFleeingSFX_1 ||
				mCurrentlyPlayingSounds[i] == mGhostFleeingSFX_2 ||
				mCurrentlyPlayingSounds[i] == mGhostFleeingSFX_3 ||
				mCurrentlyPlayingSounds[i] == mGhostFleeingSFX_4)
				mCurrentlyPlayingSounds.erase(mCurrentlyPlayingSounds.begin() + i);
		}

		// Pause all other fleeing SFX
		PauseGhostFleeingSFX_1();
		PauseGhostFleeingSFX_2();
		PauseGhostFleeingSFX_3();
		PauseGhostFleeingSFX_4();
	}
}

// -------------------------------------------------------------------------- //

void AudioManager::PlayGameStartSFX()
{
	if (mGameStartSFX->GetState() != S2D::SoundEffectState::PLAYING && mGameStartSFX)
	{
		S2D::Audio::Play(mGameStartSFX);

		mCurrentlyPlayingSounds.push_back(mGameStartSFX);
	}
}

// -------------------------------------------------------------------------- //

void AudioManager::StopAllAudio()
{
	mCurrentlyPlayingSounds.clear();

	if (mDotCollectionSFX)
		S2D::Audio::Stop(mDotCollectionSFX);

	if (mEatingFruitSFX)
		S2D::Audio::Stop(mEatingFruitSFX);

	if (mExtraLifeAllocationSFX)
		S2D::Audio::Stop(mExtraLifeAllocationSFX);

	if (mDeathSFX_1)
		S2D::Audio::Stop(mDeathSFX_1);

	if(mDeathSFX_2)
		S2D::Audio::Stop(mDeathSFX_2);

	if(mEatingGhostSFX)
		S2D::Audio::Stop(mEatingGhostSFX);

	if(mGhostGoingToHomeSFX)
		S2D::Audio::Stop(mGhostGoingToHomeSFX);

	if (mGhostFleeingSFX_1)
		S2D::Audio::Stop(mGhostFleeingSFX_1);

	if (mGhostFleeingSFX_2)
		S2D::Audio::Stop(mGhostFleeingSFX_2);

	if (mGhostFleeingSFX_3)
		S2D::Audio::Stop(mGhostFleeingSFX_3);

	if (mGhostFleeingSFX_4)
		S2D::Audio::Stop(mGhostFleeingSFX_4);

	if (mGhostFleeingSFX_5)
		S2D::Audio::Stop(mGhostFleeingSFX_5);

	if (mGameStartSFX)
		S2D::Audio::Stop(mGameStartSFX);
}

// -------------------------------------------------------------------------- //

bool AudioManager::GetPacmanDeathSFXFinishedPlaying()
{
	if (mDeathSFX_1 && mDeathSFX_2 && mDeathSFX_1->GetState() == S2D::SoundEffectState::STOPPED && mDeathSFX_2->GetState() == S2D::SoundEffectState::STOPPED)
		return true;

	return false;
}

// -------------------------------------------------------------------------- //

void AudioManager::PauseGhostFleeingSFX_1() 
{
	if (mGhostFleeingSFX_1)
	{
		S2D::Audio::Pause(mGhostFleeingSFX_1);

		RemoveSoundFromCurrentlyPlayingList(mGhostFleeingSFX_1);
	}
}

// -------------------------------------------------------------------------- //

void AudioManager::PauseGhostFleeingSFX_2() 
{ 
	if (mGhostFleeingSFX_2)
	{
		S2D::Audio::Pause(mGhostFleeingSFX_2);

		RemoveSoundFromCurrentlyPlayingList(mGhostFleeingSFX_2);
	}
}

// -------------------------------------------------------------------------- //

void AudioManager::PauseGhostFleeingSFX_3() 
{ 
	if (mGhostFleeingSFX_3)
	{
		S2D::Audio::Pause(mGhostFleeingSFX_3);

		RemoveSoundFromCurrentlyPlayingList(mGhostFleeingSFX_3);
	}
}

// -------------------------------------------------------------------------- //

void AudioManager::PauseGhostFleeingSFX_4() 
{ 
	if (mGhostFleeingSFX_4)
	{
		S2D::Audio::Pause(mGhostFleeingSFX_4);

		RemoveSoundFromCurrentlyPlayingList(mGhostFleeingSFX_4);
	}
}

// -------------------------------------------------------------------------- //

void AudioManager::PauseGhostFleeingSFX_5() 
{ 
	if (mGhostFleeingSFX_5)
	{
		S2D::Audio::Pause(mGhostFleeingSFX_5);

		RemoveSoundFromCurrentlyPlayingList(mGhostFleeingSFX_5);
	}
}

// -------------------------------------------------------------------------- //

void AudioManager::RemoveSoundFromCurrentlyPlayingList(S2D::SoundEffect* sfx)
{
	for (unsigned int i = 0; i < mCurrentlyPlayingSounds.size(); i++)
	{
		if (mCurrentlyPlayingSounds[i] == sfx)
			mCurrentlyPlayingSounds.erase(mCurrentlyPlayingSounds.begin() + i);
	}
}

// -------------------------------------------------------------------------- //

void AudioManager::PauseAllAudio()
{
	for (unsigned int i = 0; i < mCurrentlyPlayingSounds.size(); i++)
	{
		S2D::Audio::Pause(mCurrentlyPlayingSounds[i]);
	}
}

// -------------------------------------------------------------------------- //

void AudioManager::ResumeAllAudio()
{
	for (unsigned int i = 0; i < mCurrentlyPlayingSounds.size(); i++)
	{
		S2D::Audio::Resume(mCurrentlyPlayingSounds[i]);
	}
}

// -------------------------------------------------------------------------- //

void AudioManager::Update()
{
	// Check if any of the currently playing audio tracks have finished playing
	for (unsigned int i = 0; i < mCurrentlyPlayingSounds.size(); i++)
	{
		if (mCurrentlyPlayingSounds[i]->GetState() == S2D::SoundEffectState::STOPPED)
			RemoveSoundFromCurrentlyPlayingList(mCurrentlyPlayingSounds[i]);
	}
}

// -------------------------------------------------------------------------- //