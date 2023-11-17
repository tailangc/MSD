package com.example.myapplication;



import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import com.neovisionaries.ws.client.WebSocket;
import com.neovisionaries.ws.client.WebSocketFactory;

import java.io.IOException;

public class MainActivity extends AppCompatActivity {
    public static final String WS_URL = "ws://10.0.2.2:8080/endpoint";
    static WebSocket ws;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Button buttonLogin = findViewById(R.id.joinButton);
        EditText editTextName = findViewById(R.id.userID);
        EditText editTextRoom = findViewById(R.id.roomID);
        try {
            ws = new WebSocketFactory().createSocket(WS_URL);
            //listen for event and will use this class to implement them
            ws.addListener(new MyWebsocket());
            ws.connectAsynchronously();
//            ws.sendText("{\"type\": \"join\",\"room\":\""+ roomnameInput +"\",\"user\":\""+ usernameInput+"\"}");

        } catch (IOException e) {
            //AlertDialog alert = new AlertDialog("Server failed");
            Log.d("chatactivity", "some error");
        }

        buttonLogin.setOnClickListener((view) -> {
            Log.d("button", "button clicked");
            String textname = editTextName.getText().toString();
            String textroom = editTextRoom.getText().toString();
            ws.sendText("{\"type\":\"join\",\"room\":\""+ textroom +"\",\"user\":\""+ textname+"\"}");
            if (!textname.isEmpty() && !textroom.isEmpty()) {
                Intent intent = new Intent(this, ChatRoomActivity.class);
                intent.putExtra("username", textname);
                intent.putExtra("room", textroom);
                startActivity(intent);
                Log.d("intent", "intent started");
            } else {
                Toast.makeText(MainActivity.this, "Please Enter userName and Room Name", Toast.LENGTH_SHORT).show();
            }

        });
    }
}