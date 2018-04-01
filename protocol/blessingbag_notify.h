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

#ifndef DANMU_CORE_BLESSINGBAG_NOTIFY_H
#define DANMU_CORE_BLESSINGBAG_NOTIFY_H

#include "protobuf.h"
#include "blessingbag_info.h"
#include "blessingbag_info.h"

namespace protocol {
    class BlessingbagNotify : public Protocol {
    public:
        BlessingbagNotify() : b(linkerProtocol::BlessingbagNotify()) {};
        explicit BlessingbagNotify(const linkerProtocol::BlessingbagNotify &us) : b(us) {};
        const linkerProtocol::BlessingbagNotify &get_blessingbag_notify() const { return this->b; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->b.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->b.ByteSize()];
            this->b.SerializeToArray(ptr, this->b.ByteSize());
            return std::make_shared<Buffer>(ptr, this->b.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if (o.has<jsonxx::Object>("liveBag")) {
	jsonxx::Object info = o.get<jsonxx::Object>("liveBag");
	Blessingbag_info b;
	b.from_json(info);

	auto _b = new linkerProtocol::BlessingbagInfo();
	uint8_t buf[_b.get_blessingbag_info().ByteSize()];
	_b.get_blessingbag_info().SerializeToArray(buf, n.get_blessingbag_info().ByteSize());
	_b->ParseFromArray(buf, _b.get_blessingbag_info().ByteSize());
	this->b.set_allocated_livebag(_b);
}

if (o.has<jsonxx::Object>("showBag")) {
	jsonxx::Object info = o.get<jsonxx::Object>("showBag");
	Blessingbag_info b;
	b.from_json(info);

	auto _b = new linkerProtocol::BlessingbagInfo();
	uint8_t buf[_b.get_blessingbag_info().ByteSize()];
	_b.get_blessingbag_info().SerializeToArray(buf, n.get_blessingbag_info().ByteSize());
	_b->ParseFromArray(buf, _b.get_blessingbag_info().ByteSize());
	this->b.set_allocated_showbag(_b);
}

if(o.has<jsonxx::Number>("owid")) {
	this->b.set_owid(int32_t(o.get<jsonxx::Number>("owid")));
}

if(o.has<jsonxx::Number>("uid")) {
	this->b.set_uid(int32_t(o.get<jsonxx::Number>("uid")));
}

if(o.has<jsonxx::String>("message")) {
	this->b.set_message((o.get<jsonxx::String>("message")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";

Blessingbag_info b(this->b.livebag());
ss << "\"liveBag\":" << b.to_jsonstr() << ",";

Blessingbag_info b(this->b.showbag());
ss << "\"showBag\":" << b.to_jsonstr() << ",";
ss << "\"owid\":"<< this->b.owid() << ",";
ss << "\"uid\":"<< this->b.uid() << ",";
ss << "\"message\":"<< "\"" << this->b.message() << "\"";
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::BlessingbagNotify b;
    };
}
#endif //DANMU_CORE_BLESSINGBAG_NOTIFY_H