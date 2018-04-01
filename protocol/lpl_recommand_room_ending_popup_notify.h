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

#ifndef DANMU_CORE_LPL_RECOMMAND_ROOM_ENDING_POPUP_NOTIFY_H
#define DANMU_CORE_LPL_RECOMMAND_ROOM_ENDING_POPUP_NOTIFY_H

#include "protobuf.h"
#include "lpl_recommand_room_ending_popup_notify_item.h"

namespace protocol {
    class Lpl_recommand_room_ending_popup_notify : public Protocol {
    public:
        Lpl_recommand_room_ending_popup_notify() : l(linkerProtocol::LplRecommandRoomEndingPopupNotify()) {};

        explicit Lpl_recommand_room_ending_popup_notify(const linkerProtocol::LplRecommandRoomEndingPopupNotify &us)
                : l(us) {};

        const linkerProtocol::LplRecommandRoomEndingPopupNotify &
        get_lpl_recommand_room_ending_popup_notify() const { return this->l; }

        virtual bool decode_from_buf(Buffer &buf) {
            return this->l.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr <Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->l.ByteSize()];
            this->l.SerializeToArray(ptr, this->l.ByteSize());
            return std::make_shared<Buffer>(ptr, this->l.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if (o.has<jsonxx::Number>("owid")) {
                this->l.set_owid(int32_t(o.get<jsonxx::Number>("owid")));
            }

            if (o.has<jsonxx::String>("title")) {
                this->l.set_title((o.get<jsonxx::String>("title")));
            }

            if (o.has<jsonxx::Number>("second")) {
                this->l.set_second(int32_t(o.get<jsonxx::Number>("second")));
            }

            if (o.has<jsonxx::Array>("rooms")) {
                auto ls = o.get<jsonxx::Array>("rooms");
                for (size_t i = 0; i < ls.size(); i++) {
                    auto j = ls.get<jsonxx::Object>(i);
                    Lpl_recommand_room_ending_popup_notify_item k;
                    k.from_json(j);
                    uint8_t buf[k.get_lpl_recommand_room_ending_popup_notify_item().ByteSize()];
                    k.get_lpl_recommand_room_ending_popup_notify_item().SerializeToArray(buf,
                                                                                         k.get_lpl_recommand_room_ending_popup_notify_item().ByteSize());

                    auto m = this->l.add_rooms();
                    m->ParseFromArray(buf, k.get_lpl_recommand_room_ending_popup_notify_item().ByteSize());
                }
            }

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
            ss << "{";
            ss << "\"owid\":" << this->l.owid() << ",";
            ss << "\"title\":" << "\"" << this->l.title() << "\"" << ",";
            ss << "\"second\":" << this->l.second() << ",";

            std::stringstream rooms_stream;
            rooms_stream << "[";
            for (int32_t i = 0; i < this->l.rooms_size(); i++) {
                rooms_stream << Lpl_recommand_room_ending_popup_notify_item(this->l.rooms(i)).to_jsonstr();
                if (i != this->l.rooms_size() - 1) {
                    rooms_stream << ",";
                }
            }
            rooms_stream << "]";
            ss << "\"rooms\":" << rooms_stream.str();
            ss << "}";
            return ss.str();

        }

    private:
        linkerProtocol::LplRecommandRoomEndingPopupNotify l;
    };
}
#endif //DANMU_CORE_LPL_RECOMMAND_ROOM_ENDING_POPUP_NOTIFY_H