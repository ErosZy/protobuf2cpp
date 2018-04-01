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

#ifndef DANMU_CORE_OFFICIAL_LIVE_NAVIGATION_CHANGE_H
#define DANMU_CORE_OFFICIAL_LIVE_NAVIGATION_CHANGE_H

#include "protobuf.h"

namespace protocol {
    class OfficialLiveNavigationChange : public Protocol {
    public:
        OfficialLiveNavigationChange() : o(linkerProtocol::OfficialLiveNavigationChange()) {};
        explicit OfficialLiveNavigationChange(const linkerProtocol::OfficialLiveNavigationChange &us) : o(us) {};
        const linkerProtocol::OfficialLiveNavigationChange &get_official_live_navigation_change() const { return this->o; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->o.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->o.ByteSize()];
            this->o.SerializeToArray(ptr, this->o.ByteSize());
            return std::make_shared<Buffer>(ptr, this->o.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::Number>("srcOwid")) {
	this->o.set_srcowid(int32_t(o.get<jsonxx::Number>("srcOwid")));
}

if(o.has<jsonxx::Number>("destOwid")) {
	this->o.set_destowid(int32_t(o.get<jsonxx::Number>("destOwid")));
}

if(o.has<jsonxx::String>("streamUrl")) {
	this->o.set_streamurl((o.get<jsonxx::String>("streamUrl")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"srcOwid\":"<< this->o.srcowid() << ",";
ss << "\"destOwid\":"<< this->o.destowid() << ",";
ss << "\"streamUrl\":"<< "\"" << this->o.streamurl() << "\"";
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::OfficialLiveNavigationChange o;
    };
}
#endif //DANMU_CORE_OFFICIAL_LIVE_NAVIGATION_CHANGE_H