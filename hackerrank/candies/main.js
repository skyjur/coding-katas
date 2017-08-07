process.stdin.resume();
process.stdin.setEncoding("ascii");
var input = "";
process.stdin.on("data", function (chunk) {
    input += chunk;
});
process.stdin.on("end", function () {
    //solve(input);
});

function solve(input) {
    var marks = input.split('\n').slice(1).map(Number);
    var sweets = marks.map(() => 1);

    for(var i=marks.length-1; i>0; i--) {
        if(marks[i] < marks[i-1] && sweets[i-1] <= sweets[i]) {
            sweets[i-1] = sweets[i] + 1;
        }
    }
    
    for(var i=0; i<marks.length-1; i++) {
        if(marks[i] < marks[i+1] && sweets[i+1] <= sweets[i]) {
            sweets[i+1] = sweets[i] + 1;
        }
    }
    
    console.log(sweets.reduce((a,b)=>a+b));
}

fs = require('fs');
solve(fs.readFileSync('hackerrank/candies/sample0.in', {encoding: 'ascii'}));
solve(fs.readFileSync('hackerrank/candies/sample1.in', {encoding: 'ascii'}));