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

#ifndef DANMU_CORE_SHARED_NOTIFY_H
#define DANMU_CORE_SHARED_NOTIFY_H

#include "protobuf.h"
#include "room_attr.h"
#include "user.h"

namespace protocol {
    class Shared_notify : public Protocol {
    public:
        Shared_notify() : s(linkerProtocol::SharedNotify()) {};

        explicit Shared_notify(const linkerProtocol::SharedNotify &us) : s(us) {};

        const linkerProtocol::SharedNotify &get_shared_notify() const { return this->s; }

        virtual bool decode_from_buf(Buffer &buf) {
            return this->s.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr <Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->s.ByteSize()];
            this->s.SerializeToArray(ptr, this->s.ByteSize());
            return std::make_shared<Buffer>(ptr, this->s.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if (o.has<jsonxx::Number>("owid")) {
                this->s.set_owid(int32_t(o.get<jsonxx::Number>("owid")));
            }

            if (o.has<jsonxx::Object>("roomAttr")) {
                jsonxx::Object info = o.get<jsonxx::Object>("roomAttr");
                Room_attr r;
                r.from_json(info);

                auto _r = new linkerProtocol::RoomAttr();
                uint8_t buf[r.get_room_attr().ByteSize()];
                r.get_room_attr().SerializeToArray(buf, r.get_room_attr().ByteSize());
                _r->ParseFromArray(buf, r.get_room_attr().ByteSize());
                this->s.set_allocated_roomattr(_r);
            }

            if (o.has<jsonxx::Object>("user")) {
                jsonxx::Object info = o.get<jsonxx::Object>("user");
                User u;
                u.from_json(info);

                auto _u = new linkerProtocol::User();
                uint8_t buf[u.get_user().ByteSize()];
                u.get_user().SerializeToArray(buf, u.get_user().ByteSize());
                _u->ParseFromArray(buf, u.get_user().ByteSize());
                this->s.set_allocated_user(_u);
            }

            if (o.has<jsonxx::String>("type")) {
                this->s.set_type((o.get<jsonxx::String>("type")));
            }

            if (o.has<jsonxx::String>("tips")) {
                this->s.set_tips((o.get<jsonxx::String>("tips")));
            }

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
            ss << "{";
            ss << "\"owid\":" << this->s.owid() << ",";

            Room_attr r_1(this->s.roomattr());
            ss << "\"roomAttr\":" << r_1.to_jsonstr() << ",";

            User u_2(this->s.user());
            ss << "\"user\":" << u_2.to_jsonstr() << ",";
            ss << "\"type\":" << "\"" << this->s.type() << "\"" << ",";
            ss << "\"tips\":" << "\"" << this->s.tips() << "\"";
            ss << "}";
            return ss.str();

        }

    private:
        linkerProtocol::SharedNotify s;
    };
}
#endif //DANMU_CORE_SHARED_NOTIFY_H