#include "CShTPSCollisionsManager.h"

CShTPSCollisionsManager::CShTPSCollisionsManager(void)
: m_aCollisionShape()
, m_CollisionShapeCount(0)
{
}

CShTPSCollisionsManager::~CShTPSCollisionsManager(void)
{
}

void CShTPSCollisionsManager::Update(void)
{
}

void CShTPSCollisionsManager::Initialize(const CShIdentifier & levelIdentifier)
{
	ShCollisionShape::GetCollisionShapeArray(levelIdentifier,m_aCollisionShape);
	m_CollisionShapeCount = m_aCollisionShape.GetCount();
}

void CShTPSCollisionsManager::CheckBulletCollisionShapeCollision(CShTPSAmmo* bullet)
{
	CShVector2 position = bullet->GetPosition()+ bullet->GetDirection()*bullet->GetSpeed();
	CShSegment2 * trajectoire = new CShSegment2(bullet->GetPosition(),position);
	for(int i = 0; i < m_CollisionShapeCount; i++) //for each collision shape
	{
		int nbPoints = ShCollisionShape::GetPointCount(m_aCollisionShape.At(i)); // on r�cup�re le nombre de point du collisionshape
		for(int j = 0; j < nbPoints; j++) // pour chaque point on va �tablir un segment avec le point contigu� pour v�rifier l'intersection avec la trajectoire de la balle
		{
			int k;
			if(j == nbPoints-1)
			{
				k = 0;
			}
			else
			{
				k = j+1;
			}
			CShSegment2 * segment = new CShSegment2(ShCollisionShape::GetPoint(m_aCollisionShape.At(i),j), ShCollisionShape::GetPoint(m_aCollisionShape.At(i),k));
			if(shTRUE == shIntersect(*trajectoire, *segment))
			{
				bullet->SetMoving(false);
			}
		}
	}
}

void CShTPSCollisionsManager::CheckBulletCharacterCollision(CShTPSAmmo* bullet, CShTPSCharacter* character)
{
	if(ShEntity2::Intersect(bullet->GetSprite(),character->GetSprite()))
	{
		bullet->SetMoving(false);
		character->death();
	}
}