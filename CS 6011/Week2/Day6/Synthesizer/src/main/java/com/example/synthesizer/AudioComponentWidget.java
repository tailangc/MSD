package com.example.synthesizer;

import javafx.event.ActionEvent;
import javafx.geometry.Bounds;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.control.Label;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Pane;
import javafx.scene.control.Button;
import javafx.scene.control.Slider;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Line;

public class AudioComponentWidget extends Pane {
    AudioComponent ac_;
    AnchorPane parent_;
    double mouseXPos, mouseYPos, widgetXPos, widgetYPos;
    Line line_;

    //Constructor

    AudioComponentWidget (AudioComponent ac, AnchorPane parent){
        ac_ = ac;
        parent_ = parent;


        HBox baseLayout = new HBox();
        baseLayout.setStyle("-fx-border-color: black; -fx-border-image-width: 5; -fx-background-color: white");


        VBox rightSide = new VBox();
        Button closeBtn = new Button("x");
        closeBtn.setOnAction(e->closeWidget(e));
        Circle output = new Circle(10);
        output.setFill(Color.AQUA);

        //Handle Drawing The Line
        output.setOnMousePressed(e -> startConn(e, output));
        output.setOnMouseDragged(e -> moveConn(e, output));
        output.setOnMouseReleased(e -> endConn(e, output));

        rightSide.getChildren().add(closeBtn);
        rightSide.getChildren().add(output);

        rightSide.setAlignment(Pos.CENTER);
        rightSide.setPadding(new Insets(5));
        rightSide.setSpacing(5);

        //SetLeftSide
        VBox leftSide = new VBox();
        Label freqLabel = new Label("SineWave");
        Slider freqSlider = new Slider(200,400,300);
        leftSide.getChildren().add(freqLabel);
        leftSide.getChildren().add(freqSlider);
        leftSide.setOnMousePressed(e -> getPosInfo(e));
        leftSide.setOnMouseDragged((e -> moveWidget(e)));


        freqSlider.setOnMouseDragged(e -> setFrequency(e, freqSlider, freqLabel));
        baseLayout.getChildren().add(leftSide);
        baseLayout.getChildren().add(rightSide);
        this.getChildren().add(baseLayout);



        this.setLayoutX(50);
        this.setLayoutY(50);

    }
    private void closeWidget(ActionEvent e){
        parent_.getChildren().remove(this);
        SynthesizeApplication.widgets.remove(this);
        SynthesizeApplication.ConnectedWidgets.remove(this);
        parent_.getChildren().remove(line_);
    }

    private void setFrequency (MouseEvent e, Slider freqSLider, Label freqLabel){
        ((SineWave)ac_).setFrequency(freqSLider.getValue());
        int val = (int) freqSLider.getValue();
        freqLabel.setText("Sinewave " + val + "Hz");
    }

     private void moveWidget(MouseEvent e){
        double delX = e.getSceneX() - mouseXPos;
        double delY = e.getSceneY() - mouseYPos;

        this.relocate(delX + widgetXPos, delY+widgetYPos);
        //this.relocate (e.getSceneX(), e.getSceneY())
     }

    private void getPosInfo(MouseEvent e){
        mouseXPos = e.getSceneX();
        mouseYPos = e.getSceneY();
        widgetXPos = this.getLayoutX();
        widgetYPos = this.getLayoutY();
    };

    private void startConn(MouseEvent e, Circle output){
        if(line_ != null){
            parent_.getChildren().remove(line_);
        }
        Bounds parentBounds = parent_.getBoundsInParent();
        Bounds bounds = output.localToScene(output.getBoundsInLocal());

        line_ = new Line();
        line_.setStrokeWidth(5);

        line_.setStartX(bounds.getCenterX() - parentBounds.getMinX());
        line_.setStartY(bounds.getCenterY() - parentBounds.getMinY());

        line_.setEndX(e.getSceneX());
        line_.setEndY(e.getSceneY());

        parent_.getChildren().add(line_);
    }

    private void moveConn (MouseEvent e, Circle output){
        Bounds parentBound = parent_.getBoundsInParent();
        line_.setEndX(e.getSceneX() - parentBound.getMinX());
        line_.setEndY(e.getSceneY() - parentBound.getMinY());
    }

    private void endConn (MouseEvent e, Circle output){
        Circle speaker = SynthesizeApplication.speaker;
        Bounds speakerBounds = speaker.localToScene(speaker.getBoundsInLocal());
        double distance = Math.sqrt(Math.pow(speakerBounds.getCenterX() - e.getSceneX(), 2.0)+Math.pow(speakerBounds.getCenterY() - e.getSceneY(), 2.0));
        if (distance < 10){
            SynthesizeApplication.widgets.add(this);
        }
        else{
            parent_.getChildren().remove(line_);
            line_ = null;
        }
    }


}
