#include "stdafx.h"
#include "SoundMgr.h"

void SoundMgr::Init(int totalChannels)
{
	for (int i = 0; i < totalChannels; ++i)
	{
		sf::Sound* sound = new sf::Sound();
		sound->setVolume(sfxVolume);
		waiting.push_back(sound);
	}
}

void SoundMgr::Release()
{
	for (auto sound : waiting)
	{
		delete sound;
	}
	waiting.clear();
	for (auto sound : playing)
	{
		delete sound;
	}
	playing.clear();
}

void SoundMgr::Update(float dt)
{
	auto it = playing.begin();
	while (it != playing.end())
	{
		if ((*it)->getStatus() == sf::Sound::Stopped)
		{
			buffers.erase(std::find(buffers.begin(), buffers.end(), (*it)->getBuffer()));
			waiting.push_back(*it);
			it = playing.erase(it);
			
			//sameFrameSoundCount = Utils::Clamp(--sameFrameSoundCount, 0, sameFrameSoundLimit);
		}
		else
		{
			++it;
		}
	}
}

void SoundMgr::PlayBgm(std::string id, bool loop)
{
	PlayBgm(SOUNDBUFFER_MGR.Get(id), loop);
}

void SoundMgr::PlayBgm(sf::SoundBuffer& buffer, bool loop)
{
	bgm.stop();
	bgm.setLoop(loop);
	bgm.setBuffer(buffer);
	bgm.play();
}

void SoundMgr::StopBgm()
{
	bgm.stop();
}

void SoundMgr::PlaySfx(std::string id, bool loop)
{
	PlaySfx(SOUNDBUFFER_MGR.Get(id), loop);
}

void SoundMgr::PlaySfx(sf::SoundBuffer& buffer, bool loop)
{
	sf::Sound* sound = nullptr;

	if (std::find(buffers.begin(), buffers.end(), &buffer) != buffers.end())
		return;

	if (waiting.empty())
	{
		sound = playing.front();
		playing.pop_front();
		sound->stop();
	}
	else
	{
		sound = waiting.front();
		waiting.pop_front();
	}
	sound->setBuffer(buffer);
	buffers.push_back(&buffer);
	std::cout << buffers.size() << std::endl;
	sound->setLoop(loop);
	sound->play();
	playing.push_back(sound);
}

void SoundMgr::SetSfxVolume(float v)
{
	sfxVolume = v;
	for (auto sound : playing)
	{
		sound->setVolume(sfxVolume);
	}
}

void SoundMgr::StopAllSfx()
{
	for (auto sound : playing)
	{
		sound->stop();
		waiting.push_back(sound);
	}
	playing.clear();
}
