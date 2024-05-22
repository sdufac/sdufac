var tablesize = 10;
document.body.style.zoom=0.9;

class snake{
    constructor(x,y){
        this.positionx=x;
        this.positiony=y;
        this.previousposx;
        this.previousposy;
        this.sprite=new Image;
        this.sprite.src="image/steve.png"
    }
    afficher(){
        document.getElementById(this.positionx+","+this.positiony).appendChild(this.sprite);
    }
}

class body{
    constructor(x,y){
        this.positionx=x;
        this.positiony=y;
        this.previousposx=0;
        this.previousposy=0;
        this.sprite=new Image;
        this.sprite.src="image/stevebody.png"
    }
    afficher(){
        document.getElementById(this.positionx+","+this.positiony).appendChild(this.sprite);
    }
}

class pomme{
    constructor(){
        this.positionx=Math.floor(Math.random() * tablesize+1);
        this.positiony=Math.floor(Math.random() * tablesize+1);

        var flag;

        //Redonne une position aléatoire si la pomme spawn sur le snake
        do{
            flag=true;
            tabsnake.forEach(element => {
                if(((element.positionx == this.positionx) && (element.positiony == this.positiony)) || (this.positionx == head.positionx && this.positiony == head.positiony)){
                    this.positionx=Math.floor(Math.random() * tablesize+1);
                    this.positiony=Math.floor(Math.random() * tablesize+1);
                    
                    flag=false;
                }
            });
        }
        while(flag==false);

        this.sprite=new Image;
        this.sprite.src="image/apple.png";
    }
    afficher(){
        document.getElementById(this.positionx+','+this.positiony).appendChild(this.sprite);
    }

    manger(){
        if(this.positionx == head.positionx && this.positiony == head.positiony){
            document.getElementById(this.positionx+","+this.positiony).removeChild(this.sprite);
            grow();
            score=(tabsnake.length)-2;
            document.getElementById('score').innerHTML = 'Score :'+score;
            pommespawn();  
        }    
    }
}

function pommespawn(){
    pomme1 = new pomme();
    pomme1.afficher();
}

var head;
var body1;
var body2;
var pomme1;
var score;

var tabsnake = new Array();
var previousmove;
var actualdirection='right';

function start(){

    head=new snake(3,2);
    head.afficher();

    body1=new body(2,2);
    tabsnake.push(body1);
    body1.afficher();

    body2=new body(1,2);
    tabsnake.push(body2);
    body2.afficher();

    pomme1 = new pomme();
    pomme1.afficher();
    
    score=(tabsnake.length)-2;
    document.getElementById('score').innerHTML = 'Score :'+score;
}

function grow(){
    var last=tabsnake[tabsnake.length-1];
    var bodyx=new body(last.previousposx,last.previousposy);
    tabsnake[tabsnake.length]=bodyx;
    bodyx.afficher();
}

//permet de bouger le snake
var movement =setInterval(function move(){
    if(actualdirection=='right' && previousmove!='left')
    {
        tabsnake.forEach(element => {
            if((head.positionx ==element.positionx) && (head.positiony==element.positiony)){
                lose();
            }
        });
        
        if(head.positionx<tablesize){
            head.previousposx = head.positionx;
            head.previousposy = head.positiony;

            head.positionx +=1;
            head.sprite.style.transform ="rotate(0deg)";
            head.afficher();
            bodymove();
            pomme1.manger();

            previousmove='right';
        }
        else{
            lose();
            
        }
    }
    if(actualdirection=='left' && previousmove!='right')
    {
        tabsnake.forEach(element => {
            if((head.positionx ==element.positionx) && (head.positiony==element.positiony)){
                lose();
            }
        });
        
        if(head.positionx>1){
            head.previousposx = head.positionx;
            head.previousposy = head.positiony;

            head.positionx -=1;
            head.sprite.style.transform ="rotate(180deg)";
            head.afficher();
            bodymove();
            pomme1.manger();

            previousmove='left';
        }
        else{
            lose();
            
        }
    }
    if(actualdirection=='down' && previousmove!='up')
    {
        tabsnake.forEach(element => {
            if((head.positionx==element.positionx) && (head.positiony==element.positiony)){
                lose();
            }
        });

        if(head.positiony<tablesize){
            head.previousposx = head.positionx;
            head.previousposy = head.positiony;

            head.positiony +=1;
            head.sprite.style.transform ="rotate(90deg)";
            head.afficher();
            bodymove();
            pomme1.manger();

            previousmove='down';
        }
        else{
            lose();
        }
    }
    if(actualdirection=='up' && previousmove!='down')
    {
        tabsnake.forEach(element => {
            if((head.positionx==element.positionx) && (head.positiony==element.positiony)){
                lose();
            }
        });
        
        if(head.positiony>1){
            head.previousposx = head.positionx;
            head.previousposy = head.positiony;

            head.positiony -=1;
            head.sprite.style.transform ="rotate(270deg)";
            head.afficher();
            bodymove();
            pomme1.manger();

            previousmove='up';
        }
        else{
            lose();
        }
    } 
},300);

function bodymove(){

    var flag1=false;
    var i=tabsnake.length;
    tabsnake.forEach(element => {
        if(flag1==false){
            
            element.previousposx=element.positionx;
            element.previousposy=element.positiony;
            
            element.positionx=head.previousposx;
            element.positiony=head.previousposy;
            element.afficher();
            
        }
        if(flag1==true && (tabsnake.length-i)<tabsnake.length)
        {
            element.previousposx=element.positionx;
            element.previousposy=element.positiony;

            element.positionx=tabsnake[tabsnake.length-i].previousposx;
            element.positiony=tabsnake[tabsnake.length-i].previousposy;
            element.afficher();
            i--;
        }
        flag1=true;
    });
}

window.addEventListener("keydown", checkKeyPressed, false);

function checkKeyPressed(evt) {
    if (evt.keyCode == "38" && previousmove!='down') {
        actualdirection='up';
    }
    if (evt.keyCode == "37" && previousmove!='right') {
        actualdirection='left';
    }
    if (evt.keyCode == "40" && previousmove!='up') {
        actualdirection='down';
    }
    if (evt.keyCode == "39" && previousmove!='left') {
        actualdirection='right';
    }
}

function lose(){
    clearInterval(movement);
    window.alert("perdu");
    location.reload();
}

window.onload = (event) => {
    start();
};


