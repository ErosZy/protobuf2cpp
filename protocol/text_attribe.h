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

#ifndef DANMU_CORE_TEXT_ATTRIBE_H
#define DANMU_CORE_TEXT_ATTRIBE_H

#include "protobuf.h"

namespace protocol {
    class Text_attribe : public Protocol {
    public:
        Text_attribe() : t(linkerProtocol::TextAttribe()) {};
        explicit Text_attribe(const linkerProtocol::TextAttribe &us) : t(us) {};
        const linkerProtocol::TextAttribe &get_text_attribe() const { return this->t; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->t.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->t.ByteSize()];
            this->t.SerializeToArray(ptr, this->t.ByteSize());
            return std::make_shared<Buffer>(ptr, this->t.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::String>("font")) {
	this->t.set_font((o.get<jsonxx::String>("font")));
}

if(o.has<jsonxx::Number>("fontSize")) {
	this->t.set_fontsize(int32_t(o.get<jsonxx::Number>("fontSize")));
}

if(o.has<jsonxx::Number>("color")) {
	this->t.set_color(int32_t(o.get<jsonxx::Number>("color")));
}

if(o.has<jsonxx::Number>("floatStyle")) {
	this->t.set_floatstyle(int32_t(o.get<jsonxx::Number>("floatStyle")));
}

if(o.has<jsonxx::Number>("shading")) {
	this->t.set_shading(int32_t(o.get<jsonxx::Number>("shading")));
}

if(o.has<jsonxx::Number>("payMethod")) {
	this->t.set_paymethod(int32_t(o.get<jsonxx::Number>("payMethod")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"font\":"<< "\"" << this->t.font() << "\"" << ",";
ss << "\"fontSize\":"<< this->t.fontsize() << ",";
ss << "\"color\":"<< this->t.color() << ",";
ss << "\"floatStyle\":"<< this->t.floatstyle() << ",";
ss << "\"shading\":"<< this->t.shading() << ",";
ss << "\"payMethod\":"<< this->t.paymethod();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::TextAttribe t;
    };
}
#endif //DANMU_CORE_TEXT_ATTRIBE_H