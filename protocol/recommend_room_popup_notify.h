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

#ifndef DANMU_CORE_RECOMMEND_ROOM_POPUP_NOTIFY_H
#define DANMU_CORE_RECOMMEND_ROOM_POPUP_NOTIFY_H

#include "protobuf.h"
#include "recommend_room_popup_room.h"

namespace protocol {
    class RecommendRoomPopupNotify : public Protocol {
    public:
        RecommendRoomPopupNotify() : r(linkerProtocol::RecommendRoomPopupNotify()) {};
        explicit RecommendRoomPopupNotify(const linkerProtocol::RecommendRoomPopupNotify &us) : r(us) {};
        const linkerProtocol::RecommendRoomPopupNotify &get_recommend_room_popup_notify() const { return this->r; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->r.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->r.ByteSize()];
            this->r.SerializeToArray(ptr, this->r.ByteSize());
            return std::make_shared<Buffer>(ptr, this->r.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::Number>("owid")) {
	this->r.set_owid(int32_t(o.get<jsonxx::Number>("owid")));
}

if (o.has<jsonxx::Array>("rooms")) {
	auto rs = o.get<jsonxx::Array>("rooms");
	for (size_t i = 0; i < rs.size(); i++) {
		auto j = rs.get<jsonxx::Object>(i);
		RecommendRoomPopupRoom k;
		k.from_json(j);
		uint8_t buf[k.get_recommend_room_popup_room().ByteSize()];
		k.get_recommend_room_popup_room().SerializeToArray(buf, k.get_recommend_room_popup_room().ByteSize());

		auto m = this->r.add_rooms();
		m->ParseFromArray(buf, k.get_recommend_room_popup_room().ByteSize());
	}
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"owid\":"<< this->r.owid() << ",";

std::stringstream rooms_stream;
rooms_stream << "[";
for (int32_t i = 0; i < this->r.rooms_size(); i++) {
	rooms_stream << RecommendRoomPopupRoom(this->r.rooms(i)).to_jsonstr();
	if (i != this->r.rooms_size() - 1) {
		rooms_stream << ",";
	}
}
rooms_stream << "]";
ss << "\"rooms\":" << rooms_stream.str();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::RecommendRoomPopupNotify r;
    };
}
#endif //DANMU_CORE_RECOMMEND_ROOM_POPUP_NOTIFY_H