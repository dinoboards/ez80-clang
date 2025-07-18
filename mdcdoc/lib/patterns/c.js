
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
exports.applyToGenerator = function (g) {

    g.addCodePattern(/^#define/, t => {
        //set t.header to the 2nd word from t.code
        const words = t.code.trim().split(/\s+/);
        t.header = words[1] || '';
    })
    g.addCodePattern(/^Functions/, t => t.header = "Functions");

    g.addCodePattern(/^typedef/, (t) => {

        // Split lines and get the last line
        const lines = t.code.trim().split('\n');
        let lastLine = lines[lines.length - 1].trim();
        // Remove '}' and ';' and extra spaces
        lastLine = lastLine.replace(/[};]/g, '').trim();
        t.header = lastLine;
    });

    g.addCodePattern(/\(/, (t) => {
        // Find the first word preceding an opening bracket and set header to that word
        const match = t.code.match(/(\w+)\s*\(/);
        t.header = match ? match[1] : '';
    });

    g.addCodePattern(/^[^\(]*$/, (t) => {
        t.header = "🔧 " + t.code;
    });

};
