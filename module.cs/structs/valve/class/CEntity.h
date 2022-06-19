#pragma once
#include "../structs/clientclass.h"
#include "../../netvar/netvar.h"
#include "colids.h"

class CEntity {
public:
	enum EFlags : std::int32_t
	{
		FL_ONGROUND = (1 << 0),
		FL_DUCKING = (1 << 1),
		FL_ANIMDUCKING = (1 << 2),
		FL_WATERJUMP = (1 << 3),
		FL_ONTRAIN = (1 << 4),
		FL_INRAIN = (1 << 5),
		FL_FROZEN = (1 << 6),
		FL_ATCONTROLS = (1 << 7),
		FL_CLIENT = (1 << 8),
		FL_FAKECLIENT = (1 << 9),
		FL_INWATER = (1 << 10),
		FL_FLY = (1 << 11),
		FL_SWIM = (1 << 12),
		FL_CONVEYOR = (1 << 13),
		FL_NPC = (1 << 14),
		FL_GODMODE = (1 << 15),
		FL_NOTARGET = (1 << 16),
		FL_AIMTARGET = (1 << 17),
		FL_PARTIALGROUND = (1 << 18),
		FL_STATICPROP = (1 << 19),
		FL_GRAPHED = (1 << 20),
		FL_GRENADE = (1 << 21),
		FL_STEPMOVEMENT = (1 << 22),
		FL_DONTTOUCH = (1 << 23),
		FL_BASEVELOCITY = (1 << 24),
		FL_WORLDBRUSH = (1 << 25),
		FL_OBJECT = (1 << 26),
		FL_KILLME = (1 << 27),
		FL_ONFIRE = (1 << 28),
		FL_DISSOLVING = (1 << 29),
		FL_TRANSRAGDOLL = (1 << 30),
		FL_UNBLOCKABLE_BY_PLAYER = (1 << 31)
	};

	enum EWeaponType : int
	{
		WEAPONTYPE_KNIFE = 0,
		WEAPONTYPE_PISTOL = 1,
		WEAPONTYPE_SUBMACHINEGUN = 2,
		WEAPONTYPE_RIFLE = 3,
		WEAPONTYPE_SHOTGUN = 4,
		WEAPONTYPE_SNIPER = 5,
		WEAPONTYPE_MACHINEGUN = 6,
		WEAPONTYPE_C4 = 7,
		WEAPONTYPE_PLACEHOLDER = 8,
		WEAPONTYPE_GRENADE = 9,
		WEAPONTYPE_HEALTHSHOT = 11,
		WEAPONTYPE_FISTS = 12,
		WEAPONTYPE_BREACHCHARGE = 13,
		WEAPONTYPE_BUMPMINE = 14,
		WEAPONTYPE_TABLET = 15,
		WEAPONTYPE_MELEE = 16
	};

	//NETVARS
	NETVAR(getEntityHealth, "CBasePlayer->m_iHealth", int)
	NETVAR(getEntityTeam, "CBaseEntity->m_iTeamNum", int)
	NETVAR(getEntityFlags, "CBasePlayer->m_fFlags", int)
	NETVAR(getEntityFlashMaxAlpha,"CCSPlayer->m_flFlashMaxAlpha",float)
	NETVAR(setEntitySpotted,"CBaseEntity->m_bSpotted",bool)
	NETVAR(isScoped,"CCSPlayer->m_bIsScoped",bool)
	NETVAR(getWeaponZoomLevel,"CWeaponCSBaseGun->m_zoomLevel",int)
	NETVAR(getRecoilPunchAngle,"CBasePlayer->m_aimPunchAngle",vec3_t)
	NETVAR(getRecoilViewPunchAngle,"CBasePlayer->m_viewPunchAngle",vec3_t)
	NETVAR(netvarAciveWeapon,"CCSPlayer->m_hActiveWeapon",int)
	//EXT
	void* networkable() {
		return reinterpret_cast<void*>(uintptr_t(this) + 0x8);
	}
	CClientClass* getEntityClass()
	{
		using original_fn = CClientClass * (__thiscall*)(void*);
		return (*(original_fn**)networkable())[2](networkable());
	}
	bool isAlive()
	{
		if (!this) return false;
		return this->getEntityHealth() > 0;
	}
	collideable_t* collideable() {
		using original_fn = collideable_t * (__thiscall*)(void*);
		return (*(original_fn**)this)[3](this);
	}
	vec3_t& absOrigin() {
		using original_fn = vec3_t & (__thiscall*)(void*);
		return (*(original_fn**)this)[10](this);;
	}
	bool isDormant() {
		using original_fn = bool(__thiscall*)(void*);
		return (*static_cast<original_fn**>(networkable()))[9](networkable());
	}

};