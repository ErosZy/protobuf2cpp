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

#ifndef DANMU_CORE_ROOM_AD_PUSH_H
#define DANMU_CORE_ROOM_AD_PUSH_H

#include "protobuf.h"
#include "room_ad_attr.h"
#include "room_ad_excl_owid.h"
#include "room_ad_excl_cateid.h"
#include "retetion_attr.h"

namespace protocol {
    class RoomAdPush : public Protocol {
    public:
        RoomAdPush() : r(linkerProtocol::RoomAdPush()) {};
        explicit RoomAdPush(const linkerProtocol::RoomAdPush &us) : r(us) {};
        const linkerProtocol::RoomAdPush &get_room_ad_push() const { return this->r; }
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

if(o.has<jsonxx::Number>("dateline")) {
	this->r.set_dateline(int32_t(o.get<jsonxx::Number>("dateline")));
}

if(o.has<jsonxx::Number>("style")) {
	this->r.set_style(int32_t(o.get<jsonxx::Number>("style")));
}

if (o.has<jsonxx::Array>("adlist")) {
	auto rs = o.get<jsonxx::Array>("adlist");
	for (size_t i = 0; i < rs.size(); i++) {
		auto j = rs.get<jsonxx::Object>(i);
		RoomAdAttr k;
		k.from_json(j);
		uint8_t buf[k.get_room_ad_attr().ByteSize()];
		k.get_room_ad_attr().SerializeToArray(buf, k.get_room_ad_attr().ByteSize());

		auto m = this->r.add_adlist();
		m->ParseFromArray(buf, k.get_room_ad_attr().ByteSize());
	}
}

if (o.has<jsonxx::Array>("exclroomlist")) {
	auto rs = o.get<jsonxx::Array>("exclroomlist");
	for (size_t i = 0; i < rs.size(); i++) {
		auto j = rs.get<jsonxx::Object>(i);
		RoomAdExclOwid k;
		k.from_json(j);
		uint8_t buf[k.get_room_ad_excl_owid().ByteSize()];
		k.get_room_ad_excl_owid().SerializeToArray(buf, k.get_room_ad_excl_owid().ByteSize());

		auto m = this->r.add_exclroomlist();
		m->ParseFromArray(buf, k.get_room_ad_excl_owid().ByteSize());
	}
}

if (o.has<jsonxx::Array>("exclcatelist")) {
	auto rs = o.get<jsonxx::Array>("exclcatelist");
	for (size_t i = 0; i < rs.size(); i++) {
		auto j = rs.get<jsonxx::Object>(i);
		RoomAdExclCateid k;
		k.from_json(j);
		uint8_t buf[k.get_room_ad_excl_cateid().ByteSize()];
		k.get_room_ad_excl_cateid().SerializeToArray(buf, k.get_room_ad_excl_cateid().ByteSize());

		auto m = this->r.add_exclcatelist();
		m->ParseFromArray(buf, k.get_room_ad_excl_cateid().ByteSize());
	}
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

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"owid\":"<< this->r.owid() << ",";
ss << "\"dateline\":"<< this->r.dateline() << ",";
ss << "\"style\":"<< this->r.style() << ",";

std::stringstream adlist_stream;
adlist_stream << "[";
for (int32_t i = 0; i < this->r.adlist_size(); i++) {
	adlist_stream << RoomAdAttr(this->r.adlist(i)).to_jsonstr();
	if (i != this->r.adlist_size() - 1) {
		adlist_stream << ",";
	}
}
adlist_stream << "]";
ss << "\"adlist\":" << adlist_stream.str() << ",";

std::stringstream exclroomlist_stream;
exclroomlist_stream << "[";
for (int32_t i = 0; i < this->r.exclroomlist_size(); i++) {
	exclroomlist_stream << RoomAdExclOwid(this->r.exclroomlist(i)).to_jsonstr();
	if (i != this->r.exclroomlist_size() - 1) {
		exclroomlist_stream << ",";
	}
}
exclroomlist_stream << "]";
ss << "\"exclroomlist\":" << exclroomlist_stream.str() << ",";

std::stringstream exclcatelist_stream;
exclcatelist_stream << "[";
for (int32_t i = 0; i < this->r.exclcatelist_size(); i++) {
	exclcatelist_stream << RoomAdExclCateid(this->r.exclcatelist(i)).to_jsonstr();
	if (i != this->r.exclcatelist_size() - 1) {
		exclcatelist_stream << ",";
	}
}
exclcatelist_stream << "]";
ss << "\"exclcatelist\":" << exclcatelist_stream.str() << ",";

Retetion_attr r(this->r.retetionattr());
ss << "\"retetionAttr\":" << r.to_jsonstr();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::RoomAdPush r;
    };
}
#endif //DANMU_CORE_ROOM_AD_PUSH_H