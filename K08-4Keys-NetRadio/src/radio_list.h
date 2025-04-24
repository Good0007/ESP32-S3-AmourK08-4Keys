#pragma once
#include <vector>
#include <string>

#ifdef ARDUINO
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <FS.h>
#include <HTTPClient.h>
#else
#include <fstream>
#include <sstream>
#include <nlohmann/json.hpp>
#endif

struct RadioChannel {
    std::string name;
    std::string url;
};

class RadioList {
public:
    // 直接加载本地文件并返回频道集合
    static std::vector<RadioChannel> loadFromFile(const std::string& path) {
#ifdef ARDUINO
        std::vector<RadioChannel> result;
        File file = SPIFFS.open(path.c_str(), "r");
        if (!file) return result;
        size_t size = file.size();
        std::unique_ptr<char[]> buf(new char[size + 1]);
        file.readBytes(buf.get(), size);
        buf[size] = '\0';
        file.close();
        DynamicJsonDocument doc(8192);
        DeserializationError err = deserializeJson(doc, buf.get());
        if (err) return result;
        for (JsonObject obj : doc.as<JsonArray>()) {
            if (obj.containsKey("name") && obj.containsKey("url")) {
                result.push_back({obj["name"].as<std::string>(), obj["url"].as<std::string>()});
            }
        }
        return result;
#else
        std::vector<RadioChannel> result;
        std::ifstream infile(path);
        if (!infile.is_open()) return result;
        std::stringstream buffer;
        buffer << infile.rdbuf();
        infile.close();
        try {
            auto arr = nlohmann::json::parse(buffer.str());
            for (auto& obj : arr) {
                if (obj.contains("name") && obj.contains("url")) {
                    result.push_back({obj["name"], obj["url"]});
                }
            }
        } catch (...) {}
        return result;
#endif
    }

    // 直接加载网络json并返回频道集合
    static std::vector<RadioChannel> loadFromUrl(const std::string& url) {
#ifdef ARDUINO
        std::vector<RadioChannel> result;
        HTTPClient http;
        http.begin(url.c_str());
        int httpCode = http.GET();
        if (httpCode != HTTP_CODE_OK) {
            http.end();
            return result;
        }
        String payload = http.getString();
        http.end();
        DynamicJsonDocument doc(8192);
        DeserializationError err = deserializeJson(doc, payload.c_str());
        if (err) return result;
        for (JsonObject obj : doc.as<JsonArray>()) {
            if (obj.containsKey("name") && obj.containsKey("url")) {
                result.push_back({obj["name"].as<std::string>(), obj["url"].as<std::string>()});
            }
        }
        return result;
#else
        // PC端可用curl等方式实现，这里略
        return {};
#endif
    }
};