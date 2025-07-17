
/*
Original: https://github.com/forntoh/mdcdoc

MIT License

Copyright (c) 2021 Forntoh Thomas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Additional local changes made by Dean Netherton (c) 2025

*/

const path = require("path");


function parseCode(text, docName) {
  var lines = text.split("\n");

  var line;
  var lineNo = 0;
  var codeBlocks = [{ section: 'Functions' }];
  var typeBlocks = [{ section: 'Types' }];
  var fileBlock = { file: path.parse(docName).name.toUpperCase(), brief: [] }

  function nextLine() {
    lineNo++;
    return lines.shift();
  }

  while ((lines.length > 0)) {
    line = nextLine();
    var l = line.trim();

    if (!l.startsWith("/**")) {
      continue;
    }

    var block = {
      text: [],
      file: null,
      params: [],
      brief: [],
      notes: [],
      seealso: [],
      textLine: lineNo
    };

    while ((line = nextLine())) {
      l = line.trim();

      if (l.startsWith("*/") || l.startsWith("**/")) break;

      if (l.startsWith("* @return")) block.return = trimText(l.substr(9));
      else if (l.startsWith("* @param")) block.params.push(l.substr(8));
      else if (l.startsWith("* @brief")) block.brief.push(l.substr(9));
      else if (l.startsWith("* @details")) block.text.push(l.substr(11));
      else if (l.startsWith("* @note")) block.notes.push(l.substr(8));
      else if (l.startsWith("* @see")) block.seealso.push(l.substr(7));
      else if (l.startsWith("* @file")) block.file = path.parse(l.substr(8)).name.toUpperCase();
      else if (l.startsWith("* @hide")) block.hide = true
      else block.text.push(trimText(l));
    }

    l = nextLine();
    block.codeLine = lineNo;

    if (l.startsWith("/**")) {
      lines.unshift(l)
    }

    else if (block.hide) {
    }

    else if (l.startsWith('typedef')) {
      let typedefLines = [l];
      // Keep reading lines until we find a line ending with '};' or '} <name>;'
      while (lines.length > 0) {
        let typedefLine = nextLine();
        typedefLines.push(typedefLine);
        if (/}\s*[\w]*\s*;/.test(typedefLine.trim())) break;
      }
      block.code = typedefLines.join('\n');
      typeBlocks.push(block)
    }

    else if (block.file) {
      fileBlock = block
    }

    else {
      block.code = trimCode(l, nextLine);
      codeBlocks.push(block);
    }
  }

  return [fileBlock].concat(codeBlocks.concat(typeBlocks));
}

function trimCode(code, nextLine) {
  if (!code) return code;

  //if code does not have then ending ), consume nextLine until it does
  while (!code.includes(')'))
    code += " " + nextLine().trim();

  //replace "( " with "("
  code = code.replace(/\(\s+/g, '(');

  // Remove 'extern', 'static', and 'inline' at the start (with optional whitespace)
  code = code.replace(/^\s*(extern|static|inline)\b\s*/g, '');
  // Remove any remaining 'inline' or 'static' elsewhere (just in case)
  code = code.replace(/\b(inline|static)\b\s*/g, '');
  // Remove function body: anything from the first '{' to the last '}' (non-greedy)
  code = code.replace(/\{[\s\S]*?\}/g, '');
  // Replace (void) with ()
  code = code.replace(/\(\s*void\s*\)/g, '()');
  return stripRight(code.trim(), "{;").trim();
}

function trimText(text) {
  if (!text) return text;

  text = text.trim();

  if (text.startsWith("* ")) {
    text = text.substr(2);
  }

  if (text == "*") {
    text = "";
  }

  return text;
}

function stripRight(s, chars) {
  var regex;
  var pattern;
  var ss = s == null ? "" : "" + s;

  if (chars === undefined) {
    pattern = /\s+$/g;
  } else {
    pattern = new RegExp("[" + chars + "]+$", "g");
  }

  return ss.replace(pattern, "");
}

exports.parseCode = parseCode;
