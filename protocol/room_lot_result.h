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

#ifndef DANMU_CORE_ROOM_LOT_RESULT_H
#define DANMU_CORE_ROOM_LOT_RESULT_H

#include "protobuf.h"
#include "room_lot_win_user.h"
#include "room_lot_gift_attr.h"

namespace protocol {
    class Room_lot_result : public Protocol {
    public:
        Room_lot_result() : r(linkerProtocol::RoomLotResult()) {};

        explicit Room_lot_result(const linkerProtocol::RoomLotResult &us) : r(us) {};

        const linkerProtocol::RoomLotResult &get_room_lot_result() const { return this->r; }

        virtual bool decode_from_buf(Buffer &buf) {
            return this->r.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr <Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->r.ByteSize()];
            this->r.SerializeToArray(ptr, this->r.ByteSize());
            return std::make_shared<Buffer>(ptr, this->r.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if (o.has<jsonxx::Number>("lotId")) {
                this->r.set_lotid(int32_t(o.get<jsonxx::Number>("lotId")));
            }

            if (o.has<jsonxx::Number>("giftType")) {
                this->r.set_gifttype(int32_t(o.get<jsonxx::Number>("giftType")));
            }

            if (o.has<jsonxx::Number>("shardingNum")) {
                this->r.set_shardingnum(int32_t(o.get<jsonxx::Number>("shardingNum")));
            }

            if (o.has<jsonxx::Number>("shardingId")) {
                this->r.set_shardingid(int32_t(o.get<jsonxx::Number>("shardingId")));
            }

            if (o.has<jsonxx::Array>("list")) {
                auto rs = o.get<jsonxx::Array>("list");
                for (size_t i = 0; i < rs.size(); i++) {
                    auto j = rs.get<jsonxx::Object>(i);
                    Room_lot_win_user k;
                    k.from_json(j);
                    uint8_t buf[k.get_room_lot_win_user().ByteSize()];
                    k.get_room_lot_win_user().SerializeToArray(buf, k.get_room_lot_win_user().ByteSize());

                    auto m = this->r.add_list();
                    m->ParseFromArray(buf, k.get_room_lot_win_user().ByteSize());
                }
            }

            if (o.has<jsonxx::Object>("giftAttr")) {
                jsonxx::Object info = o.get<jsonxx::Object>("giftAttr");
                Room_lot_gift_attr r;
                r.from_json(info);

                auto _r = new linkerProtocol::RoomLotGiftAttr();
                uint8_t buf[r.get_room_lot_gift_attr().ByteSize()];
                r.get_room_lot_gift_attr().SerializeToArray(buf, r.get_room_lot_gift_attr().ByteSize());
                _r->ParseFromArray(buf, r.get_room_lot_gift_attr().ByteSize());
                this->r.set_allocated_giftattr(_r);
            }

            if (o.has<jsonxx::Number>("owid")) {
                this->r.set_owid(int32_t(o.get<jsonxx::Number>("owid")));
            }

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
            ss << "{";
            ss << "\"lotId\":" << this->r.lotid() << ",";
            ss << "\"giftType\":" << this->r.gifttype() << ",";
            ss << "\"shardingNum\":" << this->r.shardingnum() << ",";
            ss << "\"shardingId\":" << this->r.shardingid() << ",";

            std::stringstream list_stream;
            list_stream << "[";
            for (int32_t i = 0; i < this->r.list_size(); i++) {
                list_stream << Room_lot_win_user(this->r.list(i)).to_jsonstr();
                if (i != this->r.list_size() - 1) {
                    list_stream << ",";
                }
            }
            list_stream << "]";
            ss << "\"list\":" << list_stream.str() << ",";

            Room_lot_gift_attr r_5(this->r.giftattr());
            ss << "\"giftAttr\":" << r_5.to_jsonstr() << ",";
            ss << "\"owid\":" << this->r.owid();
            ss << "}";
            return ss.str();

        }

    private:
        linkerProtocol::RoomLotResult r;
    };
}
#endif //DANMU_CORE_ROOM_LOT_RESULT_H