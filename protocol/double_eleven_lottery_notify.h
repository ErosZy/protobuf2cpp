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

#ifndef DANMU_CORE_DOUBLE_ELEVEN_LOTTERY_NOTIFY_H
#define DANMU_CORE_DOUBLE_ELEVEN_LOTTERY_NOTIFY_H

#include "protobuf.h"
#include "double_eleven_lottery_draw_list.h"
#include "double_eleven_lottery_prize_list.h"
#include "double_eleven_lottery_best_assist_list.h"

namespace protocol {
    class Double_eleven_lottery_notify : public Protocol {
    public:
        Double_eleven_lottery_notify() : d(linkerProtocol::DoubleElevenLotteryNotify()) {};
        explicit Double_eleven_lottery_notify(const linkerProtocol::DoubleElevenLotteryNotify &us) : d(us) {};
        const linkerProtocol::DoubleElevenLotteryNotify &get_double_eleven_lottery_notify() const { return this->d; }
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

if (o.has<jsonxx::Array>("drawList")) {
	auto ds = o.get<jsonxx::Array>("drawList");
	for (size_t i = 0; i < ds.size(); i++) {
		auto j = ds.get<jsonxx::Object>(i);
		Double_eleven_lottery_draw_list k;
		k.from_json(j);
		uint8_t buf[k.get_double_eleven_lottery_draw_list().ByteSize()];
		k.get_double_eleven_lottery_draw_list().SerializeToArray(buf, k.get_double_eleven_lottery_draw_list().ByteSize());

		auto m = this->d.add_drawlist();
		m->ParseFromArray(buf, k.get_double_eleven_lottery_draw_list().ByteSize());
	}
}

if (o.has<jsonxx::Array>("prizeList")) {
	auto ds = o.get<jsonxx::Array>("prizeList");
	for (size_t i = 0; i < ds.size(); i++) {
		auto j = ds.get<jsonxx::Object>(i);
		Double_eleven_lottery_prize_list k;
		k.from_json(j);
		uint8_t buf[k.get_double_eleven_lottery_prize_list().ByteSize()];
		k.get_double_eleven_lottery_prize_list().SerializeToArray(buf, k.get_double_eleven_lottery_prize_list().ByteSize());

		auto m = this->d.add_prizelist();
		m->ParseFromArray(buf, k.get_double_eleven_lottery_prize_list().ByteSize());
	}
}

if (o.has<jsonxx::Array>("bestAssistList")) {
	auto ds = o.get<jsonxx::Array>("bestAssistList");
	for (size_t i = 0; i < ds.size(); i++) {
		auto j = ds.get<jsonxx::Object>(i);
		Double_eleven_lottery_best_assist_list k;
		k.from_json(j);
		uint8_t buf[k.get_double_eleven_lottery_best_assist_list().ByteSize()];
		k.get_double_eleven_lottery_best_assist_list().SerializeToArray(buf, k.get_double_eleven_lottery_best_assist_list().ByteSize());

		auto m = this->d.add_bestassistlist();
		m->ParseFromArray(buf, k.get_double_eleven_lottery_best_assist_list().ByteSize());
	}
}

        }

        virtual std::string to_jsonstr() {
            std::stringstream ss;
ss << "{";
ss << "\"owid\":"<< this->d.owid() << ",";

std::stringstream drawlist_stream;
drawlist_stream << "[";
for (int32_t i = 0; i < this->d.drawlist_size(); i++) {
	drawlist_stream << Double_eleven_lottery_draw_list(this->d.drawlist(i)).to_jsonstr();
	if (i != this->d.drawlist_size() - 1) {
		drawlist_stream << ",";
	}
}
drawlist_stream << "]";
ss << "\"drawList\":" << drawlist_stream.str() << ",";

std::stringstream prizelist_stream;
prizelist_stream << "[";
for (int32_t i = 0; i < this->d.prizelist_size(); i++) {
	prizelist_stream << Double_eleven_lottery_prize_list(this->d.prizelist(i)).to_jsonstr();
	if (i != this->d.prizelist_size() - 1) {
		prizelist_stream << ",";
	}
}
prizelist_stream << "]";
ss << "\"prizeList\":" << prizelist_stream.str() << ",";

std::stringstream bestassistlist_stream;
bestassistlist_stream << "[";
for (int32_t i = 0; i < this->d.bestassistlist_size(); i++) {
	bestassistlist_stream << Double_eleven_lottery_best_assist_list(this->d.bestassistlist(i)).to_jsonstr();
	if (i != this->d.bestassistlist_size() - 1) {
		bestassistlist_stream << ",";
	}
}
bestassistlist_stream << "]";
ss << "\"bestAssistList\":" << bestassistlist_stream.str();
ss << "}";
return ss.str();

        }
        
    private:
        linkerProtocol::DoubleElevenLotteryNotify d;
    };
}
#endif //DANMU_CORE_DOUBLE_ELEVEN_LOTTERY_NOTIFY_H