#include"SceneBase.h"
#include "SceneController.h"

void SceneBase::Update()
{
	switch (cur_step_step)
	{
	case SceneStep::InitStep:
		InitStep();
		break;
	case SceneStep::ThreadStep:
		UpdateThreadStep();
		break;
	case SceneStep::MainStep:
		MainStep();
		break;
	case SceneStep::EndStep:
		EndStep();
		break;
	default:
		break;
	}

}
