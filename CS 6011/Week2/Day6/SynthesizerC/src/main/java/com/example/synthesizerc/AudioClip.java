package com.example.synthesizerc;

import java.util.Arrays;

public class AudioClip {
    private static final double duration  = 2.0; // creat const duration for 2 seconds
    private static final int sampleRate = 44100;//creat const sampleRate for 44.1 KHz
    byte[] data;
    public static final int TOTAL_SAMPLES = (int) duration* sampleRate; // creat total samples is duration times sampleRate
    static private byte[] audioClipArray = new byte[(int) (duration * sampleRate * 2)];
    // creat new audioClipArray and times 2 for the audioClipArray
    public static int getSample( int index) {//get the index sample
        int lowerByte = audioClipArray[ 2 * index];
        int upperByte = audioClipArray[(2*index) + 1 ];
        int result = (upperByte << 8) | (lowerByte & 0xFF);
        return result;
        //for example byte0 is 10001001  byte1 is 10101101
        //(Byte1 << 8) ganna be   10101101 00000000
        //(Byte0 & 0xFF) ganna be 00000000 10001001
        // | those two ganna be   10101101 10001001
        //lower byte -> 0000000000000000 00000010
        //upper byte -> 0000000 10001001 00000010
    }
    public static void setSample (int index, int value) {//set the index sample
        byte lowerbyte= (byte) (value & 0xff);
        byte upperbyte =  (byte) (value >> 8);
        audioClipArray[index * 2] = lowerbyte;
        audioClipArray[index * 2 + 1] = upperbyte;
        //for example value is  0001 0011 1000 1000
        //the audioClipArray[0] is the last byte of the value which is 1000 1000
        // and the audioClipArray[1] is move value >> 8, so we get the 0001 0011
    }
    public byte[] getData(){
        return Arrays.copyOf(audioClipArray,audioClipArray.length);
    }        // Return a copy of the audio data
}
