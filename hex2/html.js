'use strict'

const fs = require('fs');
const data = fs.readFileSync('./colors.json', 'utf-8');
const colors = JSON.parse(data);

let out = `<!DOCTYPE html>\n`;
out += `<html lang="en">\n`;
out += `<head>\n`;
out += `  <meta charset="utf-8">\n`
out += `  <title>Colors!</title>\n`;
out += `  <style>\n`;
out += `      body, html {\n`;
out += `        margin: 0;\n`;
out += `        padding: 0;\n`;
out += `        font-size: 24px;\n`;
out += `          }`;
out += `      div {`;
out += `        margin: 0;`;
out += `          }`;
out += `      h1, p {`;
out += `        padding: 1em;\n`;
out += `        margin: 0;\n`;
out += `     }\n`;
out += `  </style>\n`;
out += "</head>\n";
out += "<body>\n";

colors.forEach(c => {
    out += `\n<div>\n`;
    out += `  <h1 style='background-color: ${c.Name}'>${c.Name}</h1>\n`;
    out += `  <p style='background-color: rgb(${c.RGB[0]}, ${c.RGB[1]}, ${c.RGB[2]})'>RGB: ${c.RGB[0]}, ${c.RGB[1]}, ${c.RGB[2]}</p>\n`;
    out += `  <p style='background-color: hsl(${c.HSL[0]}, ${c.HSL[1]}%, ${c.HSL[2]}%)'>HSL: ${c.HSL[0]}, ${c.HSL[1]}, ${c.HSL[2]}</p>\n`;
    out += `  <p style='background-color: #${c.Hex}'>HEX: #${c.Hex}</p>\n`;
    out += `</div>`;
});

out += '\n</body>\n</html>';
fs.writeFile('out.html', out, 'utf-8', (err) => {
    if (err)
        console.log(err);
});
