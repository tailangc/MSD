package com.example.myapplication;

//import static com.example.AndroidChatClient.MainActivity.ws;
import static com.example.myapplication.MainActivity.ws;
import static com.example.myapplication.R.id.chatroom;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.RecyclerView;

import com.neovisionaries.ws.client.WebSocket;
import com.neovisionaries.ws.client.WebSocketFactory;

import java.io.IOException;
import java.security.Key;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Date;
import java.util.Locale;

public class ChatRoomActivity extends AppCompatActivity {
    public static ListView chatList;
    public static ArrayAdapter chatListAdapter;
    public static ArrayList<String> msgs = new ArrayList<>();
    String username;
    String roomName;


    @Override
    protected void onCreate(Bundle savedInstanceState) {

        Log.d("activity", "new activity started");

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_chat_room);



        Bundle extras = getIntent().getExtras();
        if(extras!= null){
            username = extras.getString("username");
            roomName = extras.getString("room");
            TextView chatroom = findViewById(R.id.chatroom);
            chatroom.setText(roomName);
        }
        chatList = findViewById(R.id.chatlist);
        chatListAdapter = new ArrayAdapter<>(this, android.R.layout.simple_list_item_1, msgs);
        chatList.setAdapter(chatListAdapter);
    }

    public void sendMsg(View view) {
        EditText textMessage = findViewById(R.id.textMessage) ;
        String message = String.valueOf(textMessage.getText());

        ws.sendText("{\"type\":\"message\",\"user\":\""+username +"\",\"room\":\"" +roomName+"\",\"message\":\"" +message+"\"}");
        textMessage.setText(null);
    }

    public void handleLeaveMsg(View view){
        ws.sendText("{\"user\":\""+username +"\",\"type\":\"leave\",\"room\":\"" +roomName+"\"}");
        //MyWebsocket.wsIsOpen = false;
        Intent leaveIntent = new Intent( ChatRoomActivity.this, MainActivity.class );
        startActivity(leaveIntent);

    }
}