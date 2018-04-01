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

#ifndef DANMU_CORE_USER_LEVEL_UP_NOTIFY_H
#define DANMU_CORE_USER_LEVEL_UP_NOTIFY_H

#include "protobuf.h"
#include "room_attr.h"
#include "user.h"

namespace protocol {
    class User_level_up_notify : public Protocol {
    public:
        User_level_up_notify() : u(linkerProtocol::UserLevelUpNotify()) {};

        explicit User_level_up_notify(const linkerProtocol::UserLevelUpNotify &us) : u(us) {};

        const linkerProtocol::UserLevelUpNotify &get_user_level_up_notify() const { return this->u; }

        virtual bool decode_from_buf(Buffer &buf) {
            return this->u.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr <Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->u.ByteSize()];
            this->u.SerializeToArray(ptr, this->u.ByteSize());
            return std::make_shared<Buffer>(ptr, this->u.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if (o.has<jsonxx::Number>("owid")) {
                this->u.set_owid(int32_t(o.get<jsonxx::Number>("owid")));
            }

            if (o.has<jsonxx::Object>("roomAttr")) {
                jsonxx::Object info = o.get<jsonxx::Object>("roomAttr");
                Room_attr r;
                r.from_json(info);

                auto _r = new linkerProtocol::RoomAttr();
                uint8_t buf[r.get_room_attr().ByteSize()];
                r.get_room_attr().SerializeToArray(buf, r.get_room_attr().ByteSize());
                _r->ParseFromArray(buf, r.get_room_attr().ByteSize());
                this->u.set_allocated_roomattr(_r);
            }

            if (o.has<jsonxx::Object>("user")) {
                jsonxx::Object info = o.get<jsonxx::Object>("user");
                User u;
                u.from_json(info);

                auto _u = new linkerProtocol::User();
                uint8_t buf[u.get_user().ByteSize()];
                u.get_user().SerializeToArray(buf, u.get_user().ByteSize());
                _u->ParseFromArray(buf, u.get_user().ByteSize());
                this->u.set_allocated_user(_u);
            }

            if (o.has<jsonxx::Number>("nextLevel")) {
                this->u.set_nextlevel(int32_t(o.get<jsonxx::Number>("nextLevel")));
            }

            if (o.has<jsonxx::Number>("needDiamod")) {
                this->u.set_needdiamod(int32_t(o.get<jsonxx::Number>("needDiamod")));
            }

            if (o.has<jsonxx::Number>("percent")) {
                this->u.set_percent(int32_t(o.get<jsonxx::Number>("percent")));
            }

            if (o.has<jsonxx::Number>("type")) {
                this->u.set_type(int32_t(o.get<jsonxx::Number>("type")));
            }

            if (o.has<jsonxx::String>("tips")) {
                this->u.set_tips((o.get<jsonxx::String>("tips")));
            }

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
            ss << "{";
            ss << "\"owid\":" << this->u.owid() << ",";

            Room_attr r_1(this->u.roomattr());
            ss << "\"roomAttr\":" << r_1.to_jsonstr() << ",";

            User u_2(this->u.user());
            ss << "\"user\":" << u_2.to_jsonstr() << ",";
            ss << "\"nextLevel\":" << this->u.nextlevel() << ",";
            ss << "\"needDiamod\":" << this->u.needdiamod() << ",";
            ss << "\"percent\":" << this->u.percent() << ",";
            ss << "\"type\":" << this->u.type() << ",";
            ss << "\"tips\":" << "\"" << this->u.tips() << "\"";
            ss << "}";
            return ss.str();

        }

    private:
        linkerProtocol::UserLevelUpNotify u;
    };
}
#endif //DANMU_CORE_USER_LEVEL_UP_NOTIFY_H