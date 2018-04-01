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

#ifndef DANMU_CORE_LINK_GIFT_PK_NOTIFY_H
#define DANMU_CORE_LINK_GIFT_PK_NOTIFY_H

#include "protobuf.h"
#include "gift_pk_user_info.h"
#include "gift_pk_user_info.h"

namespace protocol {
    class LinkGiftPkNotify : public Protocol {
    public:
        LinkGiftPkNotify() : l(linkerProtocol::LinkGiftPkNotify()) {};
        explicit LinkGiftPkNotify(const linkerProtocol::LinkGiftPkNotify &us) : l(us) {};
        const linkerProtocol::LinkGiftPkNotify &get_link_gift_pk_notify() const { return this->l; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->l.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->l.ByteSize()];
            this->l.SerializeToArray(ptr, this->l.ByteSize());
            return std::make_shared<Buffer>(ptr, this->l.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::Number>("owid")) {
	this->l.set_owid(int32_t(o.get<jsonxx::Number>("owid")));
}

if (o.has<jsonxx::Object>("applyUserInfo")) {
	jsonxx::Object info = o.get<jsonxx::Object>("applyUserInfo");
	Gift_pk_user_info g;
	g.from_json(info);

	auto _g = new linkerProtocol::GiftPkUserInfo();
	uint8_t buf[_g.get_gift_pk_user_info().ByteSize()];
	_g.get_gift_pk_user_info().SerializeToArray(buf, n.get_gift_pk_user_info().ByteSize());
	_g->ParseFromArray(buf, _g.get_gift_pk_user_info().ByteSize());
	this->l.set_allocated_applyuserinfo(_g);
}

if (o.has<jsonxx::Object>("acceptUserInfo")) {
	jsonxx::Object info = o.get<jsonxx::Object>("acceptUserInfo");
	Gift_pk_user_info g;
	g.from_json(info);

	auto _g = new linkerProtocol::GiftPkUserInfo();
	uint8_t buf[_g.get_gift_pk_user_info().ByteSize()];
	_g.get_gift_pk_user_info().SerializeToArray(buf, n.get_gift_pk_user_info().ByteSize());
	_g->ParseFromArray(buf, _g.get_gift_pk_user_info().ByteSize());
	this->l.set_allocated_acceptuserinfo(_g);
}

if(o.has<jsonxx::String>("title")) {
	this->l.set_title((o.get<jsonxx::String>("title")));
}

if(o.has<jsonxx::Number>("startTime")) {
	this->l.set_starttime(int32_t(o.get<jsonxx::Number>("startTime")));
}

if(o.has<jsonxx::Number>("endTime")) {
	this->l.set_endtime(int32_t(o.get<jsonxx::Number>("endTime")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"owid\":"<< this->l.owid() << ",";
Gift_pk_user_info g(this->l.applyuserinfo());
ss << ""applyUserInfo":" << g.to_jsonstr() << ",";
Gift_pk_user_info g(this->l.acceptuserinfo());
ss << ""acceptUserInfo":" << g.to_jsonstr() << ",";
ss << "\"title\":"<< "\"" << this->l.title() << "\"" << ",";
ss << "\"startTime\":"<< this->l.starttime() << ",";
ss << "\"endTime\":"<< this->l.endtime();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::LinkGiftPkNotify l;
    };
}
#endif //DANMU_CORE_LINK_GIFT_PK_NOTIFY_H