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

#ifndef DANMU_CORE_BLESSINGBAG_GLOBAL_MSG_NOTIFY_H
#define DANMU_CORE_BLESSINGBAG_GLOBAL_MSG_NOTIFY_H

#include "protobuf.h"
#include "blessingbag_ext.h"

namespace protocol {
    class Blessingbag_global_msg_notify : public Protocol {
    public:
        Blessingbag_global_msg_notify() : b(linkerProtocol::BlessingbagGlobalMsgNotify()) {};
        explicit Blessingbag_global_msg_notify(const linkerProtocol::BlessingbagGlobalMsgNotify &us) : b(us) {};
        const linkerProtocol::BlessingbagGlobalMsgNotify &get_blessingbag_global_msg_notify() const { return this->b; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->b.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->b.ByteSize()];
            this->b.SerializeToArray(ptr, this->b.ByteSize());
            return std::make_shared<Buffer>(ptr, this->b.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::Number>("owid")) {
	this->b.set_owid(int32_t(o.get<jsonxx::Number>("owid")));
}

if (o.has<jsonxx::Array>("ext")) {
	auto bs = o.get<jsonxx::Array>("ext");
	for (size_t i = 0; i < bs.size(); i++) {
		auto j = bs.get<jsonxx::Object>(i);
		Blessingbag_ext k;
		k.from_json(j);
		uint8_t buf[k.get_blessingbag_ext().ByteSize()];
		k.get_blessingbag_ext().SerializeToArray(buf, k.get_blessingbag_ext().ByteSize());

		auto m = this->b.add_ext();
		m->ParseFromArray(buf, k.get_blessingbag_ext().ByteSize());
	}
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"owid\":"<< this->b.owid() << ",";

std::stringstream ext_stream;
ext_stream << "[";
for (int32_t i = 0; i < this->b.ext_size(); i++) {
	ext_stream << Blessingbag_ext(this->b.ext(i)).to_jsonstr();
	if (i != this->b.ext_size() - 1) {
		ext_stream << ",";
	}
}
ext_stream << "]";
ss << "\"ext\":" << ext_stream.str();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::BlessingbagGlobalMsgNotify b;
    };
}
#endif //DANMU_CORE_BLESSINGBAG_GLOBAL_MSG_NOTIFY_H