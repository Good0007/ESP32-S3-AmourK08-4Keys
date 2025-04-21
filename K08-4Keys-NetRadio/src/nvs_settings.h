#pragma once
#include <nvs_flash.h>
#include <nvs.h>

class NvsSettings {
public:
    NvsSettings(const char* ns = "storage") : _ns(ns), _handle(0) {}

    bool begin() {
        nvs_flash_init();
        return nvs_open(_ns, NVS_READWRITE, &_handle) == ESP_OK;
    }

    void setInt(const char* key, int value) {
        nvs_set_i32(_handle, key, value);
        nvs_commit(_handle);
    }

    int getInt(const char* key, int defaultValue) {
        int32_t val = defaultValue;
        nvs_get_i32(_handle, key, &val);
        return val;
    }

    void close() {
        if (_handle) nvs_close(_handle);
        _handle = 0;
    }

    ~NvsSettings() { close(); }

private:
    const char* _ns;
    nvs_handle_t _handle;
};