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

#ifndef DANMU_CORE_OPTION_DETAIL_H
#define DANMU_CORE_OPTION_DETAIL_H

#include "protobuf.h"

namespace protocol {
    class OptionDetail : public Protocol {
    public:
        OptionDetail() : o(linkerProtocol::OptionDetail()) {};
        explicit OptionDetail(const linkerProtocol::OptionDetail &us) : o(us) {};
        const linkerProtocol::OptionDetail &get_option_detail() const { return this->o; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->o.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->o.ByteSize()];
            this->o.SerializeToArray(ptr, this->o.ByteSize());
            return std::make_shared<Buffer>(ptr, this->o.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::String>("info")) {
	this->o.set_info((o.get<jsonxx::String>("info")));
}

if(o.has<jsonxx::Number>("optionId")) {
	this->o.set_optionid(int32_t(o.get<jsonxx::Number>("optionId")));
}

if(o.has<jsonxx::Number>("num")) {
	this->o.set_num(int32_t(o.get<jsonxx::Number>("num")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"info\":"<< "\"" << this->o.info() << "\"" << ",";
ss << "\"optionId\":"<< this->o.optionid() << ",";
ss << "\"num\":"<< this->o.num();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::OptionDetail o;
    };
}
#endif //DANMU_CORE_OPTION_DETAIL_H