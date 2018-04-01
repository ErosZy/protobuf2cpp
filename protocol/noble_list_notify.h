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

#ifndef DANMU_CORE_NOBLE_LIST_NOTIFY_H
#define DANMU_CORE_NOBLE_LIST_NOTIFY_H

#include "protobuf.h"
#include "user.h"

namespace protocol {
    class Noble_list_notify : public Protocol {
    public:
        Noble_list_notify() : n(linkerProtocol::NobleListNotify()) {};
        explicit Noble_list_notify(const linkerProtocol::NobleListNotify &us) : n(us) {};
        const linkerProtocol::NobleListNotify &get_noble_list_notify() const { return this->n; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->n.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->n.ByteSize()];
            this->n.SerializeToArray(ptr, this->n.ByteSize());
            return std::make_shared<Buffer>(ptr, this->n.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::Number>("owid")) {
	this->n.set_owid(int32_t(o.get<jsonxx::Number>("owid")));
}

if(o.has<jsonxx::Number>("noblemanCount")) {
	this->n.set_noblemancount(int32_t(o.get<jsonxx::Number>("noblemanCount")));
}

if (o.has<jsonxx::Array>("noblemanList")) {
	auto us = o.get<jsonxx::Array>("noblemanList");
	for (size_t i = 0; i < us.size(); i++) {
		auto j = us.get<jsonxx::Object>(i);
		User k;
		k.from_json(j);
		uint8_t buf[k.get_user().ByteSize()];
		k.get_user().SerializeToArray(buf, k.get_user().ByteSize());

		auto m = this->n.add_noblemanlist();
		m->ParseFromArray(buf, k.get_user().ByteSize());
	}
}

if(o.has<jsonxx::Number>("ts")) {
	this->n.set_ts(int32_t(o.get<jsonxx::Number>("ts")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"owid\":"<< this->n.owid() << ",";
ss << "\"noblemanCount\":"<< this->n.noblemancount() << ",";

std::stringstream noblemanlist_stream;
noblemanlist_stream << "[";
for (int32_t i = 0; i < this->n.noblemanlist_size(); i++) {
	noblemanlist_stream << User(this->n.noblemanlist(i)).to_jsonstr();
	if (i != this->n.noblemanlist_size() - 1) {
		noblemanlist_stream << ",";
	}
}
noblemanlist_stream << "]";
ss << "\"noblemanList\":" << noblemanlist_stream.str() << ",";
ss << "\"ts\":"<< this->n.ts();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::NobleListNotify n;
    };
}
#endif //DANMU_CORE_NOBLE_LIST_NOTIFY_H