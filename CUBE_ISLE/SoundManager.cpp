#include "stdafx.h"
#include "SoundManager.h"


#if _WIN64
#pragma comment(lib, "FMOD/lib/fmod64_vc.lib")
#else
#pragma comment(lib, "FMOD/lib/fmod_vc.lib")
#endif



namespace
{
	deque<pair<string, Vector3>> g_PlayListQueue;

	FMOD_RESULT F_CALLBACK systemcallback(FMOD_SYSTEM *system, FMOD_SYSTEM_CALLBACK_TYPE type, void *commanddata1, void *commanddata2, void* userdata)
	{
		auto sys = reinterpret_cast<FMOD::System *>(system);
		if (type & FMOD_SYSTEM_CALLBACK_DEVICELISTCHANGED)
		{
			sys->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
		}

		return FMOD_OK;
	}
};

void PushPlayQueue(string Tag, Vector3& position) { g_PlayListQueue.emplace_back(move(Tag), move(position)); }

pair<string, Vector3> PopPlayQueue()
{
	auto retval = g_PlayListQueue.front();
	g_PlayListQueue.pop_front();
	return retval;
}

size_t PlayQueueSize() { return g_PlayListQueue.size(); }



CFMODSystem::CFMODSystem()
{
	FMOD_RESULT result;

	result = FMOD::System_Create(&m_System);
	if (result != FMOD_RESULT::FMOD_OK) goto Fail;

	result = m_System->getVersion(&m_fmodVersion);
	if (result != FMOD_RESULT::FMOD_OK) goto Fail;

	if (m_fmodVersion < FMOD_VERSION)
	{
		TCHAR strerr[256];
		::wsprintf(strerr, TEXT("FMOD lib version %08x doesn't match header version %08x"), m_fmodVersion, FMOD_VERSION);
		::OutputDebugString(strerr);
		if (::IsDebuggerPresent()) ::DebugBreak();
		goto Fail;
	}

	result = m_System->init(FMOD_MAX_CHANNEL_WIDTH, FMOD_INIT_NORMAL, nullptr);
	if (result != FMOD_RESULT::FMOD_OK) goto Fail;

	//	result = m_System->setCallback(systemcallback);
	//	if (result != FMOD_RESULT::FMOD_OK) goto Fail;

	return;


Fail:
	if (m_System)
	{
		m_System->close();
		m_System->release();
	}

}



CFMODSystem::~CFMODSystem()
{
	if (m_System)
	{
		m_System->close();
		m_System->release();
	}
}



shared_ptr<CFMODSystem> CFMODSystem::Get()
{
	static shared_ptr<CFMODSystem> instance{ new CFMODSystem{} };
	return instance;
}

FMOD_RESULT CFMODSystem::update() const
{
	return m_System->update();
}

// 머리 위치를 항상 update 귀는 머리에 있으니까
// look up 카메라위치 look과 up은 normalize해야됨
FMOD_RESULT CFMODSystem::update(float fTimeElapsed, Vector3 vLook, Vector3 vUp, Vector3 vPosition)
{
	auto system = Get()->GetSystem();

	if (Get()->m_bNotInitPosition)
	{
		Get()->m_bNotInitPosition = false;
		Get()->m_ptLast = vPosition;
	}

	FMOD_VECTOR forward = { vLook.x, vLook.y, vLook.z };
	FMOD_VECTOR up = { vUp.x, vUp.y, vUp.z };
	FMOD_VECTOR listenerpos = { vPosition.x, vPosition.y, vPosition.z };

	// 1초에 얼마나 가느냐.. 표현.. 왜 쓰는지 도율찡도 모르겠다 예제 코드임
	auto xmfVel = (vPosition - Get()->m_ptLast) * (1.f / fTimeElapsed);

	auto vel = FMOD_VECTOR{ xmfVel.x, xmfVel.y, xmfVel.z };
	
	Get()->m_ptLast = vPosition;

	system->set3DListenerAttributes(0, &listenerpos, &vel, &forward, &up);
	return Get()->update();
}



CSoundManager::CSoundManager()
	: m_System{ FMOD_System_Instance() }
{
}

CSoundManager::~CSoundManager()
{
}

bool CSoundManager::AddSound(string key, path szPath, SoundType SoundType)
{
	auto& Elem = m_Sound[key];

	if (Elem.Sound) Elem.Sound->release();

	FMOD_RESULT result;

	switch (Elem.type = SoundType)
	{
	case SoundType::Stream:
		result = GetSystem()->createStream(szPath.generic_string().c_str(), FMOD_LOOP_NORMAL | FMOD_2D, nullptr, &Elem.Sound);
		break;
	case SoundType::Effect3D:
		result = GetSystem()->createSound(szPath.generic_string().c_str(), FMOD_3D | FMOD_3D_LINEARSQUAREROLLOFF, nullptr, &Elem.Sound);
		break;
	case SoundType::Effect2D:
		result = GetSystem()->createSound(szPath.generic_string().c_str(), FMOD_DEFAULT, nullptr, &Elem.Sound);
		break;
	default: result = FMOD_RESULT::FMOD_ERR_FILE_NOTFOUND;
	}

	return (result == FMOD_RESULT::FMOD_OK);
}

bool CSoundManager::AddSound(string key, path szPath, float fMinDist, float fMaxDist)
{
	auto retval = AddSound(key, szPath, SoundType::Effect3D);
	Set3DSoundAttributes(key, fMinDist, fMaxDist);

	return retval;
}

bool CSoundManager::Play(string key)
{
	if (m_Sound.count(key) == 0) return false;
	auto& Elem = m_Sound.at(key);

	if (Elem.type == SoundType::Stream		&& m_System->IsMuteBGM())		return true;
	if (Elem.type == SoundType::Effect2D	&& m_System->IsMuteEffect())	return true;

	GetSystem()->playSound(Elem.Sound, nullptr, false, &Elem.Channel);
	return true;
}

bool CSoundManager::Play(string key, FMOD_VECTOR pos)
{
	if (m_Sound.count(key) == 0) return false;
	auto& Elem = m_Sound.at(key);

	if (Elem.type == SoundType::Effect3D	&& m_System->IsMuteEffect())	return true;

	GetSystem()->playSound(Elem.Sound, nullptr, true, &Elem.Channel);
	// Setting 3D Attribue : 재생 중 작업하면 소리가 이상하게 남
	Elem.Channel->set3DAttributes(&pos, nullptr);
	Elem.Channel->setPaused(false);

	return true;
}


bool CSoundManager::Play(string key, Vector3& pos)
{
	return Play(key, FMOD_VECTOR{ pos.x, pos.y, pos.z });
}

void CSoundManager::Stop(string key)
{
	if (m_Sound.count(key) == 0) return;
	auto& Elem = m_Sound.at(key);
	if (!Elem.Channel) return;

	bool bNowPlaying;
	Elem.Channel->isPlaying(&bNowPlaying);

	if (bNowPlaying) Elem.Channel->stop();
	Elem.Channel = nullptr;
}

void CSoundManager::Stop() const
{
	FMOD::ChannelGroup * masterChannelGroup{ nullptr };
	GetSystem()->getMasterChannelGroup(&masterChannelGroup);
	if (!masterChannelGroup) return;
	masterChannelGroup->stop();
}

void CSoundManager::Pause(string key, bool bPause)
{
	if (m_Sound.count(key) == 0) return;
	auto& Elem = m_Sound.at(key);
	if (!Elem.Channel) return;

	bool bNowPlaying;
	Elem.Channel->isPlaying(&bNowPlaying);

	if (!bNowPlaying) return;
	Elem.Channel->setPaused(bPause);
}

void CSoundManager::inversePause(string key)
{
	if (m_Sound.count(key) == 0) return;
	auto& Elem = m_Sound.at(key);
	if (!Elem.Channel) return;

	bool bNowPlaying;
	Elem.Channel->isPlaying(&bNowPlaying);

	if (!bNowPlaying) return;
	bool bPause;
	Elem.Channel->getPaused(&bPause);
	Elem.Channel->setPaused(!bPause);
}

void CSoundManager::Set3DSoundAttributes(string key, float fMinDist, float fMaxDist)
{
	if (m_Sound.count(key) == 0) return;
	auto& Elem = m_Sound.at(key);

	Elem.Sound->set3DMinMaxDistance(fMinDist, fMaxDist);
}
