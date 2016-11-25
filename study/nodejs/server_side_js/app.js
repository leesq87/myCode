var express = require('express'); // express-> 함수임
var bodyParser = require('body-parser'); // body-parser 를 include
var app = express();
//get 방식은 express에서 제공하지만 post는 제공하지않는다.
//그러므로 post 방식을 사용하려면 body-pasrser를 사용해야 한다.
app.locals.pretty = true;
//jade의 코드가 (web에서 보는) 깔끔하게 보이도록 하는 코드.

app.set('view engine','jade');
// view engien -> 템플릿 엔진, 약속된것임, 'jade' -> jade를 연동시키겠다.
app.set('views','./views');
//jade 파일은 /views 폴더에 넣겠다는것. 거기서 읽어온다는것임.
//express는 views폴더를 찾도록 기본설정되어 있다.

app.use(bodyParser.urlencoded({extended: false}));
//body-parser 모듈을 app 객체에 붙여서 쓰겠다.
//앞으로 모든 요청은 body-parser를 먼저 통과한다음에 router를 통하게 한다.
//post방식으로 사용자가 전송했다면, request에서 body라는 객체를 body-parser가 추가하여
//body라는 객체의 property에 값을 넣어서 사용자에게 제공한다. 라는 방식

app.use(express.static('public')); // 정적파일을 사용하기위해서 추가
//public 은 폴더 이름이고, 관습적으로 사용함

app.listen(3000, function(){  // port 번호임, 리스너등록됨
  console.log('connected 3000 port');
});

app.get('/template',function(req, res){
  //template엔진은 소스코드를 렌더링한다. send 아님, template파일을 읽어옴
  //{time: 'hello'} -> jade에 변수를 보주는것이다.
  //{변수명: 보낼것(함수포함됨)} 형식
  // res.render('temp',{time:'hello'}); //temp파일을 렌더링해서 res로 보내준다.
  res.render('temp',{time:Date(), _title:'jade'});
});


// 사용자가 접속시 알려주기위해,
// '/'홈페이지로 접속한 접속자를 구분하기 위해서 사용됨
app.get('/',function(req, res){ // req, res -> 약속되어 있는것임
  res.send('hello home page'); // 전달
});

app.get('/dynamic',function(req, res){

  var lis = '';
  for(var i=0;i<5;i++){
    lis = lis + '<li>coding</li>';
  }

  var time = Date();  //JavaScript가 갖고있는 현재시간에 대하여 나타내는것

  //`-> 그레이브 엑센트임, 따음표 아님. commented text 기능임
  //HTML문서식으로 사용이 가능함
  var output = `
  <!DOCTYPE html>
  <html>
    <head>
      <meta charset="utf-8">
      <title></title>
    </head>
    <body>
      Hello dynamic HTML in JS
      <ul>
      ${lis}
      </ul>
      ${time}
    </body>
  </html>`
  res.send(output);
  // ${lis} -> 문자열 내에 lis라는 값을 출력할때 사용한다. -> ${변수이름}

//javaScript에서는 html과 같은 방식의 문법을 사용하려면 뒤에 \를 넣어서 사용해야한다.
//보기 안좋아서 많이 사용은 안함
//   res.send('<!DOCTYPE html>\
//   <html>\
//     <head>\
//       <meta charset="utf-8">\
//       <title></title>\
//     </head>\
//     <body>\
//       Hello Static With HTML\
//     </body>\
//   </html>\
// ')
})

app.get('/route', function(req, res){
  res.send('hello Router, <img src = "/image1.jpg">');
});

//라우터 -> 요청이 들어왔을때 연결해주는것.
//.get의 경우 function내부에 send가 1개만 있어야 작동함.
app.get('/login',function(req, res){  //get -> 라우터(router) --> 길을 찾아준다
  // res.send('login plz');
  res.send('<h1>login aaa</h1>');
});


//query string 관련~~
//get방식에서는 query string을 쓸 수 있지만, Post 방식에서는 못쓴다.
app.get('/topic/:id', function(req, res){
  var topics=[
    'Javasciprt is...',
    'Nodejs is...',
    'Express is...'
  ];

  var output = `
  <a href="/topic/0">JavaScript</a><br>
  <a href="/topic/1">NodeJs</a><br>
  <a href="/topic/2">Express</a><br><br><br>
  ${topics[req.params.id]} `
  //req.query.id -> url/topic?id=111 방식
  //req.params.id - >
  res.send(output);
  //query.id에서의 id -> url/topic?id=~~ 요 부분임
  //즉 query string에서의 것과 동일해야함
  // res.send(req.query.id); // request에서의 query에서 받은 id의 값을 send한다.
  // query string에서 2개이상의 query를 출력할경우 + 사용
  // url/topic?id=11&name=adsf --> & 기호로 구분
  // res.send(req.query.id + req.query.name);
});

//get 방식과 post방식의 차이점
app.get('/form',function(req,res){
  res.render('form');
});

app.get('/form_receiver',function(req,res){
  var title = req.query.title;
  var description = req.query.description;
  res.send(title+','+description);
});

app.post('/form_receiver',function(req,res){
  //post에서는 .body를 붙여야한다.
  //post를 사용하기위해선 body-parser를 사용해야 한다.
  var title = req.body.title;
  var description = req.body.description;
  res.send(title+','+description);

});
