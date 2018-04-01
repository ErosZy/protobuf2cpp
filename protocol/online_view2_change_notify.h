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

#ifndef DANMU_CORE_ONLINE_VIEW2_CHANGE_NOTIFY_H
#define DANMU_CORE_ONLINE_VIEW2_CHANGE_NOTIFY_H

#include "protobuf.h"

namespace protocol {
    class Online_view2_change_notify : public Protocol {
    public:
        Online_view2_change_notify() : o(linkerProtocol::OnlineView2ChangeNotify()) {};
        explicit Online_view2_change_notify(const linkerProtocol::OnlineView2ChangeNotify &us) : o(us) {};
        const linkerProtocol::OnlineView2ChangeNotify &get_online_view2_change_notify() const { return this->o; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->o.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->o.ByteSize()];
            this->o.SerializeToArray(ptr, this->o.ByteSize());
            return std::make_shared<Buffer>(ptr, this->o.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::Number>("owid")) {
	this->o.set_owid(int32_t(o.get<jsonxx::Number>("owid")));
}

if(o.has<jsonxx::Number>("online2")) {
	this->o.set_online2(int32_t(o.get<jsonxx::Number>("online2")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"owid\":"<< this->o.owid() << ",";
ss << "\"online2\":"<< this->o.online2();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::OnlineView2ChangeNotify o;
    };
}
#endif //DANMU_CORE_ONLINE_VIEW2_CHANGE_NOTIFY_H