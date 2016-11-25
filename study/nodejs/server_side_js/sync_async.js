var fs = require('fs');

//Sync
console.log(1);
var data = fs.readFileSync('data.txt','utf8');
console.log(data);

// Async
console.log(2);
var data2 = fs.readFile('data.txt','utf8',
                        (err, data2)=>{
                          console.log(3);
                          console.log(data2);}
                        );
console.log(4);
