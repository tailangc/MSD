package com.example.lab4

import android.net.Uri
import android.os.Bundle
import android.util.Log
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.viewModels
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.material3.Button
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.getValue
import androidx.compose.runtime.livedata.observeAsState
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.rememberCoroutineScope
import androidx.compose.runtime.setValue
import androidx.compose.ui.Modifier
import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel
import com.example.lab4.ui.theme.Lab4Theme
import com.google.gson.Gson
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.Job
import kotlinx.coroutines.launch
import kotlinx.coroutines.withContext
import java.io.InputStreamReader
import java.net.HttpURLConnection
import java.net.URL



class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {

        val vm: JokeViewModel by viewModels{  JokeViewModelFactory((application as JokeApplication).jokeRepository)}

        super.onCreate(savedInstanceState)
        setContent {
            Lab4Theme {
                // A surface container using the 'background' color from the theme
                Surface(
                    modifier = Modifier.fillMaxSize(),
                    color = MaterialTheme.colorScheme.background
                ) {
                    Column {

                        val scope = rememberCoroutineScope()
                        var job: Job? by remember { mutableStateOf<Job?>((null)) }
                        //val job: State<Job?> = remember {Job()}
                        Row {
                            Button(onClick = {
                                job = scope.launch {
                                    val response = getRandomJokeCoroutine()
                                    vm.addJoke(response.value)
                                }
                            }) {
                                Text("Get New Joke")
                            }
                        }

                        val previousJokes by vm.previousJokes.observeAsState()
                        LazyColumn {
                            for (entry in (previousJokes ?: listOf()).asReversed()) {
                                item {
                                    Text(
                                        "${entry.joke} \n"
                                    )
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    data class ISSResult(var value: String)

    class ISSViewModel : ViewModel() {
        private val _data = MutableLiveData<List<ISSResult>>(listOf())
        val data = _data as LiveData<List<ISSResult>>
        fun addData(newVal: ISSResult) {
            _data.value = _data.value?.plus(newVal)
            Log.e("UPDATE", "${data.value?.size}")
        }
    }

    suspend fun getRandomJokeCoroutine(): ISSResult {
        return withContext(Dispatchers.IO) {

            val url: Uri = Uri.Builder().scheme("https")
                .authority("api.chucknorris.io")
                .appendPath("jokes")
                .appendPath("random").build()

            val conn = URL(url.toString()).openConnection() as HttpURLConnection
            conn.connect()
            val gson = Gson()
            val result = gson.fromJson(
                InputStreamReader(conn.inputStream, "UTF-8"),
                ISSResult::class.java
            )
            Log.e("data!", gson.toJson(result).toString())
            result
        }
    }
}