using Microsoft.Extensions.Logging;
using Microsoft.Maui.Controls;
using Microsoft.Maui.Controls.Shapes;
using MySqlConnector;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;
using static ChessBrowser.parsePGN;
using static System.Runtime.InteropServices.JavaScript.JSType;

namespace ChessBrowser
{
  internal class Queries
  {

    /// <summary>
    /// This function runs when the upload button is pressed.
    /// Given a filename, parses the PGN file, and uploads
    /// each chess game to the user's database.
    /// </summary>
    /// <param name="PGNfilename">The path to the PGN file</param>
    internal static async Task InsertGameData( string PGNfilename, MainPage mainPage )
    {
      // This will build a connection string to your user's database on atr,
      // assuimg you've typed a user and password in the GUI

       // TODO:
      //       Load and parse the PGN file
      //       We recommend creating separate libraries to represent chess data and load the file

      // TODO:
      //       Use this to tell the GUI's progress bar how many total work steps there are
      //       For example, one iteration of your main upload loop could be one work step
      //mainPage.SetNumWorkItems( ... );

      string connection = mainPage.GetConnectionString();


      Console.WriteLine("at parser");
            List<ChessGame> games = parse(PGNfilename);
            mainPage.SetNumWorkItems(games.Count);
            Console.WriteLine("parsed");





            using (MySqlConnection conn = new MySqlConnection(connection))
            {
                try
                {
                    // Open a connection
                    conn.Open();
                    var commands = new List<MySqlCommand>();
                    Console.WriteLine(games.Count());
                }
                
                catch (Exception e)
                {
                    System.Diagnostics.Debug.WriteLine(e.Message);

                }

                for (int i = 0; i < games.Count(); i++)
                {
                    try
                    {
                        MySqlCommand eventsCommand = conn.CreateCommand();
                        MySqlCommand command = conn.CreateCommand();
                        MySqlCommand eIDCommand = conn.CreateCommand();
                        MySqlCommand command2 = conn.CreateCommand();

                        // check for existing event
                        eventsCommand.CommandText = "SELECT Name,Site,Date,eID from Events Where Name LIKE '" + games[i].eventName + "';";
                        bool eventExists = false;
                        long eID = 0;


                        using (MySqlDataReader reader = eventsCommand.ExecuteReader())
                        {
                            while (reader.Read())
                            {
                                if (reader["Name"].ToString() == games[i].eventName && reader["Site"].ToString() == games[i].site && Convert.ToDateTime(reader["Date"].ToString()).ToString("MM/dd/yyyy hh:mm:ss tt") == Convert.ToDateTime(games[i].eventDate).ToString("MM/dd/yyyy hh:mm:ss tt"))
                                {
                                    eID = long.Parse(reader["eID"].ToString());
                                    eventExists = true;
                                    break;
                                }
                            }
                        }

                        // check for existing players
                        eventsCommand.CommandText = "SELECT DISTINCT Name,Elo,pID FROM Players;";
                        bool wPlayerExists = false;
                        bool bPlayerExists = false;

                        long wpID = 0;
                        long bpID = 0;
                        using (MySqlDataReader reader = eventsCommand.ExecuteReader())
                        {
                            while (reader.Read())
                            {


                                if (reader["Name"].ToString() == games[i].blackPlayer)
                                {
                                    bpID = long.Parse(reader["pID"].ToString());
                                    bPlayerExists = true;

                                }

                                if (reader["Name"].ToString() == games[i].whitePlayer)
                                {
                                    wpID = long.Parse(reader["pID"].ToString());
                                    wPlayerExists = true;
                                }

                            }
                        }
                        if (eventExists)
                        {
                            command.Parameters.AddWithValue("@eventName", games[i].eventName);
                            command.Parameters.AddWithValue("@site", games[i].site);
                            command.Parameters.AddWithValue("@date", games[i].eventDate);
                            command.Parameters.AddWithValue("@blackName", games[i].blackPlayer);
                            command.Parameters.AddWithValue("@blackElo", games[i].blackElo);
                            command.Parameters.AddWithValue("@whiteName", games[i].whitePlayer);
                            command.Parameters.AddWithValue("@whiteElo", games[i].whiteElo);


                            command.Parameters.AddWithValue("@eID", eID);
                            command.Parameters.AddWithValue("@bpID", null);
                            command.Parameters.AddWithValue("@wpID", null);

                            command.CommandText = "INSERT INTO Players Values (@blackName, @blackElo, @bpID) ON DUPLICATE KEY UPDATE Elo=GREATEST(Elo, VALUES(Elo));";
                            command.ExecuteNonQuery();
                            if (!bPlayerExists)
                                bpID = command.LastInsertedId;

                            command.CommandText = "INSERT INTO Players Values (@whiteName, @whiteElo, @wpID) ON DUPLICATE KEY UPDATE Elo=GREATEST(Elo, VALUES(Elo));"; ;
                            command.ExecuteNonQuery();
                            if (!wPlayerExists)
                                wpID = command.LastInsertedId;

                            command.CommandText = "INSERT INTO Games Values(@round, @result, @moves, @blackID, @whiteID, @eIDGenerated) ON DUPLICATE KEY UPDATE Result=Result;";

                            command.Parameters.AddWithValue("@round", games[i].round);
                            command.Parameters.AddWithValue("@result", games[i].result);
                            command.Parameters.AddWithValue("@moves", games[i].moves);
                            command.Parameters.AddWithValue("@blackID", bpID);
                            command.Parameters.AddWithValue("@whiteID", wpID);
                            command.Parameters.AddWithValue("@eIDGenerated", eID);

                            command.ExecuteNonQuery();
                        }

                        else
                        {
                            command.Parameters.AddWithValue("@eventName", games[i].eventName);
                            command.Parameters.AddWithValue("@site", games[i].site);

                            command.Parameters.AddWithValue("@date", games[i].eventDate);
                            command.Parameters.AddWithValue("@blackName", games[i].blackPlayer);
                            command.Parameters.AddWithValue("@blackElo", games[i].blackElo);
                            command.Parameters.AddWithValue("@whiteName", games[i].whitePlayer);
                            command.Parameters.AddWithValue("@whiteElo", games[i].whiteElo);
                            command.Parameters.AddWithValue("@eID", null);
                            command.Parameters.AddWithValue("@bpID", null);
                            command.Parameters.AddWithValue("@wpID", null);

                            command.CommandText = "INSERT INTO Events Values (@eventName, @site, @date, @eID);";
                            command.ExecuteNonQuery();
                            eID = command.LastInsertedId;

                            command.CommandText = "INSERT INTO Players Values (@blackName, @blackElo, @bpID) ON DUPLICATE KEY UPDATE Elo=GREATEST(Elo, VALUES(Elo));";
                            command.ExecuteNonQuery();
                            if (!bPlayerExists)
                                bpID = command.LastInsertedId;

                            command.CommandText = "INSERT INTO Players Values (@whiteName, @whiteElo, @wpID) ON DUPLICATE KEY UPDATE Elo=GREATEST(Elo, VALUES(Elo));"; ;
                            command.ExecuteNonQuery();
                            if (!wPlayerExists)
                                wpID = command.LastInsertedId;

                            command.CommandText = "INSERT INTO Games Values(@round, @result, @moves, @blackID, @whiteID, @eIDGenerated) ON DUPLICATE KEY UPDATE Result=Result;";

                            command.Parameters.AddWithValue("@round", games[i].round);
                            command.Parameters.AddWithValue("@result", games[i].result);
                            command.Parameters.AddWithValue("@moves", games[i].moves);
                            command.Parameters.AddWithValue("@blackID", bpID);
                            command.Parameters.AddWithValue("@whiteID", wpID);
                            command.Parameters.AddWithValue("@eIDGenerated", eID);

                            command.ExecuteNonQuery();

                        }
                        await mainPage.NotifyWorkItemCompleted();

                    }

                    catch (Exception e)
                    {
                        System.Diagnostics.Debug.WriteLine(e.Message);
                        await mainPage.NotifyWorkItemCompleted();

                    }

                }

            }
        }


    

     


    /// <summary>
    /// Queries the database for games that match all the given filters.
    /// The filters are taken from the various controls in the GUI.
    /// </summary>
    /// <param name="white">The white player, or null if none</param>
    /// <param name="black">The black player, or null if none</param>
    /// <param name="opening">The first move, e.g. "1.e4", or null if none</param>
    /// <param name="winner">The winner as "W", "B", "D", or null if none</param>
    /// <param name="useDate">True if the filter includes a date range, False otherwise</param>
    /// <param name="start">The start of the date range</param>
    /// <param name="end">The end of the date range</param>
    /// <param name="showMoves">True if the returned data should include the PGN moves</param>
    /// <returns>A string separated by newlines containing the filtered games</returns>
    internal static string PerformQuery( string white, string black, string opening,
      string winner, bool useDate, DateTime start, DateTime end, bool showMoves,
      MainPage mainPage )
    {
      // This will build a connection string to your user's database on atr,
      // assuimg you've typed a user and password in the GUI
      string connection = mainPage.GetConnectionString();

      // Build up this string containing the results from your query
      string parsedResult = "";

      // Use this to count the number of rows returned by your query
      // (see below return statement)
      int numRows = 0;

      using ( MySqlConnection conn = new MySqlConnection( connection ) )
      {
        try
        {
          // Open a connection
          conn.Open();

          // TODO:
          //       Generate and execute an SQL command,
          //       then parse the results into an appropriate string and return it.


          // generate sql command query NOTE: ideally only want one query so joining all tables
                    string query = "SELECT event.Name AS EventName, event.Site AS Site, event.Date AS Date,\n" +
                        "playerWhite.Name AS PlayerWhiteName, playerBlack.Name AS PlayerBlackName,\n" +
                        "playerWhite.Elo AS EloWhite, playerBlack.Elo AS EloBlack,\n" +
                        "game.Result AS Result, game.Moves AS Moves\n" +
                        "FROM Events event JOIN Games game ON event.eID = game.eID\n" +
                        "JOIN Players playerWhite ON game.WhitePlayer = playerWhite.pID\n" +
                        "JOIN Players playerBlack ON game.BlackPlayer = playerBlack.pID\n" +
                        "WHERE TRUE"; 

                    if (white != null) 
                    {
                        query += " AND playerWhite.Name = @PlayerWhiteName"; 
                    }
                    if (black != null)
                    {
                        query += " AND playerBlack.Name = @PlayerBlackName";
                    }
                    if (opening != null)
                    {
                        query += " AND Moves LIKE @OpeningMove";
                    }
                    if (winner != null)
                    {
                        query += " AND Result = @Result";
                    }
                    if (useDate)
                    {
                        query += " AND Date >= @StartDate AND Date <= @EndDate"; 
                    }



                    // create a command from the query 
                    MySqlCommand command = new MySqlCommand(query, conn);

                    // NOTE: use prepred statements to prevent injection attacks
                    if (white != null) // if user passed value for white, want to pass to command as params used above
                    {
                        command.Parameters.AddWithValue("@PlayerWhiteName", white);
                    }
                    if (black != null)
                    {
                        command.Parameters.AddWithValue("@PlayerBlackName", black);
                    }
                    if (opening != null)
                    {
                        command.Parameters.AddWithValue("@OpeningMove", opening + "%");
                    }
                    if (winner != null)
                    {
                        command.Parameters.AddWithValue("@Result", winner);
                    }
                    if (useDate)
                    {
                        command.Parameters.AddWithValue("@StartDate", start);
                        command.Parameters.AddWithValue("@EndDate", end);
                    }




                  //parse the results into an appropriate string and return it.
                    MySqlDataReader rdr = command.ExecuteReader(); // this method queries the database
                    while (rdr.Read())
                    {
                        numRows += 1;
                        parsedResult += "\nEvent: " + rdr["EventName"];
                        parsedResult += "\nSite: " + rdr["Site"];
                        parsedResult += "\nDate: " + rdr["Date"];
                        parsedResult += "\nWhite: " + rdr["PlayerWhiteName"] + " (" + rdr["EloWhite"] + ")";
                        parsedResult += "\nBlack: " + rdr["PlayerBlackName"] + " (" + rdr["EloBlack"] + ")";
                        parsedResult += "\nResult: " + rdr["Result"];

                        if (showMoves)
                        {
                            parsedResult += "\nMoves: " + rdr["Moves"];
                        }
                    }
                    rdr.Close();
        }
        catch ( Exception e )
        {
          System.Diagnostics.Debug.WriteLine( e.Message );
        }
      }

      return numRows + " results\n" + parsedResult;
    }

  }
}
