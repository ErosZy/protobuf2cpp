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

#ifndef DANMU_CORE_ROOM_LOT_WIN_USER_H
#define DANMU_CORE_ROOM_LOT_WIN_USER_H

#include "protobuf.h"

namespace protocol {
    class Room_lot_win_user : public Protocol {
    public:
        Room_lot_win_user() : r(linkerProtocol::RoomLotWinUser()) {};
        explicit Room_lot_win_user(const linkerProtocol::RoomLotWinUser &us) : r(us) {};
        const linkerProtocol::RoomLotWinUser &get_room_lot_win_user() const { return this->r; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->r.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->r.ByteSize()];
            this->r.SerializeToArray(ptr, this->r.ByteSize());
            return std::make_shared<Buffer>(ptr, this->r.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::Number>("uid")) {
	this->r.set_uid(int32_t(o.get<jsonxx::Number>("uid")));
}

if(o.has<jsonxx::Number>("score")) {
	this->r.set_score(int32_t(o.get<jsonxx::Number>("score")));
}

if(o.has<jsonxx::Number>("rank")) {
	this->r.set_rank(int32_t(o.get<jsonxx::Number>("rank")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"uid\":"<< this->r.uid() << ",";
ss << "\"score\":"<< this->r.score() << ",";
ss << "\"rank\":"<< this->r.rank();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::RoomLotWinUser r;
    };
}
#endif //DANMU_CORE_ROOM_LOT_WIN_USER_H