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

#ifndef DANMU_CORE_RED_ENVELOPE_NOTIFY_H
#define DANMU_CORE_RED_ENVELOPE_NOTIFY_H

#include "protobuf.h"
#include "room_attr.h"
#include "user.h"
#include "retetion_attr.h"

namespace protocol {
    class RedEnvelopeNotify : public Protocol {
    public:
        RedEnvelopeNotify() : r(linkerProtocol::RedEnvelopeNotify()) {};
        explicit RedEnvelopeNotify(const linkerProtocol::RedEnvelopeNotify &us) : r(us) {};
        const linkerProtocol::RedEnvelopeNotify &get_red_envelope_notify() const { return this->r; }
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

if (o.has<jsonxx::Object>("user")) {
	jsonxx::Object info = o.get<jsonxx::Object>("user");
	User u;
	u.from_json(info);

	auto _u = new linkerProtocol::User();
	uint8_t buf[_u.get_user().ByteSize()];
	_u.get_user().SerializeToArray(buf, n.get_user().ByteSize());
	_u->ParseFromArray(buf, _u.get_user().ByteSize());
	this->r.set_allocated_user(_u);
}

if(o.has<jsonxx::Number>("rid")) {
	this->r.set_rid(int32_t(o.get<jsonxx::Number>("rid")));
}

if(o.has<jsonxx::Number>("type")) {
	this->r.set_type(int32_t(o.get<jsonxx::Number>("type")));
}

if(o.has<jsonxx::Number>("amount")) {
	this->r.set_amount(int32_t(o.get<jsonxx::Number>("amount")));
}

if(o.has<jsonxx::String>("txt")) {
	this->r.set_txt((o.get<jsonxx::String>("txt")));
}

if (o.has<jsonxx::Object>("retetionAttr")) {
	jsonxx::Object info = o.get<jsonxx::Object>("retetionAttr");
	Retetion_attr r;
	r.from_json(info);

	auto _r = new linkerProtocol::RetetionAttr();
	uint8_t buf[_r.get_retetion_attr().ByteSize()];
	_r.get_retetion_attr().SerializeToArray(buf, n.get_retetion_attr().ByteSize());
	_r->ParseFromArray(buf, _r.get_retetion_attr().ByteSize());
	this->r.set_allocated_retetionattr(_r);
}

if(o.has<jsonxx::Number>("key")) {
	this->r.set_key(uint32_t(o.get<jsonxx::Number>("key")));
}

if(o.has<jsonxx::Number>("boxType")) {
	this->r.set_boxtype(int32_t(o.get<jsonxx::Number>("boxType")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"owid\":"<< this->r.owid() << ",";
Room_attr r(this->r.roomattr());
ss << ""roomAttr":" << r.to_jsonstr() << ",";
User u(this->r.user());
ss << ""user":" << u.to_jsonstr() << ",";
ss << "\"rid\":"<< this->r.rid() << ",";
ss << "\"type\":"<< this->r.type() << ",";
ss << "\"amount\":"<< this->r.amount() << ",";
ss << "\"txt\":"<< "\"" << this->r.txt() << "\"" << ",";
Retetion_attr r(this->r.retetionattr());
ss << ""retetionAttr":" << r.to_jsonstr() << ",";
ss << "\"key\":"<< this->r.key() << ",";
ss << "\"boxType\":"<< this->r.boxtype();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::RedEnvelopeNotify r;
    };
}
#endif //DANMU_CORE_RED_ENVELOPE_NOTIFY_H