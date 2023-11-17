package com.example.synthesizerc;

public interface AudioComponent {
    public AudioClip getClip();
    boolean hasInput();
    void connectInput(AudioComponent input);



}
