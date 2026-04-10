// dllmain.cpp : Defines the entry point for the DLL application.
#include "Features.h"

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>

void PatchAll()
{
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

	int ErrorAt = 0;

	std::chrono::seconds Timeout(5);
	std::this_thread::sleep_for(Timeout);

	std::cout << "[+] Uncensoring Museum" << std::endl;
	while (ErrorAt = UncensorMuseum()) {
		std::cout << "[-] Uncensoring Museum Error @: " << ErrorAt << "\n";
		std::this_thread::sleep_for(Timeout);
	};
	std::cout << "[+] Success!" << std::endl;

	std::cout << "[+] Improving Fishing" << std::endl;
	while (ErrorAt = ImproveFishing()) {
		std::cout << "[-] Improving Fishing Error @: " << ErrorAt << "\n";
		std::this_thread::sleep_for(Timeout);
	};
	std::cout << "[+] Success!" << std::endl;

	std::cout << "[+] Unlocking Rewards" << std::endl;
	while (ErrorAt = UnlockRewards()) {
		std::cout << "[-] Unlocking Rewards Error @: " << ErrorAt << "\n";
		std::this_thread::sleep_for(Timeout);
	};
	std::cout << "[+] Success!" << std::endl;

	std::cout << "[+] Custom Avatar Image" << std::endl;
	while (ErrorAt = CustomAvatarImage()) {
		std::cout << "[-] Custom Avatar Image Error @: " << ErrorAt << "\n";
		std::this_thread::sleep_for(Timeout);
	};
	std::cout << "[+] Success!" << std::endl;

	std::cout << "[+] Anti PNG Bomb" << std::endl;
	while (ErrorAt = AntiPNGBomb()) {
		std::cout << "[-] Anti PNG Bomb Error @: " << ErrorAt << "\n";
		std::this_thread::sleep_for(Timeout);
	};
	std::cout << "[+] Success!" << std::endl;

	std::cout << "[+] Custom Thumbnail" << std::endl;
	while (ErrorAt = CustomThumbnail()) {
		std::cout << "[-] Custom Thumbnail Error @: " << ErrorAt << "\n";
		std::this_thread::sleep_for(Timeout);
	};
	std::cout << "[+] Success!" << std::endl;

#ifdef _DEBUG
	std::cout << "[+] DLC Unlocker" << std::endl;
	while (!DLCUnlocker()) {};
	std::cout << "[+] Success!" << std::endl;
#endif

	std::cout << "[+] Color Unlocker" << std::endl;
	while (ErrorAt = ColorUnlocker()) {
		std::cout << "[-] Color Unlocker Error @: " << ErrorAt << "\n";
		std::this_thread::sleep_for(Timeout);
	};
	std::cout << "[+] Success!" << std::endl;

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
