package com.example.synthesizerc;
//定义了一个名为LinearRamp的类，实现了AudioComponent接口。LinearRamp类代表一个线性斜坡音频组件，可以生成一个线性变化的音频剪辑
//LinearRamp类用于生成一个音频剪辑，该音频剪辑包含一个线性斜坡，该斜坡从 start_ 到 stop_ 进行渐变。
public class LinearRamp implements AudioComponent{
    public float start_;
    public float stop_;
    LinearRamp(float start, float stop){//Constructor and assigns them to start_ and stop_
        this.start_ = start;
        this.stop_ = stop;
    }
    @Override
    public AudioClip getClip() {
        AudioClip testClip = new AudioClip();
        for(int i = 0; i <AudioClip.TOTAL_SAMPLES; i++)
        {
            int setTo = (int) ( (start_ * (AudioClip.TOTAL_SAMPLES - i ) + stop_ * i ) / AudioClip.TOTAL_SAMPLES);
            testClip.setSample(i, setTo);
        }
        return testClip;
    }//这个方法生成一个 AudioClip 对象，其中音频样本是一个线性斜坡，
    // 从 start_ 到 stop_ 进行渐变。它通过迭代音频样本并应用线性插值来创建渐变。
    @Override
    public boolean hasInput() {
        return false;
    }
    //这些方法是AudioComponent接口的实现。hasInput() 始终返回 false，
    // 表示该音频组件没有输入。
    @Override
    public void connectInput(AudioComponent input) {
    }//connectInput() 方法为空实现，因为该组件不需要连接输入。
}