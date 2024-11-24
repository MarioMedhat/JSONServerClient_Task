#include "JsonServerClient.hpp"
#include <cpr/cpr.h>
#include <stdexcept>
#include <iostream>

JsonServerClient::JsonServerClient(const std::string& baseUrl) : baseUrl_(baseUrl) {}

nlohmann::json JsonServerClient::get(const std::string& endpoint) const {
    cpr::Response response = cpr::Get(cpr::Url{baseUrl_ + endpoint});
    if (response.status_code != 200) {
        throw std::runtime_error("GET request failed: " + response.error.message);
    }
    return nlohmann::json::parse(response.text);
}

nlohmann::json JsonServerClient::post(const std::string& endpoint, const nlohmann::json& payload) const {
    cpr::Response response = cpr::Post(
        cpr::Url{baseUrl_ + endpoint},
        cpr::Header{{"Content-Type", "application/json"}},
        cpr::Body{payload.dump()}
    );
    if (response.status_code != 200 && response.status_code != 201) {
        throw std::runtime_error("POST request failed: " + response.error.message);
    }
    return nlohmann::json::parse(response.text);
}

nlohmann::json JsonServerClient::put(const std::string& endpoint, const nlohmann::json& payload) const {
    cpr::Response response = cpr::Put(
        cpr::Url{baseUrl_ + endpoint},
        cpr::Header{{"Content-Type", "application/json"}},
        cpr::Body{payload.dump()}
    );
    if (response.status_code != 200) {
        throw std::runtime_error("PUT request failed: " + response.error.message);
    }
    return nlohmann::json::parse(response.text);
}

nlohmann::json JsonServerClient::del(const std::string& endpoint) const {
    cpr::Response response = cpr::Delete(cpr::Url{baseUrl_ + endpoint});
    if (response.status_code != 200) {
        throw std::runtime_error("DELETE request failed: " + response.error.message);
    }
    return nlohmann::json::parse(response.text);
}
