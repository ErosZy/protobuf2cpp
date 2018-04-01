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

#ifndef DANMU_CORE_RECOMMEND_ROOM_POPUP_ROOM_H
#define DANMU_CORE_RECOMMEND_ROOM_POPUP_ROOM_H

#include "protobuf.h"

namespace protocol {
    class Recommend_room_popup_room : public Protocol {
    public:
        Recommend_room_popup_room() : r(linkerProtocol::RecommendRoomPopupRoom()) {};
        explicit Recommend_room_popup_room(const linkerProtocol::RecommendRoomPopupRoom &us) : r(us) {};
        const linkerProtocol::RecommendRoomPopupRoom &get_recommend_room_popup_room() const { return this->r; }
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

if(o.has<jsonxx::String>("no")) {
	this->r.set_no((o.get<jsonxx::String>("no")));
}

if(o.has<jsonxx::String>("pic")) {
	this->r.set_pic((o.get<jsonxx::String>("pic")));
}

if(o.has<jsonxx::String>("title")) {
	this->r.set_title((o.get<jsonxx::String>("title")));
}

if(o.has<jsonxx::String>("btnText")) {
	this->r.set_btntext((o.get<jsonxx::String>("btnText")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"uid\":"<< this->r.uid() << ",";
ss << "\"no\":"<< "\"" << this->r.no() << "\"" << ",";
ss << "\"pic\":"<< "\"" << this->r.pic() << "\"" << ",";
ss << "\"title\":"<< "\"" << this->r.title() << "\"" << ",";
ss << "\"btnText\":"<< "\"" << this->r.btntext() << "\"";
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::RecommendRoomPopupRoom r;
    };
}
#endif //DANMU_CORE_RECOMMEND_ROOM_POPUP_ROOM_H