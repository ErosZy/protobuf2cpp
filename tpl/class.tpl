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

#ifndef DANMU_CORE_{{prevent_class_name}}_H
#define DANMU_CORE_{{prevent_class_name}}_H

{{{include_header}}}

namespace protocol {
    class {{class_name}} : public Protocol {
    public:
        {{class_name}}() : {{var_name}}({{protobuf_pkg_name}}::{{protobuf_class_name}}()) {};
        explicit {{class_name}}(const {{protobuf_pkg_name}}::{{protobuf_class_name}} &us) : {{var_name}}(us) {};
        const {{protobuf_pkg_name}}::{{protobuf_class_name}} &get_{{protobuf_lower_class_name}}() const { return this->{{var_name}}; }
        virtual bool decode_from_buf(Buffer &buf) {
            return this->{{var_name}}.ParseFromArray(buf.get_buf_ptr(), buf.get_length());
        }

        virtual std::shared_ptr<Buffer> encode_to_buf() {
            auto ptr = new uint8_t[this->{{var_name}}.ByteSize()];
            this->{{var_name}}.SerializeToArray(ptr, this->{{var_name}}.ByteSize());
            return std::make_shared<Buffer>(ptr, this->{{var_name}}.ByteSize());
        }

        virtual void from_json(jsonxx::Object &o) {
            {{{from_json_code}}}
        }

        virtual std::string to_jsonstr() {
            {{{to_jsonstr_code}}}
        }
        
    private:
        {{protobuf_pkg_name}}::{{protobuf_class_name}} {{var_name}};
    };
}
#endif //DANMU_CORE_{{prevent_class_name}}_H