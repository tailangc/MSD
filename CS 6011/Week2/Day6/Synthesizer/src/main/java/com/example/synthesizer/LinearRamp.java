package com.example.synthesizer;

public class LinearRamp implements AudioComponent{
    float start;
    float stop;

    public LinearRamp(float start, float stop){
        this.start = start;
        this.stop = stop;
    }

    @Override
    public AudioClip getClip(){
        AudioClip clip = new AudioClip();
        for (int i = 0; i < AudioClip.TOTAL_SAMPLES; i++){
            int result = (int) ((start * (AudioClip.TOTAL_SAMPLES - i) + stop * i)/ AudioClip.TOTAL_SAMPLES);
            clip.setSample(i, result);
        }
        return clip;
    }

    @Override
    public boolean hasInput(){
        return false;
    }

    @Override
    public void connectInput (AudioComponent input){

    }


}
