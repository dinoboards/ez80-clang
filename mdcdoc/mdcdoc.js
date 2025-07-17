#!/usr/bin/env node

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

const fs = require("fs");
const path = require("path");
const minimist = require("./lib/minimist");

const tokenizer = require("./lib/tokenizer.js");
const generator = require("./lib/generator.js");

const args = minimist(process.argv.slice(2), {
  boolean: ["help", "line", "file"],
  alias: {
    h: "help",
    p: "pattern",
    o: "output",
    l: "line",
    f: "file",
  },
});

if (args.help) {
  console.log(
    fs
      .readFileSync(__dirname + "/help.txt")
      .toString()
      .trim()
  );
  return;
}

function readStdin(callback) {
  let data = "";
  process.stdin.setEncoding("utf8");
  process.stdin.on("data", chunk => data += chunk);
  process.stdin.on("end", () => callback(data));
}


function main(text) {
  var tokens = tokenizer.parseCode(text, args.o);

  var g = new generator.Generator({
    addLineNumber: args.line,
    addFileHeader: args.file,
    file: path.basename(args._[0] || "stdin"),
  });

  if (args.pattern === undefined) {
    args.pattern = "cpp"; // default pattern
  }

  require(`./lib/patterns/${args.pattern}.js`).applyToGenerator(g);

  g.generate(tokens);

  var md = g.doc.join("\n");

  if (args.o) {
    fs.writeFileSync(args.o, md);
  } else {
    console.log(md);
  }
}

if (args._.length === 0 || args._[0] === "-") {
  // Read from stdin
  readStdin(main);
} else if (args._.length === 1) {
  // Read from file
  var text = fs.readFileSync(args._[0]).toString();
  main(text);
} else {
  console.error("No file.");
  return;
}
