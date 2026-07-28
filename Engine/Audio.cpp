#include "pch.h"
#include "Audio.h"

//namespace nu
//{
//	bool Audio::Initialize() 
//	{
//		FMOD_RESULT result = FMOD::System_Create(/*TODO: pass address of m_fmodSystem*/ &m_fmodSystem);
//		if (!CheckFMODResult(result)) 
//			return false;
//
//		void* extradriverdata = nullptr;
//		result = m_fmodSystem->init(32, FMOD_INIT_NORMAL, extradriverdata);
//		if (!CheckFMODResult(result)) 
//			return false;
//
//		return true;
//	}
//
//	void Audio::Shutdown()
//	{
//		//CheckFMODResult(/*TODO: release() fmod system*/);
//	}
//
//	void Audio::Update()
//	{
//		//CheckFMODResult(/*TODO: update() fmod system*/);
//	}
//}