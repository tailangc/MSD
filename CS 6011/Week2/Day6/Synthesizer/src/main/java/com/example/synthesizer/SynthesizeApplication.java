package com.example.synthesizer;
import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.control.TextField;
import javafx.scene.input.DragEvent;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.stage.Stage;

import javax.sound.sampled.AudioFormat;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.sound.sampled.LineUnavailableException;
import java.io.IOException;
import java.util.ArrayList;

public class SynthesizeApplication extends Application {

    AnchorPane mainCenter;
    public static Circle speaker;

    public static ArrayList<AudioComponentWidget> widgets = new ArrayList<>();
    public static ArrayList<AudioComponentWidget> ConnectedWidgets = new ArrayList<>();

    @Override
    public void start(Stage stage) throws IOException {


        BorderPane mainLayout = new BorderPane();

        //RightPanel
        VBox rightpanel = new VBox();
        rightpanel.setStyle("-fx-background-color: #b97241");
        rightpanel.setPadding(new Insets(4));
        Button sinwaveBtn = new Button("Sinewave");
        Button mixerBtn = new Button("Mixer");
        mixerBtn.setOnAction(e->creatComponent(e));
//        sinwaveBtn.setOnAction(e->creatMixer(e));
        rightpanel.getChildren().add(mixerBtn);
        rightpanel.getChildren().add(sinwaveBtn);


        //CenterPanel
        mainCenter = new AnchorPane();
        mainCenter.setStyle("-fx-background-color: #e0c094");
        Circle speaker = new Circle(400,200,15);
        speaker.setFill(Color.DARKBLUE);
        mainCenter.getChildren().add(speaker);



        mainLayout.setRight(rightpanel);
        mainLayout.setCenter(mainCenter);

        //BottomPanel
        HBox bottomPanel = new HBox();
        bottomPanel.setStyle("-fx-background-color: #5b1616");
        Button playBtn = new Button("Play");
        playBtn.setOnAction(e->playAudio(e));
        bottomPanel.getChildren().add(playBtn);
        mainLayout.setBottom(bottomPanel);


        Scene scene = new Scene(mainLayout, 320, 340);
        stage.setTitle("Hello!");
        stage.setScene(scene);
        stage.show();


//        Mainlayout.setStyle("-fx-padding: 10; -fx-background-color: white");
//        Label frequencyLabel = new Label("SineWave");
//        frequencyLabel.setStyle("-fx-font: 12; -fx-font-weight: bold");
//
//        VBox freqBox = new VBox();
//        freqBox.setStyle("-fx-background-color: yellow");
//        freqBox.relocate(70,120);
//
//        Slider freqSlider = new Slider(200,400,320);
//
//        freqBox.getChildren().add(frequencyLabel);
//        freqBox.getChildren().add(freqSlider);
//        freqSlider.setOnMouseDragged(g->handleFreq(g, freqSlider, frequencyLabel));
//
//        VBox v1 = new VBox();
//        Label l1 = new Label("Dragging");
//        l1.setStyle("-fx-background-color: red");
//        v1.getChildren().add(l1);
//        freqSlider.setOnMouseDragged(g->handleFreq(g, freqSlider, frequencyLabel));
//        Mainlayout.getChildren().add(v1);
//
//
//        Mainlayout.getChildren().add(freqBox);
//
//
//
//        VBox rightpanel = new VBox();
//        rightpanel.setStyle("-fx-background-colour: lightblue");
//        rightpanel.setPadding(new Insets(4));
//        Button sinwaveBtn = new Button("Sinewave");
//        sinwaveBtn.setOnAction(e->creatComponent(e));






    }

    private void playAudio(ActionEvent e) {
        try {
            Clip c = AudioSystem.getClip();
            AudioFormat format16 = new AudioFormat(44100, 16, 1, true, false);

            Mixer mixer = new Mixer();
            for(AudioComponentWidget w : widgets){
                AudioComponent ac = w.ac_;
                mixer.connectInput(ac);
                //get
            }

            AudioClip clip = mixer.getClip();
//          byte[] data = widgets.get(0).ac_.getClip().getData();
            c.open(format16, clip.getData(), 0, clip.getData().length);
            c.start();
            AudioListener listener = new AudioListener(c);
            c.addLineListener(listener);
        }
        catch(LineUnavailableException k){
            System.out.println(k.getMessage());

        }

    }

//    private void handleFreq(MouseEvent g, Slider freqSlider, Label frequencyLabel) {
//        int result = (int) freqSlider.getValue();
//        frequencyLabel.setText("SineWave" + result + "Hz");
//    }



    private void creatComponent(ActionEvent e) {
//        System.out.println("button being clickled");
        AudioComponent sineWave = new SineWave(200);
        AudioComponentWidget acw = new AudioComponentWidget(sineWave, mainCenter);
        mainCenter.getChildren().add(acw);
        widgets.add(acw);
    }

//    private void creatMixer(ActionEvent e) {
////        System.out.println("button being clickled");
//        Mixer mixer = new Mixer();
//        AudioComponentWidget acw = new AudioComponentWidget(sineWave, mainCenter);
//        mainCenter.getChildren().add(acw);
//        widgets.add(acw);
//    }

    public static void main(String[] args) {
        launch();
    }
}