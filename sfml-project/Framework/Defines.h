#pragma once

#define DEF_DEV

enum class SortingLayers
{
	Background,
	Foreground,
	Default,
	UI,
};

enum class Origins
{
	TL, TC, TR,	// 0 1 2
	ML, MC, MR,	// 3 4 5
	BL, BC, BR, // 6 7 8
	Custom
};

enum class SceneIds
{
	None = -1,
	Editor,
	Stage,
	Animator,
	Dev1,
	Dev2,
	Count,
};

enum class Sides
{
	Left,
	Right,
	None,
};

enum class Monsters
{
	Fly,
	AttackFly,
	Spider,
	Body,
	Hopper,
	LarryJr,
	Horf,
};

enum class Items
{
	Coin,
	Half_Heart,
	Heart,
	Bomb,
	Key,
};