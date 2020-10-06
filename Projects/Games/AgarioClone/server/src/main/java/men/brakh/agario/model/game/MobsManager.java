package men.brakh.agario.model.game;

import men.brakh.agario.config.GameConfig;
import men.brakh.agario.model.communicator.impl.CallbackCommunicator;
import men.brakh.agario.model.communicator.Communicator;
import men.brakh.agario.model.enums.EventType;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.ArrayList;
import java.util.List;

class MobsManager {
    Logger logger = LoggerFactory.getLogger(MobsManager.class);

    private GameConfig config = GameConfig.getInstance();
    private GameField field;
    private List<Person> mobs = new ArrayList<>();

    private void spawn() {
        Communicator communicator = new CallbackCommunicator(
                () -> {spawn(); return null;},
                (message, thisCommunicator) -> message.getEventType() == EventType.DEAD &&
                        thisCommunicator.equals(field.getCommunicator(message.getValue()))
        );

        Person mob = field.add("mob", communicator, config.getMobSize());
        logger.info(String.format("Mob[%d] spawned", mob.getId()));
    }

    MobsManager(GameField field) {
        this.field = field;
        for(int i = 0; i < config.getMobsCount(); i++) {
            spawn();
        }
    }
}
