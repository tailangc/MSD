package com.example.synthesizerc;

public class VolumeAdjuster implements AudioComponent{
    double scale_;//用于存储音频的音量调整比例。设置音量大小
    AudioComponent input_;//用于存储输入音频组件。
    public VolumeAdjuster(double scale){// 构造函数，接受一个参数 scale，用于设置音频的音量调整比例。
        scale_ = scale;
    }
    @Override
    public AudioClip getClip() {//Used to generate audio clips with volume adjustments
        //该方法实现了 AudioComponent 接口的方法，用于生成经过音量调整的音频片段。
        //首先获取输入音频组件的音频片段。
        //对输入音频片段中的每个采样点，将其乘以预设的音量调整比例 scale_，然后进行范围限制，确保样本值不超过 Short 类型的最大和最小值范围。
        //创建一个新的音频片段，并将调整后的样本值填充到新的音频片段中。
        AudioClip original = input_.getClip();//input audio
        AudioClip result = new AudioClip();//new audio
        for(int i = 0; i < AudioClip.TOTAL_SAMPLES; i++) {
            int AdjustedSample = (int)(scale_*original.getSample(i));//将输入音频的第 i 个样本值乘以音量调整比例，得到调整后的样本值。
            int max = Short.MAX_VALUE;//get the max value
            int min = Short.MIN_VALUE;//get the min value
            if(AdjustedSample > max){// see if bigger then the max then = to it
                AdjustedSample = max;
            } else if(AdjustedSample < min){// see if small then the min then = to it
                AdjustedSample = min;
            }//Limit the range to ensure that the sample size does not exceed Short
            result.setSample(i, AdjustedSample);//
        }
        return result;
    }


    @Override
    public boolean hasInput() {
        return true;
    }

    @Override//用于连接输入音频组件。在这里，将传入的音频组件存储到 input_ 中。
    public void connectInput(AudioComponent input) {
        input_ = input;
    }

    public void removeInput(AudioComponent input) {
        input_ = null;
    }
}

