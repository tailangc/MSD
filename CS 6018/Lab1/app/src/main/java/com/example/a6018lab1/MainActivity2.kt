package com.example.a6018lab1

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import com.example.a6018lab1.databinding.ActivityMain2Binding

class MainActivity2 : AppCompatActivity() {

    private lateinit var binding: ActivityMain2Binding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        // Initialize View Binding
        binding = ActivityMain2Binding.inflate(layoutInflater)
        setContentView(binding.root)

        // Get the text passed from MainActivity
        val buttonText = intent.getStringExtra("button_text")

        // Set the text to a TextView or other UI element in this activity
        binding.textView.text = buttonText
    }
}
