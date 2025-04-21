// wifi_nvs_connect.h
#pragma once
#include <WiFi.h>
#include <nvs_flash.h>
#include <nvs.h>

// 读取 NVS "wifi" 命名空间下的 ssid/password 并尝试连接
inline bool try_connect_wifi_from_nvs(int max_count = 10, int timeout_ms = 10000) {
    nvs_handle_t nvs_handle;
    esp_err_t err = nvs_open("wifi", NVS_READONLY, &nvs_handle);
    if (err != ESP_OK) return false;

    for (int i = 0; i < max_count; ++i) {
        std::string ssid_key = "ssid";
        std::string pwd_key = "password";
        if (i > 0) {
            ssid_key += std::to_string(i);
            pwd_key += std::to_string(i);
        }
        char ssid[33] = {0};
        char password[65] = {0};
        size_t ssid_len = sizeof(ssid);
        size_t pwd_len = sizeof(password);
        if (nvs_get_str(nvs_handle, ssid_key.c_str(), ssid, &ssid_len) != ESP_OK) continue;
        if (nvs_get_str(nvs_handle, pwd_key.c_str(), password, &pwd_len) != ESP_OK) continue;

        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid, password);

        unsigned long start = millis();
        while (WiFi.status() != WL_CONNECTED && millis() - start < timeout_ms) {
            delay(100);
        }
        if (WiFi.status() == WL_CONNECTED) {
            nvs_close(nvs_handle);
            return true;
        }
        WiFi.disconnect(true);
        delay(200);
    }
    nvs_close(nvs_handle);
    return false;
}