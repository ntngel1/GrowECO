#include "ServerController.h"

const char* ServerController::_host = "";
String ServerController::_token = "";
DynamicJsonBuffer ServerController::jsonBuffer(512);
ServerController::Settings ServerController::settings;

ServerController::ConnectionStatus ServerController::checkServer(void)
{
    String path; // path for request
    path = String(_host) + "/sensors/get/" + String(_token);

    ServerController::HTTPResponse r = doRequest(path.c_str(), "GET");
    JsonObject& json = parseObject(r);

    if (json.get<bool>("success") != true) {
        return SERVER_ERROR;
    }

    ServerController::jsonBuffer.clear();
    return SERVER_CONNECTED;
}

ServerController::HTTPResponse ServerController::doRequest(const char* path, const char* requestType, String json) {
    HTTPClient http;
    http.begin(path);

    if (json != "")
        http.addHeader("Content-Type", "application/json");
    else
        http.addHeader("Content-Type", "plain/text");

    HTTPStatusCode statusCode = http.sendRequest(requestType, json);
    String data;
    if (statusCode != 0)
        data = http.getString();

    HTTPResponse response(statusCode, data);

    http.end();
    return response;
}

JsonArray& ServerController::parseArray(ServerController::HTTPResponse& response) {
    JsonArray& root = ServerController::jsonBuffer.parseArray(response.data);
    return root;
}

JsonObject& ServerController::parseObject(ServerController::HTTPResponse& response) {
    JsonObject& root = ServerController::jsonBuffer.parseObject(response.data);
    return root;
}

void ServerController::updateSensors(ClimateData *data)
{
    String path = String(_host) + "/sensors/update/" + String(_token);
    Serial.print("Path: ");
    Serial.println(path);
    String json = data->toJson();
    doRequest(path.c_str(), "PUT", json);
    ServerController::jsonBuffer.clear();
}

ActionData ServerController::getAction(void) {
    String path = String(_host) + "/actions/get/" + String(_token);
    ServerController::HTTPResponse r = doRequest(path.c_str(), "GET");
    ActionData d(r.data);
    ServerController::jsonBuffer.clear();
    return d;
}

void ServerController::getSettings(bool ifUpdated) {
    String path = String(_host) + "/settings/hasUpdates/" + String(_token);
    
    if (ifUpdated) {
        ServerController::HTTPResponse r = doRequest(path.c_str(), "GET");

        JsonObject& info = parseObject(r);
        if (!info["has_updates"].as<bool>()) {
            jsonBuffer.clear();
            return;
        }
        
        jsonBuffer.clear();
    }

    path = String(_host) + "/settings/get/" + String(_token);
    ServerController::HTTPResponse r = doRequest(path.c_str(), "GET");
    JsonObject& s = parseObject(r);

    settings.autowatering_enabled = s["autowatering_enabled"].as<bool>();
    settings.autowatering_threshold = s["autowatering_threshold"].as<uint8_t>();

    jsonBuffer.clear();
}
