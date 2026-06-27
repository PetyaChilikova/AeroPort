#include "UndoCmd.h"
#include "AirportManager.h"

void UndoCmd::execute() {
    AirportManager::getInstance().popAndUndo();
}

void UndoCmd::undo() {
}