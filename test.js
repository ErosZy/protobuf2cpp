const Token = require("./token");
const Parser = require("./parser");
const Protobuf2cpp = require('./protobuf2cpp');

let tokenizer = new Token("./pro.proto");
// let token = tokenizer.next();
// for(; token != null; token = tokenizer.next()){
//     console.log(token);
// }
let parser = new Parser(tokenizer);
let protobuf2cpp = new Protobuf2cpp(parser);
protobuf2cpp.convert();
// parser.parse();
// console.log(JSON.stringify(parser.expr));