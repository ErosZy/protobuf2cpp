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

#ifndef DANMU_CORE_ROOM_AD_ATTR_H
#define DANMU_CORE_ROOM_AD_ATTR_H

#include "protobuf.h"

namespace protocol {
    class RoomAdAttr : public Protocol {
    public:
        RoomAdAttr() : r(linkerProtocol::RoomAdAttr()) {};
        explicit RoomAdAttr(const linkerProtocol::RoomAdAttr &us) : r(us) {};
        const linkerProtocol::RoomAdAttr &get_room_ad_attr() const { return this->r; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->r.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->r.ByteSize()];
            this->r.SerializeToArray(ptr, this->r.ByteSize());
            return std::make_shared<Buffer>(ptr, this->r.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::Number>("pcslotid")) {
	this->r.set_pcslotid(int32_t(o.get<jsonxx::Number>("pcslotid")));
}

if(o.has<jsonxx::Number>("iosslotid")) {
	this->r.set_iosslotid(int32_t(o.get<jsonxx::Number>("iosslotid")));
}

if(o.has<jsonxx::Number>("androidslotid")) {
	this->r.set_androidslotid(int32_t(o.get<jsonxx::Number>("androidslotid")));
}

if(o.has<jsonxx::Number>("type")) {
	this->r.set_type(int32_t(o.get<jsonxx::Number>("type")));
}

if(o.has<jsonxx::Number>("duration")) {
	this->r.set_duration(int32_t(o.get<jsonxx::Number>("duration")));
}

if(o.has<jsonxx::Number>("frequency")) {
	this->r.set_frequency(int32_t(o.get<jsonxx::Number>("frequency")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"pcslotid\":"<< this->r.pcslotid() << ",";
ss << "\"iosslotid\":"<< this->r.iosslotid() << ",";
ss << "\"androidslotid\":"<< this->r.androidslotid() << ",";
ss << "\"type\":"<< this->r.type() << ",";
ss << "\"duration\":"<< this->r.duration() << ",";
ss << "\"frequency\":"<< this->r.frequency();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::RoomAdAttr r;
    };
}
#endif //DANMU_CORE_ROOM_AD_ATTR_H