using System;
using System.Threading.Tasks;
using Newtonsoft.Json;
using NLog;
using Roulette.game.betRequest;
using Roulette.game.message;
using Roulette.logger;

namespace Roulette.game.client
{
    public abstract class RouletteClient
    {
        private Logger _logger = NLogConfiguration.CurrentLogger;
        
        private readonly RouletteSession _rouletteSession;
        private BetRequest _betRequest;
        private int _balance;
        protected readonly string Name;
        
        protected RouletteClient(RouletteSession rouletteSession, string name)
        {
            _rouletteSession = rouletteSession;
            _balance = Config.BasicBalance;
            Name = name;
        }

        public void HandleScore(int score)
        {
            if (_betRequest != null)
            {
                if (_betRequest.IsWon(score))
                {
                    int prize = _betRequest.Amount * (_betRequest.Rate + 1);
                    _rouletteSession.Broadcast(new UserMessage(Name, "won " + prize + "$", "WON_MESSAGE"));
                    _balance += prize;
                }

                _betRequest = null;
            }

            SendMessage(new ScoreMessage(score, _balance));
        }

        public void AcceptBet(BetRequest betRequest)
        {
            if (_balance - betRequest.Amount < 0)
            {
                SendMessage(new ErrorMessage("You don't have enough money"));
                return;
            }
            
            _balance -= betRequest.Amount;
            _betRequest = betRequest;
            
            _rouletteSession.Broadcast(new UserMessage(Name, "bet " + betRequest.Amount + "$"));
            
            _logger.Info("New bet from " + Name  + ": " + JsonConvert.SerializeObject(betRequest));
        }

        public abstract Task SendMessage(Message message);

    }
}