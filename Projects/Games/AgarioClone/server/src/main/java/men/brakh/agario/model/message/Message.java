package men.brakh.agario.model.message;

import men.brakh.agario.model.enums.EventType;
import men.brakh.agario.model.game.Person;

/**
 * Класс сообщений для общения с клиентом
 */
public class Message {
    /**
     * Тип изменения в игре (убийство персонажа, перемещение и тд)
     */
    private EventType eventType;

    /**
     * Персонаж, с которым случились изменения
     */
    private Person person;

    public Message() {
    }

    public Message(EventType eventType, Person person) {
        this.eventType = eventType;
        this.person = person;
    }

    public EventType getEventType() {
        return eventType;
    }

    public void setEventType(EventType eventType) {
        this.eventType = eventType;
    }

    public Person getValue() {
        return person;
    }

    public void setValue(Person person) {
        this.person = person;
    }

    @Override
    public String toString() {
        return "Message{" +
                "eventType=" + eventType +
                ", person=" + person +
                '}';
    }
}