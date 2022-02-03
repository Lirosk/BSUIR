package prog;

public interface Component {
    <T> void setContent(T o);
    <T> T getContent();
    void setName(String name);
    String getName();
    void add (Component c);
    void remove(int i);
    void printContent();
    Component getChild(int i);
}
