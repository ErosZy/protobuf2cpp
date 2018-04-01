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

#ifndef DANMU_CORE_DIALOG_BUTTON_H
#define DANMU_CORE_DIALOG_BUTTON_H

#include "protobuf.h"

namespace protocol {
    class DialogButton : public Protocol {
    public:
        DialogButton() : d(linkerProtocol::DialogButton()) {};
        explicit DialogButton(const linkerProtocol::DialogButton &us) : d(us) {};
        const linkerProtocol::DialogButton &get_dialog_button() const { return this->d; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->d.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->d.ByteSize()];
            this->d.SerializeToArray(ptr, this->d.ByteSize());
            return std::make_shared<Buffer>(ptr, this->d.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::String>("button")) {
	this->d.set_button((o.get<jsonxx::String>("button")));
}

if(o.has<jsonxx::String>("url")) {
	this->d.set_url((o.get<jsonxx::String>("url")));
}

if(o.has<jsonxx::Number>("action")) {
	this->d.set_action(int32_t(o.get<jsonxx::Number>("action")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"button\":"<< "\"" << this->d.button() << "\"" << ",";
ss << "\"url\":"<< "\"" << this->d.url() << "\"" << ",";
ss << "\"action\":"<< this->d.action();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::DialogButton d;
    };
}
#endif //DANMU_CORE_DIALOG_BUTTON_H