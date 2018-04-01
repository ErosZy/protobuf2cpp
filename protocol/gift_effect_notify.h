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

#ifndef DANMU_CORE_GIFT_EFFECT_NOTIFY_H
#define DANMU_CORE_GIFT_EFFECT_NOTIFY_H

#include "protobuf.h"
#include "retetion_attr.h"

namespace protocol {
    class Gift_effect_notify : public Protocol {
    public:
        Gift_effect_notify() : g(linkerProtocol::GiftEffectNotify()) {};

        explicit Gift_effect_notify(const linkerProtocol::GiftEffectNotify &us) : g(us) {};

        const linkerProtocol::GiftEffectNotify &get_gift_effect_notify() const { return this->g; }

        virtual bool decode_from_buf(Buffer &buf) {
            return this->g.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr <Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->g.ByteSize()];
            this->g.SerializeToArray(ptr, this->g.ByteSize());
            return std::make_shared<Buffer>(ptr, this->g.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if (o.has<jsonxx::Number>("id")) {
                this->g.set_id(int32_t(o.get<jsonxx::Number>("id")));
            }

            if (o.has<jsonxx::Number>("owid")) {
                this->g.set_owid(int32_t(o.get<jsonxx::Number>("owid")));
            }

            if (o.has<jsonxx::Number>("gid")) {
                this->g.set_gid(int32_t(o.get<jsonxx::Number>("gid")));
            }

            if (o.has<jsonxx::String>("url")) {
                this->g.set_url((o.get<jsonxx::String>("url")));
            }

            if (o.has<jsonxx::Object>("retetionAttr")) {
                jsonxx::Object info = o.get<jsonxx::Object>("retetionAttr");
                Retetion_attr r;
                r.from_json(info);

                auto _r = new linkerProtocol::RetetionAttr();
                uint8_t buf[r.get_retetion_attr().ByteSize()];
                r.get_retetion_attr().SerializeToArray(buf, r.get_retetion_attr().ByteSize());
                _r->ParseFromArray(buf, r.get_retetion_attr().ByteSize());
                this->g.set_allocated_retetionattr(_r);
            }

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
            ss << "{";
            ss << "\"id\":" << this->g.id() << ",";
            ss << "\"owid\":" << this->g.owid() << ",";
            ss << "\"gid\":" << this->g.gid() << ",";
            ss << "\"url\":" << "\"" << this->g.url() << "\"" << ",";

            Retetion_attr r_4(this->g.retetionattr());
            ss << "\"retetionAttr\":" << r_4.to_jsonstr();
            ss << "}";
            return ss.str();

        }

    private:
        linkerProtocol::GiftEffectNotify g;
    };
}
#endif //DANMU_CORE_GIFT_EFFECT_NOTIFY_H