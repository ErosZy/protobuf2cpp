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

#ifndef DANMU_CORE_LOGIN_REQ_H
#define DANMU_CORE_LOGIN_REQ_H

#include "protobuf.h"

namespace protocol {
    class LoginReq : public Protocol {
    public:
        LoginReq() : l(linkerProtocol::LoginReq()) {};
        explicit LoginReq(const linkerProtocol::LoginReq &us) : l(us) {};
        const linkerProtocol::LoginReq &get_login_req() const { return this->l; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->l.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->l.ByteSize()];
            this->l.SerializeToArray(ptr, this->l.ByteSize());
            return std::make_shared<Buffer>(ptr, this->l.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::Number>("uid")) {
	this->l.set_uid(int32_t(o.get<jsonxx::Number>("uid")));
}

if(o.has<jsonxx::String>("pwd")) {
	this->l.set_pwd((o.get<jsonxx::String>("pwd")));
}

if(o.has<jsonxx::String>("devid")) {
	this->l.set_devid((o.get<jsonxx::String>("devid")));
}

if(o.has<jsonxx::String>("app")) {
	this->l.set_app((o.get<jsonxx::String>("app")));
}

if(o.has<jsonxx::Number>("rt")) {
	this->l.set_rt(int64_t(o.get<jsonxx::Number>("rt")));
}

if(o.has<jsonxx::String>("vk")) {
	this->l.set_vk((o.get<jsonxx::String>("vk")));
}

if(o.has<jsonxx::String>("ver")) {
	this->l.set_ver((o.get<jsonxx::String>("ver")));
}

if(o.has<jsonxx::String>("channel")) {
	this->l.set_channel((o.get<jsonxx::String>("channel")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"uid\":"<< this->l.uid() << ",";
ss << "\"pwd\":"<< "\"" << this->l.pwd() << "\"" << ",";
ss << "\"devid\":"<< "\"" << this->l.devid() << "\"" << ",";
ss << "\"app\":"<< "\"" << this->l.app() << "\"" << ",";
ss << "\"rt\":"<< this->l.rt() << ",";
ss << "\"vk\":"<< "\"" << this->l.vk() << "\"" << ",";
ss << "\"ver\":"<< "\"" << this->l.ver() << "\"" << ",";
ss << "\"channel\":"<< "\"" << this->l.channel() << "\"";
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::LoginReq l;
    };
}
#endif //DANMU_CORE_LOGIN_REQ_H