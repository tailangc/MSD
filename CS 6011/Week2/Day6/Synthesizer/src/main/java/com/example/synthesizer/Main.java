package com.example.synthesizer;

import com.example.synthesizer.AudioClip;
import com.example.synthesizer.AudioComponent;
import com.example.synthesizer.SineWave;
import javax.sound.sampled.LineUnavailableException;
import java.util.ArrayList;
import javax.sound.sampled.*;
//import javax.sound.sampled.Mixer;

public class Main {
    public static void main(String[] args) throws LineUnavailableException{
        // Get properties from the system about samples rates, etc.
// AudioSystem is a class from the Java standard library.
        Clip c = AudioSystem.getClip(); // Note, this is different from our AudioClip class.
        AudioListener listener = new AudioListener(c);

        // This is the format that we're following, 44.1 KHz mono audio, 16 bits per sample.
        AudioFormat format16 = new AudioFormat( 44100, 16, 1, true, false );

         // Your code

        //part5//
        // Create instances of audio components
        AudioComponent gen = new SineWave(261);
        AudioComponent gen1 = new SineWave(330);
        AudioComponent gen2 = new SineWave(600);
        //AudioComponent gen3 = new SineWave(140);

        VFSineWave wierdTune = new VFSineWave();
        LinearRamp ramp = new LinearRamp(50,2000);
        wierdTune.connectInput(ramp);
        AudioClip tuneClip = wierdTune.getClip();

        //Test VoulmeAdjuster
        VolumeAdjuster adjustedVolume = new VolumeAdjuster(2);
        adjustedVolume.connectInput(gen);
        AudioClip adjustedVoulmeClip = adjustedVolume.getClip();


        // Create a mixer
        Mixer mixer = new Mixer();
        // Connect audio components to the mixer
        mixer.connectInput(gen1);
        mixer.connectInput(gen2);
        mixer.connectInput(gen);
        AudioClip mixedClip = mixer.getClip();


        c.open(format16, tuneClip.getData(), 0, tuneClip.getData().length);

        System.out.println("About to play...");
        c.start(); // Plays it.
        c.addLineListener(listener);
        System.out.println("Done.");
//        c.loop( 0); // Plays it 2 more times if desired, so 6 seconds total

        // Makes sure the program doesn't quit before the sound plays.

    }


}




























