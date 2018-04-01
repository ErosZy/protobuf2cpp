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

#ifndef DANMU_CORE_DOUBLE_ELEVEN_LOTTERY_SEND_NOTIFY_H
#define DANMU_CORE_DOUBLE_ELEVEN_LOTTERY_SEND_NOTIFY_H

#include "protobuf.h"

namespace protocol {
    class DoubleElevenLotterySendNotify : public Protocol {
    public:
        DoubleElevenLotterySendNotify() : d(linkerProtocol::DoubleElevenLotterySendNotify()) {};
        explicit DoubleElevenLotterySendNotify(const linkerProtocol::DoubleElevenLotterySendNotify &us) : d(us) {};
        const linkerProtocol::DoubleElevenLotterySendNotify &get_double_eleven_lottery_send_notify() const { return this->d; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->d.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->d.ByteSize()];
            this->d.SerializeToArray(ptr, this->d.ByteSize());
            return std::make_shared<Buffer>(ptr, this->d.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::Number>("owid")) {
	this->d.set_owid(int32_t(o.get<jsonxx::Number>("owid")));
}

if(o.has<jsonxx::Number>("drawNum")) {
	this->d.set_drawnum(int32_t(o.get<jsonxx::Number>("drawNum")));
}

if(o.has<jsonxx::Number>("diffProp")) {
	this->d.set_diffprop(int32_t(o.get<jsonxx::Number>("diffProp")));
}

if(o.has<jsonxx::Number>("propNum")) {
	this->d.set_propnum(int32_t(o.get<jsonxx::Number>("propNum")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"owid\":"<< this->d.owid() << ",";
ss << "\"drawNum\":"<< this->d.drawnum() << ",";
ss << "\"diffProp\":"<< this->d.diffprop() << ",";
ss << "\"propNum\":"<< this->d.propnum();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::DoubleElevenLotterySendNotify d;
    };
}
#endif //DANMU_CORE_DOUBLE_ELEVEN_LOTTERY_SEND_NOTIFY_H