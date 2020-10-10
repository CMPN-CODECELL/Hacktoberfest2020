package men.brakh.agario.model;

public class Point {
    private int x;
    private int y;

    public Point() {

    }

    public Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public Point add(Point deltaPoint) {
        x += deltaPoint.x;
        y += deltaPoint.y;
        return this;
    }


    public double distanceTo(Point point) {
        return Math.sqrt( (x - point.x)*(x - point.x) + (y - point.y)*(y - point.y));
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    public void setX(int x) {
        this.x = x;
    }

    public void setY(int y) {
        this.y = y;
    }
}
