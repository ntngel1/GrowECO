#include "ServerController.h"

const char* ServerController::_host = "";
const char* ServerController::_token = "";
StaticJsonBuffer<1024> ServerController::jsonBuffer;

ServerController::ConnectionStatus ServerController::checkServer(void)
{
    String path; // path for request
    path = String(_host) + "/sensors/get/" + String(_token);

    ServerController::HTTPResponse r = doRequest(path.c_str(), "GET");
    JsonObject& json = parseObject(r);

    if (json.get<bool>("success") != true) {
        return SERVER_ERROR;
    }

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
    debug_message(_token);
    String data;
    if (statusCode != 0)
        data = http.getString();

    HTTPResponse response(statusCode, data);
    debug_message(data.c_str());

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
    String json = data->toJson();
    doRequest(path.c_str(), "PUT", json);
}

ActionData ServerController::getAction(void) {
    String path = String(_host) + "/actions/get/" + String(_token);
    ServerController::HTTPResponse r = doRequest(path.c_str(), "GET");

    return ActionData(r.data);
}
