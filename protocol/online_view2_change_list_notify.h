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

#ifndef DANMU_CORE_ONLINE_VIEW2_CHANGE_LIST_NOTIFY_H
#define DANMU_CORE_ONLINE_VIEW2_CHANGE_LIST_NOTIFY_H

#include "protobuf.h"
#include "online_view2_change_notify.h"

namespace protocol {
    class OnlineView2ChangeListNotify : public Protocol {
    public:
        OnlineView2ChangeListNotify() : o(linkerProtocol::OnlineView2ChangeListNotify()) {};
        explicit OnlineView2ChangeListNotify(const linkerProtocol::OnlineView2ChangeListNotify &us) : o(us) {};
        const linkerProtocol::OnlineView2ChangeListNotify &get_online_view2_change_list_notify() const { return this->o; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->o.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->o.ByteSize()];
            this->o.SerializeToArray(ptr, this->o.ByteSize());
            return std::make_shared<Buffer>(ptr, this->o.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            if (o.has<jsonxx::Array>("changeList")) {
	auto os = o.get<jsonxx::Array>("changeList");
	for (size_t i = 0; i < os.size(); i++) {
		auto j = os.get<jsonxx::Object>(i);
		OnlineView2ChangeNotify k;
		k.from_json(j);
		uint8_t buf[k.get_online_view2_change_notify().ByteSize()];
		k.get_online_view2_change_notify().SerializeToArray(buf, k.get_online_view2_change_notify().ByteSize());

		auto m = this->o.add_changelist();
		m->ParseFromArray(buf, k.get_online_view2_change_notify().ByteSize());
	}
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";

std::stringstream changelist_stream;
changelist_stream << "[";
for (int32_t i = 0; i < this->o.changelist_size(); i++) {
	changelist_stream << OnlineView2ChangeNotify(this->o.changelist(i)).to_jsonstr();
	if (i != this->o.changelist_size() - 1) {
		changelist_stream << ",";
	}
}
changelist_stream << "]";
ss << "\"changeList\":" << changelist_stream.str();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::OnlineView2ChangeListNotify o;
    };
}
#endif //DANMU_CORE_ONLINE_VIEW2_CHANGE_LIST_NOTIFY_H