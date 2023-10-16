package com.example.synthesizer;
import java.util.Arrays;

public class AudioClip {
    static final int duration = 2;
    static final int sampleRate = 44100;
    public static final int TOTAL_SAMPLES =  (duration * sampleRate);

    public byte[] audioArray = new byte[duration * sampleRate *2];

    public int getSample(int index)
    {
        // sample = 1 short
        int sampleIndex = index * 2; // Each sample occupies 2 bytes
        // take a 2byte sample and push the values to the left 1 byte
        // setting the last 2 bytes of the integer and finding the first and second index of sample
        // 0000 0001 & 1111 1111 ->  0000 0001 shift (left 8) -> 1 0000 0000  or
        // 0000 0010 & 1111 1111 ->  0000 0010 ->                0 0000 0010
        //                                        sample         1 0000 0010
        int sample = ((audioArray[sampleIndex + 1] & 0xFF) << 8) | (audioArray[sampleIndex] & 0xFF);
        // 0000 0000 0000 0000 0000 0000 0001 0000 0010 -> 0000 0001 0000 0010 (short)
        //return the int as short by casting it w/short
        return (short) sample;

//        int sample;
//        //put byte value 1 in teh right position of the short sized index
//        byte byte1 = bytesArray[(index*2)+1];
//        //put the byte value 2 in the first position (left) in the short sized index
//        byte byte2 = bytesArray[(index*2)];
//        // shift the byte1 8 bits so that they don't overlap
////        byte1 <<= 8;
//        //make the sample add the value essential because they will have 0000 0000 in the opposite 2^8 bit sets
//        sample = byte1 << 8;
//        sample = sample | byte2;
//        return sample;

    }

    //every short has two bytes: seperate the bytes with masking
    public void setSample(int index, int value){
        // calculating the index for the bytes int the array of bytes
        // the sample will take 2 bytes
        //if we are looking at index 0 we will get index[0] & index[1]
        //if we are looking at index 1 we will get index[2] & index[2+1]
        int sampleIndex = index * 2;
        // we are splitting the value into 2 separate bytes
        //take the int value 2^31 -> 2- 2^15 values
        // ex.,  1011 1010 1011 1011 ->  0000 0000 1011 1010
        //                               1111 1111 1111 1111
        //                               0000 0000 1011 1010
        byte sample1 = (byte) ((value>>8)&0xFF);
        // ex., 1011 1010 1011 1011 &
        //      1111 1111 1111 1111
        //      1011 1010 1010 1010  we ignore the highest 8 bits

        byte sample2 =(byte) (value & 0xFF);
        // the first byte we get will be assigned to the position on right in the array
        // ex., we will store 1011 1010 for the right index
        audioArray[sampleIndex+1] = sample1;
        // the second byte we get will be assigned to the position before the first byte
        // we will store 1010 1010 for the left index
        audioArray[sampleIndex] = sample2;

        // 1010 1010 1011 1010
    }

    public byte[] getData(){
        //creating a copy of the bytesArray for the entire length as to not mess up data
        return Arrays.copyOf(audioArray, audioArray.length);
    }
}
