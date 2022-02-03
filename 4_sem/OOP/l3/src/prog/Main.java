package prog;

import java.lang.reflect.Type;

public class Main {

    public static void main(String[] args) {
        Folder disk = new Folder("disk");
        disk.add(new Folder("Tapping"));
        disk.add(new Folder("Games"));

        String content;

        disk.getChild(0).add(new Folder("C++"));
        disk.getChild(0).getChild(0).add(new File("cpp.cpp"));
        content = "int main() { printf(\"cpp.cpp\"); }";
        disk.getChild(0).getChild(0).getChild(0).setContent(content);


        disk.getChild(0).getChild(0).add(new File("task.cpp"));
        content = "int main() { printf(\"hello world\"); }";
        disk.getChild(0).getChild(0).getChild(1).setContent(content);


        disk.getChild(0).add(new Folder("Python"));
        disk.getChild(0).getChild(1).add(new File("py.py"));
        content = "print(\"py.py\")";
        disk.getChild(0).getChild(1).getChild(0).setContent(content);

        disk.getChild(0).getChild(1).add(new File("task.py"));
        content = "print(\"hello world\")";
        disk.getChild(0).getChild(1).getChild(1).setContent(content);

        disk.getChild(1).add(new Folder("Digger"));
        disk.getChild(1).getChild(0).add(new File("Digger.exe"));
        disk.getChild(1).add(new Folder("Digger 2"));
        disk.getChild(1).getChild(1).add(new File("Digger 2.exe"));
        disk.getChild(1).add(new Folder("Digger Remastered"));
        disk.getChild(1).getChild(2).add(new File("Digger Remastered.exe"));
        disk.getChild(1).add(new Folder("Digger Resurrected"));
        disk.getChild(1).getChild(3).add(new File("Digger Resurrected.exe"));
        disk.getChild(1).add(new Folder("Digger: new hope"));
        disk.getChild(1).getChild(4).add(new File("Digger: new hope.exe"));

        disk.printContent();
        disk.delete("Tapping/C++");
        System.out.println("\n");
        disk.printContent();
        System.out.println("\n");
        disk.delete("Games/Digger: new hope");
        disk.printContent();
        System.out.println("\n");
        disk.printOne("Tapping/Python");
        System.out.println("\n");

        disk.printOne("Tapping/Python/py.py");
        System.out.println("\n");

        disk.getByPath("Tapping/Python/py.py").setName("py.py.py");
        disk.printContent();
        System.out.println("\n");

        disk.getByPath("Games/Digger Resurrected").setContent((disk.getByPath("Tapping/Python")).getContent());
        disk.printContent();
        System.out.println("\n");
    }
}
