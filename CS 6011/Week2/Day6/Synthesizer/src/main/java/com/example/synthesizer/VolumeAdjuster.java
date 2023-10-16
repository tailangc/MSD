package com.example.synthesizer;

public class VolumeAdjuster implements AudioComponent{
    double scale;
    AudioComponent input;

    public VolumeAdjuster (double index){
        scale = index;

    }

    @Override
    public AudioClip getClip(){
        AudioClip original = input.getClip();
        AudioClip result = new AudioClip();

        for (int i = 0; i < AudioClip.TOTAL_SAMPLES; i++){
            int adjustedValue = (int)(original.getSample(i) * scale);

            if (adjustedValue >= Short.MAX_VALUE){
                adjustedValue = Short.MAX_VALUE;
            } else if (adjustedValue <= Short.MIN_VALUE) {
                adjustedValue = Short.MIN_VALUE;
            }

            result.setSample(i,adjustedValue);
        }
        return result;
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
