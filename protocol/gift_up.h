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

#ifndef DANMU_CORE_GIFT_UP_H
#define DANMU_CORE_GIFT_UP_H

#include "protobuf.h"

namespace protocol {
    class Gift_up : public Protocol {
    public:
        Gift_up() : g(linkerProtocol::GiftUp()) {};

        explicit Gift_up(const linkerProtocol::GiftUp &us) : g(us) {};

        const linkerProtocol::GiftUp &get_gift_up() const { return this->g; }

        virtual bool decode_from_buf(Buffer &buf) {
            return this->g.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr <Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->g.ByteSize()];
            this->g.SerializeToArray(ptr, this->g.ByteSize());
            return std::make_shared<Buffer>(ptr, this->g.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if (o.has<jsonxx::Number>("owid")) {
                this->g.set_owid(int32_t(o.get<jsonxx::Number>("owid")));
            }

            if (o.has<jsonxx::Number>("gid")) {
                this->g.set_gid(int32_t(o.get<jsonxx::Number>("gid")));
            }

            if (o.has<jsonxx::Number>("attrId")) {
                this->g.set_attrid(int32_t(o.get<jsonxx::Number>("attrId")));
            }

            if (o.has<jsonxx::Number>("count")) {
                this->g.set_count(int32_t(o.get<jsonxx::Number>("count")));
            }

            if (o.has<jsonxx::String>("txt")) {
                this->g.set_txt((o.get<jsonxx::String>("txt")));
            }

            if (o.has<jsonxx::String>("ext")) {
                this->g.set_ext((o.get<jsonxx::String>("ext")));
            }

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
            ss << "{";
            ss << "\"owid\":" << this->g.owid() << ",";
            ss << "\"gid\":" << this->g.gid() << ",";
            ss << "\"attrId\":" << this->g.attrid() << ",";
            ss << "\"count\":" << this->g.count() << ",";
            ss << "\"txt\":" << "\"" << this->g.txt() << "\"" << ",";
            ss << "\"ext\":" << "\"" << this->g.ext() << "\"";
            ss << "}";
            return ss.str();

        }

    private:
        linkerProtocol::GiftUp g;
    };
}
#endif //DANMU_CORE_GIFT_UP_H