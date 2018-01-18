#ifndef DATA_STORE_H_
#define DATA_STORE_H_

#include <FS.h>
#include "ArduinoJson.h"
#include "groweco_debug.h"

class DataStore {
    public:
        static void save(const char* key, const char* value);
        static const char* read(const char* key);
        static void remove(const char* key);
        static bool isExists(const char* key);
        
    private:
        static void init_storage_file(const char* filename);
        static JsonObject* decode_json(const char* json);

        DataStore(void) {}
        ~DataStore(void) {}
};

#endif