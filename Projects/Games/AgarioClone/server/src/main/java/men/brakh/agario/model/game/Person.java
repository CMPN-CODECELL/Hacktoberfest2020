package men.brakh.agario.model.game;

import men.brakh.agario.model.Point;

import java.util.Objects;

/**
 * Класс персонажа игры
 */
public class Person {
    /**
     * ID Персонажа
     */
    private int id;

    /**
     * Размер персонажа
     */
    private int size;

    /**
     * Имя персонажа
     */
    private String username;

    /**
     * Цвет персонажа
     */
    private String color;

    /**
     * Координаты центра персонажа
     */
    private Point center;


    private Person(){}

    /**
     * Съесть другого персонажа
     * @param person другой персонаж
     */
    public void eat(Person person, double coefficient) {
        if(this.size > person.size) {
            this.size += person.size / coefficient;
            person.size = -1;
        }
    }

    /**
     * Проверка, пересекаются ли персонажи
     * @return true, если пересекаются
     */
    public boolean isIntersect(Person person) {
        int r1 = size;
        int r2 = person.size;

        double d = center.distanceTo(person.center);

        int sr= r1 + r2;

        return d<=sr/2;
    }

    public void changeCenter(Point center) {
        this.center = center;
    }

    public int getId() {
        return id;
    }

    public int getSize() {
        return size;
    }

    public String getUsername() {
        return username;
    }

    public String getColor() {
        return color;
    }

    public Point getCenter() {
        return center;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Person person = (Person) o;
        return id == person.id;
    }

    @Override
    public int hashCode() {
        return Objects.hash(id, username);
    }


    /**
     * Получение билдера
     */
    public static Builder newBuilder() {
        return new Person().new Builder();
    }


    public class Builder {
        private Builder() {
        }

        public Builder setUsername(String username) {
            Person.this.username = username;
            return this;
        }

        public Builder setId(int id) {
            Person.this.id = id;
            return this;
        }

        public Builder setSize(int size) {
            Person.this.size = size;
            return this;
        }

        public Builder setColor(String color) {
            Person.this.color = color;
            return this;
        }

        public Builder setCenter(Point center) {
            Person.this.center = center;
            return this;
        }

        public Person build() {
            if(username == null) {
                throw new RuntimeException("Username not found");
            }
            return Person.this;
        }
    }
}
