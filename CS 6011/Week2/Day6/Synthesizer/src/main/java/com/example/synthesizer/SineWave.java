package com.example.synthesizer;
public class SineWave implements AudioComponent{

    double frequency;

    public SineWave(double frq){
        this.frequency = frq;
    }

    @Override
    public AudioClip getClip(){
        AudioClip clip = new AudioClip();
        for (int i = 0; i < AudioClip.TOTAL_SAMPLES; i++){
            int result = (int) (Short.MAX_VALUE * Math.sin(2*Math.PI*frequency*i / AudioClip.sampleRate));
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


    public void setFrequency(double frequency) {
        this.frequency = frequency;
    }

    public double getFrequency() {
        return frequency;
    }
}
