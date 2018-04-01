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

#ifndef DANMU_CORE_NOBLEMAN_EXT_H
#define DANMU_CORE_NOBLEMAN_EXT_H

#include "protobuf.h"

namespace protocol {
    class Nobleman_ext : public Protocol {
    public:
        Nobleman_ext() : n(linkerProtocol::NoblemanExt()) {};
        explicit Nobleman_ext(const linkerProtocol::NoblemanExt &us) : n(us) {};
        const linkerProtocol::NoblemanExt &get_nobleman_ext() const { return this->n; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->n.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->n.ByteSize()];
            this->n.SerializeToArray(ptr, this->n.ByteSize());
            return std::make_shared<Buffer>(ptr, this->n.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::Number>("level")) {
	this->n.set_level(int32_t(o.get<jsonxx::Number>("level")));
}

if(o.has<jsonxx::Number>("endTime")) {
	this->n.set_endtime(int32_t(o.get<jsonxx::Number>("endTime")));
}

if(o.has<jsonxx::Number>("roomHide")) {
	this->n.set_roomhide(int32_t(o.get<jsonxx::Number>("roomHide")));
}

if(o.has<jsonxx::Number>("status")) {
	this->n.set_status(int32_t(o.get<jsonxx::Number>("status")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"level\":"<< this->n.level() << ",";
ss << "\"endTime\":"<< this->n.endtime() << ",";
ss << "\"roomHide\":"<< this->n.roomhide() << ",";
ss << "\"status\":"<< this->n.status();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::NoblemanExt n;
    };
}
#endif //DANMU_CORE_NOBLEMAN_EXT_H