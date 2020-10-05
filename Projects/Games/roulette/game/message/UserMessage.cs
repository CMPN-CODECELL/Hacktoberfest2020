using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace Roulette.game.message
{
    public class UserMessage : Message
    {
        private string _name;
        private string _message;
        
        public UserMessage(string name, string message) : base("USER_MESSAGE")
        {
            _name = name;
            _message = message;
        }

        public UserMessage(string name, string message, string type) : base(type)
        {
            _name = name;
            _message = message;
        }
        
        [JsonProperty("message")]
        public string Message => _message;

        [JsonProperty("name")]
        public string Name => _name;
    }
}