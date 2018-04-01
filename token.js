const fs = require("fs");

const KEY_WORDS = [
  "syntax",
  "package",
  "option",
  "message",
  "required",
  "optional",
  "repeated"
];

const DATA_TYPE = [
  "bool",
  "double",
  "float",
  "int32",
  "uint32",
  "int64",
  "uint64",
  "sint32",
  "sint64",
  "fixed32",
  "fixed64",
  "sfixed32",
  "sfixed64",
  "string",
  "bytes",
  "enum"
];

module.exports = class Token {
  constructor(filepath) {
    this.filepath = filepath;
    this.content = fs.readFileSync(filepath).toString("utf-8");
    this.content = this.content.replace(/\/\/.*/g, "");
    this.contentLen = this.content.length;
    this.index = 0;
  }

  flashBack(posCount) {
    this.index -= posCount;
  }

  next() {
    let token = "";
    let skiped = this.skipBlank();
    if (!skiped) {
      return null;
    }

    while (true) {
      if (this.index > this.contentLen) {
        break;
      }

      let char = this.content[this.index];
      if (this.isBlank(char)) {
        break;
      }

      if (/[a-zA-Z_\.\"]|\d/.test(char)) {
        token += char;
        this.index += 1;
      } else if (this.isMark(char) && token.length == 0) {
        token = char;
        this.index += 1;
        break;
      } else {
        break;
      }
    }

    if (KEY_WORDS.indexOf(token) > -1) {
      return ["KEY_WORDS", token];
    } else if (DATA_TYPE.indexOf(token) > -1) {
      return ["DATA_TYPE", token];
    } else if (/^\d+$/.test(token)) {
      return ["NUMBER", token];
    } else if (token == "=") {
      return ["EQUAL_SIGN", "="];
    } else if (token == ";") {
      return ["SEMI", ";"];
    } else if (token == "{") {
      return ["LEFT_BRACKET", "{"];
    } else if (token == "}") {
      return ["RIGHT_BRACKET", "}"];
    } else if (token == "undefined") {
      return null;
    } else {
      return ["ID", token.replace(/^"|"$/g, "")];
    }
  }

  skipBlank() {
    while (true) {
      if (this.index > this.contentLen) {
        return 0;
      }

      let char = this.content[this.index];
      if (this.isBlank(char)) {
        this.index += 1;
      } else {
        break;
      }
    }

    return 1;
  }

  isBlank(char) {
    return char == " " || char == "\n" || char == "\t" || char == "\r" || char == null;
  }

  isMark(char) {
    return char == "{" || char == "}" || char == "=" || char == ";";
  }
};
