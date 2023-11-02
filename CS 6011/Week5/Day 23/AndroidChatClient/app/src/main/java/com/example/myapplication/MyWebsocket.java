package com.example.myapplication;

import android.util.Log;

import com.neovisionaries.ws.client.WebSocket;
import com.neovisionaries.ws.client.WebSocketAdapter;

import java.util.List;
import java.util.Map;

public class MyWebsocket extends WebSocketAdapter {


    @Override
    public void onConnected(WebSocket websocket, Map<String, List<String>> headers) throws Exception {
        super.onConnected(websocket,headers);
        Log.d("websocket", "ws is open");
    }


    @Override
    public void onTextMessage(WebSocket websocket, String text) throws Exception {
        super.onTextMessage(websocket, text);
    }
}