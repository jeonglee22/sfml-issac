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
	
	Boom boom;
	skillFunctionBible.insert({"boom", boom()});
	skillNames.push_back("boom");

	Lunch lunch;
	skillFunctionBible.insert({"lunch", lunch()});
	skillNames.push_back("lunch");

	Dinner dinner;
	skillFunctionBible.insert({"dinner", dinner()});
	skillNames.push_back("dinner");

	Breakfast breakfast;
	skillFunctionBible.insert({"breakfast", breakfast()});
	skillNames.push_back("breakfast");
	
	Dessert dessert;
	skillFunctionBible.insert({"dessert", dessert()});
	skillNames.push_back("dessert");
	
	TammyHead tammyhead;
	skillFunctionBible.insert({"tammyshead", tammyhead()});
	skillNames.push_back("tammyshead");

	YumHeart yumheart;
	skillFunctionBible.insert({"yumheart", yumheart()});
	skillNames.push_back("yumheart");

	MomsEye momseye;
	skillFunctionBible.insert({"momseye", momseye()});
	skillNames.push_back("momseye");
}
