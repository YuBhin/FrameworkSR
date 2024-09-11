#include "pch.h"
#include "..\Header\Loading.h"
#include "Export_Utility.h"

CLoading::CLoading(LPDIRECT3DDEVICE9 _pGraphicDev)
	: m_pGraphicDev(_pGraphicDev)
	, m_bFinish(false)
	, m_hThread(nullptr)
	, m_eID(LOADINGID::LOADING_END)
	, m_szLoading(L"")
{
	ZeroMemory(&m_tCrt, sizeof(CRITICAL_SECTION));

	m_pGraphicDev->AddRef();
}

CLoading::~CLoading()
{
}

CLoading* CLoading::Create(LPDIRECT3DDEVICE9 _pGraphicDev, LOADINGID _eID)
{
	CLoading* pLoading = new CLoading(_pGraphicDev);

	if (FAILED(pLoading->Ready_Loading(_eID)))
	{
		Safe_Release(pLoading);
		return nullptr;
	}

	return pLoading;
}

HRESULT CLoading::Ready_Loading(LOADINGID _eLoading)
{
	InitializeCriticalSection(&m_tCrt);

	m_eID = _eLoading;

	m_hThread = (HANDLE)_beginthreadex(NULL, 0, Thread_Main, this, 0, NULL);

	return S_OK;
}

_uint CLoading::Loading_Stage()
{
	lstrcpy(m_szLoading, L"Etc Loading................");

	// Etc
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_Transform", Engine::CTransform::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_Calculator", Engine::CCalculator::Create(m_pGraphicDev)), E_FAIL);
	//Beomseung
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_Left_Transform", Engine::CTransform::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_Right_Transform", Engine::CTransform::Create(m_pGraphicDev)), E_FAIL);


	lstrcpy(m_szLoading, L"Buffer Loading................");

	// Buffer
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_TriCol", Engine::CTriCol::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_RcCol", Engine::CRcCol::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_TerrainTex", Engine::CTerrainTex::Create(m_pGraphicDev, VTXCNTX, VTXCNTZ, VTXITV)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_CubeTex", Engine::CCubeTex::Create(m_pGraphicDev)), E_FAIL);
	// Floor Buffer - FirstFloor
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_FloorTex", Engine::CFloorTex::Create(m_pGraphicDev, 512, 512, VTXITV)), E_FAIL);

	//Beomseung
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_RightArmBuffer", Engine::CRcTex::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_LeftArmBuffer", Engine::CRcTex::Create(m_pGraphicDev)), E_FAIL);


	lstrcpy(m_szLoading, L"Texture Loading................");

	// Texture
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_PlayerTex", Engine::CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Player/Ma.jpg", TEXTUREID::TEX_NORMAL)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_PlayerTex2", Engine::CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Player0.png", TEXTUREID::TEX_NORMAL)), E_FAIL);
	//Jonghan Stage Change Start
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_MonsterAttackTex", Engine::CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Monster/WhiteMan/Attack/Monster_Attack%d.png", TEXTUREID::TEX_NORMAL, 14)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_MonsterHeadShotTex", Engine::CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Monster/WhiteMan/HeadShot/Monster_HeadShot%d.png", TEXTUREID::TEX_NORMAL, 21)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_MonsterBullShotTex", Engine::CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Monster/WhiteMan/BullShot/Monster_Bullshot%d.png", TEXTUREID::TEX_NORMAL, 18)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_MonsterPushOneTex", Engine::CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Monster/WhiteMan/Push/Push_1/Monster_Push%d.png", TEXTUREID::TEX_NORMAL, 23)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_MonsterPushTwoTex", Engine::CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Monster/WhiteMan/Push/Push_2/Monster_Push%d.png", TEXTUREID::TEX_NORMAL, 22)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_MonsterShotOneTex", Engine::CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Monster/WhiteMan/Shot/Shot_1/Monster_Shot%d.png", TEXTUREID::TEX_NORMAL, 24)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_MonsterShotTwoTex", Engine::CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Monster/WhiteMan/Shot/Shot_2/Monster_Shot%d.png", TEXTUREID::TEX_NORMAL, 19)), E_FAIL);
	//Jonghan Stage Change End
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_TerrainTexture", Engine::CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Terrain/Terrain0.png", TEXTUREID::TEX_NORMAL)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_TerrainTexture2", Engine::CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Terrain/Grass_%d.tga", TEXTUREID::TEX_NORMAL, 2)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_SkyBox", Engine::CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/SkyBox/burger%d.dds", TEXTUREID::TEX_CUBE, 4)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_EffectTex", Engine::CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Explosion/Explosion%d.png", TEXTUREID::TEX_NORMAL, 90)), E_FAIL);
	//Beomseung
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_RightArmTex", Engine::CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/MMJ/PlayerRight/Right%d.png", TEXTUREID::TEX_NORMAL, 3)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_LeftArmTex", Engine::CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/MMJ/PlayerLeft/Left%d.png", TEXTUREID::TEX_NORMAL, 17)), E_FAIL);
	// Floor Texture - FirstFloor
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_FirstFloor", Engine::CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/MMJFloor/FLOOR 1.png", TEXTUREID::TEX_NORMAL)), E_FAIL);

	// Floor Texture - Attribute Acid
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_AcidFloor", Engine::CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/MMJFloor/ACID A LUM.png", TEXTUREID::TEX_NORMAL)), E_FAIL);

	lstrcpy(m_szLoading, L"Loading Complete!!");

	m_bFinish = true;

	return 0;
}

unsigned int CLoading::Thread_Main(void* _pArg)
{
	CLoading* pLoading = reinterpret_cast<CLoading*>(_pArg);

	_uint iFlag(0);

	EnterCriticalSection(pLoading->Get_Crt());

	switch (pLoading->Get_LoadingID())
	{
	case LOADINGID::LOADING_STAGE:
		iFlag = pLoading->Loading_Stage();
		break;
	case LOADINGID::LOADING_BOSS:
		break;
	default :
		break;
	}

	LeaveCriticalSection(pLoading->Get_Crt());

	return iFlag;
}

void CLoading::Free()
{
	WaitForSingleObject(m_hThread, INFINITE);
	CloseHandle(m_hThread);
	DeleteCriticalSection(&m_tCrt);

	Safe_Release(m_pGraphicDev);
}