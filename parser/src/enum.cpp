#include "../inc/enum.h"

void Enum::onNewMember(string name) {
	_assert(std::find(members.begin(), members.end(), name) == members.end());
	members.push_back(name);
}
DefinitionType Enum::getType() {
	return DFT_ENUM;
}