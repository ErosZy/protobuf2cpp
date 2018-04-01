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

#ifndef DANMU_CORE_ANCHOR_INDICATE_NOTIFY_H
#define DANMU_CORE_ANCHOR_INDICATE_NOTIFY_H

#include "protobuf.h"

namespace protocol {
    class Anchor_indicate_notify : public Protocol {
    public:
        Anchor_indicate_notify() : a(linkerProtocol::AnchorIndicateNotify()) {};

        explicit Anchor_indicate_notify(const linkerProtocol::AnchorIndicateNotify &us) : a(us) {};

        const linkerProtocol::AnchorIndicateNotify &get_anchor_indicate_notify() const { return this->a; }

        virtual bool decode_from_buf(Buffer &buf) {
            return this->a.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr <Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->a.ByteSize()];
            this->a.SerializeToArray(ptr, this->a.ByteSize());
            return std::make_shared<Buffer>(ptr, this->a.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if (o.has<jsonxx::Number>("action")) {
                this->a.set_action(int32_t(o.get<jsonxx::Number>("action")));
            }

            if (o.has<jsonxx::String>("txt")) {
                this->a.set_txt((o.get<jsonxx::String>("txt")));
            }

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
            ss << "{";
            ss << "\"action\":" << this->a.action() << ",";
            ss << "\"txt\":" << "\"" << this->a.txt() << "\"";
            ss << "}";
            return ss.str();

        }

    private:
        linkerProtocol::AnchorIndicateNotify a;
    };
}
#endif //DANMU_CORE_ANCHOR_INDICATE_NOTIFY_H