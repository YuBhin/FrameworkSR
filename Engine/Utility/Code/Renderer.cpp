#include "..\..\Header\Renderer.h"

IMPLEMENT_SINGLETON(CRenderer)

CRenderer::CRenderer()
{
	// 초기화 관련 추가
	Clear_RenderGroup();

	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixOrthoLH(&m_matOrtho, (_float)WINCX, (_float)WINCY, 0.f, 1.f);
}

CRenderer::~CRenderer()
{
	Free();
}

void CRenderer::Add_RenderGroup(RENDERID _eType, CGameObject* _pGameObject)
{
	if ((_uint)RENDERID::RENDER_END <= (_uint)_eType || _pGameObject == nullptr)
		return;

	m_RenderGroup[(_uint)_eType].push_back(_pGameObject);
	_pGameObject->AddRef();
}

void CRenderer::Render_GameObject(LPDIRECT3DDEVICE9& _pGraphicDev)
{
	Render_Priority(_pGraphicDev);
	Render_NonAlpha(_pGraphicDev);
	Render_Alpha(_pGraphicDev);
	Render_UI(_pGraphicDev);

	Clear_RenderGroup();
}

void CRenderer::Clear_RenderGroup()
{
	for (size_t i = 0; i < (_uint)RENDERID::RENDER_END; ++i)
	{
		for_each(m_RenderGroup[i].begin(), m_RenderGroup[i].end(), CDeleteObj());
		m_RenderGroup[i].clear();
	}
}

void CRenderer::Render_Priority(LPDIRECT3DDEVICE9& _pGraphicDev)
{
	for (auto& pGameObject : m_RenderGroup[(_uint)RENDERID::RENDER_PRIORITY])
		pGameObject->Render_GameObject();
}

void CRenderer::Render_NonAlpha(LPDIRECT3DDEVICE9& _pGraphicDev)
{
	for (auto& pGameObject : m_RenderGroup[(_uint)RENDERID::RENDER_NONALPHA])
		pGameObject->Render_GameObject();
}

void CRenderer::Render_Alpha(LPDIRECT3DDEVICE9& _pGraphicDev)
{
	_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//_pGraphicDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//_pGraphicDev->SetRenderState(D3DRS_ALPHAREF, 0xc0);

	m_RenderGroup[(_uint)RENDERID::RENDER_ALPHA].sort
	(
		[](CGameObject* pDst, CGameObject* pSrc)->bool
		{
			return pDst->Get_ViewZ() > pSrc->Get_ViewZ();
		}
	);

	for (auto& pGameObject : m_RenderGroup[(_uint)RENDERID::RENDER_ALPHA])
		pGameObject->Render_GameObject();

	_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	//_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

void CRenderer::Render_UI(LPDIRECT3DDEVICE9& _pGraphicDev)
{
	// 직교 투영 추가
	_matrix matView, matProj;
	_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	_pGraphicDev->SetTransform(D3DTS_VIEW, &m_matView);
	_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_matOrtho);

	_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	for (auto& pGameObject : m_RenderGroup[(_uint)RENDERID::RENDER_UI])
		pGameObject->Render_GameObject();

	_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
	_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matProj);
}

void CRenderer::Free()
{
	Clear_RenderGroup();
}