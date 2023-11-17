package com.example.myapplication;

import android.util.Log;

import com.neovisionaries.ws.client.WebSocket;
import com.neovisionaries.ws.client.WebSocketAdapter;

import org.json.JSONObject;

import java.util.List;
import java.util.Map;

public class MyWebsocket extends WebSocketAdapter {
    static boolean connected = false;

    @Override
    public void onConnected(WebSocket websocket, Map<String, List<String>> headers) throws Exception {
        super.onConnected(websocket,headers);
        connected = true;
        Log.d("websocket", "ws is open");
    }


    @Override
    public void onTextMessage(WebSocket websocket, String text) throws Exception {
        super.onTextMessage(websocket, text);
        JSONObject receivedMsg = new JSONObject(text);
        String displayText = "";
        if(receivedMsg.get("type").equals("message")) {
            displayText = receivedMsg.get("user") + " : " + receivedMsg.get("message");
        }else if(receivedMsg.get("type").equals("join")){
            displayText = receivedMsg.get("user") + " join the room";
        }else if (receivedMsg.get("type").equals("leave")){
            displayText= receivedMsg.get("user") +  " left the room";
        }


        ChatRoomActivity.msgs.add(displayText);

        ChatRoomActivity.chatList.post(new Runnable() {
            @Override
            public void run() {
                ChatRoomActivity.chatListAdapter.notifyDataSetChanged();
                ChatRoomActivity.chatList.smoothScrollToPosition(ChatRoomActivity.chatListAdapter.getCount());
            }
        });

        Log.d("server msg", text);
    }
}