using System;
using System.Net.WebSockets;
using System.Threading;
using System.Threading.Tasks;
using Newtonsoft.Json;
using NLog;
using Roulette.game.betRequest;
using Roulette.game.message;
using Roulette.logger;

namespace Roulette.game.client
{
    public class WebSocketRouletteClient : RouletteClient
    {
        private Logger _logger = NLogConfiguration.CurrentLogger;
        private WebSocket _webSocket;
        
        public WebSocketRouletteClient(WebSocket webSocket, RouletteSession rouletteSession, string name) 
            : base(rouletteSession, name)
        {
            _webSocket = webSocket;
        }

        public override async Task SendMessage(Message message)
        {
            string json = JsonConvert.SerializeObject(message);
            _logger.Info("New message to " + Name + ": " + json);
            
            byte[] bytes = System.Text.Encoding.UTF8.GetBytes(json);
            await _webSocket.SendAsync(new ArraySegment<byte>(bytes, 0, bytes.Length), 
                WebSocketMessageType.Text, true, CancellationToken.None);

        }

        public void ReceiveBetAsByteArray(byte[] buffer)
        {
            string strMessage =  System.Text.Encoding.UTF8.GetString(buffer);
            BetRequest betRequest = JsonConvert.DeserializeObject<BetRequest>(strMessage);
            AcceptBet(betRequest);
        }

      
    }
}