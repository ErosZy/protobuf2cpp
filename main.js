const Token = require("./token");
const Parser = require("./parser");
const Protobuf2cpp = require('./protobuf2cpp');

let tokenizer = new Token("./protocol/gateway.proto");
let parser = new Parser(tokenizer);
let protobuf2cpp = new Protobuf2cpp(parser);
protobuf2cpp.convert();