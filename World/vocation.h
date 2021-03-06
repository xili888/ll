//-------------------------------------------------------------------------------
// Copyright (c) 2004 TENGWU Entertainment All rights reserved.
// filename: vocation.h
// author: zhangrong
// actor:
// data: 2009-8-28
// last:
// brief: 职业系统
//-------------------------------------------------------------------------------

#pragma once
#include "../WorldDefine/RoleDefine.h"

#define ITEM_SetClass		1361001
#define IM_ChangeClass		1361002

//enum E_Vocation_Return
//{
//	EVR_Success = 0,
//	EVR_Error,
//	EVR_Level_Unfit,
//	EVR_Take_Already,
//	EVR_Never_Taken,
//	EVR_V_Not_Match,
//};

//-------------------------------------------------------------------------------
// 职业类，一个重要的用途是管理专精职业与英雄职业之间的匹配
//-------------------------------------------------------------------------------
class Vocation
{
	friend class Role;
public:
	VOID Init();
	VOID Destroy();
//public:
//	// 获得专职职业
//	DWORD RoleGetVocation(Role*, EClassType);
//	// 获得英雄职业
//	DWORD RoleGetHero(Role*, EClassTypeEx);
//	// 更换职业
//	DWORD ChangeVocation(Role*, EClassType);

public:

	//---------------------------------------------------
	// 两种英雄职业对应专精职业的结构
	//---------------------------------------------------
	struct tagHeroVocation
	{
		EClassTypeEx	eHVocation_1;
		EClassTypeEx	eHVocation_2;

		tagHeroVocation(EClassTypeEx ePara_1, EClassTypeEx ePara_2):eHVocation_1(ePara_1),eHVocation_2(ePara_2){}
	};

private:
	TMap<EClassType, tagHeroVocation*>		m_mapVtoHV;	
	TMap<EClassType, tagHeroVocation*>		GetVocationMatchMap(){ return m_mapVtoHV; };
};

VOID Vocation::Init()
{
	// 生成专精职业与英雄职业对应表
	for (int i=1; i<EV_End; i++)
	{
		tagHeroVocation* pHeroVocation = new tagHeroVocation(EClassTypeEx(2*i-1), EClassTypeEx(2*i));
		m_mapVtoHV.Add(EClassType(i), pHeroVocation);
	}
}

VOID Vocation::Destroy()
{
	// 销毁专精职业与英雄职业对应表
	m_mapVtoHV.ResetIterator();
	tagHeroVocation* pTemp = NULL;

	while( m_mapVtoHV.PeekNext(pTemp))
	{
		SAFE_DEL(pTemp);
	}

	m_mapVtoHV.Clear();
}

Vocation g_VocationMap;