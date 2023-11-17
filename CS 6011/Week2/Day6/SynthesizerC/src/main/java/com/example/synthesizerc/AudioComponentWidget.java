package com.example.synthesizerc;

import javafx.geometry.Bounds;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.paint.CycleMethod;
import javafx.scene.paint.RadialGradient;
import javafx.scene.paint.Stop;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Line;


public class AudioComponentWidget extends Pane {
    private AudioComponent audioComponent_;
    AudioComponent ac_;
    String label;
    AnchorPane parent_;
    double mouseXPos, mouseYPos, widgetXPos, widgetYPos;
    Line line_;
    VBox rightSide;
    private  Circle output;
    public AudioComponentWidget(AudioComponent ac, AnchorPane parent , String label) {
        ac_ = ac;
        parent_= parent;

        this.label = label;
        HBox baseLayout = new HBox();
        baseLayout.setStyle("-fx-border-color: black;-fx-border-image-width:5 ");

        rightSide= new VBox();
        Button closeBtn= new Button("x");
        closeBtn.setOnAction(actionEvent -> {closeWidget();});
        output= new Circle(10);
        RadialGradient gradient1 = new RadialGradient(0,
                .1,
                0.5,
                0.5,
                2,
                true,
                CycleMethod.NO_CYCLE,
                new Stop(0, Color.WHITE),
                new Stop(0.5, Color.BLACK));
        output.setFill(gradient1);
        
        //handle drawing the line - handle 3 events
        output.setOnMousePressed(e->startConn(e,output));
        output.setOnMouseDragged(e->moveConn(e,output));
        output.setOnMouseReleased(e->endConn(e,output));
//        closeBtn.setOnAction(actionEvent -> {closeWidget();});

        rightSide.getChildren().add(closeBtn);
        rightSide.getChildren().add(output);

        rightSide.setAlignment(Pos.CENTER);
        rightSide.setPadding(new Insets(5));
        rightSide.setSpacing(5);
        /***** center portion of the widget *****/
        VBox leftside = new VBox();
        leftside.setOnMousePressed(e->getPosInf(e));
        leftside.setOnMouseDragged(e->moveWidget(e));
        /* add a freqLabel */
        Label freqLabel  = new Label(label);
        leftside.getChildren().add(freqLabel);
        /* add a slide */
        Slider freqSlider = new Slider(200,400,300);
        leftside.getChildren().add(freqSlider);
        freqSlider.setOnMouseDragged( g -> { handleSlider( g , freqSlider, freqLabel); });


        baseLayout.getChildren().add(leftside);
        baseLayout.getChildren().add(rightSide);

        this.getChildren().add(baseLayout);

        this.setLayoutX(50);
        this.setLayoutY(50);


    }

    private void endConn(MouseEvent e, Circle output) {
        Circle speaker = FinalSynthesizeApplication.speaker;
        Bounds speakerBounds= speaker.localToScene(speaker.getBoundsInLocal());
        double distance = Math.sqrt(Math.pow(speakerBounds.getCenterX()-e.getSceneX(),2.0) +
                Math.pow(speakerBounds.getCenterY()-e.getSceneY(),2.0 ));
        if(distance<10){
           // SynthesizeApplication.Connected_widgets_.add(this);
            //better to create a new array list for connected widgets only
            //the wave to some array list
        } else {
          parent_.getChildren().add(line_);
          line_ = null;
        }

    }

    private void moveConn(MouseEvent e, Circle output) {
        Bounds parentBounds = parent_.getBoundsInParent();
        line_.setEndX(e.getSceneX()-parentBounds.getMinX());
        line_.setEndY(e.getSceneY()- parentBounds.getMinY());
        
    }

    private void startConn(MouseEvent e, Circle output) {
        if(line_!=null){
            parent_.getChildren().remove(line_);
        }
        Bounds parentBounds = parent_.getBoundsInParent();
        Bounds bounds = output.localToScene(output.getBoundsInLocal());

        line_ =new Line();
        line_.setStrokeWidth(5);

        line_.setStartX(bounds.getCenterX() - parentBounds.getMinX());
        line_.setStartY(bounds.getCenterY() - parentBounds.getMinY());

        line_.setEndX(e.getSceneX());
        line_.setEndY(e.getSceneY());

        parent_.getChildren().add(line_);

    }

    private void moveWidget(MouseEvent e) {
        double delX = e.getSceneX() - mouseXPos;
        double delY = e.getSceneY() - mouseYPos;

        this.relocate(delX + widgetXPos,delY + widgetYPos);
    }

    private void getPosInf(MouseEvent e) {
        mouseXPos = e.getSceneX();
        mouseYPos = e.getSceneY();
        widgetXPos = this.getLayoutX();
        widgetYPos = this.getLayoutY();
        this.relocate(widgetXPos + mouseXPos, widgetYPos + mouseYPos);
        // the widget relocated to this Updated new location
        Bounds parentBounds = parent_.getBoundsInParent();
        Bounds bounds = output.localToScene(output.getBoundsInLocal());

        if ( line_ != null ) {
            line_.setStartX(bounds.getCenterX() - parentBounds.getMinX());
            line_.setStartY(bounds.getCenterY() - parentBounds.getMinY());
            System.out.println("connected");
        }
    }


    private void handleSlider(MouseEvent g, Slider freqSlider, Label freqSliderLabel) {
        int result = (int)freqSlider.getValue();
        freqSliderLabel.setText(this.label + result + "Hz");
        ((SineWave)ac_).setFrequency(freqSlider.getValue());
        audioComponent_ = new SineWave( result );
    }
    private void setFrequency(MouseEvent e, Slider freqSlider){
//        ((SineWave)ac_).setFrequency(freqSlider.getValue());
    }

    private void closeWidget(){
        parent_.getChildren().remove(this);
        FinalSynthesizeApplication.widgets_.remove(this);
        FinalSynthesizeApplication.Connected_widgets_.remove(this);
        parent_.getChildren().remove(line_);
    }
    public AudioComponent getAudioComponent() { return audioComponent_;}

}
