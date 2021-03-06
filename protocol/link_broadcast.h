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

#ifndef DANMU_CORE_LINK_BROADCAST_H
#define DANMU_CORE_LINK_BROADCAST_H

#include "protobuf.h"
#include "user.h"

namespace protocol {
    class Link_broadcast : public Protocol {
    public:
        Link_broadcast() : l(linkerProtocol::LinkBroadcast()) {};

        explicit Link_broadcast(const linkerProtocol::LinkBroadcast &us) : l(us) {};

        const linkerProtocol::LinkBroadcast &get_link_broadcast() const { return this->l; }

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

            if (o.has<jsonxx::Number>("status")) {
                this->l.set_status(int32_t(o.get<jsonxx::Number>("status")));
            }

            if (o.has<jsonxx::Array>("linkers")) {
                auto us = o.get<jsonxx::Array>("linkers");
                for (size_t i = 0; i < us.size(); i++) {
                    auto j = us.get<jsonxx::Object>(i);
                    User k;
                    k.from_json(j);
                    uint8_t buf[k.get_user().ByteSize()];
                    k.get_user().SerializeToArray(buf, k.get_user().ByteSize());

                    auto m = this->l.add_linkers();
                    m->ParseFromArray(buf, k.get_user().ByteSize());
                }
            }

            if (o.has<jsonxx::Number>("type")) {
                this->l.set_type(int32_t(o.get<jsonxx::Number>("type")));
            }

            if (o.has<jsonxx::Number>("linkersLandscape")) {
                this->l.set_linkerslandscape(int32_t(o.get<jsonxx::Number>("linkersLandscape")));
            }

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
            ss << "{";
            ss << "\"owid\":" << this->l.owid() << ",";
            ss << "\"status\":" << this->l.status() << ",";

            std::stringstream linkers_stream;
            linkers_stream << "[";
            for (int32_t i = 0; i < this->l.linkers_size(); i++) {
                linkers_stream << User(this->l.linkers(i)).to_jsonstr();
                if (i != this->l.linkers_size() - 1) {
                    linkers_stream << ",";
                }
            }
            linkers_stream << "]";
            ss << "\"linkers\":" << linkers_stream.str() << ",";
            ss << "\"type\":" << this->l.type() << ",";
            ss << "\"linkersLandscape\":" << this->l.linkerslandscape();
            ss << "}";
            return ss.str();

        }

    private:
        linkerProtocol::LinkBroadcast l;
    };
}
#endif //DANMU_CORE_LINK_BROADCAST_H