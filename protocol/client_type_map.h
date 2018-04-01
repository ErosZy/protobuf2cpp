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

#ifndef DANMU_CORE_CLIENT_TYPE_MAP_H
#define DANMU_CORE_CLIENT_TYPE_MAP_H

#include "protobuf.h"

namespace protocol {
    class Client_type_map : public Protocol {
    public:
        Client_type_map() : c(linkerProtocol::ClientTypeMap()) {};
        explicit Client_type_map(const linkerProtocol::ClientTypeMap &us) : c(us) {};
        const linkerProtocol::ClientTypeMap &get_client_type_map() const { return this->c; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->c.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->c.ByteSize()];
            this->c.SerializeToArray(ptr, this->c.ByteSize());
            return std::make_shared<Buffer>(ptr, this->c.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::Number>("ios")) {
	this->c.set_ios(int32_t(o.get<jsonxx::Number>("ios")));
}

if(o.has<jsonxx::Number>("android")) {
	this->c.set_android(int32_t(o.get<jsonxx::Number>("android")));
}

if(o.has<jsonxx::Number>("pc")) {
	this->c.set_pc(int32_t(o.get<jsonxx::Number>("pc")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"ios\":"<< this->c.ios() << ",";
ss << "\"android\":"<< this->c.android() << ",";
ss << "\"pc\":"<< this->c.pc();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::ClientTypeMap c;
    };
}
#endif //DANMU_CORE_CLIENT_TYPE_MAP_H