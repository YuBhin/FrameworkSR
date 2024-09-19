#include "pch.h"
#include "../Header/Ammo.h"
#include "Export_System.h"
#include "Export_Utility.h"

CAmmo::CAmmo(LPDIRECT3DDEVICE9 _pGraphicDev)
	: CBullet(_pGraphicDev)
	, m_pBufferCom(nullptr)
	, m_pTextureCom(nullptr)
	, m_pTransformCom(nullptr)
	, m_fTimer(0.f)
	, m_fFrame(0.f)
	, m_fMaxFrame(4.f)
{
}

CAmmo::~CAmmo()
{
}

HRESULT CAmmo::Ready_GameObject()
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	_matrix matWorld;
	m_pTransformCom->Set_Scale(0.5f, 0.5f, 0.5f);
	m_pTransformCom->Get_WorldMatrix(&matWorld);

	matWorld._41 = 0.f;
	matWorld._43 = 10.f;

	m_pTransformCom->Set_WorldMatrix(&matWorld);

	return S_OK;
}

_int CAmmo::Update_GameObject(const _float& _fTimeDelta)
{
	//Jonghan Monster Change Start
	Add_RenderGroup(RENDERID::RENDER_ALPHA, this);

	_int iExit = Engine::CBullet::Update_GameObject(_fTimeDelta);

	m_fFrame += 13.f * _fTimeDelta;
	
	if (m_fMaxFrame < m_fFrame) // Jonghan Change
		m_fFrame = 0.f;

	if (m_bisRender)
	{
		m_fTimer += _fTimeDelta;
		if (4.f < m_fTimer)
		{
			m_bisRender = false;
			m_fTimer = 0.f;
		}
	//Engine::CTransform* pPlayerTransform = dynamic_cast<Engine::CTransform*>
	//	(Engine::Get_Component(COMPONENTID::ID_DYNAMIC, L"Layer_GameLogic", L"Player", L"Com_Transform"));
	//NULL_CHECK_RETURN(pPlayerTransform, -1);
	//
	//_vec3 vPlayerPos;
	//pPlayerTransform->Get_Info(INFO::INFO_POS, &vPlayerPos);
	//
	//m_pTransformCom->Chase_Target(&vPlayerPos, 5.f * _fTimeDelta);

	//Add_RenderGroup(RENDERID::RENDER_NONALPHA, this);
		_matrix		matWorld, matView, matBill, matResult;
		m_pTransformCom->Get_WorldMatrix(&matWorld);

		m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);

		D3DXMatrixIdentity(&matBill);

		matBill._11 = matView._11;
		matBill._13 = matView._13;
		matBill._31 = matView._31;
		matBill._33 = matView._33;

		D3DXMatrixInverse(&matBill, 0, &matBill);

		matResult = matBill * matWorld;

		m_pTransformCom->Set_WorldMatrix(&(matResult));


	//Jonghan Monster Change End
	}

	return iExit;
}

void CAmmo::LateUpdate_GameObject()
{
	//Jonghan Monster Change Start
	_vec3 vPos;
	m_pTransformCom->Get_Info(INFO::INFO_POS, &vPos);

	if (m_bisRender)
	{
		m_pTransformCom->Set_Pos(vPos.x + (m_vDir.x * 0.1f), vPos.y + (m_vDir.y * 0.1f), vPos.z + (m_vDir.z * 0.1f)); //Consider Speed of Bullet
	}

	CGameObject::Compute_ViewZ(&vPos);


	//Jonghan Monster Change End
	Engine::CBullet::LateUpdate_GameObject();
}

void CAmmo::Render_GameObject()
{
	if(m_bisRender)
	{
		m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());
		//Jonghan Monster Change Start

		//m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

		m_pTextureCom->Set_Texture((_uint)m_fFrame); //Jonghan Change


		m_pBufferCom->Render_Buffer();

		m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		//m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	}
}

void CAmmo::Fire_Bullet(LPDIRECT3DDEVICE9 _pGraphicDev, const _vec3& _vStartPos, const _vec3& _vDir, const _float& _fAttackDamage)
{
	m_bisRender = true;
	m_pTransformCom->Set_Pos(_vStartPos.x, _vStartPos.y, _vStartPos.z);
	m_vDir = _vDir;
	m_fAttackDamage = _fAttackDamage;
}


CAmmo* CAmmo::Create(LPDIRECT3DDEVICE9 _pGraphicDev)
{
	CAmmo* pAmmo = new CAmmo(_pGraphicDev);

	if (FAILED(pAmmo->Ready_GameObject()))
	{
		Safe_Release(pAmmo);
		MSG_BOX("Ammo Create Failed");
		return nullptr;
	}

	return pAmmo;
}

HRESULT CAmmo::Add_Component()
{
	CComponent* pComponent = NULL;

	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[(_uint)COMPONENTID::ID_DYNAMIC].insert({ L"Com_Transform", pComponent });

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"Proto_RcTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[(_uint)COMPONENTID::ID_STATIC].insert({ L"Com_Buffer", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_AmmoTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[(_uint)COMPONENTID::ID_STATIC].insert({ L"Com_AmmoTexture", pComponent });
}

void CAmmo::Free()
{
	CBullet::Free();
}
