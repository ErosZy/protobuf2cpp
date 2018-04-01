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

#ifndef DANMU_CORE_KICKOUT_NOTIFY_H
#define DANMU_CORE_KICKOUT_NOTIFY_H

#include "protobuf.h"

namespace protocol {
    class Kickout_notify : public Protocol {
    public:
        Kickout_notify() : k(linkerProtocol::KickoutNotify()) {};
        explicit Kickout_notify(const linkerProtocol::KickoutNotify &us) : k(us) {};
        const linkerProtocol::KickoutNotify &get_kickout_notify() const { return this->k; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->k.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->k.ByteSize()];
            this->k.SerializeToArray(ptr, this->k.ByteSize());
            return std::make_shared<Buffer>(ptr, this->k.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::Number>("owid")) {
	this->k.set_owid(int32_t(o.get<jsonxx::Number>("owid")));
}

if(o.has<jsonxx::String>("msg")) {
	this->k.set_msg((o.get<jsonxx::String>("msg")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"owid\":"<< this->k.owid() << ",";
ss << "\"msg\":"<< "\"" << this->k.msg() << "\"";
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::KickoutNotify k;
    };
}
#endif //DANMU_CORE_KICKOUT_NOTIFY_H