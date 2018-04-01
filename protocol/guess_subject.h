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

#ifndef DANMU_CORE_GUESS_SUBJECT_H
#define DANMU_CORE_GUESS_SUBJECT_H

#include "protobuf.h"
#include "guess_item.h"

namespace protocol {
    class Guess_subject : public Protocol {
    public:
        Guess_subject() : g(linkerProtocol::GuessSubject()) {};

        explicit Guess_subject(const linkerProtocol::GuessSubject &us) : g(us) {};

        const linkerProtocol::GuessSubject &get_guess_subject() const { return this->g; }

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

            if (o.has<jsonxx::Number>("status")) {
                this->g.set_status(int32_t(o.get<jsonxx::Number>("status")));
            }

            if (o.has<jsonxx::String>("reason")) {
                this->g.set_reason((o.get<jsonxx::String>("reason")));
            }

            if (o.has<jsonxx::Number>("endTime")) {
                this->g.set_endtime(int32_t(o.get<jsonxx::Number>("endTime")));
            }

            if (o.has<jsonxx::Array>("items")) {
                auto gs = o.get<jsonxx::Array>("items");
                for (size_t i = 0; i < gs.size(); i++) {
                    auto j = gs.get<jsonxx::Object>(i);
                    Guess_item k;
                    k.from_json(j);
                    uint8_t buf[k.get_guess_item().ByteSize()];
                    k.get_guess_item().SerializeToArray(buf, k.get_guess_item().ByteSize());

                    auto m = this->g.add_items();
                    m->ParseFromArray(buf, k.get_guess_item().ByteSize());
                }
            }

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
            ss << "{";
            ss << "\"guessID\":" << this->g.guessid() << ",";
            ss << "\"title\":" << "\"" << this->g.title() << "\"" << ",";
            ss << "\"status\":" << this->g.status() << ",";
            ss << "\"reason\":" << "\"" << this->g.reason() << "\"" << ",";
            ss << "\"endTime\":" << this->g.endtime() << ",";

            std::stringstream items_stream;
            items_stream << "[";
            for (int32_t i = 0; i < this->g.items_size(); i++) {
                items_stream << Guess_item(this->g.items(i)).to_jsonstr();
                if (i != this->g.items_size() - 1) {
                    items_stream << ",";
                }
            }
            items_stream << "]";
            ss << "\"items\":" << items_stream.str();
            ss << "}";
            return ss.str();

        }

    private:
        linkerProtocol::GuessSubject g;
    };
}
#endif //DANMU_CORE_GUESS_SUBJECT_H