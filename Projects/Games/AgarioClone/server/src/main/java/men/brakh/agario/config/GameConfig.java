package men.brakh.agario.config;

import java.io.FileInputStream;
import java.io.IOException;
import java.util.Properties;

public class GameConfig {
    private static GameConfig instance;

    private int spawnSize;
    private String[] availableColors;
    private int maxSpeed;
    private int mobsCount;
    private int mobSize;
    private int fieldHeight;
    private int fieldWidth;
    private double eatingCoefficient;
    private int minDelay;

    public int getSpawnSize() {
        return spawnSize;
    }

    public String[] getAvailableColors() {
        return availableColors;
    }

    public int getMaxSpeed() {
        return maxSpeed;
    }

    public int getMobsCount() {
        return mobsCount;
    }

    public int getMobSize() {
        return mobSize;
    }

    public int getFieldHeight() {
        return fieldHeight;
    }

    public int getFieldWidth() {
        return fieldWidth;
    }

    public int getMinDelay() {
        return minDelay;
    }

    public double getEatingCoefficient() {
        return eatingCoefficient;
    }

    public static synchronized GameConfig getInstance() {
        if (instance == null) {
            instance = new GameConfig();
        }
        return instance;
    }

    private GameConfig() {
        String appConfigPath = "src/main/resources/game.properties";

        Properties editorProps = new Properties();
        try {
            editorProps.load(new FileInputStream(appConfigPath));
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        // Заполняем значения
        spawnSize = Integer.valueOf(editorProps.getProperty("spawn.size"));
        availableColors = editorProps.getProperty("spawn.colors").split(",");
        maxSpeed = Integer.valueOf(editorProps.getProperty("speed.max"));
        fieldWidth = Integer.valueOf(editorProps.getProperty("field.width"));
        fieldHeight = Integer.valueOf(editorProps.getProperty("field.height"));
        mobsCount = Integer.valueOf(editorProps.getProperty("mobs.count"));
        mobSize = Integer.valueOf(editorProps.getProperty("mobs.size"));
        eatingCoefficient = Double.valueOf(editorProps.getProperty("eating.coefficient"));
        minDelay = Integer.valueOf(editorProps.getProperty("speed.delay"));
    }
}
