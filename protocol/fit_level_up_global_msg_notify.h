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

#ifndef DANMU_CORE_FIT_LEVEL_UP_GLOBAL_MSG_NOTIFY_H
#define DANMU_CORE_FIT_LEVEL_UP_GLOBAL_MSG_NOTIFY_H

#include "protobuf.h"
#include "client_type_map.h"

namespace protocol {
    class FitLevelUpGlobalMsgNotify : public Protocol {
    public:
        FitLevelUpGlobalMsgNotify() : f(linkerProtocol::FitLevelUpGlobalMsgNotify()) {};
        explicit FitLevelUpGlobalMsgNotify(const linkerProtocol::FitLevelUpGlobalMsgNotify &us) : f(us) {};
        const linkerProtocol::FitLevelUpGlobalMsgNotify &get_fit_level_up_global_msg_notify() const { return this->f; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->f.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->f.ByteSize()];
            this->f.SerializeToArray(ptr, this->f.ByteSize());
            return std::make_shared<Buffer>(ptr, this->f.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::Number>("uid")) {
	this->f.set_uid(int32_t(o.get<jsonxx::Number>("uid")));
}

if(o.has<jsonxx::String>("nickname")) {
	this->f.set_nickname((o.get<jsonxx::String>("nickname")));
}

if(o.has<jsonxx::Number>("owid")) {
	this->f.set_owid(int32_t(o.get<jsonxx::Number>("owid")));
}

if(o.has<jsonxx::Number>("level")) {
	this->f.set_level(int32_t(o.get<jsonxx::Number>("level")));
}

if(o.has<jsonxx::String>("name")) {
	this->f.set_name((o.get<jsonxx::String>("name")));
}

if (o.has<jsonxx::Object>("targetMap")) {
	jsonxx::Object info = o.get<jsonxx::Object>("targetMap");
	Client_type_map c;
	c.from_json(info);

	auto _c = new linkerProtocol::ClientTypeMap();
	uint8_t buf[_c.get_client_type_map().ByteSize()];
	_c.get_client_type_map().SerializeToArray(buf, n.get_client_type_map().ByteSize());
	_c->ParseFromArray(buf, _c.get_client_type_map().ByteSize());
	this->f.set_allocated_targetmap(_c);
}

if(o.has<jsonxx::String>("validTime")) {
	this->f.set_validtime((o.get<jsonxx::String>("validTime")));
}

if(o.has<jsonxx::Number>("number")) {
	this->f.set_number(int32_t(o.get<jsonxx::Number>("number")));
}

if(o.has<jsonxx::String>("owNickName")) {
	this->f.set_ownickname((o.get<jsonxx::String>("owNickName")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"uid\":"<< this->f.uid() << ",";
ss << "\"nickname\":"<< "\"" << this->f.nickname() << "\"" << ",";
ss << "\"owid\":"<< this->f.owid() << ",";
ss << "\"level\":"<< this->f.level() << ",";
ss << "\"name\":"<< "\"" << this->f.name() << "\"" << ",";
Client_type_map c(this->f.targetmap());
ss << ""targetMap":" << c.to_jsonstr() << ",";
ss << "\"validTime\":"<< "\"" << this->f.validtime() << "\"" << ",";
ss << "\"number\":"<< this->f.number() << ",";
ss << "\"owNickName\":"<< "\"" << this->f.ownickname() << "\"";
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::FitLevelUpGlobalMsgNotify f;
    };
}
#endif //DANMU_CORE_FIT_LEVEL_UP_GLOBAL_MSG_NOTIFY_H