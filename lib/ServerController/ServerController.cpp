#include "ServerController.h"

ServerController::ConnectionStatus ServerController::connectWiFi(const char* ssid, const char* password)
{
    WiFi.begin(ssid, password);
    switch (WiFi.status()) {
        case WL_CONNECTED:
            return ConnectionStatus(CONNECTED_WIFI);
            break;
        case WL_CONNECT_FAILED:
            return ConnectionStatus(WIFI_ERROR);
            break;
    }

    return checkServer();
}

ServerController::ConnectionStatus ServerController::checkServer(void)
{
    String path; // path for request
    path = String(_host) + "/device/get/" + String(_authKey);

    HTTPClient http;
    HTTPStatusCode statusCode;

    http.begin(path.c_str());
    statusCode = http.GET();
    http.end();

    switch (statusCode) {
        case HTTP_CODE_OK:
            lastStatusCode = statusCode;
            return ConnectionStatus(SERVER_CONNECTED);
        case 400:
            lastStatusCode = statusCode;
            return ConnectionStatus(BAD_AUTH_KEY);
        default:
            lastStatusCode = statusCode;
            return ConnectionStatus(SERVER_ERROR);
    }
}

void ServerController::updateParameters(ClimateData *data)
{
    String path = String(_host) + "/sensors/update/" + String(_authKey);
    String json = data->toJson();
    HTTPClient http;
    http.begin(path.c_str());
    http.addHeader("Content-Type", "application/json");
    http.sendRequest("PUT", json);
    http.end();
}

void ServerController::handleActions(void) {

    String response;
    String path = String(_host) + "/api/actions/" + String(_authKey);

    HTTPClient http;
    http.begin(path.c_str());
    http.GET();
    response = http.getString();
    http.end();

    StaticJsonBuffer<256> jsonBuffer;
    JsonObject& json = jsonBuffer.parseObject(response.c_str());
    if (!json.success()) {
      return;
    }

    uint8_t actionCode = json["action_code"].as<uint8_t>();
    Serial.println(actionCode);
    switch (actionCode) {
      case 1:
        digitalWrite(D6, LOW);
        delay(3000);
        digitalWrite(D6, HIGH);
        break;
      case 3:
        break;
      default:
        break;
    }
}
