// dllmain.cpp : Defines the entry point for the DLL application.
#include "Features.h"

#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>

void InitializePaths()
{
	char modulePath[MAX_PATH]{};
	DWORD pathLength = GetModuleFileNameA(nullptr, modulePath, MAX_PATH);
	if (pathLength == 0 || pathLength == MAX_PATH)
	{
		GameDirectory = std::filesystem::current_path();
	}
	else
	{
		GameDirectory = std::filesystem::path(modulePath).parent_path();
	}

	ConfigFileName = GameDirectory / "GGSTEnhancer.ini";
	AvatarFileName = GameDirectory / "Avatar.png";
	AvatarBackupFileName = GameDirectory / "Avatar_Backup.png";
	OriginalAvatarFileName = GameDirectory / "Avatar_Original.png";
	ThumbnailFileName = GameDirectory / "Thumbnail.jpg";
	OriginalThumbnailFileName = GameDirectory / "Thumbnail_Original.jpg";
}

void PatchAll()
{
	InitializePaths();

	std::ifstream config(ConfigFileName);

	auto CreateConsole = [](const char* name) {
		FILE* ConsoleIO;
		if (!AllocConsole())
			return;

		freopen_s(&ConsoleIO, "CONIN$", "r", stdin);
		freopen_s(&ConsoleIO, "CONOUT$", "w", stderr);
		freopen_s(&ConsoleIO, "CONOUT$", "w", stdout);

		SetConsoleTitleA(name);
	};

	if (config.is_open())
	{
		std::string param;
		unsigned int value = 0;

		while (config >> param >> value)
		{
			if (!param.compare("Console"))
			{
				if (value == 1) CreateConsole("GGST Enhancer");
				std::cout << "[*] GGST Enhancer" << std::endl;
				std::cout << "[+] Settings Loaded: " << std::endl;
				std::cout << param << " " << value << std::endl;
			}
			if (!param.compare("GetRewardAuras"))
			{
				bGetRewardAuras = value == 1;
				std::cout << param << " " << bGetRewardAuras << std::endl;
			}
			if (!param.compare("RewardAvatarAura"))
			{
				SelectedRewardAvatarAura = (value >= 0 && value <= 3) ? value : 0;
				std::cout << param << " " << SelectedRewardAvatarAura << std::endl;
			}
			if (!param.compare("RewardNameAura"))
			{
				SelectedRewardNameAura = (value >= 0 && value <= 3) ? value : 0;
				std::cout << param << " " << SelectedRewardNameAura << std::endl;
			}
			if (!param.compare("GetRewardBadges"))
			{
				bGetRewardBadges = value == 1;
				std::cout << param << " " << bGetRewardBadges << std::endl;
			}
		}

		config.close();
	}
	else
	{
		std::ofstream ConfigFile;

		ConfigFile.open(ConfigFileName, std::ofstream::out | std::ofstream::trunc);

		ConfigFile << "Console 0" << std::endl;
		ConfigFile << "GetRewardAuras 0" << std::endl;
		ConfigFile << "RewardAvatarAura 0" << std::endl;
		ConfigFile << "RewardNameAura 0" << std::endl;
		ConfigFile << "GetRewardBadges 0" << std::endl;

		ConfigFile.close();
	}

	auto RunFeature = [](const char* name, int (*feature)()) {
		std::cout << "[+] " << name << std::endl;

		int ErrorAt = 0;
		for (int attempt = 1; attempt <= 300; ++attempt)
		{
			ErrorAt = feature();
			if (ErrorAt == 0)
			{
				std::cout << "[+] " << name << " Success!" << std::endl;
				return true;
			}

			if (attempt == 1 || attempt % 50 == 0)
			{
				std::cout << "[-] " << name << " Error @: " << ErrorAt << " - retrying..." << std::endl;
			}

			Sleep(100);
		}

		std::cout << "[!] " << name << " failed; continuing so other features can still load." << std::endl;
		return false;
	};

	RunFeature("Color Unlocker", ColorUnlocker);
	RunFeature("Uncensoring Museum", UncensorMuseum);
	RunFeature("Improving Fishing", ImproveFishing);
	RunFeature("Unlocking Rewards", UnlockRewards);
	RunFeature("Custom Avatar Image", CustomAvatarImage);
	RunFeature("Anti PNG Bomb", AntiPNGBomb);
	RunFeature("Custom Thumbnail", CustomThumbnail);

#ifdef _DEBUG
	RunFeature("DLC Unlocker", DLCUnlocker);
#endif

	DONE:

	std::cout << "[+] Done!" << std::endl;

}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)PatchAll, hModule, 0, nullptr);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
