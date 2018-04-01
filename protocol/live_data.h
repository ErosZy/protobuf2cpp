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

#ifndef DANMU_CORE_LIVE_DATA_H
#define DANMU_CORE_LIVE_DATA_H

#include "protobuf.h"

namespace protocol {
    class LiveData : public Protocol {
    public:
        LiveData() : l(linkerProtocol::LiveData()) {};
        explicit LiveData(const linkerProtocol::LiveData &us) : l(us) {};
        const linkerProtocol::LiveData &get_live_data() const { return this->l; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->l.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->l.ByteSize()];
            this->l.SerializeToArray(ptr, this->l.ByteSize());
            return std::make_shared<Buffer>(ptr, this->l.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::Number>("online")) {
	this->l.set_online(int32_t(o.get<jsonxx::Number>("online")));
}

if(o.has<jsonxx::Number>("starlight")) {
	this->l.set_starlight(int32_t(o.get<jsonxx::Number>("starlight")));
}

if(o.has<jsonxx::Number>("fight")) {
	this->l.set_fight(int32_t(o.get<jsonxx::Number>("fight")));
}

if(o.has<jsonxx::Number>("status")) {
	this->l.set_status(int32_t(o.get<jsonxx::Number>("status")));
}

if(o.has<jsonxx::Number>("views")) {
	this->l.set_views(int32_t(o.get<jsonxx::Number>("views")));
}

if(o.has<jsonxx::Number>("duration")) {
	this->l.set_duration(int32_t(o.get<jsonxx::Number>("duration")));
}

if(o.has<jsonxx::Number>("maxOnline")) {
	this->l.set_maxonline(int32_t(o.get<jsonxx::Number>("maxOnline")));
}

if(o.has<jsonxx::Boolean>("isRectify")) {
	this->l.set_isrectify((o.get<jsonxx::Boolean>("isRectify")));
}

if(o.has<jsonxx::Number>("onlineNobleman")) {
	this->l.set_onlinenobleman(int32_t(o.get<jsonxx::Number>("onlineNobleman")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"online\":"<< this->l.online() << ",";
ss << "\"starlight\":"<< this->l.starlight() << ",";
ss << "\"fight\":"<< this->l.fight() << ",";
ss << "\"status\":"<< this->l.status() << ",";
ss << "\"views\":"<< this->l.views() << ",";
ss << "\"duration\":"<< this->l.duration() << ",";
ss << "\"maxOnline\":"<< this->l.maxonline() << ",";
ss << "\"isRectify\":"<< this->l.isrectify() << ",";
ss << "\"onlineNobleman\":"<< this->l.onlinenobleman();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::LiveData l;
    };
}
#endif //DANMU_CORE_LIVE_DATA_H