using System;
using System.ComponentModel;
using System.Text;
using System.Text.RegularExpressions;
using System.Xml.Linq;
using GameController;
using Microsoft.EntityFrameworkCore.Diagnostics;
using static ChessBrowser.ChessGame;
namespace ChessBrowser
{
    public static class parsePGN
    {
        static parsePGN()
        {
        }
        public static List<ChessGame> parse(string fileName)
        {
            StreamReader sr = new StreamReader(fileName);
            string input = sr.ReadToEnd();
            string pattern = @"((?>\[{1})(?:(?'name'Event|Site|Round|White|Black|WhiteElo|BlackElo|Result|EventDate))(?>\s\W)(.+)(?>\S\]{1}))|(?<=\]\r\n\r\n)(?:.|\s|\r|\n)*?(?=\r\n\r\n)";
            Regex rgx = new Regex(pattern);
            MatchCollection matches = rgx.Matches(input);
            var games = new List<ChessGame>();
            Console.WriteLine(matches.Count());
            for (int i = 0; i < matches.Count(); i += 10)
            {
                ChessGame game = new ChessGame();
                game.eventName = matches[i].Groups[2].Value;
                game.site = matches[i + 1].Groups[2].Value;
                game.round = matches[i + 2].Groups[2].Value;
                game.whitePlayer = matches[i + 3].Groups[2].Value;
                game.blackPlayer = matches[i + 4].Groups[2].Value;
                if (matches[i + 5].Groups[2].Value.Equals("1-0"))
                {
                    game.result = "W";
                }
                else if (matches[i + 5].Groups[2].Value.Equals("0-1"))
                {
                    game.result = "B";
                }
                else if (matches[i + 5].Groups[2].Value.Equals("1/2-1/2"))
                {
                    game.result = "D";
                }
                else {
                    game.result = "N";
                }
                game.whiteElo = matches[i + 6].Groups[2].Value;
                game.blackElo = matches[i + 7].Groups[2].Value;
                game.eventDate = matches[i + 8].Groups[2].Value;
                game.moves = matches[i + 9].Groups[0].Value;
                games.Add(game);
            }
            Console.WriteLine(games.Count());
            return games;
        }
    }
}