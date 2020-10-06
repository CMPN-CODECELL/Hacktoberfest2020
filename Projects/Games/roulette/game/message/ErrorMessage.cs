using Newtonsoft.Json;

namespace Roulette.game.message
{
    public class ErrorMessage : Message
    {
        private string _message;

        public ErrorMessage(string message) : base("ERROR_MESSAGE")
        {
            _success = false;
            _message = message;
        }
        
        [JsonProperty("message")] 
        public string ErrorMessageText => _message;
    }
}