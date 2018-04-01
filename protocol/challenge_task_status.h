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

#ifndef DANMU_CORE_CHALLENGE_TASK_STATUS_H
#define DANMU_CORE_CHALLENGE_TASK_STATUS_H

#include "protobuf.h"
#include "challenge_task.h"
#include "user.h"

namespace protocol {
    class ChallengeTaskStatus : public Protocol {
    public:
        ChallengeTaskStatus() : c(linkerProtocol::ChallengeTaskStatus()) {};
        explicit ChallengeTaskStatus(const linkerProtocol::ChallengeTaskStatus &us) : c(us) {};
        const linkerProtocol::ChallengeTaskStatus &get_challenge_task_status() const { return this->c; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->c.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->c.ByteSize()];
            this->c.SerializeToArray(ptr, this->c.ByteSize());
            return std::make_shared<Buffer>(ptr, this->c.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::Number>("owid")) {
	this->c.set_owid(int32_t(o.get<jsonxx::Number>("owid")));
}

if(o.has<jsonxx::Number>("replayId")) {
	this->c.set_replayid(int32_t(o.get<jsonxx::Number>("replayId")));
}

if(o.has<jsonxx::Number>("startTime")) {
	this->c.set_starttime(int32_t(o.get<jsonxx::Number>("startTime")));
}

if(o.has<jsonxx::Number>("times")) {
	this->c.set_times(int32_t(o.get<jsonxx::Number>("times")));
}

if(o.has<jsonxx::Number>("status")) {
	this->c.set_status(int32_t(o.get<jsonxx::Number>("status")));
}

if (o.has<jsonxx::Array>("ChallengeTaskList")) {
	auto cs = o.get<jsonxx::Array>("ChallengeTaskList");
	for (size_t i = 0; i < cs.size(); i++) {
		auto j = cs.get<jsonxx::Object>(i);
		ChallengeTask k;
		k.from_json(j);
		uint8_t buf[k.get_challenge_task().ByteSize()];
		k.get_challenge_task().SerializeToArray(buf, k.get_challenge_task().ByteSize());

		auto m = this->c.add_challengetasklist();
		m->ParseFromArray(buf, k.get_challenge_task().ByteSize());
	}
}

if (o.has<jsonxx::Object>("user")) {
	jsonxx::Object info = o.get<jsonxx::Object>("user");
	User u;
	u.from_json(info);

	auto _u = new linkerProtocol::User();
	uint8_t buf[_u.get_user().ByteSize()];
	_u.get_user().SerializeToArray(buf, n.get_user().ByteSize());
	_u->ParseFromArray(buf, _u.get_user().ByteSize());
	this->c.set_allocated_user(_u);
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"owid\":"<< this->c.owid() << ",";
ss << "\"replayId\":"<< this->c.replayid() << ",";
ss << "\"startTime\":"<< this->c.starttime() << ",";
ss << "\"times\":"<< this->c.times() << ",";
ss << "\"status\":"<< this->c.status() << ",";
std::stringstream challengetasklist_stream;
challengetasklist_stream << "[";
for (int32_t i = 0; i < this->c.challengetasklist_size(); i++) {
	challengetasklist_stream << ChallengeTask(this->c.challengetasklist(i)).to_jsonstr();
	if (i != this->c.challengetasklist_size() - 1) {
		challengetasklist_stream << ",";
	}
}
challengetasklist_stream << "]"; << ",";
User u(this->c.user());
ss << ""user":" << u.to_jsonstr();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::ChallengeTaskStatus c;
    };
}
#endif //DANMU_CORE_CHALLENGE_TASK_STATUS_H