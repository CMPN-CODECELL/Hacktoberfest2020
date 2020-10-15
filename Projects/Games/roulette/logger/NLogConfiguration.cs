using NLog;

namespace Roulette.logger
{
    public static class NLogConfiguration
    {
        public static Logger CurrentLogger
        {
            get
            {
                Сonfigure();
                return LogManager.GetCurrentClassLogger();
            }
        }
        
        private static void Сonfigure()
        {
            var config = new NLog.Config.LoggingConfiguration();

            var logfile = new NLog.Targets.FileTarget("logfile") { FileName = "log.txt" };
            var logconsole = new NLog.Targets.ConsoleTarget("logconsole");
            
            config.AddRule(LogLevel.Info, LogLevel.Fatal, logconsole);
            config.AddRule(LogLevel.Debug, LogLevel.Fatal, logfile);
            
            LogManager.Configuration = config;
        }
    }
}