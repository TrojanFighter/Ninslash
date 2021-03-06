#include <game/generated/protocol.h>
#include <game/server/gamecontext.h>
#include <game/weapons.h>
#include "projectile.h"
#include "building.h"
#include "droid.h"
#include "electro.h"
#include "superexplosion.h"


CProjectile::CProjectile(CGameWorld *pGameWorld, int Weapon, int Owner, vec2 Pos, vec2 Dir, vec2 Vel, int Span,
		int Damage, int Explosive, float Force, int SoundImpact)
: CEntity(pGameWorld, CGameWorld::ENTTYPE_PROJECTILE)
{
	m_Weapon = Weapon;
	m_Pos = Pos;
	m_Direction = Dir;
	m_LifeSpan = Span;
	m_Owner = Owner;
	m_Force = Force;
	m_Damage = Damage;
	m_SoundImpact = SoundImpact;
	m_StartTick = Server()->Tick();
	m_Explosive = Explosive;
	m_Bouncy = false;
	m_Vel2 = Vel*30.0f;

	m_ElectroTimer = 0;
	
	m_OwnerBuilding = NULL;
	BounceTick = 0;
	
	UpdateStats();
	
	GameWorld()->InsertEntity(this);
}

void CProjectile::Reset()
{
	GameServer()->m_World.DestroyEntity(this);
}


void CProjectile::UpdateStats()
{
	m_Part1 = GetPart(m_Weapon, 0);
	m_Part2 = GetPart(m_Weapon, 1);
	m_Speed = GetProjectileSpeed(m_Weapon);
	m_Curvature = GetProjectileCurvature(m_Weapon);
	m_Bouncy = IsProjectileBouncy(m_Weapon);
}


vec2 CProjectile::GetPos(float Time)
{
	if (WeaponProjectilePosType(m_Weapon) == 1)
		return CalcLogPos(m_Pos, m_Direction, m_Vel2, m_Curvature, m_Speed, Time);
	
	if (WeaponProjectilePosType(m_Weapon) == 2)
		return CalcRocketPos(m_Pos, m_Direction, m_Vel2, m_Curvature, m_Speed, Time);
	
	return CalcPos(m_Pos, m_Direction, m_Vel2, m_Curvature, m_Speed, Time);
}

// todo: fix broken bouncing
bool CProjectile::Bounce(vec2 Pos)
{
	if (m_Bouncy)
	{
		BounceTick = Server()->Tick();
	
		m_Vel2 = vec2(0, 0);
		int top = GameServer()->Collision()->GetCollisionAt(Pos.x, Pos.y-16);
		int bot = GameServer()->Collision()->GetCollisionAt(Pos.x, Pos.y+16);
		int left = GameServer()->Collision()->GetCollisionAt(Pos.x-16, Pos.y);
		int right = GameServer()->Collision()->GetCollisionAt(Pos.x+16, Pos.y);
		
		int c = (top > 0) + (bot > 0) + (left > 0) + (right > 0);
		
		if (c == 4)
		{
			//m_Direction.y *= -1;
			//m_Direction.x *= -1;
			
			return false;
		}
		else
		{
			if(!top && bot)
				m_Direction.y *= -1;
			if(!bot && top)
				m_Direction.y *= -1;
			if(!left && right)
				m_Direction.x *= -1;
			if(!right && left)
				m_Direction.x *= -1;
		}
		
		GameServer()->CreateSound(Pos, SOUND_BOUNCER_BOUNCE);
		
		return true;
	}
	
	return false;
}


void CProjectile::Tick()
{
	float Pt = (Server()->Tick()-m_StartTick-1)/(float)Server()->TickSpeed();
	float Ct = (Server()->Tick()-m_StartTick)/(float)Server()->TickSpeed();
	vec2 PrevPos = GetPos(Pt);
	vec2 CurPos = GetPos(Ct);
	int Collide = 0;
	CCharacter *OwnerChar = GameServer()->GetPlayerChar(m_Owner);
	CCharacter *TargetChr = NULL;
	CCharacter *ReflectChr = NULL;
	
	Collide = GameServer()->Collision()->IntersectLine(PrevPos, CurPos, &CurPos, 0);
	
	float r = 6.0f * GetProjectileSize(m_Weapon);
	
	TargetChr = GameServer()->m_World.IntersectCharacter(PrevPos, CurPos, r, CurPos, OwnerChar);
	ReflectChr = GameServer()->m_World.IntersectScythe(PrevPos, CurPos, r+45.0f, CurPos, OwnerChar);
	
	int Team = m_Owner;
	
	if (OwnerChar && GameServer()->m_pController->IsTeamplay())
		Team = OwnerChar->GetPlayer()->GetTeam();
	
	CBuilding *TargetBuilding = NULL;
	
	TargetBuilding = GameServer()->m_World.IntersectBuilding(PrevPos, CurPos, r, CurPos, Team);
	
	
	if (m_OwnerBuilding == TargetBuilding)
		TargetBuilding = NULL;
	
	CDroid *TargetMonster = NULL;
	
	TargetMonster = GameServer()->m_World.IntersectWalker(PrevPos, CurPos, r, CurPos);
	
	if (m_Owner == NEUTRAL_BASE)
		TargetMonster = NULL;
	
	m_LifeSpan--;

	if (Collide && Bounce(CurPos))
	{
		m_StartTick = Server()->Tick()-1;
		m_Pos = CurPos;
		Collide = false;
	}
	
	if (ReflectChr)
	{
		m_StartTick = Server()->Tick()-1;
		m_Pos = CurPos;
		
		m_Direction.y *= -1;
		m_Direction.x *= -1;
		
		vec2 d = ReflectChr->m_Pos-m_Pos;
		d += vec2(frandom()-frandom(), frandom()-frandom()) * length(d) * 0.4f;
		m_Direction = -normalize(d);
		GameServer()->CreateBuildingHit(CurPos);
	}
	
	if(TargetMonster || TargetBuilding || TargetChr || Collide || m_LifeSpan < 0 || GameLayerClipped(CurPos))
	{
		if(TargetChr)
		{
			vec2 Force = m_Direction * max(0.001f, m_Force);
			TargetChr->TakeDamage(m_Owner, m_Weapon, m_Damage, Force, CurPos);
			
			GameServer()->CreateEffect(FX_BLOOD2, (CurPos+TargetChr->m_Pos)/2.0f + vec2(0, -4));
		}

		if(TargetBuilding)
		{
			TargetBuilding->TakeDamage(m_Damage, m_Owner, m_Weapon);
			GameServer()->CreateBuildingHit(CurPos);
		}
		
		if (TargetMonster)
		{
			TargetMonster->TakeDamage(m_Direction * max(0.001f, m_Force), m_Damage, m_Owner, CurPos, m_Weapon);
		}
		
		if (m_LifeSpan < 0)
			GameServer()->CreateExplosion(PrevPos, m_Owner, m_Weapon);
		else if (IsExplosiveProjectile(m_Weapon))
			GameServer()->CreateExplosion(CurPos, m_Owner, m_Weapon);
		
		GameServer()->m_World.DestroyEntity(this);
	}
	
	// fluid kills the projectile
	if (GameServer()->Collision()->IsInFluid(PrevPos.x, PrevPos.y))
		GameServer()->m_World.DestroyEntity(this);
}

void CProjectile::TickPaused()
{
	++m_StartTick;
}

void CProjectile::FillInfo(CNetObj_Projectile *pProj)
{
	pProj->m_X = (int)m_Pos.x;
	pProj->m_Y = (int)m_Pos.y;
	pProj->m_VelX = (int)(m_Direction.x*100.0f);
	pProj->m_VelY = (int)(m_Direction.y*100.0f);
	pProj->m_Vel2X = (int)(m_Vel2.x*10.0f);
	pProj->m_Vel2Y = (int)(m_Vel2.y*10.0f);
	pProj->m_StartTick = m_StartTick;
	pProj->m_Type = m_Weapon;
}

void CProjectile::Snap(int SnappingClient)
{
	float Ct = (Server()->Tick()-m_StartTick)/(float)Server()->TickSpeed();

	if(NetworkClipped(SnappingClient, GetPos(Ct)))
		return;

	CNetObj_Projectile *pProj = static_cast<CNetObj_Projectile *>(Server()->SnapNewItem(NETOBJTYPE_PROJECTILE, m_ID, sizeof(CNetObj_Projectile)));
	if(pProj)
		FillInfo(pProj);
}
