
const messagesBox = document.querySelector(".chat-messages");
const messageInput = document.getElementById("message-input");
const sendButton = document.getElementById("send-button");
const leaveButton = document.getElementById("leave-button");
const usernameInput = document.getElementById("username");
const roomnameInput = document.getElementById("roomNumber");
const users = document.querySelector(".users");


let ws = new WebSocket('ws://localhost:8080')
ws.onopen = handleOpenCB;
ws.onmessage = handleMsgCB;
roomnameInput.addEventListener("keypress", handleKeyPress);
sendButton.addEventListener("click", handleSendClicked);
leaveButton.addEventListener("click", handleLeaveClicked);


function handleOpenCB(event){
    console.log('Connected to the WebSocket server');
    // ws.send('Client connected!');
    ws.onopen = true;
}

function handleMsgCB(event){
    let data = JSON.parse(event.data)
    let userText = document.createElement("blockquote")
    let name = document.createElement("blockquote")
    let message = document.createElement("blockquote")
    switch (data.type){
        case("join"):
            userText.textContent = data.user + " has joined " + data.room
            name.textContent = data.user
            users.appendChild(name)
            messagesBox.appendChild(userText)
            break
        case("message"):
            message.textContent = data.message
            messagesBox.appendChild(message)
            break
        case("leave"):
            message.textContent = data.message
            messagesBox.appendChild(message)
            ws.close()
            break
    }
    console.log('Received message:', event.data);
    console.log('Received data type:', typeof event.data);
}

function handleKeyPress(e) {
    if (e.key === "Enter") {
        if(usernameInput.value == "" || roomnameInput.value == ""){
            alert("invalid input")
            // ws.send("message"+ " " + "Incomplete Information")
        }else if(checkRoom(roomnameInput.value.toString()) == false){
            alert("Room ID can only be lower-case letters")
        }
        else {
            ws.send("join" + " " + usernameInput.value + " " + roomnameInput.value);}
    }
}

function handleSendClicked(e){
    ws.send("message" + " " + usernameInput.value + ":" + messageInput.value)
}

function handleLeaveClicked(e){
    ws.send("message" + " " + usernameInput.value + " has left the room")
}

function checkRoom(e){
    // e = roomnameInput.value.toString()
    for(let i of e){
        if(i < 'a' || i > 'z' || i ==" "){
            return false
        }
    }
    return true
}