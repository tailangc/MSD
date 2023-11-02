function mainFunc(){
    // document.writeln("Hello World!");
    // console.log("Hello World!");
    let myObj = ["Terry", true, 72.5];

    for (let i of myObj){
        console.log(i);
    }

    let myPar = document.createElement("p");
    let myText = document.createTextNode("Hello world");
    myPar.appendChild(myText);
    document.body.appendChild(myPar);
    
}

function add(a,b){
    return a+b;
}

let addition = function (a,b){
    return a+b;
}



window.onload = mainFunc();

