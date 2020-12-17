#include "CollectDotsState_Task_Pacman.h"

#include "DotsHandler.h"
#include "PacmanCharacter.h"
#include "Stack_FiniteStateMachine.h"
#include "Constants.h"

// ---------------------------------------------------- //

CollectDotsGhostsState_Pacman::CollectDotsGhostsState_Pacman()
{
	OnEnter();
}

// ---------------------------------------------------- //

CollectDotsGhostsState_Pacman::~CollectDotsGhostsState_Pacman()
{

}

// ---------------------------------------------------- //

void CollectDotsGhostsState_Pacman::OnUpdate(S2D::Vector2 currentPosition, S2D::Vector2& targetPositionRef, std::vector<S2D::Vector2> ghostPositions, DotsHandler& dotManager)
{
	// We are not in a panic state, so lets just collect some dots
	targetPositionRef = dotManager.GetRandomDotPosition();
}

// ---------------------------------------------------- //

void CollectDotsGhostsState_Pacman::CheckTransitions(PacmanCharacter& pacman, std::vector<S2D::Vector2> ghostPositions)
{
	// If the ghosts are within a range then flee
	for (unsigned int i = 0; i < ghostPositions.size(); i++)
	{
		if ((pacman.GetCentrePosition() - ghostPositions[i]).Length() < DISTANCE_FROM_GHOST_BEFORE_FLEE)
		{
			//pacman.GetStateMachine().PushToStack(PACMAN_STATE_TYPES::FLEE);
			return;
		}
	}
}

// ---------------------------------------------------- //

void CollectDotsGhostsState_Pacman::OnEnter()
{

}

// ---------------------------------------------------- //

void CollectDotsGhostsState_Pacman::OnExit()
{

}

// ---------------------------------------------------- //