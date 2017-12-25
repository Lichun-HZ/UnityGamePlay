#include "CTest.h"
#include <vector>
//#include <stdlib>
#include <anax/anax.hpp>
#include "ECS/MovementSystem.hpp"

MovementSystem movementSystem;
anax::World* world = NULL;

int(*GameObjectNew)();
int(*GameObjectGetTransform)(int thisHandle);
void(*TransformSetPosition)(int thisHandle, Vector3 position);

////////////////////////////////////////////////////////////////
// C++ functions for C# to call
////////////////////////////////////////////////////////////////

int numCreated;

void Init(
	int(*gameObjectNew)(),
	int(*gameObjectGetTransform)(int),
	void(*transformSetPosition)(int, Vector3))
{
	GameObjectNew = gameObjectNew;
	GameObjectGetTransform = gameObjectGetTransform;
	TransformSetPosition = transformSetPosition;

	world = new anax::World();
	world->addSystem(movementSystem);
}

void  MonoBehaviourUpdate(int thisHandle)
{
	if (numCreated < 10)
	{
		anax::Entity entity = world->createEntity();
		TransformComponent& transComp = entity.addComponent<TransformComponent>();
		VelocityComponent& veloComp = entity.addComponent<VelocityComponent>();
		entity.activate();

		int goHandle = GameObjectNew();
		int transformHandle = GameObjectGetTransform(goHandle);
		transComp.transformHandle = transformHandle;

		float comp = (float)numCreated;
		veloComp.velocity = comp;
		Vector3 position = { comp, comp, comp };
		transComp.currentPos = position;
		TransformSetPosition(transformHandle, position);
		numCreated++;
	}
	else
	{
		world->refresh();
		movementSystem.update(0.1);

		//int iSize = TransformHandles.size();
		//for (int i = 0; i < iSize; ++i)
		//{
		//	float comp = (float)i;
			//Vector3 position = { comp*((rand()%1000)/1000.0f), comp*((rand() % 1000) / 1000.0f), comp*((rand() % 1000) / 1000.0f) };
			//TransformSetPosition(TransformHandles[i], position);
		//}
	}
}

void InternalransformSetPosition(int thisHandle, Vector3 position)
{
	TransformSetPosition(thisHandle, position);
}
