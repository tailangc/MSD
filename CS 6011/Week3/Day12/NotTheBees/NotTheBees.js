"use strict";

const canvas = document.getElementById("canvasDrawing")
canvas.width = window.innerWidth
canvas.height = window.innerHeight


let imageSize = 130

let randomBeeNum =  Math.max(Math.floor(Math.random() * 10), 5) + 5

const context = canvas.getContext("2d")

const canvasWidth = canvas.width
const canvasHeight = canvas.height

let cursorX = 0
let cursorY = 0

let handleWindowOnLoad = window.requestAnimationFrame(drawBees)

let bees = []
for(let i = 0; i < randomBeeNum; i++){
    bees.push(generateBee())
}

function generateBee (){
    let bee = {
        xPos: canvasWidth * Math.random(),
        yPos: canvasHeight * Math.random(),
        speed: 1,
        image: new Image(imageSize, imageSize),
        isHeadingRight: true,
        isHeadingUp: true,
    }
    bee.image.src = "Face.png"
    return bee
}

function updateBeePosition (bee) {
    bee.isHeadingRight = bee.xPos < cursorX
    bee.isHeadingUp = bee.yPos > cursorY

    if (bee.isHeadingRight) {
        bee.xPos += bee.speed;
    } else {
        bee.xPos -= bee.speed;
    }

    if (bee.isHeadingUp) {
        bee.yPos -= bee.speed;
    } else {
        bee.yPos += bee.speed;
    }
}


function drawASingleBee (bee) {
    const { xPos, yPos, image } = bee
    context.save()
    context.translate(xPos + imageSize / 2, yPos + imageSize / 2)
    // context.rotate(getRotationDegree(bee) * Math.PI / 180)
    context.drawImage(image, -imageSize / 2, -imageSize / 2, imageSize, imageSize)
    context.restore()
}


function eraseASingleBee (bee){
    context.clearRect(bee.xPos, bee.yPos, imageSize, imageSize);
}


function checkIfGameIsEnded ()  {
    const ifCollide = bees.map(checkCollision)
    return ifCollide.some(el => el)
}

// const updateBeeMovingDirections = (bee) => {
//     bee.isHeadingRight = bee.xPos < cursorX
//     bee.isHeadingUp = bee.yPos > cursorY
// }

function drawBees () {
    const ifGameIsEnded = checkIfGameIsEnded()
    if (ifGameIsEnded) {
        window.cancelAnimationFrame(handleWindowOnLoad)
        endTheGame()
    } else {
        bees.forEach(eraseASingleBee)
        // bees.forEach(updateBeeMovingDirections)
        bees.forEach(updateBeePosition)
        bees.forEach(drawASingleBee)
        window.requestAnimationFrame(drawBees)
    }
}


const calculateBeeHoneypotDistance = (bee) => {
    const deltaX = cursorX - bee.xPos
    const deltaY = cursorY - bee.yPos
    return Math.sqrt(Math.pow(deltaX, 2) + Math.pow(deltaY, 2))
}

function checkCollision (bee)  {
    let honeypotRadius = imageSize / 2 * Math.sqrt(2)
    let beeHoneypotDistance = calculateBeeHoneypotDistance(bee)
    return beeHoneypotDistance <= honeypotRadius
}



const generateEndingDiv = () => {
    const ending = document.createElement("div")
    ending.style.textAlign = "center"
    ending.style.display = "flex"
    ending.style.flexDirection = "column"
    ending.style.alignItems = "center"
    ending.style.marginTop = `${canvasHeight / 4}px`
    return ending
}

function showEndingTip  ()  {
    let ending = generateEndingDiv()
    let s1 = document.createElement("h1")
    s1.textContent = "🤯YOURE DRUNK!🤯"
    s1.style.backgroundColor = "white"
    s1.style.padding = "10px"
    let s2 = document.createElement("h1")
    s2.textContent = "Drink Responsibly Dude"
    s2.style.backgroundColor = "white"
    s2.style.padding = "10px"
    ending.appendChild(s1)
    ending.appendChild(s2)
    document.body.appendChild(ending)
}

function endTheGame ()  {
    canvas.remove()
    showEndingTip()
}

function handleOnWindowMouseMove (event) {
    cursorX = event.x
    cursorY = event.y
}

window.onload = handleWindowOnLoad

window.onmousemove = handleOnWindowMouseMove