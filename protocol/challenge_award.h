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

#ifndef DANMU_CORE_CHALLENGE_AWARD_H
#define DANMU_CORE_CHALLENGE_AWARD_H

#include "protobuf.h"
#include "room_attr.h"
#include "user.h"

namespace protocol {
    class ChallengeAward : public Protocol {
    public:
        ChallengeAward() : c(linkerProtocol::ChallengeAward()) {};
        explicit ChallengeAward(const linkerProtocol::ChallengeAward &us) : c(us) {};
        const linkerProtocol::ChallengeAward &get_challenge_award() const { return this->c; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->c.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->c.ByteSize()];
            this->c.SerializeToArray(ptr, this->c.ByteSize());
            return std::make_shared<Buffer>(ptr, this->c.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::Number>("owid")) {
	this->c.set_owid(int32_t(o.get<jsonxx::Number>("owid")));
}

if(o.has<jsonxx::Number>("replayId")) {
	this->c.set_replayid(int32_t(o.get<jsonxx::Number>("replayId")));
}

if (o.has<jsonxx::Object>("roomAttr")) {
	jsonxx::Object info = o.get<jsonxx::Object>("roomAttr");
	Room_attr r;
	r.from_json(info);

	auto _r = new linkerProtocol::RoomAttr();
	uint8_t buf[_r.get_room_attr().ByteSize()];
	_r.get_room_attr().SerializeToArray(buf, n.get_room_attr().ByteSize());
	_r->ParseFromArray(buf, _r.get_room_attr().ByteSize());
	this->c.set_allocated_roomattr(_r);
}

if (o.has<jsonxx::Object>("user")) {
	jsonxx::Object info = o.get<jsonxx::Object>("user");
	User u;
	u.from_json(info);

	auto _u = new linkerProtocol::User();
	uint8_t buf[_u.get_user().ByteSize()];
	_u.get_user().SerializeToArray(buf, n.get_user().ByteSize());
	_u->ParseFromArray(buf, _u.get_user().ByteSize());
	this->c.set_allocated_user(_u);
}

if(o.has<jsonxx::String>("source")) {
	this->c.set_source((o.get<jsonxx::String>("source")));
}

if(o.has<jsonxx::String>("tips")) {
	this->c.set_tips((o.get<jsonxx::String>("tips")));
}

if(o.has<jsonxx::Number>("diamond")) {
	this->c.set_diamond(int32_t(o.get<jsonxx::Number>("diamond")));
}

if(o.has<jsonxx::Number>("seed")) {
	this->c.set_seed(int32_t(o.get<jsonxx::Number>("seed")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"owid\":"<< this->c.owid() << ",";
ss << "\"replayId\":"<< this->c.replayid() << ",";
Room_attr r(this->c.roomattr());
ss << ""roomAttr":" << r.to_jsonstr() << ",";
User u(this->c.user());
ss << ""user":" << u.to_jsonstr() << ",";
ss << "\"source\":"<< "\"" << this->c.source() << "\"" << ",";
ss << "\"tips\":"<< "\"" << this->c.tips() << "\"" << ",";
ss << "\"diamond\":"<< this->c.diamond() << ",";
ss << "\"seed\":"<< this->c.seed();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::ChallengeAward c;
    };
}
#endif //DANMU_CORE_CHALLENGE_AWARD_H