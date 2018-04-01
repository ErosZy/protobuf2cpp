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

#ifndef DANMU_CORE_BANNER_NOTIFY_H
#define DANMU_CORE_BANNER_NOTIFY_H

#include "protobuf.h"
#include "user.h"
#include "user.h"
#include "user.h"
#include "map_entry.h"
#include "anchor_live_info.h"

namespace protocol {
    class BannerNotify : public Protocol {
    public:
        BannerNotify() : b(linkerProtocol::BannerNotify()) {};
        explicit BannerNotify(const linkerProtocol::BannerNotify &us) : b(us) {};
        const linkerProtocol::BannerNotify &get_banner_notify() const { return this->b; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->b.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->b.ByteSize()];
            this->b.SerializeToArray(ptr, this->b.ByteSize());
            return std::make_shared<Buffer>(ptr, this->b.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::Number>("owid")) {
	this->b.set_owid(int32_t(o.get<jsonxx::Number>("owid")));
}

if (o.has<jsonxx::Object>("user")) {
	jsonxx::Object info = o.get<jsonxx::Object>("user");
	User u;
	u.from_json(info);

	auto _u = new linkerProtocol::User();
	uint8_t buf[_u.get_user().ByteSize()];
	_u.get_user().SerializeToArray(buf, n.get_user().ByteSize());
	_u->ParseFromArray(buf, _u.get_user().ByteSize());
	this->b.set_allocated_user(_u);
}

if (o.has<jsonxx::Object>("anchor")) {
	jsonxx::Object info = o.get<jsonxx::Object>("anchor");
	User u;
	u.from_json(info);

	auto _u = new linkerProtocol::User();
	uint8_t buf[_u.get_user().ByteSize()];
	_u.get_user().SerializeToArray(buf, n.get_user().ByteSize());
	_u->ParseFromArray(buf, _u.get_user().ByteSize());
	this->b.set_allocated_anchor(_u);
}

if(o.has<jsonxx::Number>("templateId")) {
	this->b.set_templateid(int32_t(o.get<jsonxx::Number>("templateId")));
}

if(o.has<jsonxx::Number>("gid")) {
	this->b.set_gid(int32_t(o.get<jsonxx::Number>("gid")));
}

if(o.has<jsonxx::Number>("attrId")) {
	this->b.set_attrid(int32_t(o.get<jsonxx::Number>("attrId")));
}

if(o.has<jsonxx::Number>("giftCount")) {
	this->b.set_giftcount(int32_t(o.get<jsonxx::Number>("giftCount")));
}

if(o.has<jsonxx::String>("txt")) {
	this->b.set_txt((o.get<jsonxx::String>("txt")));
}

if (o.has<jsonxx::Object>("officialRoom")) {
	jsonxx::Object info = o.get<jsonxx::Object>("officialRoom");
	User u;
	u.from_json(info);

	auto _u = new linkerProtocol::User();
	uint8_t buf[_u.get_user().ByteSize()];
	_u.get_user().SerializeToArray(buf, n.get_user().ByteSize());
	_u->ParseFromArray(buf, _u.get_user().ByteSize());
	this->b.set_allocated_officialroom(_u);
}

if(o.has<jsonxx::Number>("landscape")) {
	this->b.set_landscape(int32_t(o.get<jsonxx::Number>("landscape")));
}

if(o.has<jsonxx::Number>("luckyMulti")) {
	this->b.set_luckymulti(int32_t(o.get<jsonxx::Number>("luckyMulti")));
}

if (o.has<jsonxx::Array>("params")) {
	auto ms = o.get<jsonxx::Array>("params");
	for (size_t i = 0; i < ms.size(); i++) {
		auto j = ms.get<jsonxx::Object>(i);
		MapEntry k;
		k.from_json(j);
		uint8_t buf[k.get_map_entry().ByteSize()];
		k.get_map_entry().SerializeToArray(buf, k.get_map_entry().ByteSize());

		auto m = this->b.add_params();
		m->ParseFromArray(buf, k.get_map_entry().ByteSize());
	}
}

if (o.has<jsonxx::Object>("liveInfo")) {
	jsonxx::Object info = o.get<jsonxx::Object>("liveInfo");
	Anchor_live_info a;
	a.from_json(info);

	auto _a = new linkerProtocol::AnchorLiveInfo();
	uint8_t buf[_a.get_anchor_live_info().ByteSize()];
	_a.get_anchor_live_info().SerializeToArray(buf, n.get_anchor_live_info().ByteSize());
	_a->ParseFromArray(buf, _a.get_anchor_live_info().ByteSize());
	this->b.set_allocated_liveinfo(_a);
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"owid\":"<< this->b.owid() << ",";
User u(this->b.user());
ss << ""user":" << u.to_jsonstr() << ",";
User u(this->b.anchor());
ss << ""anchor":" << u.to_jsonstr() << ",";
ss << "\"templateId\":"<< this->b.templateid() << ",";
ss << "\"gid\":"<< this->b.gid() << ",";
ss << "\"attrId\":"<< this->b.attrid() << ",";
ss << "\"giftCount\":"<< this->b.giftcount() << ",";
ss << "\"txt\":"<< "\"" << this->b.txt() << "\"" << ",";
User u(this->b.officialroom());
ss << ""officialRoom":" << u.to_jsonstr() << ",";
ss << "\"landscape\":"<< this->b.landscape() << ",";
ss << "\"luckyMulti\":"<< this->b.luckymulti() << ",";
std::stringstream params_stream;
params_stream << "[";
for (int32_t i = 0; i < this->b.params_size(); i++) {
	params_stream << MapEntry(this->b.params(i)).to_jsonstr();
	if (i != this->b.params_size() - 1) {
		params_stream << ",";
	}
}
params_stream << "]"; << ",";
Anchor_live_info a(this->b.liveinfo());
ss << ""liveInfo":" << a.to_jsonstr();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::BannerNotify b;
    };
}
#endif //DANMU_CORE_BANNER_NOTIFY_H