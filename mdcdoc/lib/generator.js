
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
class Generator {
  constructor(options) {
    this.options = options;

    this.level = 0;
    this.codeBlock = false;
    this.doc = [];
    this.codePatterns = [];
    this.title = ""
  }

  generate(tokens) {
    for (const t of tokens) {
      this.addToken(t);
    }
  }

  addCodePattern(pattern, fn) {
    this.codePatterns.push({
      pattern: pattern,
      callback: fn,
    });
  }

  applyCodePattern(token) {
    for (const p of this.codePatterns) {
      if (p.pattern.test(token.code)) {
        p.callback.call(this, token);
        return;
      }
    }
  }

  addToken(token) {
    // if (token.title) {
    //   // this.addTitle(token)
    // }

    if (token.file) {
      this.addFileSummary(token)
    }

    else if (token.section) {
      this.addSection(token)
    }

    else if (token.code != "") {
      this.applyCodePattern(token);
      this.addSubHeader(token.header || token.code);
      if (token.brief.length !== 0) this.addBriefLine(token.brief);
      this.addCodeLine(token);
      this.addLines(token.text, true);
      if (token.seealso.length !== 0) this.addSeeAlsoLink(token.seealso);
      if (token.params.length !== 0) this.addParamLines(token.params);
      if (token.return != undefined) this.addReturnsLine(token.return);
      if (token.notes.length !== 0) this.addNoteLine(token.notes);
      this.addLine("\n---\n")
    }
    else {
      this.addLines(token.text);
    }

    this.addLine("");
  }

  addFileSummary(token) {
    this.addLine(`\n## Library ${token.file}\n`)
    this.file = token.file
    if (token.brief.length !== 0) this.addBriefLine(token.brief);
    if (token.text) this.addLines(token.text);
  }

  addSection(token) {
    this.addLine(`\n### ${this.file} ${token.section}\n`)
  }

  addHeader(text) {
    this.addLine(heading(this.level) + " " + text);
  }

  addBriefLine(lines) {
    for (let line of lines)
      this.doc.push("*" + line.trim() + "*");
  }

  addNoteLine(lines) {
    for (let line of lines)
      this.doc.push("> " + line.trim() + "\n");
  }

  addSeeAlsoLink(links) {
    this.doc.push('\n**See also:**\n')

    for (let link of links)
      this.doc.push(`* [${link}](#${link})`)
  }

  addSubHeader(text) {
    this.addLine(
      (this.level <= 1 ? "" : "1. ") + heading(this.level + 1) + " " + text
    );
    this.addLine("");
  }

  addLine(line) {
    this.doc.push(line);
  }

  addCodeLine(token) {
    this.addLine("");
    this.addLine((this.level <= 1 ? "" : "    ") + "```cpp");
    this.addLine((this.level <= 1 ? "" : "    ") + token.code);
    this.addLine((this.level <= 1 ? "" : "    ") + "```");
    this.addLine("");
  }

  addParamLines(lines) {
    this.addLine((this.level <= 1 ? "" : "    ") + "\n**Params:**");
    this.addLine("");
    for (const l of lines) {
      var first = l.split(" ")[1];
      this.addLine(
        (this.level <= 1 ? "" : "    ") + "- `" + first + "` - " + l.substring(first.length + 1).trim()
      );
    }
    this.addLine("");
  }

  addReturnsLine(text) {
    this.addLine((this.level <= 1 ? "" : "    ") + "**Returns:**");
    this.addLine("");
    this.addLine((this.level <= 1 ? "" : "    ") + "- " + text);
  }

  addTextLine(text, relative) {
    var codeBlock = this.codeBlock;

    if (text.startsWith("```")) {
      this.codeBlock = !codeBlock;
    }

    if (this.codeBlock || codeBlock) {
      this.addLine(text);
      return;
    }

    if (text.startsWith("#")) {
      if (relative) {
        this.addLine(heading(this.level + 1) + text);
      } else {
        var prefix = text.substring(0, text.indexOf(" "));
        this.level = prefix.length;
        this.addLine(text);
      }
    } else {
      this.addLine((this.level <= 1 ? "" : "    ") + text);
    }
  }

  addLines(lines, relative) {
    for (const l of lines) {
      this.addTextLine(l, relative);
    }
  }
}

function heading(n) {
  return new Array(n + 1).join("\n####");
}

exports.Generator = Generator;
