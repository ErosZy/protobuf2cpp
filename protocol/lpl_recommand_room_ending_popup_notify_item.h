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

#ifndef DANMU_CORE_LPL_RECOMMAND_ROOM_ENDING_POPUP_NOTIFY_ITEM_H
#define DANMU_CORE_LPL_RECOMMAND_ROOM_ENDING_POPUP_NOTIFY_ITEM_H

#include "protobuf.h"

namespace protocol {
    class LplRecommandRoomEndingPopupNotifyItem : public Protocol {
    public:
        LplRecommandRoomEndingPopupNotifyItem() : l(linkerProtocol::LplRecommandRoomEndingPopupNotifyItem()) {};
        explicit LplRecommandRoomEndingPopupNotifyItem(const linkerProtocol::LplRecommandRoomEndingPopupNotifyItem &us) : l(us) {};
        const linkerProtocol::LplRecommandRoomEndingPopupNotifyItem &get_lpl_recommand_room_ending_popup_notify_item() const { return this->l; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->l.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->l.ByteSize()];
            this->l.SerializeToArray(ptr, this->l.ByteSize());
            return std::make_shared<Buffer>(ptr, this->l.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::Number>("owid")) {
	this->l.set_owid(int32_t(o.get<jsonxx::Number>("owid")));
}

if(o.has<jsonxx::String>("no")) {
	this->l.set_no((o.get<jsonxx::String>("no")));
}

if(o.has<jsonxx::String>("nickname")) {
	this->l.set_nickname((o.get<jsonxx::String>("nickname")));
}

if(o.has<jsonxx::String>("name")) {
	this->l.set_name((o.get<jsonxx::String>("name")));
}

if(o.has<jsonxx::Number>("online")) {
	this->l.set_online(int32_t(o.get<jsonxx::Number>("online")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"owid\":"<< this->l.owid() << ",";
ss << "\"no\":"<< "\"" << this->l.no() << "\"" << ",";
ss << "\"nickname\":"<< "\"" << this->l.nickname() << "\"" << ",";
ss << "\"name\":"<< "\"" << this->l.name() << "\"" << ",";
ss << "\"online\":"<< this->l.online();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::LplRecommandRoomEndingPopupNotifyItem l;
    };
}
#endif //DANMU_CORE_LPL_RECOMMAND_ROOM_ENDING_POPUP_NOTIFY_ITEM_H