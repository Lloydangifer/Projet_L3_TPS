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
	ShCamera::SetFovY(m_pCamera, ShCamera::GetFovY(m_pCamera) + .3f);
	ShCamera::SetCurrent3D(m_pCamera);

}

void CShTPSCamera::Update(CShVector2 playerPos, CShVector2 playerDir)
{
	ShCamera::SetPosition(m_pCamera, CShVector3(playerPos.m_x - playerDir.m_x * 700.0f, playerPos.m_y - playerDir.m_y * 700.0f, 400.0f));
	//ShCamera::SetPosition(m_pCamera, CShVector3(playerPos, 3000.0f));
	ShCamera::SetTarget(m_pCamera, CShVector3(playerPos, 150.0f));
}




void CShTPSCamera::DoStuff1()
{
	if (ShCamera::GetFovY(m_pCamera) < 1.99f)
		ShCamera::SetFovY(m_pCamera, ShCamera::GetFovY(m_pCamera) + .01f);
}

void CShTPSCamera::DoStuff2()
{
	if (ShCamera::GetFovY(m_pCamera) > .01f)
		ShCamera::SetFovY(m_pCamera, ShCamera::GetFovY(m_pCamera) - .01f);
}
