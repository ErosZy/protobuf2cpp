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

#ifndef DANMU_CORE_GUESS_UPDATE_H
#define DANMU_CORE_GUESS_UPDATE_H

#include "protobuf.h"
#include "guess_subject.h"

namespace protocol {
    class Guess_update : public Protocol {
    public:
        Guess_update() : g(linkerProtocol::GuessUpdate()) {};

        explicit Guess_update(const linkerProtocol::GuessUpdate &us) : g(us) {};

        const linkerProtocol::GuessUpdate &get_guess_update() const { return this->g; }

        virtual bool decode_from_buf(Buffer &buf) {
            return this->g.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr <Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->g.ByteSize()];
            this->g.SerializeToArray(ptr, this->g.ByteSize());
            return std::make_shared<Buffer>(ptr, this->g.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if (o.has<jsonxx::Number>("owid")) {
                this->g.set_owid(int32_t(o.get<jsonxx::Number>("owid")));
            }

            if (o.has<jsonxx::Array>("subjects")) {
                auto gs = o.get<jsonxx::Array>("subjects");
                for (size_t i = 0; i < gs.size(); i++) {
                    auto j = gs.get<jsonxx::Object>(i);
                    Guess_subject k;
                    k.from_json(j);
                    uint8_t buf[k.get_guess_subject().ByteSize()];
                    k.get_guess_subject().SerializeToArray(buf, k.get_guess_subject().ByteSize());

                    auto m = this->g.add_subjects();
                    m->ParseFromArray(buf, k.get_guess_subject().ByteSize());
                }
            }

            if (o.has<jsonxx::Number>("nowTime")) {
                this->g.set_nowtime(int32_t(o.get<jsonxx::Number>("nowTime")));
            }

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
            ss << "{";
            ss << "\"owid\":" << this->g.owid() << ",";

            std::stringstream subjects_stream;
            subjects_stream << "[";
            for (int32_t i = 0; i < this->g.subjects_size(); i++) {
                subjects_stream << Guess_subject(this->g.subjects(i)).to_jsonstr();
                if (i != this->g.subjects_size() - 1) {
                    subjects_stream << ",";
                }
            }
            subjects_stream << "]";
            ss << "\"subjects\":" << subjects_stream.str() << ",";
            ss << "\"nowTime\":" << this->g.nowtime();
            ss << "}";
            return ss.str();

        }

    private:
        linkerProtocol::GuessUpdate g;
    };
}
#endif //DANMU_CORE_GUESS_UPDATE_H