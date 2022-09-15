const express = require('express');
const app = express();
const path = require('path');
const router = express.Router();
const publicPath=path.join(__dirname,'express');

router.get('/',function(req,res){
  res.sendFile(path.join(publicPath+'/index.html'));
  //__dirname : It will resolve to your project folder.
});
var bodyParser=require("body-parser");
app.use(bodyParser.urlencoded({extended: true}))

// Process application/json
app.use(bodyParser.json());

app.post('/createEmp', function(req, res){  
    debugger
//now req.body will be populated with the object you sent
console.log(req.body.name); //prints john
});
// router.get('/about',function(req,res){
//   res.sendFile(path.join(publicPath+'/about.html'));
// });

// router.get('/sitemap',function(req,res){
//   res.sendFile(path.join(publicPath+'/sitemap.html'));
// });
app.get('/test', function(req, res) {
    res.sendFile('views/test.html', {root: __dirname })
});

router.get('/fun',function(req,res){
   alert("I word");
   // res.sendFile(path.join(publicPath+'/sitemap.html'));
  });



const requestListener = function (req, res) {
    res.setHeader("Content-Type", "application/json");
};

// app.get('/',function(req,res) {
//          res.sendFile('index.html');
//        });
    

//add the router
app.use('/', router);
app.listen(process.env.port || 7000);

console.log('Running at Port 7000');
// app.get('/',function(req,res) {את נראה לי לא שומעת אותי
//     res.sendFile('index.html');
//   });

