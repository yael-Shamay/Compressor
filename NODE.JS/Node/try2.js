const http = require('http');
const express = require('express');
const bodyParser = require('body-parser');
const route = require('./routes');
const app = express();
app.use(bodyParser.urlencoded({extended: false}));
app.use('/test',route);
app.get('/',(req,res)=>{
    res.status(200).send('Welcome Yeal And Miri compression project!!😀😀😀');
})
app.use((req,res,next)=>{
    res.header("Access-Control-Allow-Origin","*");
    res.header("Access-Control-Allow-Headers","Origin, X-Requested-With, Contro-Type, Accept, Authoriztion");
    if(req.method==='OPTIONS'){
        res.header("Access-Control-Allow-Methods","PUT, POST,PATCH,DELETE,GET");
        return res.status(200).json({});
    }
    next();
})
app.use((req, res,next)=>{
    res.status(404).send('<h1> Page not found </h1>');
 });


const server = http.createServer(app);
server.listen(3000);