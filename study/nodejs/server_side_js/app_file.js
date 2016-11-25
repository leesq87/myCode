var express = require('express');
var app = express();
var bodyParser = require('body-parser');
var fs = require('fs'); // file system 사용
app.use(bodyParser.urlencoded({extended: false}));
app.locals.pretty = true;
app.set('views','./views_file');
app.set('view engine','jade');

app.get('/topic/new',function(req,res){
  res.render('new');
});

app.get('/topic',function(req,res){
  //fs.readdir(path,callback(err,files)) -> 형식
  fs.readdir('data',function(err, files){
    if(err){
      console.log(err);
      res.status(500).send('server err');
    }
    //.render(file,{object:files})
    res.render('view',{topics:files});
  });
});

app.get('/topic/:id',function(req,res){
  var id = req.params.id;
  fs.readdir('data',function(err, files){
    if(err){
      console.log(err);
      res.status(500).send('server err');
    }
    //.readFile(path, 'utf8',callback(err,data))
    fs.readFile('data/'+id, 'utf8', function(err,data){
      if(err){
        console.log(err);
        res.status(500).send('err');
      }
      res.render('view',{topics:files, title:id, description:data});
    });
  });
});

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
    res.send('success');
  });
});

app.listen(3000,function(){
  console.log('connected, 3000 port');
});
