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

#ifndef DANMU_CORE_CHAT_NOTIFY_H
#define DANMU_CORE_CHAT_NOTIFY_H

#include "protobuf.h"
#include "room_attr.h"
#include "user.h"
#include "user.h"
#include "retetion_attr.h"
#include "text_attribe.h"

namespace protocol {
    class Chat_notify : public Protocol {
    public:
        Chat_notify() : c(linkerProtocol::ChatNotify()) {};

        explicit Chat_notify(const linkerProtocol::ChatNotify &us) : c(us) {};

        const linkerProtocol::ChatNotify &get_chat_notify() const { return this->c; }

        virtual bool decode_from_buf(Buffer &buf) {
            return this->c.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr <Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->c.ByteSize()];
            this->c.SerializeToArray(ptr, this->c.ByteSize());
            return std::make_shared<Buffer>(ptr, this->c.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if (o.has<jsonxx::Number>("owid")) {
                this->c.set_owid(int32_t(o.get<jsonxx::Number>("owid")));
            }

            if (o.has<jsonxx::Object>("roomAttr")) {
                jsonxx::Object info = o.get<jsonxx::Object>("roomAttr");
                Room_attr r;
                r.from_json(info);

                auto _r = new linkerProtocol::RoomAttr();
                uint8_t buf[r.get_room_attr().ByteSize()];
                r.get_room_attr().SerializeToArray(buf, r.get_room_attr().ByteSize());
                _r->ParseFromArray(buf, r.get_room_attr().ByteSize());
                this->c.set_allocated_roomattr(_r);
            }

            if (o.has<jsonxx::Object>("user")) {
                jsonxx::Object info = o.get<jsonxx::Object>("user");
                User u;
                u.from_json(info);

                auto _u = new linkerProtocol::User();
                uint8_t buf[u.get_user().ByteSize()];
                u.get_user().SerializeToArray(buf, u.get_user().ByteSize());
                _u->ParseFromArray(buf, u.get_user().ByteSize());
                this->c.set_allocated_user(_u);
            }

            if (o.has<jsonxx::Number>("type")) {
                this->c.set_type(int32_t(o.get<jsonxx::Number>("type")));
            }

            if (o.has<jsonxx::String>("txt")) {
                this->c.set_txt((o.get<jsonxx::String>("txt")));
            }

            if (o.has<jsonxx::Number>("color")) {
                this->c.set_color(int32_t(o.get<jsonxx::Number>("color")));
            }

            if (o.has<jsonxx::Array>("toUsers")) {
                auto us = o.get<jsonxx::Array>("toUsers");
                for (size_t i = 0; i < us.size(); i++) {
                    auto j = us.get<jsonxx::Object>(i);
                    User k;
                    k.from_json(j);
                    uint8_t buf[k.get_user().ByteSize()];
                    k.get_user().SerializeToArray(buf, k.get_user().ByteSize());

                    auto m = this->c.add_tousers();
                    m->ParseFromArray(buf, k.get_user().ByteSize());
                }
            }

            if (o.has<jsonxx::Object>("retetionAttr")) {
                jsonxx::Object info = o.get<jsonxx::Object>("retetionAttr");
                Retetion_attr r;
                r.from_json(info);

                auto _r = new linkerProtocol::RetetionAttr();
                uint8_t buf[r.get_retetion_attr().ByteSize()];
                r.get_retetion_attr().SerializeToArray(buf, r.get_retetion_attr().ByteSize());
                _r->ParseFromArray(buf, r.get_retetion_attr().ByteSize());
                this->c.set_allocated_retetionattr(_r);
            }

            if (o.has<jsonxx::String>("platForm")) {
                this->c.set_platform((o.get<jsonxx::String>("platForm")));
            }

            if (o.has<jsonxx::Object>("textAttr")) {
                jsonxx::Object info = o.get<jsonxx::Object>("textAttr");
                Text_attribe t;
                t.from_json(info);

                auto _t = new linkerProtocol::TextAttribe();
                uint8_t buf[t.get_text_attribe().ByteSize()];
                t.get_text_attribe().SerializeToArray(buf, t.get_text_attribe().ByteSize());
                _t->ParseFromArray(buf, t.get_text_attribe().ByteSize());
                this->c.set_allocated_textattr(_t);
            }

            if (o.has<jsonxx::Boolean>("asNobleman")) {
                this->c.set_asnobleman((o.get<jsonxx::Boolean>("asNobleman")));
            }

            if (o.has<jsonxx::String>("ver")) {
                this->c.set_ver((o.get<jsonxx::String>("ver")));
            }

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
            ss << "{";
            ss << "\"owid\":" << this->c.owid() << ",";

            Room_attr r_1(this->c.roomattr());
            ss << "\"roomAttr\":" << r_1.to_jsonstr() << ",";

            User u_2(this->c.user());
            ss << "\"user\":" << u_2.to_jsonstr() << ",";
            ss << "\"type\":" << this->c.type() << ",";
            ss << "\"txt\":" << "\"" << this->c.txt() << "\"" << ",";
            ss << "\"color\":" << this->c.color() << ",";

            std::stringstream tousers_stream;
            tousers_stream << "[";
            for (int32_t i = 0; i < this->c.tousers_size(); i++) {
                tousers_stream << User(this->c.tousers(i)).to_jsonstr();
                if (i != this->c.tousers_size() - 1) {
                    tousers_stream << ",";
                }
            }
            tousers_stream << "]";
            ss << "\"toUsers\":" << tousers_stream.str() << ",";

            Retetion_attr r_7(this->c.retetionattr());
            ss << "\"retetionAttr\":" << r_7.to_jsonstr() << ",";
            ss << "\"platForm\":" << "\"" << this->c.platform() << "\"" << ",";

            Text_attribe t_9(this->c.textattr());
            ss << "\"textAttr\":" << t_9.to_jsonstr() << ",";
            ss << "\"asNobleman\":" << this->c.asnobleman() << ",";
            ss << "\"ver\":" << "\"" << this->c.ver() << "\"";
            ss << "}";
            return ss.str();

        }

    private:
        linkerProtocol::ChatNotify c;
    };
}
#endif //DANMU_CORE_CHAT_NOTIFY_H