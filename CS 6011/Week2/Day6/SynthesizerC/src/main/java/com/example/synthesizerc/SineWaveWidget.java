package com.example.synthesizerc;

import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.layout.AnchorPane;

public class SineWaveWidget extends AudioComponentWidgetBase {
    public SineWaveWidget(AudioComponent ac, AnchorPane parent, String label) {
        super(ac, parent, label);
    }

    public void addFrequencySlider(){
        Slider freqSlider = new Slider(200,400,300);
        leftside.getChildren().add(freqSlider);
        freqSlider.setOnMouseDragged( g -> { handleFreq(freqSlider, freqLabel); });
    }
    private void handleFreq(Slider freqSlider, Label freqSliderLabel) {
        int result = (int)freqSlider.getValue();
        freqSliderLabel.setText(this.label + result + "Hz");

        ((SineWave)ac_).setFrequency(freqSlider.getValue());
    }
}


//    Slider slider = new Slider(220, 880, 440);
//    Label title = new Label();
//    public static  Circle output;
//
//    public SineWaveWidget (AudioComponent ac, AnchorPane parent, String name) {
//        super(ac, parent, name);
//    }
//
//    public void CreateSineWaveWidget( ){
//
//        title.setMouseTransparent(true);
//        title.setText("SineWave 440Hz");
//        slider.setOnMouseDragged(e-> handleSlider(e));
//        slider.setPadding(new Insets(6));
//        leftside.getChildren().add(title);
//        leftside.getChildren().add(slider);
//        baseLayout.setPrefSize(200,60);
//
//        VBox volumebar = new VBox();
//        volumebar.setAlignment(Pos.CENTER);
//
//
//        output= new Circle(10);
//        RadialGradient gradient1 = new RadialGradient(0,
//                .1,
//                0.5,
//                0.5,
//                2,
//                true,
//                javafx.scene.paint.CycleMethod.NO_CYCLE,
//                new Stop(0, Color.WHITE),
//                new Stop(0.5, Color.BLACK));
//        output.setFill(gradient1);
//
//        output.setOnMousePressed(e->startConn(e,output));
//        output.setOnMouseDragged(e->moveConn(e,output));
//        output.setOnMouseReleased(e->endConn(e,output));
//
//        rightSide.getChildren().add(output);
//
//    }
//
//    public void handleSlider(MouseEvent e) {
//        int frequency = (int) slider.getValue();
//        title.setText("SineWave " + frequency + "Hz");
//        ac_ = new SineWave(frequency);
//    }
//
//    //    @Override
//    public void moveWidget(MouseEvent e) {
//        double delX = e.getSceneX() - mouseXPos;
//        double delY = e.getSceneY() - mouseYPos;
//
//        this.relocate(delX + widgetXPos,delY + widgetYPos);
//
//        Bounds parentBounds = parent_.getBoundsInParent();
//        Bounds bounds = SineWaveWidget.output.localToScene(SineWaveWidget.output.getBoundsInLocal());
//
//        if( line_ != null ) {
//            line_.setStartX(bounds.getCenterX() - parentBounds.getMinX());
//            line_.setStartY(bounds.getCenterY() - parentBounds.getMinY());
//            System.out.println("dragging the widget and the line");
//        }
//
//
//    }