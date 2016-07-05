#include "../inc/structure.h"

void Structure::onNewMember(TypeDeclaration* td) {
	members.push_back(td);
}

DefinitionType Structure::getType() {
	return DFT_STRUCTURE;
}