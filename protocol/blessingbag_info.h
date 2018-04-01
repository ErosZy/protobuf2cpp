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

#ifndef DANMU_CORE_BLESSINGBAG_INFO_H
#define DANMU_CORE_BLESSINGBAG_INFO_H

#include "protobuf.h"

namespace protocol {
    class Blessingbag_info : public Protocol {
    public:
        Blessingbag_info() : b(linkerProtocol::BlessingbagInfo()) {};
        explicit Blessingbag_info(const linkerProtocol::BlessingbagInfo &us) : b(us) {};
        const linkerProtocol::BlessingbagInfo &get_blessingbag_info() const { return this->b; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->b.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->b.ByteSize()];
            this->b.SerializeToArray(ptr, this->b.ByteSize());
            return std::make_shared<Buffer>(ptr, this->b.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::Number>("level")) {
	this->b.set_level(int32_t(o.get<jsonxx::Number>("level")));
}

if(o.has<jsonxx::Number>("progress")) {
	this->b.set_progress(int32_t(o.get<jsonxx::Number>("progress")));
}

if(o.has<jsonxx::Number>("capacity")) {
	this->b.set_capacity(int32_t(o.get<jsonxx::Number>("capacity")));
}

if(o.has<jsonxx::Number>("status")) {
	this->b.set_status(int32_t(o.get<jsonxx::Number>("status")));
}

if(o.has<jsonxx::Number>("isCrit")) {
	this->b.set_iscrit(int32_t(o.get<jsonxx::Number>("isCrit")));
}

if(o.has<jsonxx::Number>("bid")) {
	this->b.set_bid(int32_t(o.get<jsonxx::Number>("bid")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"level\":"<< this->b.level() << ",";
ss << "\"progress\":"<< this->b.progress() << ",";
ss << "\"capacity\":"<< this->b.capacity() << ",";
ss << "\"status\":"<< this->b.status() << ",";
ss << "\"isCrit\":"<< this->b.iscrit() << ",";
ss << "\"bid\":"<< this->b.bid();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::BlessingbagInfo b;
    };
}
#endif //DANMU_CORE_BLESSINGBAG_INFO_H