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

#ifndef DANMU_CORE_ROOM_LOT_START_H
#define DANMU_CORE_ROOM_LOT_START_H

#include "protobuf.h"
#include "room_lot_attrs.h"

namespace protocol {
    class Room_lot_start : public Protocol {
    public:
        Room_lot_start() : r(linkerProtocol::RoomLotStart()) {};
        explicit Room_lot_start(const linkerProtocol::RoomLotStart &us) : r(us) {};
        const linkerProtocol::RoomLotStart &get_room_lot_start() const { return this->r; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->r.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->r.ByteSize()];
            this->r.SerializeToArray(ptr, this->r.ByteSize());
            return std::make_shared<Buffer>(ptr, this->r.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::Number>("lotId")) {
	this->r.set_lotid(int32_t(o.get<jsonxx::Number>("lotId")));
}

if(o.has<jsonxx::Number>("lotStatus")) {
	this->r.set_lotstatus(int32_t(o.get<jsonxx::Number>("lotStatus")));
}

if(o.has<jsonxx::Number>("owid")) {
	this->r.set_owid(int32_t(o.get<jsonxx::Number>("owid")));
}

if(o.has<jsonxx::Number>("uid")) {
	this->r.set_uid(int32_t(o.get<jsonxx::Number>("uid")));
}

if(o.has<jsonxx::Number>("giftType")) {
	this->r.set_gifttype(int32_t(o.get<jsonxx::Number>("giftType")));
}

if(o.has<jsonxx::Number>("giftTotalNum")) {
	this->r.set_gifttotalnum(int32_t(o.get<jsonxx::Number>("giftTotalNum")));
}

if(o.has<jsonxx::Number>("partitionNum")) {
	this->r.set_partitionnum(int32_t(o.get<jsonxx::Number>("partitionNum")));
}

if(o.has<jsonxx::Number>("lotType")) {
	this->r.set_lottype(int32_t(o.get<jsonxx::Number>("lotType")));
}

if(o.has<jsonxx::Number>("scope")) {
	this->r.set_scope(int32_t(o.get<jsonxx::Number>("scope")));
}

if(o.has<jsonxx::Number>("duration")) {
	this->r.set_duration(int32_t(o.get<jsonxx::Number>("duration")));
}

if(o.has<jsonxx::String>("startTime")) {
	this->r.set_starttime((o.get<jsonxx::String>("startTime")));
}

if(o.has<jsonxx::String>("endTime")) {
	this->r.set_endtime((o.get<jsonxx::String>("endTime")));
}

if (o.has<jsonxx::Object>("attrs")) {
	jsonxx::Object info = o.get<jsonxx::Object>("attrs");
	Room_lot_attrs r;
	r.from_json(info);

	auto _r = new linkerProtocol::RoomLotAttrs();
	uint8_t buf[r.get_room_lot_attrs().ByteSize()];
	r.get_room_lot_attrs().SerializeToArray(buf, r.get_room_lot_attrs().ByteSize());
	_r->ParseFromArray(buf, r.get_room_lot_attrs().ByteSize());
	this->r.set_allocated_attrs(_r);
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"lotId\":"<< this->r.lotid() << ",";
ss << "\"lotStatus\":"<< this->r.lotstatus() << ",";
ss << "\"owid\":"<< this->r.owid() << ",";
ss << "\"uid\":"<< this->r.uid() << ",";
ss << "\"giftType\":"<< this->r.gifttype() << ",";
ss << "\"giftTotalNum\":"<< this->r.gifttotalnum() << ",";
ss << "\"partitionNum\":"<< this->r.partitionnum() << ",";
ss << "\"lotType\":"<< this->r.lottype() << ",";
ss << "\"scope\":"<< this->r.scope() << ",";
ss << "\"duration\":"<< this->r.duration() << ",";
ss << "\"startTime\":"<< "\"" << this->r.starttime() << "\"" << ",";
ss << "\"endTime\":"<< "\"" << this->r.endtime() << "\"" << ",";

Room_lot_attrs r_12(this->r.attrs());
ss << "\"attrs\":" << r_12.to_jsonstr();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::RoomLotStart r;
    };
}
#endif //DANMU_CORE_ROOM_LOT_START_H