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

#ifndef DANMU_CORE_BLESSINGBAG_EXT_H
#define DANMU_CORE_BLESSINGBAG_EXT_H

#include "protobuf.h"
#include "user.h"

namespace protocol {
    class Blessingbag_ext : public Protocol {
    public:
        Blessingbag_ext() : b(linkerProtocol::BlessingbagExt()) {};
        explicit Blessingbag_ext(const linkerProtocol::BlessingbagExt &us) : b(us) {};
        const linkerProtocol::BlessingbagExt &get_blessingbag_ext() const { return this->b; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->b.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->b.ByteSize()];
            this->b.SerializeToArray(ptr, this->b.ByteSize());
            return std::make_shared<Buffer>(ptr, this->b.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if (o.has<jsonxx::Object>("user")) {
	jsonxx::Object info = o.get<jsonxx::Object>("user");
	User u;
	u.from_json(info);

	auto _u = new linkerProtocol::User();
	uint8_t buf[u.get_user().ByteSize()];
	u.get_user().SerializeToArray(buf, u.get_user().ByteSize());
	_u->ParseFromArray(buf, u.get_user().ByteSize());
	this->b.set_allocated_user(_u);
}

if(o.has<jsonxx::String>("txt")) {
	this->b.set_txt((o.get<jsonxx::String>("txt")));
}

if(o.has<jsonxx::Number>("color")) {
	this->b.set_color(int32_t(o.get<jsonxx::Number>("color")));
}

if(o.has<jsonxx::Number>("attrId")) {
	this->b.set_attrid(int32_t(o.get<jsonxx::Number>("attrId")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";

User u_0(this->b.user());
ss << "\"user\":" << u_0.to_jsonstr() << ",";
ss << "\"txt\":"<< "\"" << this->b.txt() << "\"" << ",";
ss << "\"color\":"<< this->b.color() << ",";
ss << "\"attrId\":"<< this->b.attrid();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::BlessingbagExt b;
    };
}
#endif //DANMU_CORE_BLESSINGBAG_EXT_H