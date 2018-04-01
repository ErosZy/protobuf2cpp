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

#ifndef DANMU_CORE_HONOR_LEVEL_UP_H
#define DANMU_CORE_HONOR_LEVEL_UP_H

#include "protobuf.h"

namespace protocol {
    class HonorLevelUp : public Protocol {
    public:
        HonorLevelUp() : h(linkerProtocol::HonorLevelUp()) {};
        explicit HonorLevelUp(const linkerProtocol::HonorLevelUp &us) : h(us) {};
        const linkerProtocol::HonorLevelUp &get_honor_level_up() const { return this->h; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->h.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->h.ByteSize()];
            this->h.SerializeToArray(ptr, this->h.ByteSize());
            return std::make_shared<Buffer>(ptr, this->h.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::Number>("uid")) {
	this->h.set_uid(int32_t(o.get<jsonxx::Number>("uid")));
}

if(o.has<jsonxx::Number>("honorOwid")) {
	this->h.set_honorowid(int32_t(o.get<jsonxx::Number>("honorOwid")));
}

if(o.has<jsonxx::Number>("honorLevel")) {
	this->h.set_honorlevel(int32_t(o.get<jsonxx::Number>("honorLevel")));
}

if(o.has<jsonxx::String>("honorName")) {
	this->h.set_honorname((o.get<jsonxx::String>("honorName")));
}

if(o.has<jsonxx::Boolean>("honorOwIsGray")) {
	this->h.set_honorowisgray((o.get<jsonxx::Boolean>("honorOwIsGray")));
}

if(o.has<jsonxx::Number>("type")) {
	this->h.set_type(int32_t(o.get<jsonxx::Number>("type")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"uid\":"<< this->h.uid() << ",";
ss << "\"honorOwid\":"<< this->h.honorowid() << ",";
ss << "\"honorLevel\":"<< this->h.honorlevel() << ",";
ss << "\"honorName\":"<< "\"" << this->h.honorname() << "\"" << ",";
ss << "\"honorOwIsGray\":"<< this->h.honorowisgray() << ",";
ss << "\"type\":"<< this->h.type();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::HonorLevelUp h;
    };
}
#endif //DANMU_CORE_HONOR_LEVEL_UP_H