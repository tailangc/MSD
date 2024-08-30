package com.example.a6018lab1

import android.content.Intent
import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import com.example.a6018lab1.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        // Initialize View Binding
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Set up button click listeners
        binding.button1.setOnClickListener {
            val intent = Intent(this, MainActivity2::class.java)
            intent.putExtra("button_text", "Button 1 clicked!")
            startActivity(intent)
        }

        binding.button2.setOnClickListener {
            val intent = Intent(this, MainActivity2::class.java)
            intent.putExtra("button_text", "Button 2 clicked!")
            startActivity(intent)
        }

        binding.button3.setOnClickListener {
            val intent = Intent(this, MainActivity2::class.java)
            intent.putExtra("button_text", "Button 3 clicked!")
            startActivity(intent)
        }

        binding.button4.setOnClickListener {
            val intent = Intent(this, MainActivity2::class.java)
            intent.putExtra("button_text", "Button 4 clicked!")
            startActivity(intent)
        }

        binding.button5.setOnClickListener {
            val intent = Intent(this, MainActivity2::class.java)
            intent.putExtra("button_text", "Button 5 clicked!")
            startActivity(intent)
        }
    }
}
