#pragma once

#if _MSC_VER // this is defined when compiling with Visual Studio
#define EXPORT_API __declspec(dllexport) // Visual Studio needs annotating exported functions with this
#else
#define EXPORT_API // XCode does not need annotating exported functions, so define is empty
#endif


extern "C"
{
	////////////////////////////////////////////////////////////////
	// C# struct types
	////////////////////////////////////////////////////////////////

	struct Vector3
	{
		float x;
		float y;
		float z;
	};


	////////////////////////////////////////////////////////////////
	// C++ functions for C# to call
	////////////////////////////////////////////////////////////////

	void EXPORT_API Init(
		int(*gameObjectNew)(),
		int(*gameObjectGetTransform)(int),
		void(*transformSetPosition)(int, Vector3));

	void EXPORT_API MonoBehaviourUpdate(int thisHandle);

}
