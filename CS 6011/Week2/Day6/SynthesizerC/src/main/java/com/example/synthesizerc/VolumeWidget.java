package com.example.synthesizerc;

import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.layout.AnchorPane;
import javafx.scene.paint.Color;
import javafx.scene.paint.RadialGradient;
import javafx.scene.paint.Stop;
import javafx.scene.shape.Circle;

public class VolumeWidget extends AudioComponentWidgetBase {
    public   static Circle VolumeInputCircle;
    public  static  double VolumeSliderValue = 0;
    public  static  Volume volumeComponent;
    public VolumeWidget(AudioComponent ac, AnchorPane parent, String label) {
        super(ac, parent, label);
        volumeComponent= (Volume) ac;
    }
    public void addVolumeSlider(){
        Slider volSlider = new Slider(0,15,8);
        leftside.getChildren().add(volSlider);
        volSlider.setOnMouseDragged( g -> { handleVolume( volSlider, freqLabel); });
    }

    private void handleVolume( Slider freqSlider, Label freqSliderLabel) {
        int result = (int)freqSlider.getValue();
        freqSliderLabel.setText(this.label + result + "Db");
        VolumeSliderValue = freqSlider.getValue();
       // ((SineWave)ac_).setFrequency(freqSlider.getValue());
    }

    public void addInputCircle(){
        VolumeInputCircle= new Circle(10);
        RadialGradient gradient1 = new RadialGradient(0,
                .1,
                0.5,
                0.5,
                2,
                true,
                javafx.scene.paint.CycleMethod.NO_CYCLE,
                new Stop(0, Color.WHITE),
                new Stop(0.5, Color.BLUE));
        VolumeInputCircle.setFill(gradient1);
//        input.setOnMousePressed(e->startConn(e,input));
//        input.setOnMouseDragged(e->moveConn(e,input));
//        input.setOnMouseReleased(e->endConn(e,input));
        leftside.getChildren().add(VolumeInputCircle);

    }


}