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

#ifndef DANMU_CORE_BAG_UP_H
#define DANMU_CORE_BAG_UP_H

#include "protobuf.h"

namespace protocol {
    class Bag_up : public Protocol {
    public:
        Bag_up() : b(linkerProtocol::BagUp()) {};
        explicit Bag_up(const linkerProtocol::BagUp &us) : b(us) {};
        const linkerProtocol::BagUp &get_bag_up() const { return this->b; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->b.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->b.ByteSize()];
            this->b.SerializeToArray(ptr, this->b.ByteSize());
            return std::make_shared<Buffer>(ptr, this->b.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::Number>("owid")) {
	this->b.set_owid(int32_t(o.get<jsonxx::Number>("owid")));
}

if(o.has<jsonxx::Number>("pid")) {
	this->b.set_pid(int32_t(o.get<jsonxx::Number>("pid")));
}

if(o.has<jsonxx::Number>("count")) {
	this->b.set_count(int32_t(o.get<jsonxx::Number>("count")));
}

if(o.has<jsonxx::String>("ext")) {
	this->b.set_ext((o.get<jsonxx::String>("ext")));
}

if(o.has<jsonxx::Number>("platform")) {
	this->b.set_platform(int32_t(o.get<jsonxx::Number>("platform")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"owid\":"<< this->b.owid() << ",";
ss << "\"pid\":"<< this->b.pid() << ",";
ss << "\"count\":"<< this->b.count() << ",";
ss << "\"ext\":"<< "\"" << this->b.ext() << "\"" << ",";
ss << "\"platform\":"<< this->b.platform();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::BagUp b;
    };
}
#endif //DANMU_CORE_BAG_UP_H