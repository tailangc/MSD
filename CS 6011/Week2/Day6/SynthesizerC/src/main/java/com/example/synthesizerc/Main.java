package com.example.synthesizerc;
import javax.sound.sampled.*;

public class Main {
//Part 3: Hearing a Sine Wave!
  public static void main(String[] args) throws LineUnavailableException {
    // Get properties from the system about samples rates, etc.
// AudioSystem is a class from the Java standard library.
    Clip c = AudioSystem.getClip(); // Note, this is different from our AudioClip class.

// This is the format that we're following, 44.1 KHz mono audio, 16 bits per sample.
    AudioFormat format16 = new AudioFormat(44100, 16, 1, true, false);
    //Part 0: More Synth Components
//    AudioComponent linearRamp = new LinearRamp(50,10000);
//    AudioComponent VarFreqWave = new VFSineWave();
//
//    VarFreqWave.connectInput(linearRamp);

    //part5//
    // Create a mixer
    Mixer mixer = new Mixer();
    // Create instances of audio components
    AudioComponent gen = new SineWave(370);
    AudioComponent gen1 = new SineWave(330);
    AudioComponent gen2 = new SineWave(440);

    // Connect audio components to the mixer
    mixer.connectInput(gen1);
    mixer.connectInput(gen2);
    mixer.connectInput(gen);

//    VolumeAdjuster lowerVolume = new VolumeAdjuster(1);
//    lowerVolume.connectInput(linearRamp);

    AudioClip mixedClip = gen.getClip();


    c.open(format16, mixedClip.getData(), 0, mixedClip.getData().length); // Reads data from our byte array to play it.

    System.out.println("About to play...");
    c.start(); // Plays it.
    c.loop(0); // Plays it 2 more times if desired, so 6 seconds total

// Makes sure the program doesn't quit before the sound plays.
    while (c.getFramePosition() < AudioClip.TOTAL_SAMPLES || c.isActive() || c.isRunning()) {
      // Do nothing while we wait for the note to play.
    }

    System.out.println("Done.");
    c.close();
  }

}
