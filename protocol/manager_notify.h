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

#ifndef DANMU_CORE_MANAGER_NOTIFY_H
#define DANMU_CORE_MANAGER_NOTIFY_H

#include "protobuf.h"
#include "room_attr.h"
#include "user.h"

namespace protocol {
    class Manager_notify : public Protocol {
    public:
        Manager_notify() : m(linkerProtocol::ManagerNotify()) {};

        explicit Manager_notify(const linkerProtocol::ManagerNotify &us) : m(us) {};

        const linkerProtocol::ManagerNotify &get_manager_notify() const { return this->m; }

        virtual bool decode_from_buf(Buffer &buf) {
            return this->m.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr <Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->m.ByteSize()];
            this->m.SerializeToArray(ptr, this->m.ByteSize());
            return std::make_shared<Buffer>(ptr, this->m.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if (o.has<jsonxx::Number>("owid")) {
                this->m.set_owid(int32_t(o.get<jsonxx::Number>("owid")));
            }

            if (o.has<jsonxx::Object>("roomAttr")) {
                jsonxx::Object info = o.get<jsonxx::Object>("roomAttr");
                Room_attr r;
                r.from_json(info);

                auto _r = new linkerProtocol::RoomAttr();
                uint8_t buf[r.get_room_attr().ByteSize()];
                r.get_room_attr().SerializeToArray(buf, r.get_room_attr().ByteSize());
                _r->ParseFromArray(buf, r.get_room_attr().ByteSize());
                this->m.set_allocated_roomattr(_r);
            }

            if (o.has<jsonxx::Object>("user")) {
                jsonxx::Object info = o.get<jsonxx::Object>("user");
                User u;
                u.from_json(info);

                auto _u = new linkerProtocol::User();
                uint8_t buf[u.get_user().ByteSize()];
                u.get_user().SerializeToArray(buf, u.get_user().ByteSize());
                _u->ParseFromArray(buf, u.get_user().ByteSize());
                this->m.set_allocated_user(_u);
            }

            if (o.has<jsonxx::Number>("status")) {
                this->m.set_status(int32_t(o.get<jsonxx::Number>("status")));
            }

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
            ss << "{";
            ss << "\"owid\":" << this->m.owid() << ",";

            Room_attr r_1(this->m.roomattr());
            ss << "\"roomAttr\":" << r_1.to_jsonstr() << ",";

            User u_2(this->m.user());
            ss << "\"user\":" << u_2.to_jsonstr() << ",";
            ss << "\"status\":" << this->m.status();
            ss << "}";
            return ss.str();

        }

    private:
        linkerProtocol::ManagerNotify m;
    };
}
#endif //DANMU_CORE_MANAGER_NOTIFY_H