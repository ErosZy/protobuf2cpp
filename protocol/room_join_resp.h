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

#ifndef DANMU_CORE_ROOM_JOIN_RESP_H
#define DANMU_CORE_ROOM_JOIN_RESP_H

#include "protobuf.h"
#include "room_attr.h"
#include "live_data.h"

namespace protocol {
    class RoomJoinResp : public Protocol {
    public:
        RoomJoinResp() : r(linkerProtocol::RoomJoinResp()) {};
        explicit RoomJoinResp(const linkerProtocol::RoomJoinResp &us) : r(us) {};
        const linkerProtocol::RoomJoinResp &get_room_join_resp() const { return this->r; }
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

if(o.has<jsonxx::Number>("code")) {
	this->r.set_code(int32_t(o.get<jsonxx::Number>("code")));
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

if (o.has<jsonxx::Object>("liveData")) {
	jsonxx::Object info = o.get<jsonxx::Object>("liveData");
	Live_data l;
	l.from_json(info);

	auto _l = new linkerProtocol::LiveData();
	uint8_t buf[_l.get_live_data().ByteSize()];
	_l.get_live_data().SerializeToArray(buf, n.get_live_data().ByteSize());
	_l->ParseFromArray(buf, _l.get_live_data().ByteSize());
	this->r.set_allocated_livedata(_l);
}

if (o.has<jsonxx::Array>("optionalTextColors")) {
	jsonxx::Array arr = o.get<jsonxx::Array>("optionalTextColors");
	for (size_t i = 0; i < arr.size(); i++) {
		this->r.add_optionaltextcolors(int32_t(arr.get<jsonxx::Number>(i)));
	}
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"owid\":"<< this->r.owid() << ",";
ss << "\"code\":"<< this->r.code() << ",";
Room_attr r(this->r.roomattr());
ss << ""roomAttr":" << r.to_jsonstr() << ",";
Live_data l(this->r.livedata());
ss << ""liveData":" << l.to_jsonstr() << ",";
ss << "\"optionalTextColors\":[";
for (int32_t i = 0; i < this->r.optionaltextcolors_size(); i++) {
	ss << this->r.optionaltextcolors(i);
	if (i != this->r.optionaltextcolors_size() - 1) {
		ss << ",";
	}
}
ss << "]"
;
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::RoomJoinResp r;
    };
}
#endif //DANMU_CORE_ROOM_JOIN_RESP_H