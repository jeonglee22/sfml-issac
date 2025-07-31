#include "stdafx.h"
#include "SkillFunctionBible.h"
#include "SceneGame.h"

void SkillFunctionBible::SetIsaac()
{
	if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Stage)
		isaac = ((SceneGame*)SCENE_MGR.GetCurrentScene())->GetIsaac();
}

void SkillFunctionBible::AddSkillFunction()
{
	Necronomicon necro;
	skillFunctionBible.insert({ "thenecronomicon", necro() });
}
