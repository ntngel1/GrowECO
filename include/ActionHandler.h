#ifndef ACTION_HANDLER_H_
#define ACTION_HANDLER_H_

#include <functional>
#include "ActionData.h"
#include "ActionHandlers.h"

class ActionHandler {
    public:
        static void handleAction(ActionData action);
    private:
        ActionHandler(void) {}
        ~ActionHandler(void) {}
        static std::function<void(void)> action_handlers[];
};

#endif