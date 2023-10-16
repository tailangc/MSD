package com.example.synthesizer;
import java.util.ArrayList;

public class Mixer implements AudioComponent{

    public ArrayList<AudioComponent> inputArray;
    public Mixer(){
        this.inputArray = new ArrayList<>();
    }

    @Override
    public AudioClip getClip() {
        AudioClip sample = new AudioClip();
        for(AudioComponent input : inputArray){
            VolumeAdjuster lowerVolume = new VolumeAdjuster(.25);
            lowerVolume.connectInput(input);

            AudioClip inputClip = lowerVolume.getClip();
            for(int i = 0; i < inputClip.TOTAL_SAMPLES; i++){
                sample.setSample(i, inputClip.getSample(i)+sample.getSample(i));
            }
        }
        return sample;
    }

    @Override
    public boolean hasInput() {
        return false;
    }

    @Override
    public void connectInput(AudioComponent input) {
        inputArray.add(input);
    }
}
