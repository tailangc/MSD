package com.example.lab4

import androidx.room.Entity
import androidx.room.PrimaryKey

//Defines a SQLITE table, basically
@Entity(tableName="jokes")
data class JokeData(var joke: String){
    @PrimaryKey(autoGenerate = true)
    var id: Int = 0 // integer primary key for the DB
}