using System;
using System.Linq;
using Newtonsoft.Json;

namespace Roulette.game.betRequest
{
    public class BetRequest
    {
        private readonly int[] _bets;
        private readonly int _amount;
        
        public BetRequest(int[] bets, int amount)
        {
            _bets = bets;
            _amount = amount;
        }

        public bool IsWon(int score)
        {
            return _bets.Contains(score);
        }

        public int Rate => 35 / _bets.Length;
        public int Amount => _amount;
    }
    
    
}




