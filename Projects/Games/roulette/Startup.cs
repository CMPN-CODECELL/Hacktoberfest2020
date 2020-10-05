using System;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Builder;
using System.Net.WebSockets;
using Microsoft.AspNetCore.Hosting;
using Microsoft.Extensions.DependencyInjection;
using NLog;
using Roulette.game;
using Roulette.game.client;
using Roulette.logger;

namespace Roulette
{
    
    public class Startup
    {
        private static int _lastId = 0;

        private readonly Logger _logger = NLogConfiguration.CurrentLogger;
        
        private readonly RouletteSession _rouletteSession = new RouletteSession();
        
        public void ConfigureServices(IServiceCollection services)
        {
        }

        public void Configure(IApplicationBuilder app, IHostingEnvironment env)
        {
            if (env.IsDevelopment())
            {
                app.UseDeveloperExceptionPage();
            }

            app.UseDefaultFiles();
            app.UseStaticFiles();
            app.UseFileServer(enableDirectoryBrowsing: true);
            app.UseWebSockets(); 
            
            app.Map("/ws", builder =>
            {
                builder.Use(async (context, next) =>
                {
                    if (context.WebSockets.IsWebSocketRequest)
                    {
                        var webSocket = await context.WebSockets.AcceptWebSocketAsync();
                        await AcceptWebsocket(webSocket);
                        return;
                    }
                    await next();
                });
            });
        }

        private async Task AcceptWebsocket(WebSocket webSocket)
        {
            byte[] buffer = new byte[1024 * 4];
            
            var name = "User " + Interlocked.Increment(ref _lastId);
            
            _logger.Info("New websocket connection: " + name);

            var rouletteClient = new WebSocketRouletteClient(webSocket, _rouletteSession, name);
            _rouletteSession.ScoresEvent += rouletteClient.HandleScore;
            _rouletteSession.MessageBroadcastEvent += rouletteClient.SendMessage;
            var result = await webSocket.ReceiveAsync(new ArraySegment<byte>(buffer), CancellationToken.None);
            while (!result.CloseStatus.HasValue)
            {
                rouletteClient.ReceiveBetAsByteArray(buffer.Take(result.Count).ToArray());
                result = await webSocket.ReceiveAsync(new ArraySegment<byte>(buffer), CancellationToken.None);
            }
            _rouletteSession.ScoresEvent -= rouletteClient.HandleScore;
            _rouletteSession.MessageBroadcastEvent -= rouletteClient.SendMessage;

            _logger.Info(name + " disconnected");

            await webSocket.CloseAsync(result.CloseStatus.Value, result.CloseStatusDescription, CancellationToken.None);
        }
    }
}
