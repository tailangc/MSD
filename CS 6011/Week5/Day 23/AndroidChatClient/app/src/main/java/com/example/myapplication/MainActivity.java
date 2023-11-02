package com.example.myapplication;



import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.EditText;

import com.neovisionaries.ws.client.WebSocket;
import com.neovisionaries.ws.client.WebSocketFactory;

import java.io.IOException;

public class MainActivity extends AppCompatActivity {

    EditText usernameInput = findViewById(R.id.userID);
    EditText roomnameInput = findViewById(R.id.roomID);
    String username = usernameInput.getText().toString();
    String roomname = roomnameInput.getText().toString();
    public static final String WS_URL = "ws://10.0.2.2:8080/endpoint";
    WebSocket ws = null;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        try {
            ws = new WebSocketFactory().createSocket(WS_URL);
            //listen for event and will use this class to implement them
            ws.addListener(new MyWebsocket());
            ws.connectAsynchronously();
            ws.sendText("{\"type\": \"join\",\"room\":\""+ roomnameInput +"\",\"user\":\""+ usernameInput+"\"}");

        } catch (IOException e) {
            //AlertDialog alert = new AlertDialog("Server failed");
            Log.d("chatactivity", "some error");
        }

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        }

    public void handleEnterBtn(View view){

        Intent intent = new Intent(MainActivity.this, ChatRoomActivity.class);
        intent.putExtra("username", username);
        intent.putExtra("roomname", roomname);
        startActivity(intent);
    }


}