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

#ifndef DANMU_CORE_ROOM_LOT_ATTRS_H
#define DANMU_CORE_ROOM_LOT_ATTRS_H

#include "protobuf.h"

namespace protocol {
    class Room_lot_attrs : public Protocol {
    public:
        Room_lot_attrs() : r(linkerProtocol::RoomLotAttrs()) {};

        explicit Room_lot_attrs(const linkerProtocol::RoomLotAttrs &us) : r(us) {};

        const linkerProtocol::RoomLotAttrs &get_room_lot_attrs() const { return this->r; }

        virtual bool decode_from_buf(Buffer &buf) {
            return this->r.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr <Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->r.ByteSize()];
            this->r.SerializeToArray(ptr, this->r.ByteSize());
            return std::make_shared<Buffer>(ptr, this->r.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if (o.has<jsonxx::String>("word")) {
                this->r.set_word((o.get<jsonxx::String>("word")));
            }

            if (o.has<jsonxx::Number>("commentType")) {
                this->r.set_commenttype(int32_t(o.get<jsonxx::Number>("commentType")));
            }

            if (o.has<jsonxx::String>("prizeName")) {
                this->r.set_prizename((o.get<jsonxx::String>("prizeName")));
            }

            if (o.has<jsonxx::Number>("partGiftId")) {
                this->r.set_partgiftid(int32_t(o.get<jsonxx::Number>("partGiftId")));
            }

            if (o.has<jsonxx::String>("partGiftName")) {
                this->r.set_partgiftname((o.get<jsonxx::String>("partGiftName")));
            }

            if (o.has<jsonxx::String>("partGiftIcon")) {
                this->r.set_partgifticon((o.get<jsonxx::String>("partGiftIcon")));
            }

            if (o.has<jsonxx::Number>("partGiftMinNum")) {
                this->r.set_partgiftminnum(int32_t(o.get<jsonxx::Number>("partGiftMinNum")));
            }

            if (o.has<jsonxx::Number>("chargeLimit")) {
                this->r.set_chargelimit(int32_t(o.get<jsonxx::Number>("chargeLimit")));
            }

            if (o.has<jsonxx::Number>("partGiftGid")) {
                this->r.set_partgiftgid(int32_t(o.get<jsonxx::Number>("partGiftGid")));
            }

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
            ss << "{";
            ss << "\"word\":" << "\"" << this->r.word() << "\"" << ",";
            ss << "\"commentType\":" << this->r.commenttype() << ",";
            ss << "\"prizeName\":" << "\"" << this->r.prizename() << "\"" << ",";
            ss << "\"partGiftId\":" << this->r.partgiftid() << ",";
            ss << "\"partGiftName\":" << "\"" << this->r.partgiftname() << "\"" << ",";
            ss << "\"partGiftIcon\":" << "\"" << this->r.partgifticon() << "\"" << ",";
            ss << "\"partGiftMinNum\":" << this->r.partgiftminnum() << ",";
            ss << "\"chargeLimit\":" << this->r.chargelimit() << ",";
            ss << "\"partGiftGid\":" << this->r.partgiftgid();
            ss << "}";
            return ss.str();

        }

    private:
        linkerProtocol::RoomLotAttrs r;
    };
}
#endif //DANMU_CORE_ROOM_LOT_ATTRS_H