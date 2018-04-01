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

#ifndef DANMU_CORE_DOUBLE_ELEVEN_LOTTERY_PRIZE_LIST_H
#define DANMU_CORE_DOUBLE_ELEVEN_LOTTERY_PRIZE_LIST_H

#include "protobuf.h"

namespace protocol {
    class Double_eleven_lottery_prize_list : public Protocol {
    public:
        Double_eleven_lottery_prize_list() : d(linkerProtocol::DoubleElevenLotteryPrizeList()) {};

        explicit Double_eleven_lottery_prize_list(const linkerProtocol::DoubleElevenLotteryPrizeList &us) : d(us) {};

        const linkerProtocol::DoubleElevenLotteryPrizeList &
        get_double_eleven_lottery_prize_list() const { return this->d; }

        virtual bool decode_from_buf(Buffer &buf) {
            return this->d.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr <Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->d.ByteSize()];
            this->d.SerializeToArray(ptr, this->d.ByteSize());
            return std::make_shared<Buffer>(ptr, this->d.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if (o.has<jsonxx::String>("prizeName")) {
                this->d.set_prizename((o.get<jsonxx::String>("prizeName")));
            }

            if (o.has<jsonxx::String>("userName")) {
                this->d.set_username((o.get<jsonxx::String>("userName")));
            }

            if (o.has<jsonxx::Number>("uid")) {
                this->d.set_uid(int32_t(o.get<jsonxx::Number>("uid")));
            }

            if (o.has<jsonxx::String>("time")) {
                this->d.set_time((o.get<jsonxx::String>("time")));
            }

            if (o.has<jsonxx::Number>("propNum")) {
                this->d.set_propnum(int32_t(o.get<jsonxx::Number>("propNum")));
            }

            if (o.has<jsonxx::String>("prizeId")) {
                this->d.set_prizeid((o.get<jsonxx::String>("prizeId")));
            }

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
            ss << "{";
            ss << "\"prizeName\":" << "\"" << this->d.prizename() << "\"" << ",";
            ss << "\"userName\":" << "\"" << this->d.username() << "\"" << ",";
            ss << "\"uid\":" << this->d.uid() << ",";
            ss << "\"time\":" << "\"" << this->d.time() << "\"" << ",";
            ss << "\"propNum\":" << this->d.propnum() << ",";
            ss << "\"prizeId\":" << "\"" << this->d.prizeid() << "\"";
            ss << "}";
            return ss.str();

        }

    private:
        linkerProtocol::DoubleElevenLotteryPrizeList d;
    };
}
#endif //DANMU_CORE_DOUBLE_ELEVEN_LOTTERY_PRIZE_LIST_H