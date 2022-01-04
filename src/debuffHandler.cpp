#include "debuffHandler.h"
#include "dataHandler.h"
void debuffHandler::initStaminaDebuff() {
	if (isPlayerExhausted) {
		DEBUG("player already exhausted!");
	}
	else {
		this->addDebuffPerk();
		this->isPlayerExhausted = true;
		DEBUG("Delegating threads");
		DEBUG("Setup stamina check");
		debuffThread::t1 = std::jthread(&debuffHandler::staminaDebuffOp, this);
		debuffThread::t1.detach();
		DEBUG("thread detached");
	}
}


void debuffHandler::staminaDebuffOp() {
	auto _debuffHandler = debuffHandler::GetSingleton();
	auto pc = RE::PlayerCharacter::GetSingleton();
	while (_debuffHandler->isPlayerExhausted && pc) {
		if (pc->GetActorValue(RE::ActorValue::kStamina) == pc->GetPermanentActorValue(RE::ActorValue::kStamina)) {
			_debuffHandler->rmDebuffPerk();
			_debuffHandler->isPlayerExhausted = false;
			break;
		}
		if (dataHandler::GetSingleton()->staminaMeterBlink) {
			Utils::FlashHUDMenuMeter(RE::ActorValue::kStamina);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

