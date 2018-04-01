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

#ifndef DANMU_CORE_RED_PACKET_START_H
#define DANMU_CORE_RED_PACKET_START_H

#include "protobuf.h"

namespace protocol {
    class Red_packet_start : public Protocol {
    public:
        Red_packet_start() : r(linkerProtocol::RedPacketStart()) {};
        explicit Red_packet_start(const linkerProtocol::RedPacketStart &us) : r(us) {};
        const linkerProtocol::RedPacketStart &get_red_packet_start() const { return this->r; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->r.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->r.ByteSize()];
            this->r.SerializeToArray(ptr, this->r.ByteSize());
            return std::make_shared<Buffer>(ptr, this->r.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::Number>("id")) {
	this->r.set_id(int32_t(o.get<jsonxx::Number>("id")));
}

if(o.has<jsonxx::Number>("owid")) {
	this->r.set_owid(int32_t(o.get<jsonxx::Number>("owid")));
}

if(o.has<jsonxx::String>("redcode")) {
	this->r.set_redcode((o.get<jsonxx::String>("redcode")));
}

if(o.has<jsonxx::String>("nickname")) {
	this->r.set_nickname((o.get<jsonxx::String>("nickname")));
}

if(o.has<jsonxx::Number>("level")) {
	this->r.set_level(int32_t(o.get<jsonxx::Number>("level")));
}

if(o.has<jsonxx::String>("portrait")) {
	this->r.set_portrait((o.get<jsonxx::String>("portrait")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"id\":"<< this->r.id() << ",";
ss << "\"owid\":"<< this->r.owid() << ",";
ss << "\"redcode\":"<< "\"" << this->r.redcode() << "\"" << ",";
ss << "\"nickname\":"<< "\"" << this->r.nickname() << "\"" << ",";
ss << "\"level\":"<< this->r.level() << ",";
ss << "\"portrait\":"<< "\"" << this->r.portrait() << "\"";
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::RedPacketStart r;
    };
}
#endif //DANMU_CORE_RED_PACKET_START_H