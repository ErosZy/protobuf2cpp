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

#ifndef DANMU_CORE_LINK_GIFT_PK_END_H
#define DANMU_CORE_LINK_GIFT_PK_END_H

#include "protobuf.h"
#include "gift_pk_user_info.h"
#include "gift_pk_user_info.h"

namespace protocol {
    class Link_gift_pk_end : public Protocol {
    public:
        Link_gift_pk_end() : l(linkerProtocol::LinkGiftPkEnd()) {};
        explicit Link_gift_pk_end(const linkerProtocol::LinkGiftPkEnd &us) : l(us) {};
        const linkerProtocol::LinkGiftPkEnd &get_link_gift_pk_end() const { return this->l; }
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

if (o.has<jsonxx::Object>("winner")) {
	jsonxx::Object info = o.get<jsonxx::Object>("winner");
	Gift_pk_user_info g;
	g.from_json(info);

	auto _g = new linkerProtocol::GiftPkUserInfo();
	uint8_t buf[g.get_gift_pk_user_info().ByteSize()];
	g.get_gift_pk_user_info().SerializeToArray(buf, g.get_gift_pk_user_info().ByteSize());
	_g->ParseFromArray(buf, g.get_gift_pk_user_info().ByteSize());
	this->l.set_allocated_winner(_g);
}

if (o.has<jsonxx::Object>("loser")) {
	jsonxx::Object info = o.get<jsonxx::Object>("loser");
	Gift_pk_user_info g;
	g.from_json(info);

	auto _g = new linkerProtocol::GiftPkUserInfo();
	uint8_t buf[g.get_gift_pk_user_info().ByteSize()];
	g.get_gift_pk_user_info().SerializeToArray(buf, g.get_gift_pk_user_info().ByteSize());
	_g->ParseFromArray(buf, g.get_gift_pk_user_info().ByteSize());
	this->l.set_allocated_loser(_g);
}

if(o.has<jsonxx::Number>("type")) {
	this->l.set_type(int32_t(o.get<jsonxx::Number>("type")));
}

if(o.has<jsonxx::String>("punishment")) {
	this->l.set_punishment((o.get<jsonxx::String>("punishment")));
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

Gift_pk_user_info g_1(this->l.winner());
ss << "\"winner\":" << g_1.to_jsonstr() << ",";

Gift_pk_user_info g_2(this->l.loser());
ss << "\"loser\":" << g_2.to_jsonstr() << ",";
ss << "\"type\":"<< this->l.type() << ",";
ss << "\"punishment\":"<< "\"" << this->l.punishment() << "\"" << ",";
ss << "\"startTime\":"<< this->l.starttime() << ",";
ss << "\"endTime\":"<< this->l.endtime();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::LinkGiftPkEnd l;
    };
}
#endif //DANMU_CORE_LINK_GIFT_PK_END_H