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

#ifndef DANMU_CORE_GIFT_NOTIFY_H
#define DANMU_CORE_GIFT_NOTIFY_H

#include "protobuf.h"
#include "room_attr.h"
#include "user.h"
#include "retetion_attr.h"

namespace protocol {
    class Gift_notify : public Protocol {
    public:
        Gift_notify() : g(linkerProtocol::GiftNotify()) {};

        explicit Gift_notify(const linkerProtocol::GiftNotify &us) : g(us) {};

        const linkerProtocol::GiftNotify &get_gift_notify() const { return this->g; }

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

            if (o.has<jsonxx::Object>("roomAttr")) {
                jsonxx::Object info = o.get<jsonxx::Object>("roomAttr");
                Room_attr r;
                r.from_json(info);

                auto _r = new linkerProtocol::RoomAttr();
                uint8_t buf[r.get_room_attr().ByteSize()];
                r.get_room_attr().SerializeToArray(buf, r.get_room_attr().ByteSize());
                _r->ParseFromArray(buf, r.get_room_attr().ByteSize());
                this->g.set_allocated_roomattr(_r);
            }

            if (o.has<jsonxx::Object>("user")) {
                jsonxx::Object info = o.get<jsonxx::Object>("user");
                User u;
                u.from_json(info);

                auto _u = new linkerProtocol::User();
                uint8_t buf[u.get_user().ByteSize()];
                u.get_user().SerializeToArray(buf, u.get_user().ByteSize());
                _u->ParseFromArray(buf, u.get_user().ByteSize());
                this->g.set_allocated_user(_u);
            }

            if (o.has<jsonxx::Number>("combo")) {
                this->g.set_combo(int32_t(o.get<jsonxx::Number>("combo")));
            }

            if (o.has<jsonxx::Number>("comboId")) {
                this->g.set_comboid(int32_t(o.get<jsonxx::Number>("comboId")));
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

            if (o.has<jsonxx::Number>("luckyMulti")) {
                this->g.set_luckymulti(int32_t(o.get<jsonxx::Number>("luckyMulti")));
            }

            if (o.has<jsonxx::Number>("consumeType")) {
                this->g.set_consumetype(int32_t(o.get<jsonxx::Number>("consumeType")));
            }

            if (o.has<jsonxx::Number>("newCount")) {
                this->g.set_newcount(int32_t(o.get<jsonxx::Number>("newCount")));
            }

            if (o.has<jsonxx::Number>("newCombo")) {
                this->g.set_newcombo(int32_t(o.get<jsonxx::Number>("newCombo")));
            }

            if (o.has<jsonxx::Number>("pcExtendDelayTime")) {
                this->g.set_pcextenddelaytime(int32_t(o.get<jsonxx::Number>("pcExtendDelayTime")));
            }

            if (o.has<jsonxx::Number>("appExtendDelayTime")) {
                this->g.set_appextenddelaytime(int32_t(o.get<jsonxx::Number>("appExtendDelayTime")));
            }

            if (o.has<jsonxx::Number>("starlight")) {
                this->g.set_starlight(int32_t(o.get<jsonxx::Number>("starlight")));
            }

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
            ss << "{";
            ss << "\"owid\":" << this->g.owid() << ",";

            Room_attr r_1(this->g.roomattr());
            ss << "\"roomAttr\":" << r_1.to_jsonstr() << ",";

            User u_2(this->g.user());
            ss << "\"user\":" << u_2.to_jsonstr() << ",";
            ss << "\"combo\":" << this->g.combo() << ",";
            ss << "\"comboId\":" << this->g.comboid() << ",";
            ss << "\"gid\":" << this->g.gid() << ",";
            ss << "\"attrId\":" << this->g.attrid() << ",";
            ss << "\"count\":" << this->g.count() << ",";

            Retetion_attr r_8(this->g.retetionattr());
            ss << "\"retetionAttr\":" << r_8.to_jsonstr() << ",";
            ss << "\"luckyMulti\":" << this->g.luckymulti() << ",";
            ss << "\"consumeType\":" << this->g.consumetype() << ",";
            ss << "\"newCount\":" << this->g.newcount() << ",";
            ss << "\"newCombo\":" << this->g.newcombo() << ",";
            ss << "\"pcExtendDelayTime\":" << this->g.pcextenddelaytime() << ",";
            ss << "\"appExtendDelayTime\":" << this->g.appextenddelaytime() << ",";
            ss << "\"starlight\":" << this->g.starlight();
            ss << "}";
            return ss.str();

        }

    private:
        linkerProtocol::GiftNotify g;
    };
}
#endif //DANMU_CORE_GIFT_NOTIFY_H