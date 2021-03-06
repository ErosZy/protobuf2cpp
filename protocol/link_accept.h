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

#ifndef DANMU_CORE_LINK_ACCEPT_H
#define DANMU_CORE_LINK_ACCEPT_H

#include "protobuf.h"
#include "user.h"

namespace protocol {
    class Link_accept : public Protocol {
    public:
        Link_accept() : l(linkerProtocol::LinkAccept()) {};

        explicit Link_accept(const linkerProtocol::LinkAccept &us) : l(us) {};

        const linkerProtocol::LinkAccept &get_link_accept() const { return this->l; }

        virtual bool decode_from_buf(Buffer &buf) {
            return this->l.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr <Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->l.ByteSize()];
            this->l.SerializeToArray(ptr, this->l.ByteSize());
            return std::make_shared<Buffer>(ptr, this->l.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if (o.has<jsonxx::Number>("owid")) {
                this->l.set_owid(int32_t(o.get<jsonxx::Number>("owid")));
            }

            if (o.has<jsonxx::String>("roomName")) {
                this->l.set_roomname((o.get<jsonxx::String>("roomName")));
            }

            if (o.has<jsonxx::String>("token")) {
                this->l.set_token((o.get<jsonxx::String>("token")));
            }

            if (o.has<jsonxx::Number>("type")) {
                this->l.set_type(int32_t(o.get<jsonxx::Number>("type")));
            }

            if (o.has<jsonxx::Object>("owidInfo")) {
                jsonxx::Object info = o.get<jsonxx::Object>("owidInfo");
                User u;
                u.from_json(info);

                auto _u = new linkerProtocol::User();
                uint8_t buf[u.get_user().ByteSize()];
                u.get_user().SerializeToArray(buf, u.get_user().ByteSize());
                _u->ParseFromArray(buf, u.get_user().ByteSize());
                this->l.set_allocated_owidinfo(_u);
            }

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
            ss << "{";
            ss << "\"owid\":" << this->l.owid() << ",";
            ss << "\"roomName\":" << "\"" << this->l.roomname() << "\"" << ",";
            ss << "\"token\":" << "\"" << this->l.token() << "\"" << ",";
            ss << "\"type\":" << this->l.type() << ",";

            User u_4(this->l.owidinfo());
            ss << "\"owidInfo\":" << u_4.to_jsonstr();
            ss << "}";
            return ss.str();

        }

    private:
        linkerProtocol::LinkAccept l;
    };
}
#endif //DANMU_CORE_LINK_ACCEPT_H