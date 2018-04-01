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

#ifndef DANMU_CORE_GUESS_AWARD_H
#define DANMU_CORE_GUESS_AWARD_H

#include "protobuf.h"

namespace protocol {
    class Guess_award : public Protocol {
    public:
        Guess_award() : g(linkerProtocol::GuessAward()) {};

        explicit Guess_award(const linkerProtocol::GuessAward &us) : g(us) {};

        const linkerProtocol::GuessAward &get_guess_award() const { return this->g; }

        virtual bool decode_from_buf(Buffer &buf) {
            return this->g.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr <Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->g.ByteSize()];
            this->g.SerializeToArray(ptr, this->g.ByteSize());
            return std::make_shared<Buffer>(ptr, this->g.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if (o.has<jsonxx::Number>("guessID")) {
                this->g.set_guessid(int32_t(o.get<jsonxx::Number>("guessID")));
            }

            if (o.has<jsonxx::String>("title")) {
                this->g.set_title((o.get<jsonxx::String>("title")));
            }

            if (o.has<jsonxx::String>("desc")) {
                this->g.set_desc((o.get<jsonxx::String>("desc")));
            }

            if (o.has<jsonxx::Number>("award")) {
                this->g.set_award(int32_t(o.get<jsonxx::Number>("award")));
            }

            if (o.has<jsonxx::Number>("status")) {
                this->g.set_status(int32_t(o.get<jsonxx::Number>("status")));
            }

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
            ss << "{";
            ss << "\"guessID\":" << this->g.guessid() << ",";
            ss << "\"title\":" << "\"" << this->g.title() << "\"" << ",";
            ss << "\"desc\":" << "\"" << this->g.desc() << "\"" << ",";
            ss << "\"award\":" << this->g.award() << ",";
            ss << "\"status\":" << this->g.status();
            ss << "}";
            return ss.str();

        }

    private:
        linkerProtocol::GuessAward g;
    };
}
#endif //DANMU_CORE_GUESS_AWARD_H