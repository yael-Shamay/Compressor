const express=require('express')
const path=require('path');
const app=express();

//const publicPath=path.join(__dirname,'public');
const myProgect='C:\Users\win10\Desktop\bootCamp\project_in_dessiction\gitDownload\Compressor\UI\NewGue';
const publicPath=path.join(myProgect,'NewGue');
//console.log(publicPath);
app.use(express.static(publicPath));

app.listen(9000,()=>{
         console.log('listen...');
    })