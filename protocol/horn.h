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

#ifndef DANMU_CORE_HORN_H
#define DANMU_CORE_HORN_H

#include "protobuf.h"
#include "user.h"
#include "user.h"

namespace protocol {
    class Horn : public Protocol {
    public:
        Horn() : h(linkerProtocol::Horn()) {};

        explicit Horn(const linkerProtocol::Horn &us) : h(us) {};

        const linkerProtocol::Horn &get_horn() const { return this->h; }

        virtual bool decode_from_buf(Buffer &buf) {
            return this->h.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr <Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->h.ByteSize()];
            this->h.SerializeToArray(ptr, this->h.ByteSize());
            return std::make_shared<Buffer>(ptr, this->h.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if (o.has<jsonxx::Number>("type")) {
                this->h.set_type(int32_t(o.get<jsonxx::Number>("type")));
            }

            if (o.has<jsonxx::Number>("cid")) {
                this->h.set_cid(int32_t(o.get<jsonxx::Number>("cid")));
            }

            if (o.has<jsonxx::Object>("user")) {
                jsonxx::Object info = o.get<jsonxx::Object>("user");
                User u;
                u.from_json(info);

                auto _u = new linkerProtocol::User();
                uint8_t buf[u.get_user().ByteSize()];
                u.get_user().SerializeToArray(buf, u.get_user().ByteSize());
                _u->ParseFromArray(buf, u.get_user().ByteSize());
                this->h.set_allocated_user(_u);
            }

            if (o.has<jsonxx::Object>("anchor")) {
                jsonxx::Object info = o.get<jsonxx::Object>("anchor");
                User u;
                u.from_json(info);

                auto _u = new linkerProtocol::User();
                uint8_t buf[u.get_user().ByteSize()];
                u.get_user().SerializeToArray(buf, u.get_user().ByteSize());
                _u->ParseFromArray(buf, u.get_user().ByteSize());
                this->h.set_allocated_anchor(_u);
            }

            if (o.has<jsonxx::String>("txt")) {
                this->h.set_txt((o.get<jsonxx::String>("txt")));
            }

            if (o.has<jsonxx::Number>("expire")) {
                this->h.set_expire(int32_t(o.get<jsonxx::Number>("expire")));
            }

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
            ss << "{";
            ss << "\"type\":" << this->h.type() << ",";
            ss << "\"cid\":" << this->h.cid() << ",";

            User u_2(this->h.user());
            ss << "\"user\":" << u_2.to_jsonstr() << ",";

            User u_3(this->h.anchor());
            ss << "\"anchor\":" << u_3.to_jsonstr() << ",";
            ss << "\"txt\":" << "\"" << this->h.txt() << "\"" << ",";
            ss << "\"expire\":" << this->h.expire();
            ss << "}";
            return ss.str();

        }

    private:
        linkerProtocol::Horn h;
    };
}
#endif //DANMU_CORE_HORN_H