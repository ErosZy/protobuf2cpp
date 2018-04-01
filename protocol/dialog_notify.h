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

#ifndef DANMU_CORE_DIALOG_NOTIFY_H
#define DANMU_CORE_DIALOG_NOTIFY_H

#include "protobuf.h"
#include "dialog_button.h"
#include "map_entry.h"

namespace protocol {
    class DialogNotify : public Protocol {
    public:
        DialogNotify() : d(linkerProtocol::DialogNotify()) {};
        explicit DialogNotify(const linkerProtocol::DialogNotify &us) : d(us) {};
        const linkerProtocol::DialogNotify &get_dialog_notify() const { return this->d; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->d.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->d.ByteSize()];
            this->d.SerializeToArray(ptr, this->d.ByteSize());
            return std::make_shared<Buffer>(ptr, this->d.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::Number>("type")) {
	this->d.set_type(int32_t(o.get<jsonxx::Number>("type")));
}

if(o.has<jsonxx::String>("title")) {
	this->d.set_title((o.get<jsonxx::String>("title")));
}

if(o.has<jsonxx::String>("content")) {
	this->d.set_content((o.get<jsonxx::String>("content")));
}

if (o.has<jsonxx::Array>("buttons")) {
	auto ds = o.get<jsonxx::Array>("buttons");
	for (size_t i = 0; i < ds.size(); i++) {
		auto j = ds.get<jsonxx::Object>(i);
		DialogButton k;
		k.from_json(j);
		uint8_t buf[k.get_dialog_button().ByteSize()];
		k.get_dialog_button().SerializeToArray(buf, k.get_dialog_button().ByteSize());

		auto m = this->d.add_buttons();
		m->ParseFromArray(buf, k.get_dialog_button().ByteSize());
	}
}

if (o.has<jsonxx::Array>("paramEntries")) {
	auto ms = o.get<jsonxx::Array>("paramEntries");
	for (size_t i = 0; i < ms.size(); i++) {
		auto j = ms.get<jsonxx::Object>(i);
		MapEntry k;
		k.from_json(j);
		uint8_t buf[k.get_map_entry().ByteSize()];
		k.get_map_entry().SerializeToArray(buf, k.get_map_entry().ByteSize());

		auto m = this->d.add_paramentries();
		m->ParseFromArray(buf, k.get_map_entry().ByteSize());
	}
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"type\":"<< this->d.type() << ",";
ss << "\"title\":"<< "\"" << this->d.title() << "\"" << ",";
ss << "\"content\":"<< "\"" << this->d.content() << "\"" << ",";

std::stringstream buttons_stream;
buttons_stream << "[";
for (int32_t i = 0; i < this->d.buttons_size(); i++) {
	buttons_stream << DialogButton(this->d.buttons(i)).to_jsonstr();
	if (i != this->d.buttons_size() - 1) {
		buttons_stream << ",";
	}
}
buttons_stream << "]";
ss << "\"buttons\":" << buttons_stream.str() << ",";

std::stringstream paramentries_stream;
paramentries_stream << "[";
for (int32_t i = 0; i < this->d.paramentries_size(); i++) {
	paramentries_stream << MapEntry(this->d.paramentries(i)).to_jsonstr();
	if (i != this->d.paramentries_size() - 1) {
		paramentries_stream << ",";
	}
}
paramentries_stream << "]";
ss << "\"paramEntries\":" << paramentries_stream.str();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::DialogNotify d;
    };
}
#endif //DANMU_CORE_DIALOG_NOTIFY_H