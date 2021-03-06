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

#ifndef DANMU_CORE_LINK_NOTIFY_H
#define DANMU_CORE_LINK_NOTIFY_H

#include "protobuf.h"

namespace protocol {
    class Link_notify : public Protocol {
    public:
        Link_notify() : l(linkerProtocol::LinkNotify()) {};

        explicit Link_notify(const linkerProtocol::LinkNotify &us) : l(us) {};

        const linkerProtocol::LinkNotify &get_link_notify() const { return this->l; }

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

            if (o.has<jsonxx::Number>("applyCount")) {
                this->l.set_applycount(int32_t(o.get<jsonxx::Number>("applyCount")));
            }

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
            ss << "{";
            ss << "\"owid\":" << this->l.owid() << ",";
            ss << "\"applyCount\":" << this->l.applycount();
            ss << "}";
            return ss.str();

        }

    private:
        linkerProtocol::LinkNotify l;
    };
}
#endif //DANMU_CORE_LINK_NOTIFY_H