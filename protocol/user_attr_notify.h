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

#ifndef DANMU_CORE_USER_ATTR_NOTIFY_H
#define DANMU_CORE_USER_ATTR_NOTIFY_H

#include "protobuf.h"
#include "user.h"

namespace protocol {
    class UserAttrNotify : public Protocol {
    public:
        UserAttrNotify() : u(linkerProtocol::UserAttrNotify()) {};
        explicit UserAttrNotify(const linkerProtocol::UserAttrNotify &us) : u(us) {};
        const linkerProtocol::UserAttrNotify &get_user_attr_notify() const { return this->u; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->u.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->u.ByteSize()];
            this->u.SerializeToArray(ptr, this->u.ByteSize());
            return std::make_shared<Buffer>(ptr, this->u.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if (o.has<jsonxx::Object>("user")) {
	jsonxx::Object info = o.get<jsonxx::Object>("user");
	User u;
	u.from_json(info);

	auto _u = new linkerProtocol::User();
	uint8_t buf[_u.get_user().ByteSize()];
	_u.get_user().SerializeToArray(buf, n.get_user().ByteSize());
	_u->ParseFromArray(buf, _u.get_user().ByteSize());
	this->u.set_allocated_user(_u);
}

if(o.has<jsonxx::Number>("diamond")) {
	this->u.set_diamond(int32_t(o.get<jsonxx::Number>("diamond")));
}

if(o.has<jsonxx::Number>("starlight")) {
	this->u.set_starlight(int32_t(o.get<jsonxx::Number>("starlight")));
}

if(o.has<jsonxx::Number>("fight")) {
	this->u.set_fight(int32_t(o.get<jsonxx::Number>("fight")));
}

if(o.has<jsonxx::Number>("seed")) {
	this->u.set_seed(int32_t(o.get<jsonxx::Number>("seed")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
User u(this->u.user());
ss << ""user":" << u.to_jsonstr() << ",";
ss << "\"diamond\":"<< this->u.diamond() << ",";
ss << "\"starlight\":"<< this->u.starlight() << ",";
ss << "\"fight\":"<< this->u.fight() << ",";
ss << "\"seed\":"<< this->u.seed();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::UserAttrNotify u;
    };
}
#endif //DANMU_CORE_USER_ATTR_NOTIFY_H