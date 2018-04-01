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

#ifndef DANMU_CORE_ZAN_UP_H
#define DANMU_CORE_ZAN_UP_H

#include "protobuf.h"

namespace protocol {
    class ZanUp : public Protocol {
    public:
        ZanUp() : z(linkerProtocol::ZanUp()) {};
        explicit ZanUp(const linkerProtocol::ZanUp &us) : z(us) {};
        const linkerProtocol::ZanUp &get_zan_up() const { return this->z; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->z.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->z.ByteSize()];
            this->z.SerializeToArray(ptr, this->z.ByteSize());
            return std::make_shared<Buffer>(ptr, this->z.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::Number>("owid")) {
	this->z.set_owid(int32_t(o.get<jsonxx::Number>("owid")));
}

if(o.has<jsonxx::Number>("color")) {
	this->z.set_color(int32_t(o.get<jsonxx::Number>("color")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"owid\":"<< this->z.owid() << ",";
ss << "\"color\":"<< this->z.color();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::ZanUp z;
    };
}
#endif //DANMU_CORE_ZAN_UP_H