#pragma once
#include "Scene.h"
#include "Export_Utility.h"
#include "Export_System.h"

class CMapCreate : public CScene
{
private:
	explicit CMapCreate(LPDIRECT3DDEVICE9 _pGraphicDev);
	virtual ~CMapCreate();

public:
	static CMapCreate* Create(LPDIRECT3DDEVICE9 _pGraphicDev);

public:
	virtual HRESULT	Ready_Scene();
	virtual _int Update_Scene(const _float& _fTimeDelta);
	virtual void LateUpdate_Scene();
	virtual void Render_Scene();

private:
	//맵툴 기본 레이어들
	HRESULT Ready_LightInfo();
	HRESULT Ready_Layer_ToolEnvironment(const _tchar* _pLayerTag);
	HRESULT Ready_Layer_Terrain(const _tchar* _pLayerTag);

	//타일 저장할 레이어
	HRESULT Ready_Layer_PickingTile(const _tchar* _pLayerTag);
	//타일 저장한 레이어 찾아서 가져오기
	CLayer* Find_Layer_PickingTile();

	//바닥 오브젝트 생성
	HRESULT Create_Layer_PickingFloor(CLayer* _pLayer);
	//벽 오브젝트 생성
	HRESULT Create_Layer_PickingWall(CLayer* _pLayer);

	//벽 오브젝트 생성
	HRESULT Create_Layer_PickingWallTB(CLayer* _pLayer);

	// 가이드 지형 버퍼 가져오기
	_vec3 TilePiking_OnTerrain(int _iTile);
	// 가이드 지형의 버퍼와 마우스 좌표를 통해 [바닥] 타일 생성
	_vec3 FloorCreate_OnTerrain(HWND _hWnd, CGuideTex* _pGuideBufferCom);


	// 가이드 지형의 버퍼와 마우스 좌표를 통해 [벽] 타일 생성
	//left,right
	_vec3 WallCreate_OnTerrain1(HWND _hWnd, CGuideTex* _pGuideBufferCom);
	//top,bottom
	_vec3 WallCreate_OnTerrain2(HWND _hWnd, CGuideTex* _pGuideBufferCom);



	// 바닥 버퍼와 마우스 좌표를 통해 삭제
	HRESULT PickingTile_PosDelete(CLayer* _pLayer);
	// 이미 타일이 있으면 생성 X
	void PickingTile_PosCheck(CLayer* _pLayer);





	void MapSave(CLayer* _pLayer);
	void MapLoad(CLayer* _pLayer);


	//imgui 함수
	void ShowGUI();
	void SetMenu();

private:
	virtual void Free();


private:
	bool m_bCreateCheck;
	_vec3 m_vecWallRot;

	int m_iFloor;
	int m_iWall;
	int m_iWallTB;

};

