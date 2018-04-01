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

#ifndef DANMU_CORE_GIFT_PK_USER_INFO_H
#define DANMU_CORE_GIFT_PK_USER_INFO_H

#include "protobuf.h"
#include "user.h"

namespace protocol {
    class Gift_pk_user_info : public Protocol {
    public:
        Gift_pk_user_info() : g(linkerProtocol::GiftPkUserInfo()) {};
        explicit Gift_pk_user_info(const linkerProtocol::GiftPkUserInfo &us) : g(us) {};
        const linkerProtocol::GiftPkUserInfo &get_gift_pk_user_info() const { return this->g; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->g.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->g.ByteSize()];
            this->g.SerializeToArray(ptr, this->g.ByteSize());
            return std::make_shared<Buffer>(ptr, this->g.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if (o.has<jsonxx::Object>("user")) {
	jsonxx::Object info = o.get<jsonxx::Object>("user");
	User u;
	u.from_json(info);

	auto _u = new linkerProtocol::User();
	uint8_t buf[u.get_user().ByteSize()];
	u.get_user().SerializeToArray(buf, u.get_user().ByteSize());
	_u->ParseFromArray(buf, u.get_user().ByteSize());
	this->g.set_allocated_user(_u);
}

if(o.has<jsonxx::Number>("score")) {
	this->g.set_score(int32_t(o.get<jsonxx::Number>("score")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";

User u_0(this->g.user());
ss << "\"user\":" << u_0.to_jsonstr() << ",";
ss << "\"score\":"<< this->g.score();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::GiftPkUserInfo g;
    };
}
#endif //DANMU_CORE_GIFT_PK_USER_INFO_H