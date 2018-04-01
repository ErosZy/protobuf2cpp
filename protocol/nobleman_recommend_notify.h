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

#ifndef DANMU_CORE_NOBLEMAN_RECOMMEND_NOTIFY_H
#define DANMU_CORE_NOBLEMAN_RECOMMEND_NOTIFY_H

#include "protobuf.h"
#include "user.h"

namespace protocol {
    class Nobleman_recommend_notify : public Protocol {
    public:
        Nobleman_recommend_notify() : n(linkerProtocol::NoblemanRecommendNotify()) {};
        explicit Nobleman_recommend_notify(const linkerProtocol::NoblemanRecommendNotify &us) : n(us) {};
        const linkerProtocol::NoblemanRecommendNotify &get_nobleman_recommend_notify() const { return this->n; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->n.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->n.ByteSize()];
            this->n.SerializeToArray(ptr, this->n.ByteSize());
            return std::make_shared<Buffer>(ptr, this->n.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::Number>("owid")) {
	this->n.set_owid(int32_t(o.get<jsonxx::Number>("owid")));
}

if (o.has<jsonxx::Object>("noble")) {
	jsonxx::Object info = o.get<jsonxx::Object>("noble");
	User u;
	u.from_json(info);

	auto _u = new linkerProtocol::User();
	uint8_t buf[u.get_user().ByteSize()];
	u.get_user().SerializeToArray(buf, u.get_user().ByteSize());
	_u->ParseFromArray(buf, u.get_user().ByteSize());
	this->n.set_allocated_noble(_u);
}

if(o.has<jsonxx::Number>("endTime")) {
	this->n.set_endtime(int32_t(o.get<jsonxx::Number>("endTime")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"owid\":"<< this->n.owid() << ",";

User u_1(this->n.noble());
ss << "\"noble\":" << u_1.to_jsonstr() << ",";
ss << "\"endTime\":"<< this->n.endtime();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::NoblemanRecommendNotify n;
    };
}
#endif //DANMU_CORE_NOBLEMAN_RECOMMEND_NOTIFY_H