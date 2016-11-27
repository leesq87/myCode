var express = require('express');
var app = express();
var bodyParser = require('body-parser');
var fs = require('fs'); // file system 사용
app.use(bodyParser.urlencoded({extended: false}));
app.locals.pretty = true;
app.set('views','./views_file');
app.set('view engine','jade');

app.get('/topic/new',function(req,res){
  fs.readdir('data',function(err, files){
    if(err){
      console.log(err);
      res.status(500).send('server err');
    }
    res.render('new',{topics:files});
  });
});

//router에 []를 넣으면은 코드를 줄일 수 있다. (배열요소)
app.get(['/topic','/topic/:id'],function(req,res){
  //fs.readdir(path,callback(err,files)) -> 형식
  fs.readdir('data',function(err, files){
    if(err){
      console.log(err);
      res.status(500).send('server err');
    }
    //.render(file,{object:files})
    // res.render('view',{topics:files});

    //id가 있는경우
    var id = req.params.id;
    if(id){
      fs.readFile('data/'+id, 'utf8', function(err,data){
        if(err){
          console.log(err);
          res.status(500).send('err');
        }
        res.render('view',{topics:files, title:id, description:data});
      })
    } else{
      //id가 없을경우
      res.render('view',{topics:files,title:'WelCome',description:'Hello Java Script for Server'});
    }
  });
});

//윗부분에서 중복함수를 제거하였기에 제거
// app.get('/topic/:id',function(req,res){
//   var id = req.params.id;
//   fs.readdir('data',function(err, files){
//     if(err){
//       console.log(err);
//       res.status(500).send('server err');
//     }
//     //.readFile(path, 'utf8',callback(err,data))
//     fs.readFile('data/'+id, 'utf8', function(err,data){
//       if(err){
//         console.log(err);
//         res.status(500).send('err');
//       }
//       res.render('view',{topics:files, title:id, description:data});
//     });
//   });
// });

app.post('/topic',function(req,res){
  var title = req.body.title;
  var description = req.body.description;
  //fs.writeFile(fileName,data,callback)
  //writeFile의 callback의 인자는 err 한개뿐이다.
  fs.writeFile('data/'+title,description,function(err){
    if(err){ // 에러가 있다면
      console.log(err);
      res.status(500).send('Internal Server Error');
      //.send로 보내면 밑의 send는 안나온다. ->> 바로 리턴시키나?
    }
    //err가 없다면
    // res.send('success');
    
    //글을 작성한 페이지에게 보내는것, re-direction
    res.redirect('/topic/'+title);
  });
});

app.listen(3000,function(){
  console.log('connected, 3000 port');
});
