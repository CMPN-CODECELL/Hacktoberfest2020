using System;
using System.Threading.Tasks;
using System.Timers;
using Roulette.game.message;
using Roulette.game.betRequest;
using Roulette.game.client;
using Timer = System.Threading.Timer;

namespace Roulette.game
{
    public class RouletteSession
    {
        private const int NumbersCount = 36;
        
        private Timer _timer;
        private readonly Random _random = new Random();
        
        
        public delegate void ScoreHandler(int score);
        public event ScoreHandler ScoresEvent;

        public delegate Task MessageHandler(Message message);
        public event MessageHandler MessageBroadcastEvent;

        public RouletteSession()
        {
            _timer = new Timer(
                e => ProcessGame(),  
                null, 
                TimeSpan.Zero, 
                Config.GamesInterval);
        }

        private void ProcessGame()
        {
            ScoresEvent?.Invoke(_random.Next(NumbersCount));
        }

        public void Broadcast(Message message)
        {
            MessageBroadcastEvent?.Invoke(message);
        }
    }
}