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

#ifndef DANMU_CORE_GLOBAL_MSG_H
#define DANMU_CORE_GLOBAL_MSG_H

#include "protobuf.h"
#include "ext.h"

namespace protocol {
    class GlobalMsg : public Protocol {
    public:
        GlobalMsg() : g(linkerProtocol::GlobalMsg()) {};
        explicit GlobalMsg(const linkerProtocol::GlobalMsg &us) : g(us) {};
        const linkerProtocol::GlobalMsg &get_global_msg() const { return this->g; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->g.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->g.ByteSize()];
            this->g.SerializeToArray(ptr, this->g.ByteSize());
            return std::make_shared<Buffer>(ptr, this->g.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::Number>("type")) {
	this->g.set_type(int32_t(o.get<jsonxx::Number>("type")));
}

if (o.has<jsonxx::Array>("ext")) {
	auto es = o.get<jsonxx::Array>("ext");
	for (size_t i = 0; i < es.size(); i++) {
		auto j = es.get<jsonxx::Object>(i);
		Ext k;
		k.from_json(j);
		uint8_t buf[k.get_ext().ByteSize()];
		k.get_ext().SerializeToArray(buf, k.get_ext().ByteSize());

		auto m = this->g.add_ext();
		m->ParseFromArray(buf, k.get_ext().ByteSize());
	}
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"type\":"<< this->g.type() << ",";
std::stringstream ext_stream;
ext_stream << "[";
for (int32_t i = 0; i < this->g.ext_size(); i++) {
	ext_stream << Ext(this->g.ext(i)).to_jsonstr();
	if (i != this->g.ext_size() - 1) {
		ext_stream << ",";
	}
}
ext_stream << "]";;
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::GlobalMsg g;
    };
}
#endif //DANMU_CORE_GLOBAL_MSG_H