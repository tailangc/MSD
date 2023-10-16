package com.example.synthesizer;

public class VFSineWave implements AudioComponent{
    AudioComponent input;


    @Override
    public AudioClip getClip() {
        AudioClip clip = input.getClip();
        float phase = 0;

        for(int i = 0; i < AudioClip.TOTAL_SAMPLES ; i ++){
            phase += ((2*Math.PI * clip.getSample(i))/AudioClip.sampleRate);
            clip.setSample(i, (int) (Short.MAX_VALUE*Math.sin(phase)));
        }
        return clip;
    }

    @Override
    public boolean hasInput() {
        return true;
    }

    @Override
    public void connectInput(AudioComponent input) {
        this.input = input;
    }
}
