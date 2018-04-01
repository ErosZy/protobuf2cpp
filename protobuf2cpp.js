const fs = require("fs");
const handlebars = require("handlebars");
const tpl = handlebars.compile(
  fs.readFileSync("./class.tpl").toString("utf-8")
);

module.exports = class Protobuf2cpp {
  constructor(parser) {
    this.parser = parser;
    this.expr = null;
    this.protobufPkgName = "";
    this.messageStatements = [];
  }

  convert() {
    this.expr = this.parser.parse();
    this.protobufPkgName = this.expr.packageStatement.packageName;
    this.messageStatements = this.expr.messageStatements;
    for (let i = 0; i < this.messageStatements.length; i++) {
      let tplInfo = this.compile(this.messageStatements[i]);
      let filename = "./protocol/" + tplInfo.protobuf_lower_class_name + ".h";
      let codeStr = tpl(tplInfo);
      fs.writeFileSync(filename, codeStr);
    }
  }

  compile(message) {
    let tplInfo = {};
    let messageName = message.messageName;
    let items = message.statementItems;
    tplInfo.prevent_class_name = this.camel(messageName).toUpperCase();
    let includeHeaders = items.filter(v => v.isCustomDataType);
    includeHeaders = ['#include "protobuf.h"'].concat(
      includeHeaders.map(v => {
        return '#include "' + this.camel(v.dataType).toLowerCase() + '.h"';
      })
    );
    tplInfo.include_header = includeHeaders.join("\n");
    tplInfo.class_name = message.messageName;
    tplInfo.var_name = message.messageName.slice(0, 1).toLowerCase();
    tplInfo.protobuf_pkg_name = this.protobufPkgName;
    tplInfo.protobuf_class_name = message.messageName;
    tplInfo.protobuf_lower_class_name = this.camel(
      message.messageName
    ).toLowerCase();
    tplInfo.from_json_code = this.fromJsonCode(tplInfo.var_name, message);
    tplInfo.to_jsonstr_code = this.toJsonStrCode(tplInfo.var_name, message);
    return tplInfo;
  }

  fromJsonCode(varName, message) {
    let statements = message.statementItems;
    let codes = statements.map(v => {
      let str = "";
      let hasRepeated = v.modifiers.indexOf("repeated") > -1;
      let isCustomDataType = v.isCustomDataType;
      let jsonType = this.getJsonType(v.dataType, isCustomDataType);
      let convertType = this.getConvertType(v.dataType, isCustomDataType);
      if (!hasRepeated) {
        if (!isCustomDataType) {
          str += `if(o.has<${jsonType}>("${v.id}")) {\n`;
          str += `\tthis->${varName}.set_${v.id.toLowerCase()}(${convertType}(o.get<${jsonType}>("${
            v.id
          }")));\n`;
          str += `}\n`;
          return str;
        } else {
          str += `if (o.has<jsonxx::Object>("${v.id}")) {\n`;
          str += `\tjsonxx::Object info = o.get<jsonxx::Object>("${v.id}");\n`;
          str += `\t${this.camel(
            v.dataType
          )} ${v.dataType[0].toLowerCase()};\n`;
          str += `\t${v.dataType[0].toLowerCase()}.from_json(info);\n\n`;
          str += `\tauto _${v.dataType[0].toLowerCase()} = new ${
            this.protobufPkgName
          }::${v.dataType}();\n`;
          str += `\tuint8_t buf[_${v.dataType[0].toLowerCase()}.get_${this.camel(
            v.dataType
          ).toLowerCase()}().ByteSize()];\n`;
          str += `\t_${v.dataType[0].toLowerCase()}.get_${this.camel(
            v.dataType
          ).toLowerCase()}().SerializeToArray(buf, n.get_${this.camel(
            v.dataType
          ).toLowerCase()}().ByteSize());\n`;
          str += `\t_${v.dataType[0].toLowerCase()}->ParseFromArray(buf, _${v.dataType[0].toLowerCase()}.get_${this.camel(
            v.dataType
          ).toLowerCase()}().ByteSize());\n`;
          str += `\tthis->${varName}.set_allocated_${v.id.toLowerCase()}(_${v.dataType[0].toLowerCase()});\n`;
          str += `}\n`;
          return str;
        }
      } else {
        str += `if (o.has<jsonxx::Array>("${v.id}")) {\n`;
        if (!isCustomDataType) {
          str += `\tjsonxx::Array arr = o.get<jsonxx::Array>("${v.id}");\n`;
          str += `\tfor (size_t i = 0; i < arr.size(); i++) {\n`;
          str += `\t\tthis->${varName}.add_${v.id.toLowerCase()}(${convertType}(arr.get<${jsonType}>(i)));\n`;
          str += `\t}\n`;
        } else {
          str += `\tauto ${v.dataType[0].toLowerCase()}s = o.get<jsonxx::Array>("${
            v.id
          }");\n`;
          str += `\tfor (size_t i = 0; i < ${v.dataType[0].toLowerCase()}s.size(); i++) {\n`;
          str += `\t\tauto j = ${v.dataType[0].toLowerCase()}s.get<jsonxx::Object>(i);\n`;
          str += `\t\t${v.dataType} k;\n`;
          str += `\t\tk.from_json(j);\n`;
          str += `\t\tuint8_t buf[k.get_${this.camel(
            v.dataType
          ).toLowerCase()}().ByteSize()];\n`;
          str += `\t\tk.get_${this.camel(
            v.dataType
          ).toLowerCase()}().SerializeToArray(buf, k.get_${this.camel(
            v.dataType
          ).toLowerCase()}().ByteSize());\n\n`;
          str += `\t\tauto m = this->${varName}.add_${v.id.toLowerCase()}();\n`;
          str += `\t\tm->ParseFromArray(buf, k.get_${this.camel(
            v.dataType
          ).toLowerCase()}().ByteSize());\n`;
          str += `\t}\n`;
        }
        str += "}\n";
        return str;
      }
    });

    return codes.join("\n");
  }

  toJsonStrCode(varName, message) {
    let statements = message.statementItems;
    let codes = statements.map((v, i) => {
      let str = "";
      let hasRepeated = v.modifiers.indexOf("repeated") > -1;
      let isCustomDataType = v.isCustomDataType;
      let isString = v.dataType == "string";
      if (!hasRepeated) {
        if (!isCustomDataType) {
          str += `ss << "\\"${v.id}\\":"`;
          if (!isString) {
            str += `<< this->${varName}.${v.id.toLowerCase()}()`;
          } else {
            str += `<< "\\"" << this->${varName}.${v.id.toLowerCase()}() << "\\""`;
          }
        } else {
          str += `\n${this.camel(
            v.dataType
          )} ${v.dataType[0].toLowerCase()}(this->${varName}.${v.id.toLowerCase()}());\n`;
          str += `ss << "\\"${
            v.id
          }\\":" << ${v.dataType[0].toLowerCase()}.to_jsonstr()`;
        }
      } else {
        if (!isCustomDataType) {
          str += `ss << "\\"${v.id}\\":[";\n`;
          str += `for (int32_t i = 0; i < this->${varName}.${v.id.toLowerCase()}_size(); i++) {\n`;
          str += `\tss << this->${varName}.${v.id.toLowerCase()}(i);\n`;
          str += `\tif (i != this->${varName}.${v.id.toLowerCase()}_size() - 1) {\n`;
          str += `\t\tss << ",";\n`;
          str += `\t}\n`;
          str += `}\n`;
          str += `ss << "]"`;
        } else {
          str += `\nstd::stringstream ${v.id.toLowerCase()}_stream;\n`;
          str += `${v.id.toLowerCase()}_stream << "[";\n`;
          str += `for (int32_t i = 0; i < this->${varName}.${v.id.toLowerCase()}_size(); i++) {\n`;
          str += `\t${v.id.toLowerCase()}_stream << ${
            v.dataType
          }(this->${varName}.${v.id.toLowerCase()}(i)).to_jsonstr();\n`;
          str += `\tif (i != this->${varName}.${v.id.toLowerCase()}_size() - 1) {\n`;
          str += `\t\t${v.id.toLowerCase()}_stream << ",";\n`;
          str += `\t}\n`;
          str += `}\n`;
          str += `${v.id.toLowerCase()}_stream << "]";\n`;
          str += `ss << "\\"${
            v.id
          }\\":" << ${v.id.toLowerCase()}_stream.str()`;
        }
      }

      if (statements.length - 1 > i) {
        str += ` << ",";\n`;
      } else {
        str += ";\n";
      }
      return str;
    });
    let str = `std::stringstream ss;\n`;
    str += `ss << "{";\n`;
    str += codes.join("");
    str += `ss << "}";\n`;
    str += `return ss.str();\n`;
    return str;
  }

  getJsonType(type, isCustomDataType) {
    if (isCustomDataType) {
      return "";
    }

    switch (type) {
      case "bool":
        return "jsonxx::Boolean";
      case "double":
      case "float":
      case "int32":
      case "uint32":
      case "int64":
      case "uint64":
      case "sint32":
      case "sint64":
      case "fixed32":
      case "fixed64":
      case "sfixed32":
      case "sfixed64":
        return "jsonxx::Number";
      case "string":
        return "jsonxx::String";
    }
  }

  getConvertType(type, isCustomDataType) {
    if (isCustomDataType) {
      return "";
    }

    switch (type) {
      case "bool":
        return "";
      case "double":
        return "double";
      case "float":
        return "float";
      case "int32":
        return "int32_t";
      case "uint32":
        return "uint32_t";
      case "int64":
        return "int64_t";
      case "uint64":
        return "uint64_t";
      case "sint32":
        return "int32_t";
      case "sint64":
        return "int64_t";
      case "fixed32":
        return "uint32_t";
      case "fixed64":
        return "uint64_t";
      case "sfixed32":
        return "int32_t";
      case "sfixed64":
        return "int64_t";
      case "string":
        return "";
    }
  }

  camel(str) {
    str = str
      .replace(/([A-Z])/g, "_$1")
      .slice(1)
      .toLowerCase();
    str = str[0].toUpperCase() + str.slice(1);
    return str;
  }
};
