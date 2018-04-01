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

#ifndef DANMU_CORE_GUESS_WIN_H
#define DANMU_CORE_GUESS_WIN_H

#include "protobuf.h"
#include "guess_award.h"

namespace protocol {
    class Guess_win : public Protocol {
    public:
        Guess_win() : g(linkerProtocol::GuessWin()) {};

        explicit Guess_win(const linkerProtocol::GuessWin &us) : g(us) {};

        const linkerProtocol::GuessWin &get_guess_win() const { return this->g; }

        virtual bool decode_from_buf(Buffer &buf) {
            return this->g.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr <Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->g.ByteSize()];
            this->g.SerializeToArray(ptr, this->g.ByteSize());
            return std::make_shared<Buffer>(ptr, this->g.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if (o.has<jsonxx::Number>("uid")) {
                this->g.set_uid(int32_t(o.get<jsonxx::Number>("uid")));
            }

            if (o.has<jsonxx::Number>("owid")) {
                this->g.set_owid(int32_t(o.get<jsonxx::Number>("owid")));
            }

            if (o.has<jsonxx::Array>("awards")) {
                auto gs = o.get<jsonxx::Array>("awards");
                for (size_t i = 0; i < gs.size(); i++) {
                    auto j = gs.get<jsonxx::Object>(i);
                    Guess_award k;
                    k.from_json(j);
                    uint8_t buf[k.get_guess_award().ByteSize()];
                    k.get_guess_award().SerializeToArray(buf, k.get_guess_award().ByteSize());

                    auto m = this->g.add_awards();
                    m->ParseFromArray(buf, k.get_guess_award().ByteSize());
                }
            }

            if (o.has<jsonxx::Number>("chips")) {
                this->g.set_chips(int32_t(o.get<jsonxx::Number>("chips")));
            }

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
            ss << "{";
            ss << "\"uid\":" << this->g.uid() << ",";
            ss << "\"owid\":" << this->g.owid() << ",";

            std::stringstream awards_stream;
            awards_stream << "[";
            for (int32_t i = 0; i < this->g.awards_size(); i++) {
                awards_stream << Guess_award(this->g.awards(i)).to_jsonstr();
                if (i != this->g.awards_size() - 1) {
                    awards_stream << ",";
                }
            }
            awards_stream << "]";
            ss << "\"awards\":" << awards_stream.str() << ",";
            ss << "\"chips\":" << this->g.chips();
            ss << "}";
            return ss.str();

        }

    private:
        linkerProtocol::GuessWin g;
    };
}
#endif //DANMU_CORE_GUESS_WIN_H