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

#ifndef DANMU_CORE_CHALLENGE_BET_H
#define DANMU_CORE_CHALLENGE_BET_H

#include "protobuf.h"
#include "user.h"
#include "challenge_task.h"

namespace protocol {
    class ChallengeBet : public Protocol {
    public:
        ChallengeBet() : c(linkerProtocol::ChallengeBet()) {};
        explicit ChallengeBet(const linkerProtocol::ChallengeBet &us) : c(us) {};
        const linkerProtocol::ChallengeBet &get_challenge_bet() const { return this->c; }
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

if (o.has<jsonxx::Object>("User")) {
	jsonxx::Object info = o.get<jsonxx::Object>("User");
	User u;
	u.from_json(info);

	auto _u = new linkerProtocol::User();
	uint8_t buf[_u.get_user().ByteSize()];
	_u.get_user().SerializeToArray(buf, n.get_user().ByteSize());
	_u->ParseFromArray(buf, _u.get_user().ByteSize());
	this->c.set_allocated_user(_u);
}

if(o.has<jsonxx::Number>("amount")) {
	this->c.set_amount(int32_t(o.get<jsonxx::Number>("amount")));
}

if(o.has<jsonxx::Number>("taskId")) {
	this->c.set_taskid(int32_t(o.get<jsonxx::Number>("taskId")));
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

if(o.has<jsonxx::Number>("combo")) {
	this->c.set_combo(int32_t(o.get<jsonxx::Number>("combo")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"owid\":"<< this->c.owid() << ",";
ss << "\"replayId\":"<< this->c.replayid() << ",";
User u(this->c.user());
ss << ""User":" << u.to_jsonstr() << ",";
ss << "\"amount\":"<< this->c.amount() << ",";
ss << "\"taskId\":"<< this->c.taskid() << ",";
std::stringstream challengetasklist_stream;
challengetasklist_stream << "[";
for (int32_t i = 0; i < this->c.challengetasklist_size(); i++) {
	challengetasklist_stream << ChallengeTask(this->c.challengetasklist(i)).to_jsonstr();
	if (i != this->c.challengetasklist_size() - 1) {
		challengetasklist_stream << ",";
	}
}
challengetasklist_stream << "]"; << ",";
ss << "\"combo\":"<< this->c.combo();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::ChallengeBet c;
    };
}
#endif //DANMU_CORE_CHALLENGE_BET_H