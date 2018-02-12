#ifndef DATA_STORE_H_
#define DATA_STORE_H_

#include <FS.h>
#include "ArduinoJson.h"
#include "groweco_debug.h"

class DataStore {
    public:
        static void save(const char* key, const char* value);
        static String read(const char* key);
        
    private:
        DataStore(void) {}
        ~DataStore(void) {}
};

#endif