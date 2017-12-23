/*
#if UNITY_IPHONE
#define CLIENTDLL "__Internal"
#else
#define CLIENTDLL "CClient"
#endif*/

using System;
using System.Runtime.InteropServices;
using UnityEngine;


class TestScript : MonoBehaviour
{
    void Awake()
    {
        ObjectStore.Init(1024);
        Init(
            Marshal.GetFunctionPointerForDelegate(
                new Func<int>(GameObjectNew)),
            Marshal.GetFunctionPointerForDelegate(
                new Func<int, int>(GameObjectGetTransform)),
            Marshal.GetFunctionPointerForDelegate(
                new Action<int, Vector3>(TransformSetPosition)));
    }

    void Update()
    {
        MonoBehaviourUpdate();
    }



    ////////////////////////////////////////////////////////////////
    // C++ functions for C# to call
    ////////////////////////////////////////////////////////////////

    [DllImport("CClient")]
    static extern void Init(
        IntPtr gameObjectNew,
        IntPtr gameObjectGetTransform,
        IntPtr transformSetPosition);

    [DllImport("CClient")]
    static extern void MonoBehaviourUpdate();

    ////////////////////////////////////////////////////////////////
    // C# functions for C++ to call
    ////////////////////////////////////////////////////////////////

    static int GameObjectNew()
    {
        GameObject go = GameObject.CreatePrimitive(PrimitiveType.Cube);
        return ObjectStore.Store(go);
    }

    static int GameObjectGetTransform(int thisHandle)
    {
        GameObject thiz = (GameObject)ObjectStore.Get(thisHandle);
        Transform transform = thiz.transform;
        return ObjectStore.Store(transform);
    }

    static void TransformSetPosition(int thisHandle, Vector3 position)
    {
        Transform thiz = (Transform)ObjectStore.Get(thisHandle);
        thiz.position = position;
    }
}