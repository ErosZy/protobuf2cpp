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

#ifndef DANMU_CORE_EXT_H
#define DANMU_CORE_EXT_H

#include "protobuf.h"
#include "user.h"
#include "room_attr.h"

namespace protocol {
    class Ext : public Protocol {
    public:
        Ext() : e(linkerProtocol::Ext()) {};

        explicit Ext(const linkerProtocol::Ext &us) : e(us) {};

        const linkerProtocol::Ext &get_ext() const { return this->e; }

        virtual bool decode_from_buf(Buffer &buf) {
            return this->e.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr <Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->e.ByteSize()];
            this->e.SerializeToArray(ptr, this->e.ByteSize());
            return std::make_shared<Buffer>(ptr, this->e.ByteSize());
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
                this->e.set_allocated_user(_u);
            }

            if (o.has<jsonxx::String>("txt")) {
                this->e.set_txt((o.get<jsonxx::String>("txt")));
            }

            if (o.has<jsonxx::Number>("color")) {
                this->e.set_color(int32_t(o.get<jsonxx::Number>("color")));
            }

            if (o.has<jsonxx::Object>("roomAttr")) {
                jsonxx::Object info = o.get<jsonxx::Object>("roomAttr");
                Room_attr r;
                r.from_json(info);

                auto _r = new linkerProtocol::RoomAttr();
                uint8_t buf[r.get_room_attr().ByteSize()];
                r.get_room_attr().SerializeToArray(buf, r.get_room_attr().ByteSize());
                _r->ParseFromArray(buf, r.get_room_attr().ByteSize());
                this->e.set_allocated_roomattr(_r);
            }

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
            ss << "{";

            User u_0(this->e.user());
            ss << "\"user\":" << u_0.to_jsonstr() << ",";
            ss << "\"txt\":" << "\"" << this->e.txt() << "\"" << ",";
            ss << "\"color\":" << this->e.color() << ",";

            Room_attr r_3(this->e.roomattr());
            ss << "\"roomAttr\":" << r_3.to_jsonstr();
            ss << "}";
            return ss.str();

        }

    private:
        linkerProtocol::Ext e;
    };
}
#endif //DANMU_CORE_EXT_H