package com.example.synthesizerc;

import javafx.geometry.Bounds;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.paint.RadialGradient;
import javafx.scene.paint.Stop;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Line;

public class AudioComponentWidgetBase extends Pane {
    AudioComponent ac_;
    String label;
    static AnchorPane parent_;
    double mouseXPos, mouseYPos, widgetXPos, widgetYPos,lineXpos,lineYPos, lineEndX, lineEndY;
    Line line_;
    VBox leftside ;
    VBox rightSide;
    Label freqLabel;
    AudioComponentWidgetBase prev;
    public AudioComponentWidgetBase(AudioComponent ac, AnchorPane parent , String label) {
        ac_ = ac;
        parent_= parent;

        this.label = label;
        HBox baseLayout = new HBox();
        baseLayout.setStyle("-fx-border-color: black;-fx-border-image-width:5 ");
        rightSide= new VBox();
        Button closeBtn= new Button("x");
        closeBtn.setOnAction(actionEvent -> {
            closeWidget();
//            if(FinalSynthesizeApplication.mixerBtn.isDisable() && this instanceof MixerWidget){
//                FinalSynthesizeApplication.mixerBtn.setDisable(false);
//            }
        });
        Circle output= new Circle(10);
        RadialGradient gradient1 = new RadialGradient(0,
                .1,
                0.5,
                0.5,
                2,
                true,
                javafx.scene.paint.CycleMethod.NO_CYCLE,
                new Stop(0, Color.WHITE),
                new Stop(0.5, Color.BLACK));
        output.setFill(gradient1);

        //handle drawing the line - handle 3 events
        output.setOnMousePressed(e->startConn(e,output));
        output.setOnMouseDragged(e->moveConn(e,output));
        output.setOnMouseReleased(e->endConn(e,output));
        rightSide.getChildren().add(closeBtn);
        rightSide.getChildren().add(output);

        rightSide.setAlignment(Pos.CENTER);
        rightSide.setPadding(new Insets(5));
        rightSide.setSpacing(5);


        //left side
        leftside = new VBox();
        freqLabel  = new Label(label);
        leftside.getChildren().add(freqLabel);
        leftside.setOnMousePressed(e->getPosInf(e));
        leftside.setOnMouseDragged(e->moveWidget(e,output));

        baseLayout.getChildren().add(leftside);
        baseLayout.getChildren().add(rightSide);

        this.getChildren().add(baseLayout);

        this.setLayoutX(50);
        this.setLayoutY(50);

    }
    private void moveWidget(MouseEvent e,Circle output) {
        // Calculate the new position based on the mouse movement
        double deltaX = e.getSceneX() - mouseXPos;
        double deltaY = e.getSceneY() - mouseYPos;

        // Update the pane position
        this.setLayoutX(widgetXPos + deltaX);
        this.setLayoutY(widgetYPos + deltaY);
        if(line_ != null){
            // Calculate the new line start position based on the pane movement
            double newLineStartX = lineXpos + deltaX;
            double newLineStartY = lineYPos + deltaY;

            // Update the line's start position
            line_.setStartX(newLineStartX);
            line_.setStartY(newLineStartY);
        }
        // Update the line's end position(prev)
        if(prev != null && prev.line_ != null) {
            double newLineEndX = lineEndX + deltaX;
            double newLinkEndY = lineEndY + deltaY;
            this.prev.line_.setEndX(newLineEndX);
            this.prev.line_.setEndY(newLinkEndY);
        }

    }



    private void getPosInf(MouseEvent e) {
        mouseXPos = e.getSceneX();
        mouseYPos = e.getSceneY();
        widgetXPos = this.getLayoutX();
        widgetYPos = this.getLayoutY();
        if(line_ != null){
            lineXpos = line_.getStartX();
            lineYPos = line_.getStartY();
        }
        if(prev != null) {
            if (prev.line_ != null) {
                lineEndX = prev.line_.getEndX();
                lineEndY = prev.line_.getEndY();
            }
        }



    }

//
    private void closeWidget(){
        parent_.getChildren().remove(this);
        FinalSynthesizeApplication.widgets_.remove(this);
        FinalSynthesizeApplication.Connected_widgets_.remove(this);
        parent_.getChildren().remove(line_);
        System.out.println("remove the line"); // remove that line so that we can create a new connection
        if (prev != null && prev.line_ != null){
            parent_.getChildren().remove(prev.line_);
        }



    }


    void handleSineWaveLine(MouseEvent e, Circle mixer, Circle volume, AudioComponentWidgetBase audioComponentWidgetBase){
        System.out.println("Sine Wave Line");
        if(mixer != null){
        Bounds mixerBounds= mixer.localToScene(mixer.getBoundsInLocal());
        double mixerDistance = Math.sqrt(Math.pow(mixerBounds.getCenterX()-e.getSceneX(),2.0) +
                Math.pow(mixerBounds.getCenterY()-e.getSceneY(),2.0 ));
            if(mixerDistance<10){
                // Handle It is Connected to Mixer
//                System.out.println("Connected Sine Wave to  Mixer");
                FinalSynthesizeApplication.Connected_widgets_.add(this);
                FinalSynthesizeApplication.mix.prev = audioComponentWidgetBase;
            }
            else {
                parent_.getChildren().remove(line_);
                System.out.println("mixer distance is "+mixerDistance);
            }

        }
        else if(volume != null){
            Bounds volumeBounds= volume.localToScene(volume.getBoundsInLocal());
            double volDistance = Math.sqrt(Math.pow(volumeBounds.getCenterX()-e.getSceneX(),2.0) +
                    Math.pow(volumeBounds.getCenterY()-e.getSceneY(),2.0 ));
            if (volDistance<10){
                // Handle It is Connected to Volume
                System.out.println("Connected  Sine Wave to Volume");
                FinalSynthesizeApplication.Connected_widgets_.add(this);
                FinalSynthesizeApplication.vol.prev = audioComponentWidgetBase;
            }
            else {
                parent_.getChildren().remove(line_);
                System.out.println("volume distance is "+volDistance);
            }
        }
        else {
            parent_.getChildren().remove(line_);
        }
    }
    void handleMixerLine(MouseEvent e, Circle mixer, Circle volume, AudioComponentWidgetBase audioComponentWidgetBase){
        System.out.println("Mixer Wave Line");

        if(volume != null){
            Bounds volumeBounds= volume.localToScene(volume.getBoundsInLocal());
            double volDistance = Math.sqrt(Math.pow(volumeBounds.getCenterX()-e.getSceneX(),2.0) +
                    Math.pow(volumeBounds.getCenterY()-e.getSceneY(),2.0 ));
            if (volDistance< volume.getRadius()){
                System.out.println("Connected From  Mixer to Volume");
                FinalSynthesizeApplication.vol.prev = audioComponentWidgetBase;
            }
            else {
                System.out.println("mixer distance to volume "+volDistance);
                parent_.getChildren().remove(line_);
                line_ = null;
            }

        }
        else if(mixer != null){
            Bounds mixerBounds= mixer.localToScene(mixer.getBoundsInLocal());
            double mixerDistance = Math.sqrt(Math.pow(mixerBounds.getCenterX()-e.getSceneX(),2.0) +
                    Math.pow(mixerBounds.getCenterY()-e.getSceneY(),2.0 ));
            if(mixerDistance<mixer.getRadius()){
                System.out.println("Connected to Another Mixer");
                FinalSynthesizeApplication.mix.prev = audioComponentWidgetBase;
            }
            else {
                System.out.println("mixer distance to mixer "+mixerDistance);
                parent_.getChildren().remove(line_);
                line_ = null;
            }

        }
    }
    void handleVolumeLine(Circle speaker, MouseEvent e, AudioComponentWidgetBase audioComponentWidgetBase){
        System.out.println("Volume Line");
        Bounds speakerBounds= speaker.localToScene(speaker.getBoundsInLocal());
        double distance = Math.sqrt(Math.pow(speakerBounds.getCenterX()-e.getSceneX(),2.0) +
                Math.pow(speakerBounds.getCenterY()-e.getSceneY(),2.0 ));
        if(distance<10){
            System.out.println("Connected From  Volume to Speaker");
        }
        else {
            parent_.getChildren().remove(line_);
            System.out.println("speaker distance is "+distance);

        }
    }
    void endConn(MouseEvent e ,Circle output) {
        Circle speaker = FinalSynthesizeApplication.speaker;
        Circle mixer = MixerWidget.inputMixerCirle;
        Circle volume = VolumeWidget.VolumeInputCircle;
        Bounds speakerBounds= speaker.localToScene(speaker.getBoundsInLocal());
        double distance = Math.sqrt(Math.pow(speakerBounds.getCenterX()-e.getSceneX(),2.0) +
                Math.pow(speakerBounds.getCenterY()-e.getSceneY(),2.0 ));

        // Handle Sine Wave Line
        if(this instanceof  SineWaveWidget){
            handleSineWaveLine(e,mixer,volume, this);
        }
        if(this instanceof  VolumeWidget){
            handleVolumeLine(speaker,e, this);
        }
        if(this instanceof  MixerWidget){
            handleMixerLine(e,mixer,volume, this);
        }
    }


//    void endConn(MouseEvent e, Circle output) {
//        Circle speaker = FinalSynthesizeApplication.speaker;
//        Circle mixer = MixerWidget.inputMixerCirle;
//        Circle volume = VolumeWidget.VolumeInputCircle;
//        Bounds speakerBounds= speaker.localToScene(speaker.getBoundsInLocal());
//        double distance = Math.sqrt(Math.pow(speakerBounds.getCenterX()-e.getSceneX(),2.0) +
//                Math.pow(speakerBounds.getCenterY()-e.getSceneY(),2.0 ));
//        if(distance < 10){
//            FinalSynthesizeApplication.Connected_widgets_.add(this);
//        }
//        else{
//            System.out.println("speaker distance is "+distance);
//        }
//        if(mixer != null){
//            Bounds mixerBounds= mixer.localToScene(mixer.getBoundsInLocal());
//            double mixerDistance = Math.sqrt(Math.pow(mixerBounds.getCenterX()-e.getSceneX(),2.0) +
//                    Math.pow(mixerBounds.getCenterY()-e.getSceneY(),2.0 ));
//            if(mixerDistance<10){
//                FinalSynthesizeApplication.Connected_widgets_.add(this);
//                //better to create a new array list for connected widgets only
//                //the wave to some array list
//            }
//            else {
//                System.out.println("mixer distance is "+mixerDistance);
//            }
//        }
//
//        if(volume != null){
//            Bounds volumeBounds= volume.localToScene(volume.getBoundsInLocal());
//            double volDistance = Math.sqrt(Math.pow(volumeBounds.getCenterX()-e.getSceneX(),2.0) +
//                    Math.pow(volumeBounds.getCenterY()-e.getSceneY(),2.0 ));
//            if(volDistance<10){
//
//                FinalSynthesizeApplication.Connected_widgets_.add(this);
//
//            }
//            else {
//                System.out.println("volume distance is "+volDistance);
//            }
//        }
//
//
//    }

    void moveConn(MouseEvent e, Circle output) {
        Bounds parentBounds = parent_.getBoundsInParent();
        line_.setEndX(e.getSceneX()-parentBounds.getMinX());
        line_.setEndY(e.getSceneY()- parentBounds.getMinY());

    }

    void startConn(MouseEvent e, Circle output) {
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

}

