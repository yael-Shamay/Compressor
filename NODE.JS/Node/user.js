const { Recipe } = require("./rec");



class User{
    constructor(id,name,password,email,address,arrRec){
        this.id=id;
        this.name=name;
        this.password=password;
        this.email=email;
        this.address=address;
        this.arrRec=arrRec;
    }

    show(){
        console.log('Its Work!'+ this.id+''+this.name);
    }
}
    let myUser=new User(5,"private","11111","jj@gmail.com","jerusalem",new Recipe(1,"choclate cake",5,6,"parve","kk","kkk","kkk"));
myUser.show();
module.exports={
    User,
    myUser
}