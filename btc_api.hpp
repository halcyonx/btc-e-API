#ifndef BTC_API_HPP
#define BTC_API_HPP

#include "http/connection.hpp"
#include "hmac_sha512.hpp"
#include <ctime>

class btc_api: public uncopyable {
public:
    btc_api(const std::string& key, const std::string& secret)
        : nonce_(0), key_(key), secret_(secret), connection_("https://btc-e.com/tapi")
    {}
    
    json_data call(const std::string& method, const std::string& p) {
        std::string params = "nonce=";
        nonce_ = ::time(nullptr);
        params.append(std::to_string(nonce_));
        params.append("&method=" + method);
        params.append(p);
        
        std::map<std::string, std::string> headers;
        headers["Content-type"] = "application/x-www-form-urlencoded";
        headers["Key"] = key_;
        headers["Sign"] = this->signature(params);
        
        connection_.request(http::post(), params, headers);
        return connection_.get_response();
    }
    
    json_data getInfo() {
        return this->call("getInfo", "");
    }
    
    json_data tradeHistory() {
        return this->call("TradeHistory", "");
    }
    
private:
    std::string signature(const std::string& params) {
        HMAC_SHA512 hmac_sha512(secret_, params);
        return hmac_sha512.hex_digest();
    }
    
private:
    unsigned long nonce_;
    std::string key_;
    std::string secret_;
    
    http::connection connection_;
};

#endif