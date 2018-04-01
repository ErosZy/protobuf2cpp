/**
 * PROGRAM: SYNTAX_STATEMENT? PACKAGE_STATEMENT OPTION_STATEMENT MESSAGE_STATEMENT*
 * SYNTAX_STATEMENT: syntax=ID SEMI
 * PACKAGE_STATEMENT: package ID SEMI
 * OPTION_STATEMENT: (option ID=ID SEMI)*
 * MESSAGE_STATEMENT: message ID { STATEMENT_ITEM* }
 * STATEMENT_ITEM: MODIFIER+ ID ID = NUMBER SEMI
 * MODIFIER: repeated|required|optional
 * DATA_TYPE: bool|double|float|int32|uint32|int64|uint64|sint32|sint64|fixed32|fixed64|sfixed32|sfixed64|string|bytes|enum
 * ID: [a-zA-Z_\"\.]+
 */

module.exports = class Parser {
  constructor(tokenizer) {
    this.tokenizer = tokenizer;
  }

  flashBack(token) {
    this.tokenizer.flashBack((token[1] || "").length);
  }

  getNextToken() {
    return this.tokenizer.next() || [];
  }

  parse() {
    return this.program();
  }

  program() {
    let expr = {
      syntaxStatment: this.syntaxStatment(),
      packageStatement: this.packageStatement(),
      optionStatement: this.optionStatement(),
      messageStatements: []
    };

    let message = this.messageStatement();
    while (message) {
      expr.messageStatements.push(message);
      message = this.messageStatement();
    }

    return expr;
  }

  syntaxStatment() {
    let token = this.getNextToken();
    if (token[0] != "KEY_WORDS" && token[1] != "syntax") {
      return {
        syntax: "proto2"
      };
    }

    let assign = this.getNextToken();
    if (assign[0] != "EQUAL_SIGN") {
      throw new Error("syntax need syntax=id");
    }

    let id = this.getNextToken();
    if (id[0] != "ID") {
      throw new Error("syntax need syntax=id");
    }

    let semi = this.getNextToken();
    if(semi[0] != "SEMI"){
      throw new Error("syntax statement lose semi(;)");
    }

    return {
      syntax: id[1]
    };
  }

  packageStatement() {
    let token = this.getNextToken();
    if (token[0] != "KEY_WORDS" && token[1] != "package") {
      throw new Error("lack of package statement keywords");
    }

    token = this.getNextToken();
    if (token[0] != "ID") {
      throw new Error("package statement need a id string");
    }

    let semi = this.getNextToken();
    if (semi[0] != "SEMI") {
      throw new Error("package statement lose semi(;)");
    }

    return {
      packageName: token[1]
    };
  }

  optionStatement() {
    let options = [];
    let token = this.getNextToken();
    while (token[0] == "KEY_WORDS" && token[1] == "option") {
      let assignedVar = this.getNextToken();
      if (assignedVar[0] != "ID") {
        throw new Error("option statement need var=value");
      }

      let sign = this.getNextToken();
      if (sign[0] != "EQUAL_SIGN") {
        throw new Error("option statement need var=value");
      }

      let assignVal = this.getNextToken();
      if (assignVal[0] != "ID") {
        throw new Error("option statement need var=value");
      }

      let semi = this.getNextToken();
      if (semi[0] != "SEMI") {
        throw new Error("option statement lose semi");
      }

      options.push({ assignedVar: assignedVar[1], assignVal: assignVal[1] });
      token = this.getNextToken();
    }

    this.flashBack(token);
    return {
      options
    };
  }

  messageStatement() {
    let token = this.getNextToken();
    if (token[0] != "KEY_WORDS" && token[1] != "message") {
      return null;
    }

    let messageName = this.getNextToken();
    if (messageName[0] != "ID") {
      throw new Error("message statement need a id string");
    }

    token = this.getNextToken();
    if (token[0] != "LEFT_BRACKET") {
      throw new Error("message statement lose left bracket({)");
    }

    let statementItems = [];
    let item = this.statementItem();
    while (item) {
      statementItems.push(item);
      item = this.statementItem();
    }

    token = this.getNextToken();
    if (token[0] != "RIGHT_BRACKET") {
      throw new Error("message statement lose left bracket(})");
    }

    return {
      messageName: messageName[1],
      statementItems
    };
  }

  statementItem() {
    let modifiers = this.modifier();
    if (!modifiers.length) {
      return null;
    }

    let dataType = this.getNextToken();
    if (dataType[0] != "ID" && dataType[0] != "DATA_TYPE") {
      throw new Error("statement lose data type");
    }

    let id = this.getNextToken();
    if (id[0] != "ID" && id[1] != "message") { // why use keywords message ????
      throw new Error("statement lose need a id string");
    }

    let assign = this.getNextToken();
    if (assign[0] != "EQUAL_SIGN") {
      throw new Error("statement lose need var=number");
    }

    let number = this.getNextToken();
    if (number[0] != "NUMBER") {
      throw new Error("statement lose need var=number");
    }

    let semi = this.getNextToken();
    if (semi[0] != "SEMI") {
      throw new Error("statement lose semi(;)");
    }

    return {
      modifiers,
      isCustomDataType: dataType[0] == "ID",
      dataType: dataType[1],
      id: id[1],
      number: number[1]
    };
  }

  modifier() {
    let items = [];
    let token = this.getNextToken();
    while (
      token[0] == "KEY_WORDS" &&
      ["required", "repeated", "optional"].indexOf(token[1]) > -1
    ) {
      items.push(token[1]);
      token = this.getNextToken();
    }

    this.flashBack(token);
    return items;
  }
};
