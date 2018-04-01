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

#ifndef DANMU_CORE_ROOM_SVR_WEEKLY_STAR_NOTIFY_H
#define DANMU_CORE_ROOM_SVR_WEEKLY_STAR_NOTIFY_H

#include "protobuf.h"

namespace protocol {
    class Room_svr_weekly_star_notify : public Protocol {
    public:
        Room_svr_weekly_star_notify() : r(linkerProtocol::RoomSvrWeeklyStarNotify()) {};

        explicit Room_svr_weekly_star_notify(const linkerProtocol::RoomSvrWeeklyStarNotify &us) : r(us) {};

        const linkerProtocol::RoomSvrWeeklyStarNotify &get_room_svr_weekly_star_notify() const { return this->r; }

        virtual bool decode_from_buf(Buffer &buf) {
            return this->r.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr <Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->r.ByteSize()];
            this->r.SerializeToArray(ptr, this->r.ByteSize());
            return std::make_shared<Buffer>(ptr, this->r.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if (o.has<jsonxx::Number>("owid")) {
                this->r.set_owid(int32_t(o.get<jsonxx::Number>("owid")));
            }

            if (o.has<jsonxx::Number>("weeklyStarRank")) {
                this->r.set_weeklystarrank(int32_t(o.get<jsonxx::Number>("weeklyStarRank")));
            }

            if (o.has<jsonxx::Number>("weeklyStarScoreDiff")) {
                this->r.set_weeklystarscorediff(int32_t(o.get<jsonxx::Number>("weeklyStarScoreDiff")));
            }

            if (o.has<jsonxx::Number>("weeklyStarUpdateTime")) {
                this->r.set_weeklystarupdatetime(int32_t(o.get<jsonxx::Number>("weeklyStarUpdateTime")));
            }

            if (o.has<jsonxx::String>("weeklyStarCacheKey")) {
                this->r.set_weeklystarcachekey((o.get<jsonxx::String>("weeklyStarCacheKey")));
            }

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
            ss << "{";
            ss << "\"owid\":" << this->r.owid() << ",";
            ss << "\"weeklyStarRank\":" << this->r.weeklystarrank() << ",";
            ss << "\"weeklyStarScoreDiff\":" << this->r.weeklystarscorediff() << ",";
            ss << "\"weeklyStarUpdateTime\":" << this->r.weeklystarupdatetime() << ",";
            ss << "\"weeklyStarCacheKey\":" << "\"" << this->r.weeklystarcachekey() << "\"";
            ss << "}";
            return ss.str();

        }

    private:
        linkerProtocol::RoomSvrWeeklyStarNotify r;
    };
}
#endif //DANMU_CORE_ROOM_SVR_WEEKLY_STAR_NOTIFY_H