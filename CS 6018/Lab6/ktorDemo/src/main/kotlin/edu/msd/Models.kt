package edu.msd

import org.jetbrains.exposed.dao.id.IntIdTable
import org.jetbrains.exposed.sql.Table


object User : IntIdTable() {} //we have just one field, ID, primary, int, auto increment

object Posts : IntIdTable() {
    //The post
    val text = varchar("text", 255)
    //Timestamp of post creation
    val timestamp = long("timestamp")
}

