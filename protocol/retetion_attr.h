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

#ifndef DANMU_CORE_RETETION_ATTR_H
#define DANMU_CORE_RETETION_ATTR_H

#include "protobuf.h"

namespace protocol {
    class Retetion_attr : public Protocol {
    public:
        Retetion_attr() : r(linkerProtocol::RetetionAttr()) {};
        explicit Retetion_attr(const linkerProtocol::RetetionAttr &us) : r(us) {};
        const linkerProtocol::RetetionAttr &get_retetion_attr() const { return this->r; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->r.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->r.ByteSize()];
            this->r.SerializeToArray(ptr, this->r.ByteSize());
            return std::make_shared<Buffer>(ptr, this->r.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::Number>("aliveTime")) {
	this->r.set_alivetime(int32_t(o.get<jsonxx::Number>("aliveTime")));
}

if(o.has<jsonxx::Number>("nowTime")) {
	this->r.set_nowtime(int32_t(o.get<jsonxx::Number>("nowTime")));
}

if(o.has<jsonxx::Number>("startTime")) {
	this->r.set_starttime(int32_t(o.get<jsonxx::Number>("startTime")));
}

if(o.has<jsonxx::Number>("id")) {
	this->r.set_id(int32_t(o.get<jsonxx::Number>("id")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"aliveTime\":"<< this->r.alivetime() << ",";
ss << "\"nowTime\":"<< this->r.nowtime() << ",";
ss << "\"startTime\":"<< this->r.starttime() << ",";
ss << "\"id\":"<< this->r.id();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::RetetionAttr r;
    };
}
#endif //DANMU_CORE_RETETION_ATTR_H