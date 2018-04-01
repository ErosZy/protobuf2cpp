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

#ifndef DANMU_CORE_ROOM_GUARD_NOTIFY_H
#define DANMU_CORE_ROOM_GUARD_NOTIFY_H

#include "protobuf.h"
#include "room_attr.h"

namespace protocol {
    class RoomGuardNotify : public Protocol {
    public:
        RoomGuardNotify() : r(linkerProtocol::RoomGuardNotify()) {};
        explicit RoomGuardNotify(const linkerProtocol::RoomGuardNotify &us) : r(us) {};
        const linkerProtocol::RoomGuardNotify &get_room_guard_notify() const { return this->r; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->r.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->r.ByteSize()];
            this->r.SerializeToArray(ptr, this->r.ByteSize());
            return std::make_shared<Buffer>(ptr, this->r.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::Number>("owid")) {
	this->r.set_owid(int32_t(o.get<jsonxx::Number>("owid")));
}

if (o.has<jsonxx::Object>("roomAttr")) {
	jsonxx::Object info = o.get<jsonxx::Object>("roomAttr");
	Room_attr r;
	r.from_json(info);

	auto _r = new linkerProtocol::RoomAttr();
	uint8_t buf[_r.get_room_attr().ByteSize()];
	_r.get_room_attr().SerializeToArray(buf, n.get_room_attr().ByteSize());
	_r->ParseFromArray(buf, _r.get_room_attr().ByteSize());
	this->r.set_allocated_roomattr(_r);
}

if(o.has<jsonxx::Number>("uid")) {
	this->r.set_uid(int32_t(o.get<jsonxx::Number>("uid")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"owid\":"<< this->r.owid() << ",";

Room_attr r(this->r.roomattr());
ss << "\"roomAttr\":" << r.to_jsonstr() << ",";
ss << "\"uid\":"<< this->r.uid();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::RoomGuardNotify r;
    };
}
#endif //DANMU_CORE_ROOM_GUARD_NOTIFY_H