#include "DataStore.h"

void DataStore::save(const char* key, const char* value) {
    SPIFFS.begin();

    File f = SPIFFS.open("/variables.ds", "r");
    if (!f) {
        debug_error("File didn't open!");
        return;
    }

    uint length = f.size();
    char* content = new char[length];
    f.readBytes(content, length);
    f.close();

    JsonObject* json = decode_json(content);
    (*json)[key] = value;
    
    String buffer;
    json->printTo(buffer);

    f = SPIFFS.open("/variables.ds", "w");
    f.print(buffer);
    f.close();

    SPIFFS.end();
}

const char* DataStore::read(const char* key) {
    SPIFFS.begin();

    File f = SPIFFS.open("/variables.ds", "r");
    if (!f) {
        debug_error("File didn't open!");
        return "";
    }

    uint length = f.size();
    char* content = new char[length];
    f.readBytes(content, length);
    f.close();

    SPIFFS.end();

    JsonObject* json = decode_json(content);

    return (*json)[key];
}

void DataStore::remove(const char* key) {
    SPIFFS.begin();

    File f = SPIFFS.open("/variables.ds", "r");
    if (!f) {
        debug_error("File didn't open!");
        return;
    }

    uint length = f.size();
    char* content = new char[length];
    f.readBytes(content, length);
    f.close();

    JsonObject* json = decode_json(content);
    json->remove(key);
    
    String buffer;
    json->printTo(buffer);

    f = SPIFFS.open("/variables.ds", "w");
    f.print(buffer);
    f.close();

    SPIFFS.end();
}

bool DataStore::isExists(const char* key) {
    SPIFFS.begin();

    File f = SPIFFS.open("/variables.ds", "r");
    if (!f) {
        debug_error("File didn't open!");
        return "";
    }

    uint length = f.size();
    char* content = new char[length];
    f.readBytes(content, length);
    f.close();

    SPIFFS.end();

    JsonObject* json = decode_json(content);

    return json->containsKey(key);
}

void DataStore::init_storage_file(const char* filename) {
    File f = SPIFFS.open(filename, "w");
    f.println("{}");
    f.close();
}

JsonObject* DataStore::decode_json(const char* json) {
    StaticJsonBuffer<1024> jsonBuffer;
    JsonObject* decoded;
    bool isInitialized = false;

    while (true) {
        decoded = &(jsonBuffer.parseObject(json));

        if (!decoded->success()) {
            if (isInitialized) {
                debug_error("Couldn't pass json!");
                delete json;
                return decoded;
            }
            
            init_storage_file("/variables.ds");
            isInitialized = true;
            continue;
        }

        break;
    }

    return decoded;
}
