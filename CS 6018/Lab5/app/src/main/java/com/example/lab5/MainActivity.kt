package com.example.lab5

import android.hardware.Sensor
import android.hardware.SensorEvent
import android.hardware.SensorEventListener
import android.hardware.SensorManager
import android.os.Bundle
import android.util.Log
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.BoxWithConstraints
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.runtime.getValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Canvas
import androidx.compose.ui.graphics.Color
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import com.example.lab5.ui.theme.Lab5Theme
import kotlinx.coroutines.channels.awaitClose
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.channelFlow
import androidx.compose.foundation.Canvas
import androidx.compose.runtime.Composable
import androidx.compose.ui.geometry.Offset
import androidx.lifecycle.viewmodel.compose.viewModel


class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        val sensorManager = getSystemService(SENSOR_SERVICE) as SensorManager
        val gravSensor = sensorManager.getDefaultSensor(Sensor.TYPE_GRAVITY)
        val gravFlow : Flow<FloatArray> = getGravData(gravSensor, sensorManager)

        setContent {

            Lab5Theme {
                Surface(

                    modifier = Modifier.fillMaxSize(),
                    color = MaterialTheme.colorScheme.background
                ) {
                    val viewModel: BallViewModel = viewModel()
                    val gravReading by gravFlow.collectAsStateWithLifecycle(
                        floatArrayOf(0.0f, 0.0f, 0.0f),
                        lifecycleOwner = this@MainActivity
                    )

                    BoxWithConstraints(
                        Modifier
                            .fillMaxSize()
                            .background(Color.Gray),
                    ) {

                        Canvas(
                            modifier = Modifier
                                .fillMaxSize()
                        ) {

                            val centerX = size.width / 2
                            val centerY = size.height / 2

                            viewModel.changeLocation(gravReading, size.width/2, size.height/2)
                            // Draw the circle
                            drawCircle(
                                color = Color.Yellow,
                                center = Offset(centerX + viewModel.x.value!!, centerY + viewModel.y.value!!),
                                radius = 20f
                            )
                        }

                    }
                }
            }
        }
    }
}

fun getGravData(sensor: Sensor?, sensorManager: SensorManager): Flow<FloatArray> {
    return channelFlow {
        val listener = object : SensorEventListener {
            override fun onSensorChanged(event: SensorEvent?) {
                if (event !== null) {
                    Log.e("Sensor event!", event.values.toString())
                    var success = channel.trySend(event.values.copyOf()).isSuccess
                    Log.e("success?", success.toString())
                }

            }

            override fun onAccuracyChanged(sensor: Sensor?, accuracy: Int) {
                //If you care :shrug:
            }
        }
        sensorManager.registerListener(listener, sensor, SensorManager.SENSOR_DELAY_GAME)

        awaitClose {
            sensorManager.unregisterListener(listener)
        }
    }
}