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
	ShCamera::SetFarPlaneDistance(m_pCamera,10000.0f);
	ShCamera::SetNearPlaneDistance(m_pCamera, 1.0f);

	m_pCameraStyle = 0;

}

void CShTPSCamera::Update(CShVector2 playerPos, CShVector2 playerDir)
{
	switch (m_pCameraStyle)
	{
		case 0: // TPS camera like
		{
			ShCamera::SetProjectionPerspective(m_pCamera);
			ShCamera::SetCurrent3D(m_pCamera);
			ShCamera::SetPosition(m_pCamera, CShVector3(playerPos.m_x - playerDir.m_x * 400.0f, playerPos.m_y - playerDir.m_y * 400.0f, 250.0f));
			ShCamera::SetTarget(m_pCamera, CShVector3(playerPos.m_x + playerDir.m_x * 2000.0f, playerPos.m_y + playerDir.m_y * 2000.0f, -1.0f));
		}
		break;

		case 1: // High view, follows the direction of the player
		{
			ShCamera::SetProjectionOrtho(m_pCamera);
			ShCamera::SetCurrent2D(m_pCamera);
			ShCamera::SetPosition(m_pCamera, CShVector3(playerPos.m_x - playerDir.m_x , playerPos.m_y - playerDir.m_y, 1200.0f));
			ShCamera::SetTarget(m_pCamera, CShVector3(playerPos.m_x + playerDir.m_x * 10.0f, playerPos.m_y + playerDir.m_y * 10.0f, -200.0f));
		}
		break;

		case 2: // High view+, does not follow the direction of the player
		{
			ShCamera::SetProjectionOrtho(m_pCamera);
			ShCamera::SetCurrent2D(m_pCamera);
			ShCamera::SetPosition(m_pCamera, CShVector3(playerPos.m_x, playerPos.m_y, 2000.0f));
			ShCamera::SetTarget(m_pCamera, CShVector3(playerPos, 0.0f));
		}
		break;

	}
}




void CShTPSCamera::FovInc()
{
	if (m_pCameraStyle == 0)
	{
		if (ShCamera::GetFovY(m_pCamera) < 1.99f)
			ShCamera::SetFovY(m_pCamera, ShCamera::GetFovY(m_pCamera) + .01f);
	}
}

void CShTPSCamera::FovDec()
{
	if (m_pCameraStyle == 0)
	{
		if (ShCamera::GetFovY(m_pCamera) > .01f)
			ShCamera::SetFovY(m_pCamera, ShCamera::GetFovY(m_pCamera) - .01f);
	}
}


void CShTPSCamera::SwitchCameraStyle()
{
	m_pCameraStyle = (m_pCameraStyle + 1)%MAX_CAMERAS;
}