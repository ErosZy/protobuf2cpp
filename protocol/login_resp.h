/*
 * Copyright (C) 2018 QuanminTV. All Rights Reserved.
 *
 * @author zyeros <zyeros1991@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef DANMU_CORE_LOGIN_RESP_H
#define DANMU_CORE_LOGIN_RESP_H

#include "protobuf.h"

namespace protocol {
    class Login_resp : public Protocol {
    public:
        Login_resp() : l(linkerProtocol::LoginResp()) {};
        explicit Login_resp(const linkerProtocol::LoginResp &us) : l(us) {};
        const linkerProtocol::LoginResp &get_login_resp() const { return this->l; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->l.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->l.ByteSize()];
            this->l.SerializeToArray(ptr, this->l.ByteSize());
            return std::make_shared<Buffer>(ptr, this->l.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::Number>("status")) {
	this->l.set_status(int32_t(o.get<jsonxx::Number>("status")));
}

if(o.has<jsonxx::Number>("uid")) {
	this->l.set_uid(int32_t(o.get<jsonxx::Number>("uid")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"status\":"<< this->l.status() << ",";
ss << "\"uid\":"<< this->l.uid();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::LoginResp l;
    };
}
#endif //DANMU_CORE_LOGIN_RESP_H