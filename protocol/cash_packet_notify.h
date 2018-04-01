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

#ifndef DANMU_CORE_CASH_PACKET_NOTIFY_H
#define DANMU_CORE_CASH_PACKET_NOTIFY_H

#include "protobuf.h"
#include "retetion_attr.h"

namespace protocol {
    class Cash_packet_notify : public Protocol {
    public:
        Cash_packet_notify() : c(linkerProtocol::CashPacketNotify()) {};

        explicit Cash_packet_notify(const linkerProtocol::CashPacketNotify &us) : c(us) {};

        const linkerProtocol::CashPacketNotify &get_cash_packet_notify() const { return this->c; }

        virtual bool decode_from_buf(Buffer &buf) {
            return this->c.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr <Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->c.ByteSize()];
            this->c.SerializeToArray(ptr, this->c.ByteSize());
            return std::make_shared<Buffer>(ptr, this->c.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if (o.has<jsonxx::Number>("id")) {
                this->c.set_id(int32_t(o.get<jsonxx::Number>("id")));
            }

            if (o.has<jsonxx::Number>("owid")) {
                this->c.set_owid(int32_t(o.get<jsonxx::Number>("owid")));
            }

            if (o.has<jsonxx::String>("code")) {
                this->c.set_code((o.get<jsonxx::String>("code")));
            }

            if (o.has<jsonxx::String>("nickname")) {
                this->c.set_nickname((o.get<jsonxx::String>("nickname")));
            }

            if (o.has<jsonxx::Number>("level")) {
                this->c.set_level(int32_t(o.get<jsonxx::Number>("level")));
            }

            if (o.has<jsonxx::String>("portrait")) {
                this->c.set_portrait((o.get<jsonxx::String>("portrait")));
            }

            if (o.has<jsonxx::Number>("starttime")) {
                this->c.set_starttime(int32_t(o.get<jsonxx::Number>("starttime")));
            }

            if (o.has<jsonxx::Object>("retetionAttr")) {
                jsonxx::Object info = o.get<jsonxx::Object>("retetionAttr");
                Retetion_attr r;
                r.from_json(info);

                auto _r = new linkerProtocol::RetetionAttr();
                uint8_t buf[r.get_retetion_attr().ByteSize()];
                r.get_retetion_attr().SerializeToArray(buf, r.get_retetion_attr().ByteSize());
                _r->ParseFromArray(buf, r.get_retetion_attr().ByteSize());
                this->c.set_allocated_retetionattr(_r);
            }

            if (o.has<jsonxx::Number>("money")) {
                this->c.set_money(int32_t(o.get<jsonxx::Number>("money")));
            }

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
            ss << "{";
            ss << "\"id\":" << this->c.id() << ",";
            ss << "\"owid\":" << this->c.owid() << ",";
            ss << "\"code\":" << "\"" << this->c.code() << "\"" << ",";
            ss << "\"nickname\":" << "\"" << this->c.nickname() << "\"" << ",";
            ss << "\"level\":" << this->c.level() << ",";
            ss << "\"portrait\":" << "\"" << this->c.portrait() << "\"" << ",";
            ss << "\"starttime\":" << this->c.starttime() << ",";

            Retetion_attr r_7(this->c.retetionattr());
            ss << "\"retetionAttr\":" << r_7.to_jsonstr() << ",";
            ss << "\"money\":" << this->c.money();
            ss << "}";
            return ss.str();

        }

    private:
        linkerProtocol::CashPacketNotify c;
    };
}
#endif //DANMU_CORE_CASH_PACKET_NOTIFY_H