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

#ifndef DANMU_CORE_CHALLENGE_TASK_H
#define DANMU_CORE_CHALLENGE_TASK_H

#include "protobuf.h"

namespace protocol {
    class Challenge_task : public Protocol {
    public:
        Challenge_task() : c(linkerProtocol::ChallengeTask()) {};

        explicit Challenge_task(const linkerProtocol::ChallengeTask &us) : c(us) {};

        const linkerProtocol::ChallengeTask &get_challenge_task() const { return this->c; }

        virtual bool decode_from_buf(Buffer &buf) {
            return this->c.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr <Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->c.ByteSize()];
            this->c.SerializeToArray(ptr, this->c.ByteSize());
            return std::make_shared<Buffer>(ptr, this->c.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if (o.has<jsonxx::Number>("taskId")) {
                this->c.set_taskid(int32_t(o.get<jsonxx::Number>("taskId")));
            }

            if (o.has<jsonxx::Number>("amount")) {
                this->c.set_amount(int32_t(o.get<jsonxx::Number>("amount")));
            }

            if (o.has<jsonxx::Number>("val")) {
                this->c.set_val(int32_t(o.get<jsonxx::Number>("val")));
            }

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
            ss << "{";
            ss << "\"taskId\":" << this->c.taskid() << ",";
            ss << "\"amount\":" << this->c.amount() << ",";
            ss << "\"val\":" << this->c.val();
            ss << "}";
            return ss.str();

        }

    private:
        linkerProtocol::ChallengeTask c;
    };
}
#endif //DANMU_CORE_CHALLENGE_TASK_H