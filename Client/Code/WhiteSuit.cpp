#include "pch.h"
#include "../Header/WhiteSuit.h"
#include "Export_System.h"
#include "Export_Utility.h"

CWhiteSuit::CWhiteSuit(LPDIRECT3DDEVICE9 _pGraphicDev) :
    CMonster(_pGraphicDev)
{
    m_fMaxFrame = 14.f;
}

CWhiteSuit::~CWhiteSuit()
{
}

CWhiteSuit* CWhiteSuit::Create(LPDIRECT3DDEVICE9 _pGraphicDev)
{
	CWhiteSuit* pMonster = new CWhiteSuit(_pGraphicDev);

	if (FAILED(pMonster->Ready_GameObject()))
	{
		Safe_Release(pMonster);
		MSG_BOX("pWhiteSuit Create Failed");
		return nullptr;
	}

	return pMonster;
}

HRESULT CWhiteSuit::Ready_GameObject()
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	//m_pTransformCom->Set_Pos(10.f, 0.f, 10.f); 

	_matrix matWorld;

	m_pTransformCom->Get_WorldMatrix(&matWorld);

	matWorld._41 = -5.f;
	matWorld._43 = 10.f;

	m_pTransformCom->Set_WorldMatrix(&matWorld);

	return S_OK;
}

HRESULT CWhiteSuit::Add_Component()
{
	CComponent* pComponent = NULL;

	//pComponent = m_pBufferCom = dynamic_cast<CTriCol*>(Engine::Clone_Proto(L"Proto_TriCol"));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[(_uint)COMPONENTID::ID_STATIC].insert({ L"Com_Buffer", pComponent });

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"Proto_RcTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[(_uint)COMPONENTID::ID_STATIC].insert({ L"Com_Buffer", pComponent });

	pComponent = m_pTextureCom[MONSTERSTATE::MONSTER_ATTACK] = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_MonsterAttackTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[(_uint)COMPONENTID::ID_STATIC].insert({ L"Com_AttackTexture", pComponent });

	pComponent = m_pTextureCom[MONSTERSTATE::MONSTER_HEADSHOT] = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_MonsterHeadShotTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[(_uint)COMPONENTID::ID_STATIC].insert({ L"Com_HeadShotTexture", pComponent });

	pComponent = m_pTextureCom[MONSTERSTATE::MONSTER_BULLSHOT] = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_MonsterBullShotTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[(_uint)COMPONENTID::ID_STATIC].insert({ L"Com_BullShotTexture", pComponent });

	pComponent = m_pTextureCom[MONSTERSTATE::MONSTER_PUSH_ONE] = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_MonsterPushOneTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[(_uint)COMPONENTID::ID_STATIC].insert({ L"Com_PushOneTexture", pComponent });

	pComponent = m_pTextureCom[MONSTERSTATE::MONSTER_PUSH_TWO] = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_MonsterPushTwoTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[(_uint)COMPONENTID::ID_STATIC].insert({ L"Com_PushTwoTexture", pComponent });

	pComponent = m_pTextureCom[MONSTERSTATE::MONSTER_SHOT_ONE] = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_MonsterShotOneTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[(_uint)COMPONENTID::ID_STATIC].insert({ L"Com_ShotOneTexture", pComponent });

	pComponent = m_pTextureCom[MONSTERSTATE::MONSTER_SHOT_TWO] = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_MonsterShotTwoTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[(_uint)COMPONENTID::ID_STATIC].insert({ L"Com_ShotTwoTexture", pComponent });

	pComponent = m_pCalculatorCom = dynamic_cast<CCalculator*>(Engine::Clone_Proto(L"Proto_Calculator"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[(_uint)COMPONENTID::ID_DYNAMIC].insert({ L"Com_Calculator", pComponent });

	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[(_uint)COMPONENTID::ID_DYNAMIC].insert({ L"Com_Transform", pComponent });

	return S_OK;
}

void CWhiteSuit::State_Check()
{
	if (m_eCurState != m_ePreState)
	{
		switch (m_eCurState)
		{
		case CMonster::MONSTER_ATTACK:
			m_fFrame = 0.f;
			m_fMaxFrame = 14.f;
			break;
		case CMonster::MONSTER_HEADSHOT:
			m_fFrame = 0.f;
			m_fMaxFrame = 21.f;
			break;
		case CMonster::MONSTER_PUSH_ONE:
			m_fFrame = 0.f;
			m_fMaxFrame = 23.f;
			break;
		case CMonster::MONSTER_PUSH_TWO:
			m_fFrame = 0.f;
			m_fMaxFrame = 22.f;
			break;
		case CMonster::MONSTER_BULLSHOT:
			m_fFrame = 0.f;
			m_fMaxFrame = 18.f;
			break;
		case CMonster::MONSTER_SHOT_ONE:
			m_fFrame = 0.f;
			m_fMaxFrame = 24.f;
			break;
		case CMonster::MONSTER_SHOT_TWO:
			m_fFrame = 0.f;
			m_fMaxFrame = 19.f;
			break;
		}

		m_ePreState = m_eCurState;
	}
}

void CWhiteSuit::Free()
{
	CMonster::Free();
}
