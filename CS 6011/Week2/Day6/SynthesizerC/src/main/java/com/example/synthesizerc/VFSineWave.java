package com.example.synthesizerc;

public class VFSineWave implements AudioComponent {
    AudioComponent input_;
    //AudioClip ramp;

    @Override
    public AudioClip getClip() {

       // AudioClip testClip = new AudioClip();
        float phase=0;
        AudioClip output = new AudioClip();
        output=input_.getClip();
        for(int i = 0; i <AudioClip.TOTAL_SAMPLES; i++)
        {
            phase += (float) (2 * Math.PI * output.getSample(i) / 44100);
            int sinvalue=(int) (Short.MAX_VALUE * Math.sin(phase));
            output.setSample(i,sinvalue);
        }
        return output;
    }

    @Override
    public boolean hasInput() {
        return true;
    }

    @Override
    public void connectInput(AudioComponent input) {
        this.input_=input;
      //  ramp = input.getClip();
    }
}