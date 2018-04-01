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

#ifndef DANMU_CORE_GUESS_ITEM_H
#define DANMU_CORE_GUESS_ITEM_H

#include "protobuf.h"

namespace protocol {
    class GuessItem : public Protocol {
    public:
        GuessItem() : g(linkerProtocol::GuessItem()) {};
        explicit GuessItem(const linkerProtocol::GuessItem &us) : g(us) {};
        const linkerProtocol::GuessItem &get_guess_item() const { return this->g; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->g.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->g.ByteSize()];
            this->g.SerializeToArray(ptr, this->g.ByteSize());
            return std::make_shared<Buffer>(ptr, this->g.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if(o.has<jsonxx::String>("desc")) {
	this->g.set_desc((o.get<jsonxx::String>("desc")));
}

if(o.has<jsonxx::Number>("odd")) {
	this->g.set_odd(float(o.get<jsonxx::Number>("odd")));
}

if(o.has<jsonxx::Number>("stake")) {
	this->g.set_stake(int32_t(o.get<jsonxx::Number>("stake")));
}

if(o.has<jsonxx::Number>("balance")) {
	this->g.set_balance(int32_t(o.get<jsonxx::Number>("balance")));
}

if(o.has<jsonxx::Number>("itemID")) {
	this->g.set_itemid(int32_t(o.get<jsonxx::Number>("itemID")));
}

if(o.has<jsonxx::Boolean>("isWin")) {
	this->g.set_iswin((o.get<jsonxx::Boolean>("isWin")));
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"desc\":"<< "\"" << this->g.desc() << "\"" << ",";
ss << "\"odd\":"<< this->g.odd() << ",";
ss << "\"stake\":"<< this->g.stake() << ",";
ss << "\"balance\":"<< this->g.balance() << ",";
ss << "\"itemID\":"<< this->g.itemid() << ",";
ss << "\"isWin\":"<< this->g.iswin();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::GuessItem g;
    };
}
#endif //DANMU_CORE_GUESS_ITEM_H