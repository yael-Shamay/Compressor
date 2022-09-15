


  class Recipe{
    constructor(id,name,like,level,kosher,pic,ingredient ,instruction ){
         
        this.id=id;
        this.name=name;
        this.like=like;
        this.level=level;
        this.kosher=kosher;
        this.pic=pic;
        this.ingredient=ingredient;
        this.instruction=instruction;
    }

    show(){
        console.log('Its Work!'+ this.id+''+this.name);
    }
}
let myRec=new Recipe(1,"choclate cake",5,6,"parve","kk","kkk","kkk");
    
myRec.show();
module.exports={
    Recipe,
    myRec
}