const http = require('http');
//require  -> NodeJs에서 만들어놓은 웹서버를 사용하고, 불러오기위해 만들어 놓은것
//require('http') -> NodeJS에서 제공하는 http부품이 필요하다.

const hostname = '127.0.0.1';
const port = 3000;

const server = http.createServer((req, res) => {
  res.statusCode = 200;
  res.setHeader('Content-Type', 'text/plain');
  res.end('Hello World\n');
});

//createServer -> 서버 만들기
// .listen -> 리슨하게 만들기, (port, hostname)
//  -> NodeJs로 서버를 만들었을때 port에서 리슨하게 만들고, hostname으로 접속한 사람에게 응답한다는 내용

server.listen(port, hostname, () => {
  console.log(`Server running at http://${hostname}:${port}/`);
});
