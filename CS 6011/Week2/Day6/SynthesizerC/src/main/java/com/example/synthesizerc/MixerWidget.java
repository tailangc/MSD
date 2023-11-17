package com.example.synthesizerc;

import javafx.scene.layout.AnchorPane;
import javafx.scene.paint.Color;
import javafx.scene.paint.RadialGradient;
import javafx.scene.paint.Stop;
import javafx.scene.shape.Circle;

import java.util.ArrayList;

public class MixerWidget extends AudioComponentWidgetBase {

    public static Circle inputMixerCirle;



    public MixerWidget(AudioComponent audioComponent, AnchorPane parent, String label) {

        //final shoe here is ac1Mixer.getClip()
        super(audioComponent, parent, label);
    }

    public void addInputCircle(){
        inputMixerCirle= new Circle(10);

        inputMixerCirle.setFill(Color.BROWN);
//        input.setOnMousePressed(e->startConn(e,input));
//        input.setOnMouseDragged(e->moveConn(e,input));
//        input.setOnMouseReleased(e->endConn(e,input));
        leftside.getChildren().add(inputMixerCirle);

    }


}


