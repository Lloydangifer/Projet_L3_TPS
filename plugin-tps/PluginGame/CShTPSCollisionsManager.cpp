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
		int nbPoints = ShCollisionShape::GetPointCount(m_aCollisionShape.At(i)); // on récupère le nombre de point du collisionshape
		for(int j = 0; j < nbPoints; j++) // pour chaque point on va établir un segment avec le point contiguë pour vérifier l'intersection avec la trajectoire de la balle
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
	if(bullet->GetOrigin() != character)
	{
		if(ShObject::e_type_entity2 == ShObject::GetType(character->GetSprite()))
		{
			if(ShEntity2::Intersect(bullet->GetSprite(),(ShEntity2 *)character->GetSprite()))
			{
				bullet->SetMoving(false);
				character->death();
			}
		}
	}
}

void CShTPSCollisionsManager::CheckPlayerEnemyViewField(CShTPSPlayer* player, CShTPSEnemy* enemy)
{
	bool seen = true;
	CShSegment2 * view = new CShSegment2(enemy->GetPosition(), player->GetPosition());
	for(int i = 0; i < m_CollisionShapeCount; i++) //for each collision shape
	{
		int nbPoints = ShCollisionShape::GetPointCount(m_aCollisionShape.At(i)); // on récupère le nombre de point du collisionshape
		for(int j = 0; j < nbPoints; j++) // pour chaque point on va établir un segment avec le point contiguë pour vérifier l'intersection avec la ligne de vue de l'ennemi
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
			if(shTRUE == shIntersect(*view, *segment)) // If the enemy see the player, he will go on the player position
			{
				seen = false;
			}
			if(!seen)
			{
				break;
			}
		}
		if(!seen)
		{
			break;
		}
	}

	if(seen)
	{
		enemy->SetTarget(player->GetPosition());
	}

}