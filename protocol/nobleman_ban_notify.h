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

#ifndef DANMU_CORE_NOBLEMAN_BAN_NOTIFY_H
#define DANMU_CORE_NOBLEMAN_BAN_NOTIFY_H

#include "protobuf.h"
#include "user.h"

namespace protocol {
    class Nobleman_ban_notify : public Protocol {
    public:
        Nobleman_ban_notify() : n(linkerProtocol::NoblemanBanNotify()) {};
        explicit Nobleman_ban_notify(const linkerProtocol::NoblemanBanNotify &us) : n(us) {};
        const linkerProtocol::NoblemanBanNotify &get_nobleman_ban_notify() const { return this->n; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->n.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->n.ByteSize()];
            this->n.SerializeToArray(ptr, this->n.ByteSize());
            return std::make_shared<Buffer>(ptr, this->n.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::Number>("owid")) {
	this->n.set_owid(int32_t(o.get<jsonxx::Number>("owid")));
}

if(o.has<jsonxx::Number>("uid")) {
	this->n.set_uid(int32_t(o.get<jsonxx::Number>("uid")));
}

if (o.has<jsonxx::Object>("oper")) {
	jsonxx::Object info = o.get<jsonxx::Object>("oper");
	User u;
	u.from_json(info);

	auto _u = new linkerProtocol::User();
	uint8_t buf[u.get_user().ByteSize()];
	u.get_user().SerializeToArray(buf, u.get_user().ByteSize());
	_u->ParseFromArray(buf, u.get_user().ByteSize());
	this->n.set_allocated_oper(_u);
}

if(o.has<jsonxx::Number>("deadtime")) {
	this->n.set_deadtime(int32_t(o.get<jsonxx::Number>("deadtime")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"owid\":"<< this->n.owid() << ",";
ss << "\"uid\":"<< this->n.uid() << ",";

User u_2(this->n.oper());
ss << "\"oper\":" << u_2.to_jsonstr() << ",";
ss << "\"deadtime\":"<< this->n.deadtime();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::NoblemanBanNotify n;
    };
}
#endif //DANMU_CORE_NOBLEMAN_BAN_NOTIFY_H