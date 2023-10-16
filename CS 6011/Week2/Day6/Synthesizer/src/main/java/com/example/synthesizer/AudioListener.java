package com.example.synthesizer;
import javax.sound.sampled.Clip;
import javax.sound.sampled.LineEvent;
import javax.sound.sampled.LineListener;


public class AudioListener implements LineListener {
    public AudioListener (Clip c) {

        clip_ = c;
    }

    private Clip clip_;
    @Override
    public void update(LineEvent event) {
        if(event.getType() == LineEvent.Type.STOP){
            clip_.close();
        }
    }

}
