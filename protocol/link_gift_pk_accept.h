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

#ifndef DANMU_CORE_LINK_GIFT_PK_ACCEPT_H
#define DANMU_CORE_LINK_GIFT_PK_ACCEPT_H

#include "protobuf.h"
#include "user.h"

namespace protocol {
    class Link_gift_pk_accept : public Protocol {
    public:
        Link_gift_pk_accept() : l(linkerProtocol::LinkGiftPkAccept()) {};
        explicit Link_gift_pk_accept(const linkerProtocol::LinkGiftPkAccept &us) : l(us) {};
        const linkerProtocol::LinkGiftPkAccept &get_link_gift_pk_accept() const { return this->l; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->l.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->l.ByteSize()];
            this->l.SerializeToArray(ptr, this->l.ByteSize());
            return std::make_shared<Buffer>(ptr, this->l.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if (o.has<jsonxx::Object>("recipient")) {
	jsonxx::Object info = o.get<jsonxx::Object>("recipient");
	User u;
	u.from_json(info);

	auto _u = new linkerProtocol::User();
	uint8_t buf[u.get_user().ByteSize()];
	u.get_user().SerializeToArray(buf, u.get_user().ByteSize());
	_u->ParseFromArray(buf, u.get_user().ByteSize());
	this->l.set_allocated_recipient(_u);
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";

User u_0(this->l.recipient());
ss << "\"recipient\":" << u_0.to_jsonstr();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::LinkGiftPkAccept l;
    };
}
#endif //DANMU_CORE_LINK_GIFT_PK_ACCEPT_H