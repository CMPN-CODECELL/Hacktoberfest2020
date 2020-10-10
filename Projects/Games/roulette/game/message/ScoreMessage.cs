using Newtonsoft.Json;

namespace Roulette.game.message
{
    public class ScoreMessage : Message
    {
        private int _score;
        private int _newBalance;
        
        public ScoreMessage(int score, int newBalance) : base("SCORE_MESSAGE")
        {
            _score = score;
            _newBalance = newBalance;
            _success = true;
        }
        
        [JsonProperty("score")]
        public int Score => _score;

        [JsonProperty("balance")]
        public int NewBalance => _newBalance;
    }
}