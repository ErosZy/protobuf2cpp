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

#ifndef DANMU_CORE_GUESS_OWNER_AWARD_H
#define DANMU_CORE_GUESS_OWNER_AWARD_H

#include "protobuf.h"

namespace protocol {
    class GuessOwnerAward : public Protocol {
    public:
        GuessOwnerAward() : g(linkerProtocol::GuessOwnerAward()) {};
        explicit GuessOwnerAward(const linkerProtocol::GuessOwnerAward &us) : g(us) {};
        const linkerProtocol::GuessOwnerAward &get_guess_owner_award() const { return this->g; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->g.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->g.ByteSize()];
            this->g.SerializeToArray(ptr, this->g.ByteSize());
            return std::make_shared<Buffer>(ptr, this->g.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::Number>("owid")) {
	this->g.set_owid(int32_t(o.get<jsonxx::Number>("owid")));
}

if(o.has<jsonxx::Number>("guessID")) {
	this->g.set_guessid(int32_t(o.get<jsonxx::Number>("guessID")));
}

if(o.has<jsonxx::String>("title")) {
	this->g.set_title((o.get<jsonxx::String>("title")));
}

if(o.has<jsonxx::Number>("award")) {
	this->g.set_award(int32_t(o.get<jsonxx::Number>("award")));
}

if(o.has<jsonxx::Number>("chips")) {
	this->g.set_chips(int32_t(o.get<jsonxx::Number>("chips")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"owid\":"<< this->g.owid() << ",";
ss << "\"guessID\":"<< this->g.guessid() << ",";
ss << "\"title\":"<< "\"" << this->g.title() << "\"" << ",";
ss << "\"award\":"<< this->g.award() << ",";
ss << "\"chips\":"<< this->g.chips();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::GuessOwnerAward g;
    };
}
#endif //DANMU_CORE_GUESS_OWNER_AWARD_H