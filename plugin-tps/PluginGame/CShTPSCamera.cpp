#include "CShTPSCamera.h"

CShTPSCamera::CShTPSCamera()
: m_pCamera(shNULL)
{
}

CShTPSCamera::~CShTPSCamera(void)
{
}

void CShTPSCamera::Initialize(void)
{
	// Create camera
	m_pCamera = ShCamera::Create(GID(global), GID(camera_free), false);
	SH_ASSERT(NULL != m_pCamera);
	ShCamera::SetPosition(m_pCamera, CShVector3(-300.0f,-1500.0f, 1000.0f));
	ShCamera::SetTarget(m_pCamera, CShVector3(0.0f, 0.0f, 100.0f));
	ShCamera::SetFarPlaneDistance(m_pCamera, 3000.0f);
	ShCamera::SetCurrent2D(m_pCamera);
	ShCamera::SetCurrent3D(m_pCamera);
	ShCamera::SetProjectionOrtho(m_pCamera);
}

void CShTPSCamera::Update(CShVector2 playerPos)
{
	ShCamera::SetPosition(m_pCamera, CShVector3(playerPos, 3000.0f));
	ShCamera::SetTarget(m_pCamera, CShVector3(playerPos, 0.0f));
}