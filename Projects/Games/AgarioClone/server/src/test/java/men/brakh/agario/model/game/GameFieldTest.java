package men.brakh.agario.model.game;

import men.brakh.agario.model.Point;
import men.brakh.agario.model.communicator.Communicator;
import men.brakh.agario.model.enums.EventType;
import men.brakh.agario.model.message.Message;
import org.junit.Test;

import java.util.ArrayList;
import java.util.List;

import static org.junit.Assert.assertEquals;

public class GameFieldTest {
    private class TestCommunicator implements Communicator {
        List<Message> messages = new ArrayList<>();

        @Override
        public void send(Message message) {
            messages.add(message);
        }
    };

    @Test
    public void add() {
        GameField gameField = new GameField(false);
        TestCommunicator com1 = new TestCommunicator();
        gameField.add("1", com1);

        assertEquals(com1.messages.get(0).getEventType(), EventType.SPAWN);

    }

    @Test
    public void checkForIntersect() {
    }

    @Test
    public void move() {
        GameField gameField = new GameField(false);
        TestCommunicator com1 = new TestCommunicator();
        TestCommunicator com2 = new TestCommunicator();

        Person person1 = gameField.add("1", com1);
        Person person2 = gameField.add("2", com2);

        gameField.move(com1, new Point(0,0 ));

        assertEquals(com1.messages.get(com1.messages.size() - 1).getEventType(), EventType.COORDS_CHANGING);
        assertEquals(com2.messages.get(com2.messages.size() - 1).getEventType(), EventType.COORDS_CHANGING);

        assertEquals(com1.messages.get(com1.messages.size() - 1).getValue().getUsername(), "1");
        assertEquals(com2.messages.get(com2.messages.size() - 1).getValue().getUsername(), "1");

        Communicator mobCommunicator = new TestCommunicator();
        Person mob = gameField.add("mob", mobCommunicator, 10);
        assertEquals(com1.messages.get(com1.messages.size() - 1).getEventType(), EventType.SPAWN);
        Point mobCenter = com1.messages.get(com1.messages.size() - 1).getValue().getCenter();

        gameField.move(mobCommunicator, person2.getCenter());

        assertEquals(com1.messages.get(com1.messages.size() - 1).getEventType(), EventType.DEAD);
        assertEquals(com1.messages.get(com1.messages.size() - 1).getValue().getId(), 3);
    }
}