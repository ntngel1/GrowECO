#include "DataStore.h"

void DataStore::save(const char* key, const char* value) {
    SPIFFS.begin();

    File f = SPIFFS.open("/sets.ds", "r");
    if (!f) {
        f.close();
        debug_error("File didn't open! Creating it");
        f = SPIFFS.open("/sets.ds", "w");
        if (!f) {
            SPIFFS.end();
            f.close();
            debug_error("File didn't create!");
            return;
        }
        f.close();
    }
    f.close();
    f = SPIFFS.open("/sets.ds", "r");

    uint length = f.size();
    char* content = new char[length + 30];
    f.readBytes(content, length);
    f.close();
    content[length] = '\0';

    StaticJsonBuffer<256> jsonBuffer;
    JsonObject& json = jsonBuffer.parseObject(content);

    bool isClear = false;

    if (!json.success()) {
        isClear = true;
        jsonBuffer.clear();
    }
    
    if (isClear) {
        JsonObject& j = jsonBuffer.createObject();
        j[key] = value;

        String buffer;
        j.printTo(buffer);

        f = SPIFFS.open("/sets.ds", "w");
        f.print(buffer);
        f.close();
        delete content;
        return;
    }

    json[key] = value;

    String buffer;
    json.printTo(buffer);

    f = SPIFFS.open("/sets.ds", "w");
    f.print(buffer);
    f.close();

    SPIFFS.end();
    delete content;
    jsonBuffer.clear();
}

String DataStore::read(const char* key) {
    SPIFFS.begin();

    File f = SPIFFS.open("/sets.ds", "r");
    if (!f) {
        SPIFFS.end();
        f.close();
        debug_error("File didn't open!");
        return "";
    }

    uint length = f.size();
    char* content = new char[length + 30];
    f.readBytes(content, length);
    content[length] = '\0';
    f.close();
    SPIFFS.end();

    StaticJsonBuffer<256> jsonBuffer;
    JsonObject& json = jsonBuffer.parseObject(content);

    if (!json.success()) {
        debug_error("ERROR WHILE PARSING IN READ");
        jsonBuffer.clear();
        delete content;
        return "";
    }

    String r = json[key].as<String>();
    jsonBuffer.clear();
    delete content;
    return r;
}