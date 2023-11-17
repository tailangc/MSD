package com.example.synthesizerc;

public class SineWave implements AudioComponent{
    double frequency;//Used to store the frequency of the sine wave用于存储正弦波的频率
    double sampleRate=44100;//:采样率，默认为 44100 Hz。
    AudioComponent input_;
    public SineWave(double freq){//构造函数，接受频率作为参数，并将其赋值给 frequency
        //Constructor，Accepts frequency as a parameter and assigns it to frequency
        this.frequency=freq;
    }
    public void setFrequency(double frequency){
        this.frequency=frequency;
    }
    @Override
    public AudioClip getClip() {
        //该方法实现了 AudioComponent 接口的方法，用于生成代表正弦波的音频片段。
        //首先创建一个新的 AudioClip 对象用于存储音频片段。
        //然后通过正弦波的数学公式计算每个采样点的值，并将其设置到 AudioClip 中。
        //返回填充好的 AudioClip 对象。
        //create a new AudioClip
        AudioClip clip = new AudioClip();//creat new AudioClip to store the  audio clip.
        int result;
        //sample[ i ] = maxValue * sine( 2*pi*frequency * i / sampleRate );
        for(int i=0; i<AudioClip.TOTAL_SAMPLES;i++){//loop over the data of AudioClip
        //fill the array with the formula provided
            result =(int)(Short.MAX_VALUE * Math.sin(2*Math.PI*frequency * i / sampleRate) );
            clip.setSample(i,result);//i is x ,y is result
        }
        return clip;
    }

    @Override
    public boolean hasInput() {
        return true;//实现 AudioComponent 接口的方法，指示该音频组件是否有输入。在这里，总是返回 true。
    }
    @Override
    public void connectInput(AudioComponent input) {
        input_ = input;//实现 AudioComponent 接口的方法，用于连接输入音频组件。在这里，将传入的音频组件存储到 input_ 成员变量中。
//        SineWave sn = (SineWave) input;
//        this.frequency = sn.frequency;
    }
}//这段代码定义了一个能生成正弦波音频片段的音频组件，频率由构造函数指定，然后通过 getClip() 方法生成对应的音频片段。
