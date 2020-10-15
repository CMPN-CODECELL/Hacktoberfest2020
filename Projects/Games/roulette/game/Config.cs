using System;

namespace Roulette.game
{
    public static class Config
    {
        public static int BasicBalance => 1000;
        public static TimeSpan GamesInterval => TimeSpan.FromSeconds(30); // TimeSpan.FromMinutes(1);
    }
}