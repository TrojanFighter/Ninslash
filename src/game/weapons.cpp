#include <engine/shared/protocol.h>
#include <game/generated/client_data.h>

#include "weapons.h"


enum WeaponParts1
{
	PART_
	
};


float GetProjectileSprite(int Weapon)
{
	if (IsDroid(Weapon))
	{
		switch (GetDroidType(Weapon))
		{
			case DROIDTYPE_WALKER: return 7;
			case DROIDTYPE_STAR: return 4;
			default: return 0;
		};
	}
	
	if (IsStaticWeapon(Weapon))
	{
		switch (GetStaticType(Weapon))
		{
			case SW_BUBBLER: return 1;
			case SW_BAZOOKA: return 12;
			case SW_BOUNCER: return 13;
			default: return 0;
		};
	}
	
	
	int Part1 = GetPart(Weapon, 0);
	int Part2 = GetPart(Weapon, 1);
	
	if (Part1 == 1 && Part2 == 1) return 1;
	if (Part1 == 1 && Part2 == 2) return 0;
	if (Part1 == 1 && Part2 == 3) return 3;
	if (Part1 == 1 && Part2 == 4) return 3;
	if (Part1 == 1 && Part2 == 5) return 1;
	
	if (Part1 == 2) return 2;
	
	if (Part1 == 3 && Part2 == 1) return 4;
	if (Part1 == 3 && Part2 == 2) return 5;
	if (Part1 == 3 && Part2 == 3) return 6;
	if (Part1 == 3 && Part2 == 4) return 7;
	if (Part1 == 3 && Part2 == 5) return 5;
	
	if (Part1 == 4 && Part2 == 1) return 10;
	if (Part1 == 4 && Part2 == 2) return 9;
	if (Part1 == 4 && Part2 == 3) return 8;
	if (Part1 == 4 && Part2 == 4) return 8;
	if (Part1 == 4 && Part2 == 5) return 8;
	
	return 0;
}

int GetProjectileTraceType(int Weapon)
{

	if (IsDroid(Weapon))
	{
		switch (GetDroidType(Weapon))
		{
			case DROIDTYPE_WALKER: return -3;
			case DROIDTYPE_STAR: return -3;
			default: return 0;
		};
	}
	
	if (IsStaticWeapon(Weapon))
	{
		switch (GetStaticType(Weapon))
		{
			case SW_GUN1: return 4;
			case SW_BUBBLER: return -1;
			case SW_SHURIKEN: return -4;
			case SW_GRENADE2: return 5;
			case SW_GRENADE1: return 4;
			case SW_BAZOOKA: return -1;
			case SW_BOUNCER: return 6;
			default: return 0;
		};
	}
	
	
	int Part1 = GetPart(Weapon, 0);
	
	if (Part1 == 3) return -3;
	if (Part1 == 2) return -1;
	if (Part1 == 1) return 1;
	if (Part1 == 4) return 2;
	
	return 1;
}

float GetWeaponTraceThreshold(int Weapon)
{
	if (IsStaticWeapon(Weapon))
	{
		switch (GetStaticType(Weapon))
		{
			case SW_SHURIKEN: return 20.0f;
			case SW_GRENADE2: return 0.0f;
			case SW_GRENADE1: return 0.0f;
			default: return 0.0f;
		};
	}
	
	return 0.0f;
}


bool AIWeaponCharge(int Weapon)
{
	if (GetWeaponFiringType(Weapon) == WFT_THROW || GetWeaponFiringType(Weapon) == WFT_CHARGE)
		return true;
	
	return false;
}

vec2 GetWeaponColorswap(int Weapon)
{
	float Charge = GetWeaponCharge(Weapon) / float(max(1, WeaponMaxLevel(Weapon)));
	
	if (IsStaticWeapon(Weapon))
	{
		switch (GetStaticType(Weapon))
		{
			case SW_GRENADE1: return vec2(0.0f, 0.0f);
			case SW_GRENADE2: return vec2(0.9f, 1.0f);
			case SW_BOUNCER: return vec2(0.0f+Charge*0.9f, 0.0f+Charge*0.4f);
			case SW_BAZOOKA: return vec2(0.0f+Charge*1.0f, 0.0f+Charge*0.4f);
			case SW_CHAINSAW: return vec2(0.0f+Charge*0.25f, 0.0f+Charge*0.9f);
			case SW_FLAMER: return vec2(0.0f+Charge*0.6f, 0.0f+Charge*0.8f);
			default: return vec2(0.0f, 0.0f);
		};
	}
	
	int Part1 = GetPart(Weapon, 0);
	
	if (Part1 == 1) return vec2(0.0f+Charge*0.25f, 0.0f+Charge*0.6f);
	if (Part1 == 2) return vec2(0.0f+Charge*0.25f, 0.0f+Charge*0.8f);
	if (Part1 == 3) return vec2(0.9f-Charge*0.2f, 1.0f-Charge*0.6f);
	if (Part1 == 4) return vec2(0.8f-Charge*0.6f, 0.1f-Charge*0.1f);
	if (Part1 == 5) return vec2(0.0f+Charge*0.35f, 0.0f+Charge*0.8f);
	
	return vec2(0, 0);
}

float GetProjectileSize(int Weapon)
{
	if (IsDroid(Weapon))
	{
		switch (GetDroidType(Weapon))
		{
			case DROIDTYPE_WALKER: return 1.0f;
			case DROIDTYPE_STAR: return 2.0f;
			default: return 0.0f;
		};
	}
	
	float Charge = GetWeaponCharge(Weapon) / float(max(1, WeaponMaxLevel(Weapon)));
	
	if (IsStaticWeapon(Weapon))
	{
		switch (GetStaticType(Weapon))
		{
			case SW_GRENADE1: case SW_GRENADE2: return 2.5f;
			case SW_SHURIKEN: return 2.5f;
			case SW_BUBBLER: return 0.9f;
			case SW_BAZOOKA: return 1.3f;
			case SW_BOUNCER: return 1.0f - (GetShotSpread(Weapon)-1)*0.15f;
			case SW_GUN1: return 0.7f;
			default: return 1.0f;
		};
	}
	
	int Part1 = GetPart(Weapon, 0);
	int Part2 = GetPart(Weapon, 1);
	
	float Size;
	
	switch (Part1)
	{
		case 1: Size = 0.7f; break;
		case 2: Size = 1.2f; break;
		case 3: Size = 1.2f; break;
		case 4: Size = 1.3f; break;
		default: Size = 1.0f; break;
	};
	
	switch (Part2)
	{
		case 1: Size += Charge*0.25f; Size *= 1.2f; break;
		case 2: Size += Charge*0.25f; Size *= 0.65f; break;
		case 3: Size += Charge*0.25f; Size *= 1.3f; break;
		case 4: Size += Charge*0.25f; Size *= 0.8f; break;
		case 5: Size *= 0.8f + GetWeaponCharge(Weapon)*0.25f; break;
		default: break;
	};
	
	return Size;
}

int GetExplosionSprite(int Weapon)
{
	if (IsBuilding(Weapon))
	{
		switch (GetBuildingType(Weapon))
		{
			case BUILDING_TURRET: return SPRITE_EXPLOSION1_1;
			case BUILDING_TESLACOIL: return SPRITE_EXPLOSION1_1;
			case BUILDING_FLAMETRAP: return SPRITE_EXPLOSION1_1;
			case BUILDING_BARREL: return SPRITE_EXPLOSION1_1;
			case BUILDING_POWERBARREL: return SPRITE_EXPLOSION1_1;
			default: return SPRITE_EXPLOSION1_1;
		};
	}
	else if (IsDroid(Weapon))
	{
		if (IsOnDeath(Weapon))
		{
			switch (GetDroidType(Weapon))
			{
				case DROIDTYPE_WALKER: return SPRITE_EXPLOSION1_1;
				case DROIDTYPE_STAR: return SPRITE_EXPLOSION1_1;
				case DROIDTYPE_CRAWLER: return SPRITE_EXPLOSION1_1;
				default: return 0;
			};
		}
		
		return 0;
	}
	
	if (IsStaticWeapon(Weapon))
	{
		switch (GetStaticType(Weapon))
		{
			case SW_GRENADE1: return SPRITE_EXPLOSION1_1;
			case SW_GRENADE2: return SPRITE_EXPLOSION1_1;
			case SW_BAZOOKA: return SPRITE_EXPLOSION1_1;
			default: return 0;
		};
	}
	
	if (IsModularWeapon(Weapon))
	{
		return SPRITE_EXPLOSION1_1;
	}
	return 0;
}

int GetExplosionSound(int Weapon)
{
	if (IsBuilding(Weapon))
	{
		switch (GetBuildingType(Weapon))
		{
			case BUILDING_TURRET: return SOUND_GRENADE_EXPLODE;
			case BUILDING_TESLACOIL: return SOUND_GRENADE_EXPLODE;
			case BUILDING_FLAMETRAP: return SOUND_GRENADE_EXPLODE;
			case BUILDING_BARREL: return SOUND_GRENADE_EXPLODE;
			case BUILDING_POWERBARREL: return SOUND_GRENADE_EXPLODE;
			default: return 0;
		};
	}
	else if (IsDroid(Weapon))
	{
		if (IsOnDeath(Weapon))
		{
			switch (GetDroidType(Weapon))
			{
				case DROIDTYPE_WALKER: return SOUND_GRENADE_EXPLODE;
				case DROIDTYPE_STAR: return SOUND_GRENADE_EXPLODE;
				case DROIDTYPE_CRAWLER: return SOUND_GRENADE_EXPLODE;
				default: return 0;
			};
		}
		
		return 0;
	}
	
	if (IsStaticWeapon(Weapon))
	{
		switch (GetStaticType(Weapon))
		{
			case SW_GRENADE1: return SOUND_GRENADE_EXPLODE;
			case SW_GRENADE2: return SOUND_GRENADE2_EXPLODE;
			case SW_BAZOOKA: return SOUND_GRENADE_EXPLODE;
			case SW_BOUNCER: return SOUND_GRENADE2_EXPLODE;
			default: return 0;
		};
	}
	
	int Part1 = GetPart(Weapon, 0);
	
	if (Part1 == 2)
		return SOUND_GRENADE_EXPLODE;
	
	return 0;
}


int GetWeaponFireSound(int Weapon)
{
	if (IsStaticWeapon(Weapon))
	{
		switch (GetStaticType(Weapon))
		{
			case SW_CHAINSAW: return SOUND_CHAINSAW_FIRE;
			case SW_FLAMER: return SOUND_FLAMER1;
			case SW_BAZOOKA: return SOUND_BAZOOKA_FIRE;
			case SW_BOUNCER: return SOUND_BOUNCER_FIRE;
			case SW_GUN1: return SOUND_GUN_FIRE;
			case SW_GUN2: return SOUND_LASER_FIRE;
			case SW_GRENADE1: return -1;
			case SW_GRENADE2: return -1;
			default: return -1;
		};
	}
	
	int Part1 = GetPart(Weapon, 0);
	
	if (Part1 == 1) return SOUND_BASE1_FIRE;
	if (Part1 == 2) return SOUND_BASE2_FIRE;
	if (Part1 == 3) return SOUND_BASE3_FIRE;
	if (Part1 == 4) return SOUND_BASE4_FIRE;
	if (Part1 == 5) return SOUND_HAMMER_FIRE;
	if (Part1 == 6) return SOUND_HAMMER_FIRE;
	if (Part1 == 7) return SOUND_HAMMER_FIRE;
	
	return -1;
}

int GetWeaponFireSound2(int Weapon)
{
	if (!IsModularWeapon(Weapon))
		return -1;
	
	int Part = GetPart(Weapon, 1);
	
	if (Part == 1) return SOUND_BARREL1_FIRE;
	if (Part == 2) return SOUND_BARREL2_FIRE;
	if (Part == 3) return SOUND_BARREL3_FIRE;
	if (Part == 4) return SOUND_BARREL4_FIRE;
	
	return -1;
}


float GetExplosionSize(int Weapon)
{
	if (IsBuilding(Weapon))
	{
		switch (GetBuildingType(Weapon))
		{
			case BUILDING_TURRET: return 80.0f;
			case BUILDING_TESLACOIL: return 350.0f;
			case BUILDING_FLAMETRAP: return 150.0f;
			case BUILDING_BARREL: return 200.0f;
			case BUILDING_POWERBARREL: return 300.0f;
			default: return 120.0f;
		};
	}
	else if (IsStaticWeapon(Weapon))
	{
		switch (GetStaticType(Weapon))
		{
			case SW_GUN1: return 80.0f;
			case SW_GRENADE1: return 300.0f;
			case SW_GRENADE2: return 320.0f;
			case SW_BUBBLER: return 80.0f;
			case SW_BAZOOKA: return 240.0f;
			case SW_BOUNCER: return 140.0f - (GetShotSpread(Weapon)-1)*15.0f;
			default: return 0.0f;
		};
	}
	else if (IsDroid(Weapon))
	{
		if (IsOnDeath(Weapon))
		{
			switch (GetDroidType(Weapon))
			{
				case DROIDTYPE_WALKER: return 160.0f;
				case DROIDTYPE_STAR: return 220.0f;
				case DROIDTYPE_CRAWLER: return 160.0f;
				default: return 0.0f;
			};
		}
		
		return 0;
	}
	
	float Size = 120 * GetProjectileSize(Weapon);
	
	return Size;
}

float GetExplosionDamage(int Weapon)
{
	if (IsBuilding(Weapon))
	{
		switch (GetBuildingType(Weapon))
		{
			case BUILDING_TURRET: return 20.0f;
			case BUILDING_TESLACOIL: return 120.0f;
			case BUILDING_FLAMETRAP: return 40.0f;
			case BUILDING_BARREL: return 60.0f; break;
			case BUILDING_POWERBARREL: return 120.0f; break;
			default: return 0; break;
		};
	}
	else if (IsDroid(Weapon))
	{
		if (IsOnDeath(Weapon))
		{
			switch (GetDroidType(Weapon))
			{
				case DROIDTYPE_WALKER: return 30.0f;
				case DROIDTYPE_STAR: return 40.0f;
				case DROIDTYPE_CRAWLER: return 30.0f;
				default: return 0.0f;
			};
		}
	}
	
	if (IsStaticWeapon(Weapon))
	{
		switch (GetStaticType(Weapon))
		{
			case SW_GRENADE1: return 100; break;
			case SW_GRENADE2: return 30; break;
			case SW_BUBBLER: return 14; break;
			case SW_BAZOOKA: return 80; break;
			case SW_BOUNCER: return 30 - (GetShotSpread(Weapon)-1)*4.0f; break;
			default: return 0;
		};
	}
	
	int Part1 = GetPart(Weapon, 0);
	
	if (Part1 != 2)
		return 0;
	
	float Size = 26 * (0.4f + GetProjectileSize(Weapon)*0.6f);
	
	return Size;
}


int GetWeaponRenderType(int Weapon)
{
	if (Weapon == WEAPON_NONE)
		return WRT_NONE;
	
	if (IsModularWeapon(Weapon))
	{
		int Part1 = GetPart(Weapon, 0);
		int Part2 = GetPart(Weapon, 1);
		
		if (Part1 > 4 || Part2 > 5)
			return WRT_MELEE;
		
		if (!Part1 || !Part2)
			return WRT_NONE;
		
		return WRT_WEAPON1;
	}
	
	switch (GetStaticType(Weapon))
	{
		case SW_CHAINSAW: case SW_FLAMER: case SW_BAZOOKA: case SW_BOUNCER: case SW_BUBBLER: return WRT_WEAPON1;
		case SW_GUN1: case SW_GUN2: return WRT_WEAPON2;
		default: return WRT_ITEM1;
	};
}

ivec2 GetWeaponVisualSize(int Weapon)
{
	if (IsModularWeapon(Weapon))
	{
		if (GetWeaponRenderType(Weapon) == WRT_MELEE)
			return ivec2(3, 2);
		
		// WRT_WEAPON1
		return ivec2(4, 3);
	}
	
	switch (GetStaticType(Weapon))
	{
		case SW_CHAINSAW: case SW_BUBBLER: return ivec2(7, 3);
		case SW_FLAMER: case SW_BAZOOKA: case SW_BOUNCER: return ivec2(6, 3);
		case SW_GUN1: case SW_GUN2: return ivec2(4, 2);
		case SW_GRENADE1: case SW_GRENADE2: return ivec2(2, 3);
		case SW_SHURIKEN: return ivec2(4, 4);
		case SW_TOOL: return ivec2(2, 4);
	};
	
	return ivec2(0, 0);
}

ivec2 GetWeaponVisualSize2(int Weapon)
{
	if (IsModularWeapon(Weapon))
	{
		if (GetWeaponRenderType(Weapon) == WRT_MELEE)
			return ivec2(8, 2);
		
		// WRT_WEAPON1
		return ivec2(4, 3);
	}
	
	return ivec2(0, 0);
}


int GetWeaponFiringType(int Weapon)
{
	if (Weapon == WEAPON_NONE)
		return WFT_NONE;
	
	if (IsModularWeapon(Weapon))
	{
		if (GetPart(Weapon, 1) == 5)
			return WFT_CHARGE;
		
		if (GetPart(Weapon, 0) > 4)
			return WFT_MELEE;
		
		return WFT_PROJECTILE;
	}
	
	switch (GetStaticType(Weapon))
	{
		case SW_CHAINSAW: case SW_FLAMER: return WFT_HOLD;
		case SW_BUBBLER: return WFT_PROJECTILE;
		case SW_BAZOOKA: return WFT_PROJECTILE;
		case SW_BOUNCER: return WFT_PROJECTILE;
		case SW_GUN1: return WFT_PROJECTILE;
		case SW_GUN2: return WFT_CHARGE;
		case SW_GRENADE1: case SW_GRENADE2: return WFT_THROW;
		case SW_SHURIKEN: return WFT_THROW;
		default: return WFT_NONE;
	};
	
	return WFT_NONE;
}


float GetWeaponRenderRecoil(int Weapon)
{
	if (IsModularWeapon(Weapon))
	{
		switch (GetPart(Weapon, 1))
		{
			case 1: return 13.0f;
			case 2: return 15.0f;
			case 3: return 14.0f;
			case 4: return 12.0f;
			default: return 0.0f;
		};
	}
	
	if (!IsStaticWeapon(Weapon))
		return 12.0f;
	
	switch (GetStaticType(Weapon))
	{
		//case SW_GRENADE1: case SW_GRENADE2: return -20.0f;
		//case SW_SHURIKEN: return -25.0f;
		case SW_BUBBLER: return 15.0f;
		case SW_BAZOOKA: return 18.0f;
		case SW_BOUNCER: return 13.0f;
		case SW_CHAINSAW: return 2.0f;
		case SW_GUN1: case SW_GUN2: return 13.0f;
		default: return 0.0f;
	};
	
	return 0.0f;
}


vec2 GetWeaponRenderOffset(int Weapon)
{
	if (IsModularWeapon(Weapon))
	{
		if (GetWeaponRenderType(Weapon) == WRT_MELEE)
			return vec2(-12, -2);
		
		return vec2(24, 0);
	}
	
	if (IsStaticWeapon(Weapon))
	{
		switch (GetStaticType(Weapon))
		{
			case SW_BAZOOKA: return vec2(30, 0);
			case SW_BOUNCER: return vec2(30, 0);
			case SW_BUBBLER: return vec2(30, 0);
			case SW_CHAINSAW: return vec2(30, 0);
			case SW_FLAMER: return vec2(30, 0);
			case SW_GUN1: case SW_GUN2: return vec2(16, -8);
			case SW_GRENADE1: case SW_GRENADE2: return vec2(4, 0);
			case SW_SHURIKEN: return vec2(0, 0);
			default: return vec2(0, 0);
		};
	}
	
	return vec2(0, 0);
}

vec2 GetMuzzleRenderOffset(int Weapon)
{
	if (GetStaticType(Weapon) == SW_GUN1)
		return vec2(20, -5);
	
	if (GetStaticType(Weapon) == SW_BUBBLER)
		return vec2(64, -4);
	if (GetStaticType(Weapon) == SW_BAZOOKA)
		return vec2(60, 0);
	if (GetStaticType(Weapon) == SW_BOUNCER)
		return vec2(62, 0);
	
	if (IsModularWeapon(Weapon))
	{
		switch (GetPart(Weapon, 1))
		{
			case 1: return vec2(66, 0);
			case 2: return vec2(64, 0);
			case 3: return vec2(74, 0);
			case 4: return vec2(60, -3);
			case 5: return vec2(68, 0);
			default: return vec2(50, 0);
		};
	}
	
	return vec2(0, 0);
}


int WeaponProjectilePosType(int Weapon)
{
	if (IsDroid(Weapon))
	{
		switch (GetDroidType(Weapon))
		{
			case DROIDTYPE_WALKER: return 0;
			case DROIDTYPE_STAR: return 1;
			default: return 0;
		};
	}
	
	if (GetStaticType(Weapon) == SW_BUBBLER)
		return 1;
	
	if (GetStaticType(Weapon) == SW_BAZOOKA)
		return 2;
	
	return 0;
}

vec2 GetProjectileOffset(int Weapon)
{
	if (IsModularWeapon(Weapon))
	{
		switch (GetPart(Weapon, 1))
		{
			case 1: return vec2(60, -11);
			case 2: return vec2(58, -11);
			case 3: return vec2(70, -11);
			case 4: return vec2(56, -11);
			case 5: return vec2(62, -11);
			case 6: return vec2(70, -12);
			case 7: return vec2(70, -12);
			case 8: return vec2(80, -12);
			default: return vec2(50, -11);
		};
	}
	
	if (IsStaticWeapon(Weapon))
	{
		switch (GetStaticType(Weapon))
		{
			case SW_BAZOOKA: return vec2(65, -8);
			case SW_BOUNCER: return vec2(65, -11);
			case SW_BUBBLER: return vec2(66, -12);
			case SW_CHAINSAW: return vec2(53, -11);
			case SW_FLAMER: return vec2(86, -11);
			case SW_GUN1: case SW_GUN2: return vec2(36, -16);
			default: return vec2(0, 0);
		};
	}
	return vec2(0, 0);
}


float GetMeleeHitRadius(int Weapon)
{
	float Charge = GetWeaponCharge(Weapon) / float(max(1, WeaponMaxLevel(Weapon)));
	
	if (IsStaticWeapon(Weapon))
	{
		switch (GetStaticType(Weapon))
		{
			case SW_SHURIKEN: return 20.0f;
			case SW_CHAINSAW: return 14.0f+Charge*5.0f;
			case SW_FLAMER: return 24.0f;
			default: return 0.0f;
		};
	}
	
	if (IsModularWeapon(Weapon))
	{
		switch (GetPart(Weapon, 1))
		{
			case 6: return 52.0f+Charge*17.0f;
			case 7: return 52.0f+Charge*17.0f;
			case 8: return 46.0f+Charge*17.0f;
			default: return 0.0f;
		};
	}
	
	return 0.0f;
}


bool WeaponAimline(int Weapon)
{
	if (IsModularWeapon(Weapon) && (GetPart(Weapon, 0) == 4 || GetPart(Weapon, 1) == 3))
		return true;

	return false;
}

bool IsLaserWeapon(int Weapon)
{
	if (IsModularWeapon(Weapon) && GetPart(Weapon, 0) == 3 && (GetPart(Weapon, 1) == 2 || GetPart(Weapon, 1) == 3))
		return true;

	return false;
}


int WeaponMaxLevel(int Weapon)
{
	if (IsModularWeapon(Weapon))
		return 4;

	if (IsStaticWeapon(Weapon))
	{
		switch (GetStaticType(Weapon))
		{
			case SW_BAZOOKA: return 2;
			case SW_FLAMER: return 2;
			case SW_BOUNCER: return 2;
			case SW_CHAINSAW: return 2;
			default: return false;
		};
	}
	
	
	return 0;
}


int GetLaserCharge(int Weapon)
{
	if (IsModularWeapon(Weapon))
	{
		if (GetPart(Weapon, 0) == 3)
		{
			float Charge = GetWeaponCharge(Weapon) / float(max(1, WeaponMaxLevel(Weapon)));
			
			if (GetPart(Weapon, 1) == 2) return -1;
			if (GetPart(Weapon, 1) == 3) return 50 + Charge*70;
		}
	}

	return 0;
}

int GetLaserRange(int Weapon)
{
	if (IsModularWeapon(Weapon))
	{
		if (GetPart(Weapon, 0) == 3)
		{
			if (GetPart(Weapon, 1) == 2) return 450;
			if (GetPart(Weapon, 1) == 3) return 700;
		}
	}

	return 0;
}

int GetMuzzleType(int Weapon)
{
	if (GetStaticType(Weapon) == SW_GUN2)
		return 1;
	
	if (GetStaticType(Weapon) == SW_BUBBLER)
		return 0;
	if (GetStaticType(Weapon) == SW_BAZOOKA)
		return 0;
	if (GetStaticType(Weapon) == SW_BOUNCER)
		return 2;
	
	if (IsModularWeapon(Weapon))
	{
		if (GetPart(Weapon, 0) == 3)
			return 1;
		if (GetPart(Weapon, 0) == 4)
			return 2;
	}

	return 0;
}

int GetMuzzleAmount(int Weapon)
{
	if (IsModularWeapon(Weapon))
	{
		switch (GetPart(Weapon, 1))
		{
			case 2: return 15;
			default: return 10;
			
		};
	}

	return 10;
}

float GetProjectileSpeed(int Weapon)
{
	if (IsDroid(Weapon))
	{
		switch (GetDroidType(Weapon))
		{
			case DROIDTYPE_WALKER: return 1400;
			case DROIDTYPE_STAR: return 24;
			default: return 0.0f;
		};
	}
	
	if (GetStaticType(Weapon) == SW_GUN1)
		return 1200.0f;
	
	if (GetStaticType(Weapon) == SW_BUBBLER)
		return 25.0f;
	if (GetStaticType(Weapon) == SW_BAZOOKA)
		return 400.0f;
	if (GetStaticType(Weapon) == SW_BOUNCER)
		return 1500.0f;
	
	float Charge = GetWeaponCharge(Weapon) / float(max(1, WeaponMaxLevel(Weapon)));
	
	int Part1 = GetPart(Weapon, 0);
	int Part2 = GetPart(Weapon, 1);
	
	float Speed;
	
	switch (Part1)
	{
		case 1: Speed = 1400; break;
		case 2: Speed = 900; break;
		case 3: Speed = 1200; break;
		case 4: Speed = 1700; break;
		default: Speed = 1200; break;
	};
	
	if (Part1 == 3 && Part2 == 1)
		Speed += Charge * 400.0f;
	
	switch (Part2)
	{
		case 1: break;
		case 2: Speed *= 1.3f; break;
		case 3: Speed *= 2.5f; break;
		case 4: Speed *= 1.4f; break;
		default: break;
	};

	return Speed;
}

float GetProjectileCurvature(int Weapon)
{
	if (IsDroid(Weapon))
	{
		switch (GetDroidType(Weapon))
		{
			default: return 0.0f;
		};
	}
	
	if (GetStaticType(Weapon) == SW_GUN1)
		return 2.2f;
	
	if (GetStaticType(Weapon) == SW_BUBBLER)
		return 2400.0f;
	
	if (GetStaticType(Weapon) == SW_BAZOOKA)
		return 0.0f;
	
	if (GetStaticType(Weapon) == SW_BOUNCER)
		return 0.0f;
	
	int Part1 = GetPart(Weapon, 0);
	int Part2 = GetPart(Weapon, 1);
	
	float Curvature;
	
	switch (Part1)
	{
		case 1: Curvature = 2.0f; break;
		case 2: Curvature = 6.0f; break;
		case 3: Curvature = 1.5f; break;
		case 4: Curvature = 1.8f; break;
		default: Curvature = 3.0f; break;
	};
	
	switch (Part2)
	{
		case 1: break;
		case 2: Curvature *= 1.0f; break;
		case 3: Curvature *= 0.4f; break;
		case 4: Curvature *= 0.6f; break;
		case 5: Curvature *= 1.0f - GetWeaponCharge(Weapon) * 0.1f; break;
		default: break;
	};
	
	
	
	return Curvature;
}

int GetShotSpread(int Weapon)
{
	float Charge = GetWeaponCharge(Weapon) / float(max(1, WeaponMaxLevel(Weapon)));
	
	if (IsStaticWeapon(Weapon))
	{
		if (GetStaticType(Weapon) == SW_BOUNCER)
			return 1 + Charge*2.0f;
		
		return 1;
	}
	
	int Part1 = GetPart(Weapon, 0);
	int Part2 = GetPart(Weapon, 1);
	
	int Spread = 1;
	
	if (Part1 == 1 && Part2 == 2) Spread = 5+Charge*2.0f;
	if (Part1 == 2 && Part2 == 2) Spread = 4+Charge*2.0f;
	if (Part1 == 3 && Part2 == 2) Spread = 5+Charge*2.0f;
	if (Part1 == 4 && Part2 == 2) Spread = 4+Charge*2.0f;
	
	return Spread;
}

float GetProjectileSpread(int Weapon)
{
	if (GetStaticType(Weapon) == SW_GUN1)
		return 0.06f;
	
	if (GetStaticType(Weapon) == SW_BUBBLER)
		return 0.04f;
	
	int Part2 = GetPart(Weapon, 1);
	
	float Spread = 0.05f;
	
	if (Part2 == 3) Spread = 0.0f;
	
	return Spread;
}

bool IsFlammableProjectile(int Weapon)
{
	if (Weapon == WEAPON_ACID)
		return 0.0f;
	
	if (IsStaticWeapon(Weapon))
	{
		switch (GetStaticType(Weapon))
		{
			case SW_FLAMER: return true;
			case SW_BUBBLER: return true;
			default: return false;
		};
	}
	
	if (IsBuilding(Weapon))
	{
		switch (GetBuildingType(Weapon))
		{
			case BUILDING_FLAMETRAP: return true;
			default: return false;
		};
	}
	
	return false;
}


float WeaponFlameAmount(int Weapon)
{
	if (IsStaticWeapon(Weapon))
	{
		switch (GetStaticType(Weapon))
		{
			case SW_FLAMER: return 1.0f;
			case SW_BUBBLER: return 1.0f;
			default: return 0.0f;
		};
	}
	
	if (IsBuilding(Weapon))
	{
		switch (GetBuildingType(Weapon))
		{
			case BUILDING_FLAMETRAP: return 1.0f;
			default: return 0.0f;
		};
	}
	
	return 0.0f;
}

int AIAttackRange(int Weapon)
{
	// seeing distance for free hands / no weapon
	if (Weapon == 0)
		return 1000;
	
	if (IsModularWeapon(Weapon))
	{
		int Part1 = GetPart(Weapon, 0);
		int Part2 = GetPart(Weapon, 1);
	
		if (Part2 == 2)
			return 600;
		
		if (Part1 == 1)
			return 900;
		
		if (Part1 == 2)
			return 700;
		
		if (Part1 == 3)
			return 900;
		
		if (Part1 == 4)
			return 900;
		
		if (Part2 > 5)
			return 250;
		
	}
	
	if (IsBuilding(Weapon))
	{
		switch (GetBuildingType(Weapon))
		{
			case BUILDING_TESLACOIL: return 800;
			default: return 0;
		};
	}
	
	if (IsStaticWeapon(Weapon))
	{
		switch (GetStaticType(Weapon))
		{
			case SW_GRENADE1: case SW_GRENADE2: return 700;
			case SW_GUN1: return 700;
			case SW_GUN2: return 500;
			case SW_SHURIKEN: return 700;
			case SW_BUBBLER: return 700;
			case SW_BAZOOKA: return 700;
			case SW_BOUNCER: return 700;
			case SW_FLAMER: return 600;
			case SW_CHAINSAW: return 150;
			default: return 0;
		};
	}
	
	return 0;
}


float WeaponElectroAmount(int Weapon)
{
	if (Weapon == WEAPON_ACID)
		return 0.0f;
	
	if (IsDroid(Weapon))
	{
		switch (GetDroidType(Weapon))
		{
			case DROIDTYPE_WALKER: return 0.5f;
			case DROIDTYPE_STAR: return 1.0f;
			default: return 0.0f;
		};
	}
	
	
	if (IsModularWeapon(Weapon))
	{
		float Charge = GetWeaponCharge(Weapon) / float(max(1, WeaponMaxLevel(Weapon)));
		
		int Part1 = GetPart(Weapon, 0);
		int Part2 = GetPart(Weapon, 1);
	
		if (Part1 == 3)
		{
			if (Part2 == 1) return 1.0f+Charge*0.7f;
			if (Part2 == 2) return 0.5f+Charge*0.3f;
			if (Part2 == 3) return 1.0f+Charge*0.7f;
			if (Part2 == 4) return 0.3f+Charge*0.3f;
		}
		
		if (Part1 == 5 && Part2 == 6 && Charge > 0.5f)
			return 0.0f + Charge * 0.5f;
		
		return 0.0f;	
	}
	
	if (IsBuilding(Weapon))
	{
		switch (GetBuildingType(Weapon))
		{
			case BUILDING_LIGHTNINGWALL: return 1.0f;
			case BUILDING_TESLACOIL: return 1.0f;
			default: return 0.0f;
		};
	}
	
	if (IsStaticWeapon(Weapon))
	{
		switch (GetStaticType(Weapon))
		{
			case SW_GRENADE2: return 0.5f;
			case SW_GUN2: return 0.5f;
		};
	}
	
	return 0.0f;
}

int WeaponBurstCount(int Weapon)
{
	float Charge = GetWeaponCharge(Weapon) / float(max(1, WeaponMaxLevel(Weapon)));
	
	if (IsStaticWeapon(Weapon))
	{
		switch (GetStaticType(Weapon))
		{
			case SW_BUBBLER: return 5;
			case SW_BAZOOKA: return 1+Charge*2.0f;
		};
		
		return 0;
	}
	
	
	if (IsModularWeapon(Weapon))
	{
		int Part1 = GetPart(Weapon, 0);
		int Part2 = GetPart(Weapon, 1);
	
		if (Part1 == 1 && Part2 == 2) return 2+Charge*2.0f;
		if (Part1 == 3 && Part2 == 4) return 3+Charge*4.0f;
		
		if (Part2 == 2) return 1+Charge*2.0f;
		if (Part1 == 2 && Part2 == 1) return 1+Charge*2.0f;
	}
	
	return 0;
}

float WeaponBurstReload(int Weapon)
{
	float Charge = GetWeaponCharge(Weapon) / float(max(1, WeaponMaxLevel(Weapon)));
	
	if (IsStaticWeapon(Weapon))
	{
		switch (GetStaticType(Weapon))
		{
			case SW_BUBBLER: return 0.2f;
			case SW_BAZOOKA: return 1.0f - Charge * 0.6f;
			default: return 0.0f;
		};
	}
	
	if (IsModularWeapon(Weapon))
	{
		int Part1 = GetPart(Weapon, 0);
		int Part2 = GetPart(Weapon, 1);
	
		if (Part1 == 1 && Part2 == 2) return 0.4f;
		if (Part1 == 3 && Part2 == 4) return 0.25f;
		
		if (Part1 == 2 && Part2 == 1) return 0.9f-Charge*0.25f;
		
		return 0.9f;
	}
	
	return 1.0f;
}


float GetProjectileDamage(int Weapon)
{
	float Charge = GetWeaponCharge(Weapon) / float(max(1, WeaponMaxLevel(Weapon)));
	
	if (IsDroid(Weapon))
	{
		switch (GetDroidType(Weapon))
		{
			case DROIDTYPE_WALKER: return 6.0f;
			case DROIDTYPE_STAR: return 14.0f;
			default: return 0.0f;
		};
	}
	
	if (IsStaticWeapon(Weapon))
	{
		switch (GetStaticType(Weapon))
		{
			case SW_SHURIKEN: return 100.0f;
			case SW_FLAMER: return 2.0f+Charge*3.0f;
			case SW_CHAINSAW: return 6.0f+Charge*4.0f;
			case SW_BUBBLER: return 6.0f;
			case SW_BAZOOKA: return 20.0f;
			case SW_BOUNCER: return 0.0f;
			case SW_GUN1: return 12.0f;
			case SW_GUN2: return 35.0f;
			default: return 0.0f;
		};
	}

	if (IsModularWeapon(Weapon))
	{
		int Part1 = GetPart(Weapon, 0);
		int Part2 = GetPart(Weapon, 1);
		
		if (Part1 == 1)
		{
			if (Part2 == 1) return 20+Charge*12.0f;
			if (Part2 == 2) return 7+Charge*4.0f;
			if (Part2 == 3) return 30+Charge*15.0f;
			if (Part2 == 4) return 16+Charge*5.0f;
		}
		else if (Part1 == 2)
		{

			if (Part2 == 1) return 10+Charge*5.0f;
			if (Part2 == 2) return 4+Charge*4.0f;
			if (Part2 == 3) return 15+Charge*5.0f;
			if (Part2 == 4) return 10+Charge*5.0f;
		}
		else if (Part1 == 3)
		{

			if (Part2 == 1) return 25+Charge*10.0f;
			if (Part2 == 2) return 8+Charge*4.0f;
			if (Part2 == 3) return 33+Charge*17.0f;
			if (Part2 == 4) return 15+Charge*5.0f;
		}
		else if (Part1 == 4)
		{

			if (Part2 == 1) return 32+Charge*12.0f;
			if (Part2 == 2) return 9+Charge*7.0f;
			if (Part2 == 3) return 40+Charge*20.0f;
			if (Part2 == 4) return 25+Charge*10.0f;
		}
		else if (Part1 == 5)
		{

			if (Part2 == 6) return 35+Charge*15.0f;
			if (Part2 == 7) return 30+Charge*10.0f;
			if (Part2 == 8) return 40+Charge*20.0f;
		}
	}
	
	return 0;
}

int GetRandomWeaponType()
{
	if (rand()%11 < 5)
		return GetModularWeapon(1+rand()%4, 1+rand()%4);
	
	// swords
	if (rand()%10 < 3)
		return GetModularWeapon(5, 6+rand()%3);
	
	return GetStaticWeapon(1+rand()%(NUM_SW-3));
}

float GetProjectileKnockback(int Weapon)
{
	if (IsDroid(Weapon))
	{
		switch (GetDroidType(Weapon))
		{
			case DROIDTYPE_WALKER: return 1.0f;
			case DROIDTYPE_STAR: return 2.0f;
			default: return 0.0f;
		};
	}
	
	if (IsModularWeapon(Weapon))
	{
		float Charge = GetWeaponCharge(Weapon) / float(max(1, WeaponMaxLevel(Weapon)));
		
		int Part1 = GetPart(Weapon, 0);
		int Part2 = GetPart(Weapon, 1);
		
		if (Part1 == 1)
		{
			if (Part2 == 1) return 3.0f+Charge*5.0f;
			if (Part2 == 2) return 2.0f;
			if (Part2 == 3) return 4.0f+Charge*5.0f;
			if (Part2 == 4) return 2.0f;
		}
		
		if (Part1 == 2)
		{
			if (Part2 == 1) return 5.0f;
			if (Part2 == 2) return 3.0f;
			if (Part2 == 3) return 5.0f;
			if (Part2 == 4) return 3.0f;
		}
		
		if (Part1 == 3)
		{
			return 0.0f;
		}
		
		if (Part1 == 4)
		{
			if (Part2 == 1) return 6.0f+Charge*6.0f;
			if (Part2 == 2) return 3.0f+Charge*4.0f;
			if (Part2 == 3) return 8.0f+Charge*6.0f;
			if (Part2 == 4) return 5.0f+Charge*5.0f;
		}
	}
	
	return 0.0f;
}

float GetProjectileLife(int Weapon)
{
	if (IsDroid(Weapon))
	{
		switch (GetDroidType(Weapon))
		{
			case DROIDTYPE_WALKER: return 0.6f;
			case DROIDTYPE_STAR: return 1.2f;
			default: return 0.0f;
		};
	}
	
	if (IsStaticWeapon(Weapon))
	{
		switch (GetStaticType(Weapon))
		{
			case SW_GUN1: return 0.6f;
			case SW_BUBBLER: return 0.8f;
			case SW_BAZOOKA: return 0.8f;
			case SW_BOUNCER: return 1.2f;
			default: return 0.0f;
		};
	}
	
	float v = 1100.0f / GetProjectileSpeed(Weapon) / ((GetShotSpread(Weapon)+2.0f)/3.0f);
	
	int Part2 = GetPart(Weapon, 1);
	
	if (Part2 == 2)
	{
		float Charge = GetWeaponCharge(Weapon) / float(max(1, WeaponMaxLevel(Weapon)));
		v *= (1.0f + Charge*0.25f);
	}
	
	return v;
}

float WeaponThrowForce(int Weapon)
{
	if (IsStaticWeapon(Weapon))
	{
		switch (GetStaticType(Weapon))
		{
			case SW_GRENADE1: case SW_GRENADE2: return 1.0f;
			case SW_SHURIKEN: return 1.4f;
			default: return 0.0f;
		};
	}
	
	return 0.0f;
}

float GetWeaponFireRate(int Weapon)
{
	// 0.0f <= Charge <= 1.0f
	float Charge = GetWeaponCharge(Weapon) / float(max(1, WeaponMaxLevel(Weapon)));
	
	if (IsStaticWeapon(Weapon))
	{
		switch (GetStaticType(Weapon))
		{
			case SW_CHAINSAW: return 500;
			case SW_FLAMER: return 200;
			case SW_BAZOOKA: return 600;
			case SW_BOUNCER: return 240;
			case SW_BUBBLER: return 600;
			case SW_GUN1: return 240;
			case SW_GUN2: return 200;
			default: return 0;
		};
	}
	
	int Part1 = GetPart(Weapon, 0);
	int Part2 = GetPart(Weapon, 1);
	
	if (Part1 == 1 && Part2 == 2) return 500;
	if (Part1 == 3 && Part2 == 4) return 500 - Charge*30.0f;
	
	float v = 10;
	
	switch (Part1)
	{
		case 1: v = 280; break;
		case 2: v = 490; break;
		case 3: v = 370; break;
		case 4: v = 500; v -= Charge*60.0f; break;
		case 5: v = 400; break;
		default: v = 300; break;
	};
	
	switch (Part2)
	{
		case 1: v -= Charge*80.0f; break;
		case 2: v -= Charge*90.0f; v *= 1.1f; break;
		case 3: v -= Charge*90.0f; v *= 1.2f; break;
		case 4: v -= Charge*80.0f; v *= 0.60f; break;
		case 5: v -= Charge*50.0f; v *= 0.65f; break;
		case 6: v -= Charge*35.0f; v *= 1.0f; break;
		case 7: v -= Charge*50.0f; v *= 0.8f; break;
		case 8: v -= Charge*35.0f; v *= 1.2f; break;
		default: break;
	};
	
	return v;
}


float GetWeaponKnockback(int Weapon)
{
	if (IsModularWeapon(Weapon))
	{
		float Charge = GetWeaponCharge(Weapon) / float(max(1, WeaponMaxLevel(Weapon)));
		
		int Part1 = GetPart(Weapon, 0);
		int Part2 = GetPart(Weapon, 1);
		
		if (Part1 == 1)
		{
			if (Part2 == 1) return 1.5f+Charge*1.25f;
			if (Part2 == 2) return 2.0f+Charge*1.25f;
			if (Part2 == 3) return 2.0f+Charge*1.25f;
			if (Part2 == 4) return 1.0f+Charge*1.25f;
		}
		
		if (Part1 == 2)
		{
			if (Part2 == 1) return 2.0f+Charge*1.25f;
			if (Part2 == 2) return 3.0f+Charge*1.25f;
			if (Part2 == 3) return 2.0f+Charge*1.25f;
			if (Part2 == 4) return 1.5f+Charge*1.25f;
		}
		
		if (Part1 == 3)
		{
			return 0.0f;
		}
		
		if (Part1 == 4)
		{
			if (Part2 == 1) return 1.5f+Charge*1.25f;
			if (Part2 == 2) return 2.0f+Charge*1.25f;
			if (Part2 == 3) return 2.0f+Charge*1.25f;
			if (Part2 == 4) return 1.0f+Charge*1.25f;
		}
	}
	
	return 0.0f;
}


bool GetWeaponFullAuto(int Weapon)
{
	// modular weapons
	if (IsModularWeapon(Weapon))
	{
		int Part2 = GetPart(Weapon, 1);
		
		if (Part2 == 2 || Part2 == 3)
			return false;
		
		return true;
	}
	
	// static weapons
	switch (GetStaticType(Weapon))
	{
		case SW_GUN1: return false;
		default: return true;
	};
	
	return true;
}

bool IsProjectileBouncy(int Weapon)
{
	if (GetStaticType(Weapon) == SW_BOUNCER)
		return true;
	
	return false;
}


bool IsExplosiveProjectile(int Weapon)
{
	return true;
}


int GetWeaponMaxAmmo(int Weapon)
{
	// 0.0f <= Charge <= 1.0f
	float Charge = GetWeaponCharge(Weapon) / float(max(1, WeaponMaxLevel(Weapon)));
	
	if (IsModularWeapon(Weapon))
	{
		int v = 0;
		
		int Part1 = GetPart(Weapon, 0);
		int Part2 = GetPart(Weapon, 1);
		
		if (Part1 == 1)
		{
			if (Part2 == 1) return 25 + Charge*10.0f;
			if (Part2 == 2) return 20 + Charge*10.0f;
			if (Part2 == 3) return 15 + Charge*10.0f;
			if (Part2 == 4) return 35 + Charge*15.0f;
		}
		
		if (Part1 == 2)
		{
			if (Part2 == 1) return 15 + Charge*10.0f;
			if (Part2 == 2) return 10 + Charge*10.0f;
			if (Part2 == 3) return 10 + Charge*10.0f;
			if (Part2 == 4) return 20 + Charge*15.0f;
		}
		
		if (Part1 == 3)
		{
			if (Part2 == 1) return 20 + Charge*10.0f;
			if (Part2 == 2) return 20 + Charge*10.0f;
			if (Part2 == 3) return 15 + Charge*10.0f;
			if (Part2 == 4) return 30 + Charge*15.0f;
		}
		
		if (Part1 == 4)
		{
			if (Part2 == 1) return 15 + Charge*10.0f;
			if (Part2 == 2) return 15 + Charge*10.0f;
			if (Part2 == 3) return 15 + Charge*10.0f;
			if (Part2 == 4) return 20 + Charge*15.0f;
		}
		
		return v;
	}
	
	if (IsStaticWeapon(Weapon))
	{
		switch (GetStaticType(Weapon))
		{
			case SW_GUN1: return 0;
			case SW_BUBBLER: return 30;
			case SW_BAZOOKA: return 6+Charge*9.0f;
			case SW_BOUNCER: return 20+Charge*20.0f;
			case SW_CHAINSAW: return 15;
			case SW_FLAMER: return 25+Charge*15.0f;
			default: return 0;
		};
	}
	
	return 0;
}

bool WeaponUseAmmo(int Weapon)
{
	if (IsModularWeapon(Weapon) && GetPart(Weapon, 0) < 5)
		return true;
	
	if (IsStaticWeapon(Weapon))
	{
		float Charge = GetWeaponCharge(Weapon) / float(max(1, WeaponMaxLevel(Weapon)));
		
		switch (GetStaticType(Weapon))
		{
			case SW_BAZOOKA: return true;
			case SW_BOUNCER: return true;
			case SW_BUBBLER: return true;
			case SW_CHAINSAW: return Charge < 0.9f ? true : false;
			case SW_FLAMER: return true;
			default: return false;
		};
	}
	
	return false;
}




