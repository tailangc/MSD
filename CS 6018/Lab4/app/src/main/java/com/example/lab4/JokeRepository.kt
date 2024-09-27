package com.example.lab4

import androidx.lifecycle.asLiveData
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.delay
import kotlinx.coroutines.launch
import java.util.Date
import kotlin.random.Random

class JokeRepository( val scope: CoroutineScope, val dao: JokeDAO) {

    val previousJokes = dao.getJokes().asLiveData()
    fun addJoke(joke: String){
        scope.launch {
            dao.addJokeData(
                JokeData(joke))
        }
    }
}