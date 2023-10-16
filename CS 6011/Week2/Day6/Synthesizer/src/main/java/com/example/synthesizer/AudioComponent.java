package com.example.synthesizer;

public interface AudioComponent {
    public AudioClip getClip();

    public boolean hasInput();

    void connectInput( AudioComponent input);

}

