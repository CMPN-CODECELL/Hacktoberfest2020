using Newtonsoft.Json;

namespace Roulette.game.message
{
    public abstract class Message
    {
        protected bool _success;
        private string _type;

        protected Message(string type)
        {
            _type = type;
        }
        
        [JsonProperty("success")]
        public bool Success => _success;

        [JsonProperty("type")] 
        public string Type => _type;
    }
}