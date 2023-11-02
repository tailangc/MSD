function mainFunc(){
    let myTitle = document.createElement("p");
    let myText = document.createTextNode("Terry Tsao");
    myTitle.appendChild(myText);
    document.body.appendChild(myTitle);

    myTitle.style.fontWeight = "bold";
    // myTitle.style.position = "absolute";
    // myTitle.style.top = "-20px";
    // myTitle.style.left = "40%";
    myTitle.style.fontSize = "50px";

    // let div = document.createElement("div");
    let mySelfie = document.createElement("img");
    // let scaleIndex = 0.2;
    mySelfie.src = "selfie.JPG";
    // mySelfie.style.width = '${scaleIndex * 100}%';
    // mySelfie.style.height = '${scaleIndex * 100}%';
    // div.appendChild(mySelfie);
    document.body.appendChild(mySelfie);

    let myPar = document.createElement("p");
    let myIntro = document.createTextNode("Hey guys, my name is Terry!");
    myPar.appendChild(myIntro);
    document.body.appendChild(myPar);
    myPar.style.fontSize ="30px";

    // let imgDiv = document.getElementById("imgID1");
    // let img1 = document.createElement('img');
    // img1.src = "selfie.JPG";
    // imgDiv.appendChild(img1);

}

window.onload = mainFunc();