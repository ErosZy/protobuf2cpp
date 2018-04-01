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

#ifndef DANMU_CORE_LINK_APPLY_H
#define DANMU_CORE_LINK_APPLY_H

#include "protobuf.h"
#include "user.h"

namespace protocol {
    class Link_apply : public Protocol {
    public:
        Link_apply() : l(linkerProtocol::LinkApply()) {};

        explicit Link_apply(const linkerProtocol::LinkApply &us) : l(us) {};

        const linkerProtocol::LinkApply &get_link_apply() const { return this->l; }

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

            if (o.has<jsonxx::Number>("uid")) {
                this->l.set_uid(int32_t(o.get<jsonxx::Number>("uid")));
            }

            if (o.has<jsonxx::Number>("applyCount")) {
                this->l.set_applycount(int32_t(o.get<jsonxx::Number>("applyCount")));
            }

            if (o.has<jsonxx::Object>("applyUser")) {
                jsonxx::Object info = o.get<jsonxx::Object>("applyUser");
                User u;
                u.from_json(info);

                auto _u = new linkerProtocol::User();
                uint8_t buf[u.get_user().ByteSize()];
                u.get_user().SerializeToArray(buf, u.get_user().ByteSize());
                _u->ParseFromArray(buf, u.get_user().ByteSize());
                this->l.set_allocated_applyuser(_u);
            }

            if (o.has<jsonxx::Number>("type")) {
                this->l.set_type(int32_t(o.get<jsonxx::Number>("type")));
            }

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
            ss << "{";
            ss << "\"owid\":" << this->l.owid() << ",";
            ss << "\"uid\":" << this->l.uid() << ",";
            ss << "\"applyCount\":" << this->l.applycount() << ",";

            User u_3(this->l.applyuser());
            ss << "\"applyUser\":" << u_3.to_jsonstr() << ",";
            ss << "\"type\":" << this->l.type();
            ss << "}";
            return ss.str();

        }

    private:
        linkerProtocol::LinkApply l;
    };
}
#endif //DANMU_CORE_LINK_APPLY_H