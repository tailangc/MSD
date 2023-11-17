package com.example.synthesizerc;

public class Volume implements AudioComponent{
    private double volumeScale;
    private AudioComponent input_; // from the interface AudioComponent how to bring in your sineWave

    // constructor
    Volume(double vol ) {
        volumeScale = vol;
    }


    Volume( ) {

    }
    @Override
    public AudioClip getClip() {
        AudioClip AdjustedClip = new AudioClip();
        AudioClip original = input_.getClip();

        for ( int i= 0; i< AudioClip.TOTAL_SAMPLES; i++){

            double adjustedVolume = volumeScale * original.getSample(i);

            if ( adjustedVolume > Short.MAX_VALUE) {
                adjustedVolume = Short.MAX_VALUE;
            } else if (adjustedVolume < Short.MIN_VALUE) {
                adjustedVolume = Short.MIN_VALUE;
            }
            AdjustedClip.setSample(i, (short) adjustedVolume);
            // Todo create a clamp () in the AudioComponent and call it here and in the mixer getClip()
        }
        return AdjustedClip;
    }

    @Override
    public boolean hasInput() {
        return true;
    }


    @Override
    public void connectInput(AudioComponent input) {
        this.input_ = input;
    }

    public void setVolumeScale(double scale){
        volumeScale = scale;
    }

    public void removeInput(AudioComponent input) {
        input_ = null;
    }
}