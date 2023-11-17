package com.example.synthesizerc;

import java.util.ArrayList;

//实现一个名为 Mixer 的类，该类实现了 AudioComponent 接口，用于混合多个音频输入并生成合成的音频片段。
public class Mixer implements AudioComponent{
    private ArrayList<AudioComponent> inputs;//A list of input audio components to store用于存储输入音频组件的列表
    public Mixer() {//构造函数，初始化 inputs 列表为空
        this.inputs = new ArrayList<>();
    }

    @Override
    public AudioClip getClip() {//Used to generate mixed audio clips.

        // Initialize an empty AudioClip
        AudioClip sample = new AudioClip();
        // Mix audio from all input components
        for (AudioComponent input : inputs) {
            //Go through all the input audio components,
            //and make the clip lowerVolume.and put in to the inputClip
            VolumeAdjuster lowerVolume = new VolumeAdjuster(.25);
            lowerVolume.connectInput(input);
            AudioClip inputClip = lowerVolume.getClip();
//The sample value of the corresponding position is obtained from each input audio clip and blended together.
            for (int i = 0; i < AudioClip.TOTAL_SAMPLES; i++) {
                sample.setSample(i, (inputClip.getSample(i) + sample.getSample(i)));
            }//loop all the data and put the i and the lowerVolume + the sample.getS to the sample.setS
        }
        return sample;
    }

    @Override
    public boolean hasInput() {
        return true;
    }

    @Override
    public void connectInput(AudioComponent input) {
        inputs.add(input);//this is adding the input to inputs
    }

    public void disconnectInput(AudioComponent input) {
        inputs.remove(input);//用于断开与特定输入音频组件的连接。
    }
}
