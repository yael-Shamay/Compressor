const express = require('express');
const bodyParser = require('body-parser');
const app = express();
const path=require('path')
const constDir='C:\\Users\\win10\\Desktop\\bootCamp\\project_in_dessiction\\gitDownload\\Compressor\\filesToUpload';
app.use(express.static(path.join(__dirname, 'public')));
app.use(express.static(path.join(__dirname, '/public/assets')));
app.use(express.static(path.join(__dirname, '/public/style.css')));
app.use(bodyParser.urlencoded({ extended: true })); 

app.post('/example', (req, res) => {
  res.send(`Full name is:${req.body.fname} ${req.body.lname}.`);
});
app.get("/", (req, res) => {
    res.status(200).send(`Welcome Yeal And Miri compression project!!😀😀😀`);
    console.log(`I am work?????????`);
  })
  app.get("/Compress", (req, res) => {
   
    res.sendFile(path.join(__dirname+'/public/Compress.html'));
  })
  app.get("/Decompress", (req, res) => {
   
    res.sendFile(path.join(__dirname+'/public/Decompress.html'));
  })
  app.get("/Compare", (req, res) => {
   
    res.sendFile(path.join(__dirname+'/public/Compare.html'));
  })
  app.get("/Test", (req, res) => {
   
    res.sendFile(path.join(__dirname+'/public/Test.html'));
  })

  var exec = require('child_process').execFile;
  app.post('/Compress', function(req, res) {
    const select=0;
    const pathCompress=path.join(constDir,req.body.Compress);
   // res.send('LOok I am Here!!!! ' + req.body.Compress + '.');
   
   var opt = function(){
     exec('Compressor.exe', ["0", pathCompress], function(err, data) {  
       console.log(err)
       console.log(data.toString());                       
   }); 

 }
 opt();
    res.sendFile(path.join(__dirname+'/public/Compress.html'));
  });
  app.post('/Decompress', function(req,res) {

    const select=1;
    const pathDeompress=path.join(constDir,req.body.decompress);
    var opt = function(){
      exec('Compressor.exe', ["1", pathDeompress], function(err, data) {  
        console.log(err)
        console.log(data.toString());                       
    }); 
    
  }
  opt();
   // res.send('You sent Decompress the name ' + pathDeompress + '.');
   res.sendFile(path.join(__dirname+'/public/DeCompress.html'));
  });
  app.post('/Compare', function(req, res) {
    const select=2;
    const pathDeompress1=path.join(constDir,req.body.compare[0]);
    const pathDeompress2=path.join(constDir,req.body.compare[1]);
  //   var opt = function(){
  //     exec('Compressor.exe', ["2", pathDeompress1,pathDeompress2], function(err, data) {  
  //       console.log(err)
  //       console.log(data.toString());                       
  //   }); 
    
  // }
  // opt();
   res.send('You sent Compare the name ', pathDeompress1 ,'.        ',pathDeompress2);
  //res.sendFile(path.join(__dirname+'/public/Compare.html'));
  });
  app.post('/Test', function(req, res) {
    const select=4;
    const pathDeompress=path.join(constDir,req.body.file);
   // res.send('You sent the name ' + pathDeompress + '.');
   res.sendFile(path.join(__dirname+'/public/Test.html'));
  });
const port = 8080;

app.listen(port, () => {
  console.log(`http://127.0.0.1:${port}`);
});