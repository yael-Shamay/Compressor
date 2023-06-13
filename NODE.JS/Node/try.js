//"use strict"

const express=require('express')
const app=express();
const bodyParser=require('body-parser');

const cors = require('cors');
app.use(cors());

app.use(bodyParser.json());

app.use((req,res,next)=>{
    res.header("Access-Control-Allow-Origin","*");
    res.header("Access-Control-Allow-Headers","Origin, X-Requested-With, Contro-Type, Accept, Authoriztion");
    if(req.method==='OPTIONS'){
        res.header("Access-Control-Allow-Methods","PUT, POST,PATCH,DELETE,GET");
        return res.status(200).json({});
    }
    next();
})

const logger=(req,res,next)=>{
    console.log(req.originalUrl);
    next();
}


app.use(logger);

app.get('/',(req,res)=>{
    res.status(200).send('Welcome Yeal And Miri compression project!!😀😀😀');
})

// let rec=require('./rec');
// let user=require('./user')



// app.listen(4200,()=>{
//     console.log('listen...');
// })