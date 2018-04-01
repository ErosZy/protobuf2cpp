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

#ifndef DANMU_CORE_OFFICIAL_LIVE_STATUS_NOTIFY_H
#define DANMU_CORE_OFFICIAL_LIVE_STATUS_NOTIFY_H

#include "protobuf.h"
#include "user.h"
#include "user.h"

namespace protocol {
    class Official_live_status_notify : public Protocol {
    public:
        Official_live_status_notify() : o(linkerProtocol::OfficialLiveStatusNotify()) {};

        explicit Official_live_status_notify(const linkerProtocol::OfficialLiveStatusNotify &us) : o(us) {};

        const linkerProtocol::OfficialLiveStatusNotify &get_official_live_status_notify() const { return this->o; }

        virtual bool decode_from_buf(Buffer &buf) {
            return this->o.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr <Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->o.ByteSize()];
            this->o.SerializeToArray(ptr, this->o.ByteSize());
            return std::make_shared<Buffer>(ptr, this->o.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if (o.has<jsonxx::Number>("owid")) {
                this->o.set_owid(int32_t(o.get<jsonxx::Number>("owid")));
            }

            if (o.has<jsonxx::Array>("anchorList")) {
                auto us = o.get<jsonxx::Array>("anchorList");
                for (size_t i = 0; i < us.size(); i++) {
                    auto j = us.get<jsonxx::Object>(i);
                    User k;
                    k.from_json(j);
                    uint8_t buf[k.get_user().ByteSize()];
                    k.get_user().SerializeToArray(buf, k.get_user().ByteSize());

                    auto m = this->o.add_anchorlist();
                    m->ParseFromArray(buf, k.get_user().ByteSize());
                }
            }

            if (o.has<jsonxx::Object>("currentAnchor")) {
                jsonxx::Object info = o.get<jsonxx::Object>("currentAnchor");
                User u;
                u.from_json(info);

                auto _u = new linkerProtocol::User();
                uint8_t buf[u.get_user().ByteSize()];
                u.get_user().SerializeToArray(buf, u.get_user().ByteSize());
                _u->ParseFromArray(buf, u.get_user().ByteSize());
                this->o.set_allocated_currentanchor(_u);
            }

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
            ss << "{";
            ss << "\"owid\":" << this->o.owid() << ",";

            std::stringstream anchorlist_stream;
            anchorlist_stream << "[";
            for (int32_t i = 0; i < this->o.anchorlist_size(); i++) {
                anchorlist_stream << User(this->o.anchorlist(i)).to_jsonstr();
                if (i != this->o.anchorlist_size() - 1) {
                    anchorlist_stream << ",";
                }
            }
            anchorlist_stream << "]";
            ss << "\"anchorList\":" << anchorlist_stream.str() << ",";

            User u_2(this->o.currentanchor());
            ss << "\"currentAnchor\":" << u_2.to_jsonstr();
            ss << "}";
            return ss.str();

        }

    private:
        linkerProtocol::OfficialLiveStatusNotify o;
    };
}
#endif //DANMU_CORE_OFFICIAL_LIVE_STATUS_NOTIFY_H