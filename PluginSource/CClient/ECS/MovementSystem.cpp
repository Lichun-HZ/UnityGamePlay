///
/// anax
/// An open source C++ entity system.
///
/// Copyright (C) 2013-2014 Miguel Martin (miguel@miguel-martin.com)
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
///

#include "MovementSystem.hpp"
#include "../CTest.h"

void MovementSystem::update(double deltaTime)
{
    auto entities = getEntities();
    for(auto& entity : entities)
    {
        int& transformHandle = entity.getComponent<TransformComponent>().transformHandle;
		Vector3& pos = entity.getComponent<TransformComponent>().currentPos;
        float& velocity = entity.getComponent<VelocityComponent>().velocity;	

		pos.x += deltaTime*velocity;
		if (pos.x > 7.0f)
			pos.x = -2.0f;

		float comp = (float)velocity;
		Vector3 position = { comp*((rand()%1000)/2000.0f), comp*((rand() % 1000) / 1000.0f), comp*((rand() % 1000) / 1000.0f) };
		InternalransformSetPosition(transformHandle, pos);
    }
}
