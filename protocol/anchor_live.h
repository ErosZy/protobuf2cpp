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

#ifndef DANMU_CORE_ANCHOR_LIVE_H
#define DANMU_CORE_ANCHOR_LIVE_H

#include "protobuf.h"

namespace protocol {
    class AnchorLive : public Protocol {
    public:
        AnchorLive() : a(linkerProtocol::AnchorLive()) {};
        explicit AnchorLive(const linkerProtocol::AnchorLive &us) : a(us) {};
        const linkerProtocol::AnchorLive &get_anchor_live() const { return this->a; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->a.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->a.ByteSize()];
            this->a.SerializeToArray(ptr, this->a.ByteSize());
            return std::make_shared<Buffer>(ptr, this->a.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::Number>("owid")) {
	this->a.set_owid(int32_t(o.get<jsonxx::Number>("owid")));
}

if(o.has<jsonxx::Number>("status")) {
	this->a.set_status(int32_t(o.get<jsonxx::Number>("status")));
}

if(o.has<jsonxx::String>("nickname")) {
	this->a.set_nickname((o.get<jsonxx::String>("nickname")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"owid\":"<< this->a.owid() << ",";
ss << "\"status\":"<< this->a.status() << ",";
ss << "\"nickname\":"<< "\"" << this->a.nickname() << "\"";
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::AnchorLive a;
    };
}
#endif //DANMU_CORE_ANCHOR_LIVE_H