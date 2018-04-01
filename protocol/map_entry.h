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

#ifndef DANMU_CORE_MAP_ENTRY_H
#define DANMU_CORE_MAP_ENTRY_H

#include "protobuf.h"

namespace protocol {
    class Map_entry : public Protocol {
    public:
        Map_entry() : m(linkerProtocol::MapEntry()) {};

        explicit Map_entry(const linkerProtocol::MapEntry &us) : m(us) {};

        const linkerProtocol::MapEntry &get_map_entry() const { return this->m; }

        virtual bool decode_from_buf(Buffer &buf) {
            return this->m.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr <Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->m.ByteSize()];
            this->m.SerializeToArray(ptr, this->m.ByteSize());
            return std::make_shared<Buffer>(ptr, this->m.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if (o.has<jsonxx::String>("key")) {
                this->m.set_key((o.get<jsonxx::String>("key")));
            }

            if (o.has<jsonxx::String>("value")) {
                this->m.set_value((o.get<jsonxx::String>("value")));
            }

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
            ss << "{";
            ss << "\"key\":" << "\"" << this->m.key() << "\"" << ",";
            ss << "\"value\":" << "\"" << this->m.value() << "\"";
            ss << "}";
            return ss.str();

        }

    private:
        linkerProtocol::MapEntry m;
    };
}
#endif //DANMU_CORE_MAP_ENTRY_H