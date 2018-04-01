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

#ifndef DANMU_CORE_ROOM_AD_EXCL_CATEID_H
#define DANMU_CORE_ROOM_AD_EXCL_CATEID_H

#include "protobuf.h"

namespace protocol {
    class RoomAdExclCateid : public Protocol {
    public:
        RoomAdExclCateid() : r(linkerProtocol::RoomAdExclCateid()) {};
        explicit RoomAdExclCateid(const linkerProtocol::RoomAdExclCateid &us) : r(us) {};
        const linkerProtocol::RoomAdExclCateid &get_room_ad_excl_cateid() const { return this->r; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->r.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->r.ByteSize()];
            this->r.SerializeToArray(ptr, this->r.ByteSize());
            return std::make_shared<Buffer>(ptr, this->r.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::Number>("cateid")) {
	this->r.set_cateid(int32_t(o.get<jsonxx::Number>("cateid")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"cateid\":"<< this->r.cateid();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::RoomAdExclCateid r;
    };
}
#endif //DANMU_CORE_ROOM_AD_EXCL_CATEID_H