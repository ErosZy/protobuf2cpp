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

#ifndef DANMU_CORE_GIFTBOX_DONE_H
#define DANMU_CORE_GIFTBOX_DONE_H

#include "protobuf.h"

namespace protocol {
    class Giftbox_done : public Protocol {
    public:
        Giftbox_done() : g(linkerProtocol::GiftboxDone()) {};
        explicit Giftbox_done(const linkerProtocol::GiftboxDone &us) : g(us) {};
        const linkerProtocol::GiftboxDone &get_giftbox_done() const { return this->g; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->g.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->g.ByteSize()];
            this->g.SerializeToArray(ptr, this->g.ByteSize());
            return std::make_shared<Buffer>(ptr, this->g.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::Number>("owid")) {
	this->g.set_owid(int32_t(o.get<jsonxx::Number>("owid")));
}

if(o.has<jsonxx::Number>("type")) {
	this->g.set_type(int32_t(o.get<jsonxx::Number>("type")));
}

if(o.has<jsonxx::Number>("boxid")) {
	this->g.set_boxid(int32_t(o.get<jsonxx::Number>("boxid")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"owid\":"<< this->g.owid() << ",";
ss << "\"type\":"<< this->g.type() << ",";
ss << "\"boxid\":"<< this->g.boxid();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::GiftboxDone g;
    };
}
#endif //DANMU_CORE_GIFTBOX_DONE_H