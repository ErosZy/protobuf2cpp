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

#ifndef DANMU_CORE_ZAN_NOTIFY_H
#define DANMU_CORE_ZAN_NOTIFY_H

#include "protobuf.h"
#include "room_attr.h"
#include "user.h"

namespace protocol {
    class ZanNotify : public Protocol {
    public:
        ZanNotify() : z(linkerProtocol::ZanNotify()) {};
        explicit ZanNotify(const linkerProtocol::ZanNotify &us) : z(us) {};
        const linkerProtocol::ZanNotify &get_zan_notify() const { return this->z; }
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

if (o.has<jsonxx::Object>("roomAttr")) {
	jsonxx::Object info = o.get<jsonxx::Object>("roomAttr");
	Room_attr r;
	r.from_json(info);

	auto _r = new linkerProtocol::RoomAttr();
	uint8_t buf[_r.get_room_attr().ByteSize()];
	_r.get_room_attr().SerializeToArray(buf, n.get_room_attr().ByteSize());
	_r->ParseFromArray(buf, _r.get_room_attr().ByteSize());
	this->z.set_allocated_roomattr(_r);
}

if (o.has<jsonxx::Object>("user")) {
	jsonxx::Object info = o.get<jsonxx::Object>("user");
	User u;
	u.from_json(info);

	auto _u = new linkerProtocol::User();
	uint8_t buf[_u.get_user().ByteSize()];
	_u.get_user().SerializeToArray(buf, n.get_user().ByteSize());
	_u->ParseFromArray(buf, _u.get_user().ByteSize());
	this->z.set_allocated_user(_u);
}

if(o.has<jsonxx::Number>("color")) {
	this->z.set_color(int32_t(o.get<jsonxx::Number>("color")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"owid\":"<< this->z.owid() << ",";

Room_attr r(this->z.roomattr());
ss << "\"roomAttr\":" << r.to_jsonstr() << ",";

User u(this->z.user());
ss << "\"user\":" << u.to_jsonstr() << ",";
ss << "\"color\":"<< this->z.color();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::ZanNotify z;
    };
}
#endif //DANMU_CORE_ZAN_NOTIFY_H