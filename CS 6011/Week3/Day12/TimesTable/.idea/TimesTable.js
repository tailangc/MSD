function mainFunc(){
    let table = document.createElement("table")
    table.setAttribute("align", "center")
    table.setAttribute("border", 1)
    let tableBody = document.createElement("tbody");
    let previousCell = null;
    let colours = ["red", "orange", "green", "blue"];
    let currentColourIndex = 0;
    let isAnimating = false;
    let myBtn = document.createElement("button");
    myBtn.textContent = "Muahahahaha";
    myBtn.style.height = "40px"
    myBtn.style.width = "200px"
    myBtn.style.fontSize = "20px"
    myBtn.style.marginTop = "20px"
    myBtn.style.marginLeft = "43%"

    myBtn.addEventListener("click", btnClicked);

    // if(isAnimating){
        window.setInterval(changeColour,80);
        // document.body.style.color =
    // }



    for (var i = 0; i < 10; i++) {
        let creatRow = document.createElement("tr");
        for (var j = 0; j < 10; j++) {
            let cell = document.createElement( "td");
            cell.textContent = ((i+1)*(j+1));


            // Add event listeners for mouse enter and leave
            cell.addEventListener("mouseenter", mouseEnter);

            cell.addEventListener("mouseleave", mouseLeave);

            cell.addEventListener("click", handleCLick);

            // cell.style.padding = "15px";
            cell.className = "cell"
            creatRow.appendChild(cell);
        }

        tableBody.appendChild(creatRow);
        // tableBody.setAttribute("align", "center")

    }
    table.appendChild(tableBody);
    document.body.appendChild(table);
    document.body.appendChild(myBtn);


function mouseEnter(){
   this.classList.add("highlighted");
}

function mouseLeave(){
    this.classList.remove("highlighted");
}

function handleCLick(){
    if (previousCell !== null) {
        previousCell.classList.remove("clickHighlight");
    }
    this.classList.add("clickHighlight");
    previousCell = this;
}

function btnClicked(){
    isAnimating = !isAnimating
}

function changeColour() {
    if (isAnimating) {

        let randomRed = Math.floor(Math.random() * 256);
        let randomGreen = Math.floor(Math.random() * 256);
        let randomBlue = Math.floor(Math.random() * 256);

        document.body.style.background = `rgb(${randomRed},${randomGreen},${randomBlue})`;
    }
}
}

window.onload = mainFunc();