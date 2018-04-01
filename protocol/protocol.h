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

#ifndef DANMU_CORE_PROTOCOL_H
#define DANMU_CORE_PROTOCOL_H

#include <memory>
#include <sstream>
#include <cstdint>
#include "jsonxx.h"
#include "proto/gateway.pb.h"
#include "stream/buffer.h"

namespace protocol {
    class Protocol {
    public:
        virtual bool decode_from_buf(Buffer &buf)=0;

        virtual std::shared_ptr<Buffer> encode_to_buf()=0;

        virtual void from_json(jsonxx::Object &json)=0;

        virtual std::string to_jsonstr()=0;
    };
}

#endif //DANMU_CORE_PROTOCOL_H
