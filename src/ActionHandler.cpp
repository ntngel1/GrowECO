#include "ActionHandler.h"

std::function<void(void)> ActionHandler::action_handlers[] = {
    ActionHandlers::__watering_handler__
};

void ActionHandler::handleAction(ActionData action) {
    uint8_t code = action.actionCode;
    ActionHandler::action_handlers[code]();
}