#include "C:/Users/Ty/Documents/SKSEPlugins/Build/Plugins/valhallaCombat/CMakeFiles/valhallaCombat.dir/Debug/cmake_pch.hxx"
#include "loadGame.h"
#include "avHandler.h"
#include "dataHandler.h"
using namespace Utils;
namespace loadGame {
	void EventCallBACK(SKSE::MessagingInterface::Message* msg)
	{
		if (msg->type == SKSE::MessagingInterface::kPostLoadGame) {
			DEBUG("save loaded, initializing...");
			RE::Actor* pc = RE::PlayerCharacter::GetSingleton();
			animEventHandler::RegisterSink(pc);
			onHitEventHandler::Register();
			DEBUG("initialization complete!");
		}
	}



}


