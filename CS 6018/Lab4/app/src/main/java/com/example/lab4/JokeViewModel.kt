package com.example.lab4

import androidx.lifecycle.LiveData
import androidx.lifecycle.ViewModel
import androidx.lifecycle.ViewModelProvider


class JokeViewModel(private val repository: JokeRepository) : ViewModel() {


    val previousJokes: LiveData<List<JokeData>> = repository.previousJokes

    fun addJoke(joke: String){
        repository.addJoke(joke)
    }

}

// This factory class allows us to define custom constructors for the view model
class JokeViewModelFactory(private val repository: JokeRepository) : ViewModelProvider.Factory {
    override fun <T : ViewModel> create(modelClass: Class<T>): T {
        if (modelClass.isAssignableFrom(JokeViewModel::class.java)) {
            @Suppress("UNCHECKED_CAST")
            return JokeViewModel(repository) as T
        }
        throw IllegalArgumentException("Unknown ViewModel class")
    }
}
