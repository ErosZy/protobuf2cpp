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

#ifndef DANMU_CORE_VOTE_NOTIFY_H
#define DANMU_CORE_VOTE_NOTIFY_H

#include "protobuf.h"
#include "option_detail.h"

namespace protocol {
    class Vote_notify : public Protocol {
    public:
        Vote_notify() : v(linkerProtocol::VoteNotify()) {};
        explicit Vote_notify(const linkerProtocol::VoteNotify &us) : v(us) {};
        const linkerProtocol::VoteNotify &get_vote_notify() const { return this->v; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->v.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->v.ByteSize()];
            this->v.SerializeToArray(ptr, this->v.ByteSize());
            return std::make_shared<Buffer>(ptr, this->v.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::Number>("owid")) {
	this->v.set_owid(int32_t(o.get<jsonxx::Number>("owid")));
}

if(o.has<jsonxx::Number>("voteId")) {
	this->v.set_voteid(int32_t(o.get<jsonxx::Number>("voteId")));
}

if(o.has<jsonxx::String>("title")) {
	this->v.set_title((o.get<jsonxx::String>("title")));
}

if(o.has<jsonxx::Number>("uid")) {
	this->v.set_uid(int32_t(o.get<jsonxx::Number>("uid")));
}

if(o.has<jsonxx::Number>("status")) {
	this->v.set_status(int32_t(o.get<jsonxx::Number>("status")));
}

if(o.has<jsonxx::Number>("isShow")) {
	this->v.set_isshow(int32_t(o.get<jsonxx::Number>("isShow")));
}

if(o.has<jsonxx::Number>("startTime")) {
	this->v.set_starttime(int32_t(o.get<jsonxx::Number>("startTime")));
}

if(o.has<jsonxx::Number>("endTime")) {
	this->v.set_endtime(int32_t(o.get<jsonxx::Number>("endTime")));
}

if (o.has<jsonxx::Array>("options")) {
	auto os = o.get<jsonxx::Array>("options");
	for (size_t i = 0; i < os.size(); i++) {
		auto j = os.get<jsonxx::Object>(i);
		Option_detail k;
		k.from_json(j);
		uint8_t buf[k.get_option_detail().ByteSize()];
		k.get_option_detail().SerializeToArray(buf, k.get_option_detail().ByteSize());

		auto m = this->v.add_options();
		m->ParseFromArray(buf, k.get_option_detail().ByteSize());
	}
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"owid\":"<< this->v.owid() << ",";
ss << "\"voteId\":"<< this->v.voteid() << ",";
ss << "\"title\":"<< "\"" << this->v.title() << "\"" << ",";
ss << "\"uid\":"<< this->v.uid() << ",";
ss << "\"status\":"<< this->v.status() << ",";
ss << "\"isShow\":"<< this->v.isshow() << ",";
ss << "\"startTime\":"<< this->v.starttime() << ",";
ss << "\"endTime\":"<< this->v.endtime() << ",";

std::stringstream options_stream;
options_stream << "[";
for (int32_t i = 0; i < this->v.options_size(); i++) {
	options_stream << Option_detail(this->v.options(i)).to_jsonstr();
	if (i != this->v.options_size() - 1) {
		options_stream << ",";
	}
}
options_stream << "]";
ss << "\"options\":" << options_stream.str();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::VoteNotify v;
    };
}
#endif //DANMU_CORE_VOTE_NOTIFY_H