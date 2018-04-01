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

#ifndef DANMU_CORE_FRIEND_STATUS_H
#define DANMU_CORE_FRIEND_STATUS_H

#include "protobuf.h"
#include "user.h"
#include "user.h"

namespace protocol {
    class Friend_status : public Protocol {
    public:
        Friend_status() : f(linkerProtocol::FriendStatus()) {};

        explicit Friend_status(const linkerProtocol::FriendStatus &us) : f(us) {};

        const linkerProtocol::FriendStatus &get_friend_status() const { return this->f; }

        virtual bool decode_from_buf(Buffer &buf) {
            return this->f.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr <Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->f.ByteSize()];
            this->f.SerializeToArray(ptr, this->f.ByteSize());
            return std::make_shared<Buffer>(ptr, this->f.ByteSize());
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
                this->f.set_allocated_user(_u);
            }

            if (o.has<jsonxx::Object>("anchor")) {
                jsonxx::Object info = o.get<jsonxx::Object>("anchor");
                User u;
                u.from_json(info);

                auto _u = new linkerProtocol::User();
                uint8_t buf[u.get_user().ByteSize()];
                u.get_user().SerializeToArray(buf, u.get_user().ByteSize());
                _u->ParseFromArray(buf, u.get_user().ByteSize());
                this->f.set_allocated_anchor(_u);
            }

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
            ss << "{";

            User u_0(this->f.user());
            ss << "\"user\":" << u_0.to_jsonstr() << ",";

            User u_1(this->f.anchor());
            ss << "\"anchor\":" << u_1.to_jsonstr();
            ss << "}";
            return ss.str();

        }

    private:
        linkerProtocol::FriendStatus f;
    };
}
#endif //DANMU_CORE_FRIEND_STATUS_H