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

#ifndef DANMU_CORE_USER_H
#define DANMU_CORE_USER_H

#include "protobuf.h"
#include "nobleman_ext.h"

namespace protocol {
    class User : public Protocol {
    public:
        User() : u(linkerProtocol::User()) {};

        explicit User(const linkerProtocol::User &us) : u(us) {};

        const linkerProtocol::User &get_user() const { return this->u; }

        virtual bool decode_from_buf(Buffer &buf) {
            return this->u.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr <Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->u.ByteSize()];
            this->u.SerializeToArray(ptr, this->u.ByteSize());
            return std::make_shared<Buffer>(ptr, this->u.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if (o.has<jsonxx::Number>("uid")) {
                this->u.set_uid(int32_t(o.get<jsonxx::Number>("uid")));
            }

            if (o.has<jsonxx::Number>("gender")) {
                this->u.set_gender(int32_t(o.get<jsonxx::Number>("gender")));
            }

            if (o.has<jsonxx::Number>("verified")) {
                this->u.set_verified(int32_t(o.get<jsonxx::Number>("verified")));
            }

            if (o.has<jsonxx::Number>("exp")) {
                this->u.set_exp(int32_t(o.get<jsonxx::Number>("exp")));
            }

            if (o.has<jsonxx::Number>("level")) {
                this->u.set_level(int32_t(o.get<jsonxx::Number>("level")));
            }

            if (o.has<jsonxx::Number>("authed")) {
                this->u.set_authed(int32_t(o.get<jsonxx::Number>("authed")));
            }

            if (o.has<jsonxx::Number>("status")) {
                this->u.set_status(int32_t(o.get<jsonxx::Number>("status")));
            }

            if (o.has<jsonxx::String>("nickname")) {
                this->u.set_nickname((o.get<jsonxx::String>("nickname")));
            }

            if (o.has<jsonxx::Number>("guard")) {
                this->u.set_guard(int32_t(o.get<jsonxx::Number>("guard")));
            }

            if (o.has<jsonxx::Number>("rider")) {
                this->u.set_rider(int32_t(o.get<jsonxx::Number>("rider")));
            }

            if (o.has<jsonxx::String>("portrait")) {
                this->u.set_portrait((o.get<jsonxx::String>("portrait")));
            }

            if (o.has<jsonxx::Array>("guardArray")) {
                jsonxx::Array arr = o.get<jsonxx::Array>("guardArray");
                for (size_t i = 0; i < arr.size(); i++) {
                    this->u.add_guardarray((arr.get<jsonxx::String>(i)));
                }
            }

            if (o.has<jsonxx::Number>("honorOwid")) {
                this->u.set_honorowid(int32_t(o.get<jsonxx::Number>("honorOwid")));
            }

            if (o.has<jsonxx::Number>("honorLevel")) {
                this->u.set_honorlevel(int32_t(o.get<jsonxx::Number>("honorLevel")));
            }

            if (o.has<jsonxx::String>("honorName")) {
                this->u.set_honorname((o.get<jsonxx::String>("honorName")));
            }

            if (o.has<jsonxx::Boolean>("honorOwIsGray")) {
                this->u.set_honorowisgray((o.get<jsonxx::Boolean>("honorOwIsGray")));
            }

            if (o.has<jsonxx::Number>("no")) {
                this->u.set_no(int32_t(o.get<jsonxx::Number>("no")));
            }

            if (o.has<jsonxx::Number>("noType")) {
                this->u.set_notype(int32_t(o.get<jsonxx::Number>("noType")));
            }

            if (o.has<jsonxx::Object>("nobleInfo")) {
                jsonxx::Object info = o.get<jsonxx::Object>("nobleInfo");
                Nobleman_ext n;
                n.from_json(info);

                auto _n = new linkerProtocol::NoblemanExt();
                uint8_t buf[n.get_nobleman_ext().ByteSize()];
                n.get_nobleman_ext().SerializeToArray(buf, n.get_nobleman_ext().ByteSize());
                _n->ParseFromArray(buf, n.get_nobleman_ext().ByteSize());
                this->u.set_allocated_nobleinfo(_n);
            }

            if (o.has<jsonxx::String>("nickColor")) {
                this->u.set_nickcolor((o.get<jsonxx::String>("nickColor")));
            }

            if (o.has<jsonxx::Number>("cashBalance")) {
                this->u.set_cashbalance(int32_t(o.get<jsonxx::Number>("cashBalance")));
            }

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
            ss << "{";
            ss << "\"uid\":" << this->u.uid() << ",";
            ss << "\"gender\":" << this->u.gender() << ",";
            ss << "\"verified\":" << this->u.verified() << ",";
            ss << "\"exp\":" << this->u.exp() << ",";
            ss << "\"level\":" << this->u.level() << ",";
            ss << "\"authed\":" << this->u.authed() << ",";
            ss << "\"status\":" << this->u.status() << ",";
            ss << "\"nickname\":" << "\"" << this->u.nickname() << "\"" << ",";
            ss << "\"guard\":" << this->u.guard() << ",";
            ss << "\"rider\":" << this->u.rider() << ",";
            ss << "\"portrait\":" << "\"" << this->u.portrait() << "\"" << ",";
            ss << "\"guardArray\":[";
            for (int32_t i = 0; i < this->u.guardarray_size(); i++) {
                ss << this->u.guardarray(i);
                if (i != this->u.guardarray_size() - 1) {
                    ss << ",";
                }
            }
            ss << "]" << ",";
            ss << "\"honorOwid\":" << this->u.honorowid() << ",";
            ss << "\"honorLevel\":" << this->u.honorlevel() << ",";
            ss << "\"honorName\":" << "\"" << this->u.honorname() << "\"" << ",";
            ss << "\"honorOwIsGray\":" << this->u.honorowisgray() << ",";
            ss << "\"no\":" << this->u.no() << ",";
            ss << "\"noType\":" << this->u.notype() << ",";

            Nobleman_ext n_18(this->u.nobleinfo());
            ss << "\"nobleInfo\":" << n_18.to_jsonstr() << ",";
            ss << "\"nickColor\":" << "\"" << this->u.nickcolor() << "\"" << ",";
            ss << "\"cashBalance\":" << this->u.cashbalance();
            ss << "}";
            return ss.str();

        }

    private:
        linkerProtocol::User u;
    };
}
#endif //DANMU_CORE_USER_H