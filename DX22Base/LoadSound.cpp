#include "LoadSound.h"
#include "SoundManager.h"

void LoadBattleSE()
{
	SoundManager::AddSE("HitKick01", "Assets/SE/SE_HitKick01.wav");
	SoundManager::AddSE("HitPunch01", "Assets/SE/SE_HitPunch01.wav");
	SoundManager::AddSE("HitPunch02", "Assets/SE/SE_HitPunch02.wav");
	SoundManager::AddSE("HitSword01", "Assets/SE/SE_HitSword01.wav");
	SoundManager::AddSE("HitSword02", "Assets/SE/SE_HitSword02.wav");
	SoundManager::AddSE("Kill01", "Assets/SE/SE_Kill01.wav");
	SoundManager::AddSE("MissKick01", "Assets/SE/SE_MissKick01.wav");
	SoundManager::AddSE("MissPunch01", "Assets/SE/SE_MissPunch01.wav");
	SoundManager::AddSE("MissSword01", "Assets/SE/SE_MissSword01.wav");
	SoundManager::AddSE("MissSword02", "Assets/SE/SE_MissSword02.wav");
	SoundManager::AddSE("ShoutOfWay", "Assets/SE/SE_ShoutOfWay.wav");
}

void LoadSelectSE()
{
	SoundManager::AddSE("Cancel", "Assets/SE/SE_Cancel.wav");
	SoundManager::AddSE("Enter01", "Assets/SE/SE_Enter01.wav");
	SoundManager::AddSE("Select", "Assets/SE/SE_Select.wav");

}
