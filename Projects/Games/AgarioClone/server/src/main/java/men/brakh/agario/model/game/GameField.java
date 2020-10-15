package men.brakh.agario.model.game;

import men.brakh.agario.config.GameConfig;
import men.brakh.agario.model.Point;
import men.brakh.agario.model.communicator.Communicator;
import men.brakh.agario.model.enums.EventType;
import men.brakh.agario.model.message.Message;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.Date;
import java.util.Map;
import java.util.Random;
import java.util.concurrent.ConcurrentHashMap;

public class GameField {
    private Logger logger = LoggerFactory.getLogger(GameField.class);

    private GameConfig config = GameConfig.getInstance();

    private Map<Communicator, Person> persons = new ConcurrentHashMap<>();
    private Map<Communicator, Date> lastUpdate = new ConcurrentHashMap<>();

    private volatile int lastId = 0;

    private MobsManager mobsManager;


    public GameField() {
        this(true);
    }

    public GameField(boolean withMobs) {
        if(withMobs) {
            mobsManager = new MobsManager(this);
        }
    }

    /**
     * Получение рандомного цвета для нового игрока
     */
    private String getRandColor() {
        String[] colors = config.getAvailableColors();
        return colors[new Random().nextInt(colors.length)];
    }

    /**
     * Получение нового id для нового игрока
     */
    private synchronized int getNewId() {
        return ++lastId;
    }

    /**
     * Получение точки, где нет игроков
     */
    private Point getFreePoint() {
        int x = new Random().nextInt(config.getFieldWidth());
        int y = new Random().nextInt(config.getFieldHeight());

        final boolean[] isFree = {true};
        persons.forEach(
                (communicator, currPerson) -> {
                    if( (x > currPerson.getCenter().getX() - currPerson.getSize()
                            && x < currPerson.getCenter().getX() + currPerson.getSize()
                        ) || (
                            y > currPerson.getCenter().getY() - currPerson.getSize()
                            && y < currPerson.getCenter().getY() + currPerson.getSize()))  {

                        isFree[0] = false;
                    }
                }
        );

        if(isFree[0]) {
            return new Point(x,y);
        }

        return getFreePoint();
    }

    /**
     * Добавление нового игрока
     * @param username Имя игрока
     * @param communicator Объект для связи с игроком
     * @return добавленный игрок
     */
    public Person add(String username, Communicator communicator, int size) {
        Person person = Person.newBuilder()
                .setId(getNewId())
                .setUsername(username)
                .setSize(size)
                .setColor(getRandColor())
                .setCenter(getFreePoint())
                .build();

        persons.put(communicator, person);
        lastUpdate.put(communicator, new Date());
        communicator.send(new Message(EventType.MY_SPAWN, person));
        broadcast(new Message(EventType.SPAWN, person), person);

        persons.forEach(
                (otherCommunicator, otherPerson) -> {
                    if(!person.equals(otherPerson)) {
                        communicator.send(new Message(EventType.SPAWN, otherPerson));
                    }
                }
        );

        return person;
    }

    public Person add(String username, Communicator communicator) {
        return add(username, communicator, config.getSpawnSize());
    }

    /**
     * Проверяет, не пересекаются ли персонажи. Если пересекаются - персонажи едят друг друга
     * @param person Персонаж
     * @return true, если запрашиваемый персонаж умер
     */
    public boolean checkForIntersect(Person person) {
        boolean[] isDead = {false};

        persons.forEach(
                (communicator, secondPerson) -> {
                    if(person.isIntersect(secondPerson) && !person.equals(secondPerson)) {
                        Person deadPerson;
                        Person extendedPerson;

                        if(person.getSize() > secondPerson.getSize()) {
                            deadPerson = secondPerson;
                            extendedPerson = person;
                        } else if(person.getSize() < secondPerson.getSize()){
                            deadPerson = person;
                            isDead[0] = true;
                            extendedPerson = secondPerson;
                        } else {
                            return;
                        }

                        extendedPerson.eat(deadPerson, config.getEatingCoefficient());
                        kill(getCommunicator(deadPerson));
                        broadcast(new Message(EventType.SIZE_CHANGING, extendedPerson));
                        logger.info(String.format("%s[%d] eat %s[%d]", extendedPerson.getUsername(), extendedPerson.getId(),
                                deadPerson.getUsername(), deadPerson.getId()));
                    }
                }
        );

        return isDead[0];
    }

    public Communicator getCommunicator(Person person) {
        Communicator[] communicator = {null};
        persons.forEach(
                (communicator1, person1) -> {
                    if(person.equals(person1)) {
                        communicator[0] = communicator1;
                    }
                }
        );

        return communicator[0];
    }

    /**
     * Перемещение персонажа
     */
    public void move(Communicator communicator, Point newPoint) {
        Person person = persons.get(communicator);

        if(!lastUpdate.containsKey(communicator)) {
            return;
        }
        int delay = (int) ((new Date().getTime() - lastUpdate.get(communicator).getTime()));
        lastUpdate.put(communicator, new Date());

        if(delay < config.getMinDelay() - 5 // Поегрешность
                || Math.abs(person.getCenter().getX() - newPoint.getX()) > config.getMaxSpeed()
                || Math.abs(person.getCenter().getY() - newPoint.getY()) > config.getMaxSpeed()) {
            logger.warn(String.format("CHEATING by %s[%d]. Delay: %d, speed: %d/%d",
                    person.getUsername(), person.getId(), delay,
                    person.getCenter().getX() - newPoint.getX(),
                    person.getCenter().getY() - newPoint.getY()));

            communicator.send(new Message(EventType.CHEATING, person));
            broadcast(new Message(EventType.COORDS_CHANGING, person));
            return;

        }
        // TODO: CHEATING CHECKING
        person.changeCenter(newPoint);

        if(checkForIntersect(person)) {
            return;
        }

        broadcast(new Message(EventType.COORDS_CHANGING, person));
    }

    public void kill(Communicator communicator) {
        Person person = persons.get(communicator);
        broadcast(new Message(EventType.DEAD, person));
        persons.remove(communicator);
        lastUpdate.remove(communicator);
    }

    /**
     * Отправка уведомления всем пользователям
     * @param message Объект сообщения
     */
    private void broadcast(Message message) {
        persons.forEach(
                (communicator, person) -> {
                    communicator.send(message);
                }
        );
    }

    private void broadcast(Message message, Person excludePerson) {
        persons.forEach(
                (communicator, person) -> {
                    if(!person.equals(excludePerson))
                        communicator.send(message);
                }
        );
    }
}
