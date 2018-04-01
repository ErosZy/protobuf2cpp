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

#ifndef DANMU_CORE_BAG_NOTIFY_H
#define DANMU_CORE_BAG_NOTIFY_H

#include "protobuf.h"

namespace protocol {
    class Bag_notify : public Protocol {
    public:
        Bag_notify() : b(linkerProtocol::BagNotify()) {};
        explicit Bag_notify(const linkerProtocol::BagNotify &us) : b(us) {};
        const linkerProtocol::BagNotify &get_bag_notify() const { return this->b; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->b.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->b.ByteSize()];
            this->b.SerializeToArray(ptr, this->b.ByteSize());
            return std::make_shared<Buffer>(ptr, this->b.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::Number>("uid")) {
	this->b.set_uid(int32_t(o.get<jsonxx::Number>("uid")));
}

if(o.has<jsonxx::Number>("action")) {
	this->b.set_action(int32_t(o.get<jsonxx::Number>("action")));
}

if(o.has<jsonxx::Number>("pid")) {
	this->b.set_pid(int32_t(o.get<jsonxx::Number>("pid")));
}

if(o.has<jsonxx::Number>("num")) {
	this->b.set_num(int32_t(o.get<jsonxx::Number>("num")));
}

if(o.has<jsonxx::Number>("expire")) {
	this->b.set_expire(int32_t(o.get<jsonxx::Number>("expire")));
}

if(o.has<jsonxx::Number>("expireNum")) {
	this->b.set_expirenum(int32_t(o.get<jsonxx::Number>("expireNum")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"uid\":"<< this->b.uid() << ",";
ss << "\"action\":"<< this->b.action() << ",";
ss << "\"pid\":"<< this->b.pid() << ",";
ss << "\"num\":"<< this->b.num() << ",";
ss << "\"expire\":"<< this->b.expire() << ",";
ss << "\"expireNum\":"<< this->b.expirenum();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::BagNotify b;
    };
}
#endif //DANMU_CORE_BAG_NOTIFY_H