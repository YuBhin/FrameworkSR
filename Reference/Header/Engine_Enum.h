#ifndef Engine_Enum_h__
#define Engine_Enum_h__

namespace Engine
{
	enum class WINMODE { MODE_FULL, MODE_WIN };

	enum class COMPONENTID { ID_DYNAMIC, ID_STATIC, ID_END };

	enum class INFO { INFO_RIGHT, INFO_UP, INFO_LOOK, INFO_POS, INFO_END };
	enum class ROTATION { ROT_X, ROT_Y, ROT_Z, ROT_END };

	enum class TEXTUREID { TEX_NORMAL, TEX_CUBE, TEX_END };

	enum class RENDERID { RENDER_PRIORITY, RENDER_NONALPHA, RENDER_ALPHA, RENDER_ORTHOGONAL, RENDER_END };

	enum class MOUSEKEYSTATE { DIM_LB, DIM_RB, DIM_MB, DIM_END };
	enum class MOUSEMOVESTATE { DIMS_X, DIMS_Y, DIMS_Z, DIMS_END };

	enum class KEYSTATE { KEY_PRESS, KEY_HOLD, KEY_RELEASE, KEY_END };

	enum class UITYPE
	{
		UI_PHONE,
		UI_SHOP,
		UI_PLUS,
		UI_MISTERBULLET,
		UI_ROBOTO,
		UI_PLAYER,
		UI_INVENTORY,
		UI_NORMAL,
		UI_FREECAM,
		UI_SCREEN,
		UI_END,
	};

	enum class CHANNELID
	{
		SOUND_BGM,
		SOUND_PLAYER,
		SOUND_ENEMY,
		SOUND_PROJECTILE,
		SOUND_EFFECT,
		SOUND_INTERACT,
		SOUND_INTERFACE,
		MAXCHANNEL
	};

	enum class CONTROLLERID
	{
		CONTROL_PLAYER,
		CONTROL_FREECAM,
		CONTROL_END,
	};

	//Jonghan Change
	enum class DAMAGED_STATE
	{
		DAMAGED_HEADSHOT,
		DAMAGED_BULLSHOT,
		DAMAGED_BODYSHOT,
		DAMAGED_PUSHSHOT,
		DAMAGED_KATANA,
		DAMAGED_EXECUTION,
		DAMAGED_END,
	};

	enum class ITEM_TYPE
	{
		ITEM_KNIFE,
		ITEM_AXE,
		ITEM_DRINK,
		ITEM_END,
	};
	enum class TILE_DIRECTION
	{
		TILE_FORWARD,
		TILE_RIGHT,
		TILE_LEFT,
		TILE_BACK,
	};
}

#endif // Engine_Enum_h__