#include "stdafx.h"
#include "SkillFunctionBible.h"
#include "SceneGame.h"

void SkillFunctionBible::SetIsaac()
{
	if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Stage)
		isaac = ((SceneGame *)SCENE_MGR.GetCurrentScene())->GetIsaac();
}

void SkillFunctionBible::AddSkillFunction()
{
	Necronomicon necro;
	skillFunctionBible.insert({"thenecronomicon", necro()});
	skillNames.push_back("thenecronomicon");

	TheSadOnion onion;
	skillFunctionBible.insert({"thesadonion", onion()});
	skillNames.push_back("thesadonion");

	TheInnerEye innerEye;
	skillFunctionBible.insert({"theinnereye", innerEye()});
	skillNames.push_back("theinnereye");

	CricketsHead cricketshead;
	skillFunctionBible.insert({"cricketshead", cricketshead()});
	skillNames.push_back("cricketshead");

	NumberOne numberone;
	skillFunctionBible.insert({"numberone", numberone()});
	skillNames.push_back("numberone");

	BloodMartyr bloodmartyr;
	skillFunctionBible.insert({"bloodofthemartyr", bloodmartyr()});
	skillNames.push_back("bloodofthemartyr");
}
