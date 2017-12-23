#include "CTest.h"
#include <vector>
#include <stdlib.h>

int(*GameObjectNew)();
int(*GameObjectGetTransform)(int thisHandle);
void(*TransformSetPosition)(int thisHandle, Vector3 position);

////////////////////////////////////////////////////////////////
// C++ functions for C# to call
////////////////////////////////////////////////////////////////

int numCreated;
std::vector<int> TransformHandles;

void Init(
	int(*gameObjectNew)(),
	int(*gameObjectGetTransform)(int),
	void(*transformSetPosition)(int, Vector3))
{
	GameObjectNew = gameObjectNew;
	GameObjectGetTransform = gameObjectGetTransform;
	TransformSetPosition = transformSetPosition;

	numCreated = 0;
}

void  MonoBehaviourUpdate(int thisHandle)
{
	TransformHandles.reserve(10);
	if (numCreated < 10)
	{
		int goHandle = GameObjectNew();
		int transformHandle = GameObjectGetTransform(goHandle);
		TransformHandles.push_back(transformHandle);

		float comp = (float)numCreated;
		Vector3 position = { comp, comp, comp };
		TransformSetPosition(transformHandle, position);
		numCreated++;
	}
	else
	{
		int iSize = TransformHandles.size();
		for (int i = 0; i < iSize; ++i)
		{
			float comp = (float)i;
			Vector3 position = { comp*((rand()%1000)/1000.0f), comp*((rand() % 1000) / 1000.0f), comp*((rand() % 1000) / 1000.0f) };
			TransformSetPosition(TransformHandles[i], position);
		}
	}
}
