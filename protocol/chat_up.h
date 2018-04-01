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

#ifndef DANMU_CORE_CHAT_UP_H
#define DANMU_CORE_CHAT_UP_H

#include "protobuf.h"
#include "user.h"
#include "text_attribe.h"

namespace protocol {
    class Chat_up : public Protocol {
    public:
        Chat_up() : c(linkerProtocol::ChatUp()) {};

        explicit Chat_up(const linkerProtocol::ChatUp &us) : c(us) {};

        const linkerProtocol::ChatUp &get_chat_up() const { return this->c; }

        virtual bool decode_from_buf(Buffer &buf) {
            return this->c.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr <Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->c.ByteSize()];
            this->c.SerializeToArray(ptr, this->c.ByteSize());
            return std::make_shared<Buffer>(ptr, this->c.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if (o.has<jsonxx::Number>("type")) {
                this->c.set_type(int32_t(o.get<jsonxx::Number>("type")));
            }

            if (o.has<jsonxx::String>("txt")) {
                this->c.set_txt((o.get<jsonxx::String>("txt")));
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

            if (o.has<jsonxx::Number>("color")) {
                this->c.set_color(int32_t(o.get<jsonxx::Number>("color")));
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

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
            ss << "{";
            ss << "\"type\":" << this->c.type() << ",";
            ss << "\"txt\":" << "\"" << this->c.txt() << "\"" << ",";

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
            ss << "\"color\":" << this->c.color() << ",";

            Text_attribe t_4(this->c.textattr());
            ss << "\"textAttr\":" << t_4.to_jsonstr() << ",";
            ss << "\"asNobleman\":" << this->c.asnobleman();
            ss << "}";
            return ss.str();

        }

    private:
        linkerProtocol::ChatUp c;
    };
}
#endif //DANMU_CORE_CHAT_UP_H