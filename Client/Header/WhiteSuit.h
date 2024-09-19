#pragma once
#include "Humanoid.h"

BEGIN(Engine)

class CTriCol;
class CRcTex;
class CTexture;
class CCalculator;
class CTransform;

END

class CWhiteSuit : public CHumanoid
{
private:
	explicit CWhiteSuit(LPDIRECT3DDEVICE9 _pGraphicDev);
	virtual ~CWhiteSuit();

public:
	static CWhiteSuit* Create(LPDIRECT3DDEVICE9 _pGraphicDev);

public:
	virtual HRESULT	Ready_GameObject();

private:
	virtual HRESULT	Add_Component();
	virtual void State_Check(); //Jonghan Change
	virtual void Attack();

private:
	virtual void Free();
};

