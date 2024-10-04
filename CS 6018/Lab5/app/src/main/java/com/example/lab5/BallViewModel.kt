package com.example.lab5


import android.graphics.Bitmap
import android.util.Half.abs
import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel
import kotlin.math.abs

class BallViewModel : ViewModel() {
    private val _x : MutableLiveData<Float> = MutableLiveData<Float>(0.0f)
    private val _y : MutableLiveData<Float> = MutableLiveData<Float>(0.0f)

    val x = _x as LiveData<Float>
    val y = _y as LiveData<Float>

    fun changeLocation(gravArray: FloatArray, maxX: Float, maxY:Float){

        val speed = 1

        val x_offset = _x.value!!.minus(gravArray[0] * speed)
        if(abs(x_offset) < maxX) {
            _x.value = x_offset
        }

        val y_offset = _y.value!!.plus(gravArray[1] * speed)
        if(abs(y_offset) < maxY) {
            _y.value = y_offset
        }
    }
}