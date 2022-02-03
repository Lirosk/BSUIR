package prog;

import java.util.ArrayList;

public class Folder implements Component{
    private String name;
    private ArrayList<Component> content;

    public Folder(String name) {
        this.name = name;
        this.content = new ArrayList<Component>();
    }

    @Override
    public String getName() {
        var res = this.name;
        return res;
    }

    @Override
    public void setName(String name){
        this.name = name;
    }

    @Override
    public <T> void setContent(T list) {
        content.addAll((ArrayList<Component>)list);
    }

    @Override
    public ArrayList<Component> getContent(){
        return content;
    }

    @Override
    public void remove(int i) {
        content.remove(i);
    }

    @Override
    public Component getChild(int i) {
        var res = content.get(i);
        return  res;
    }

    @Override
    public void add(Component c) {
        content.add(c);
    }

    @Override
    public void printContent() {
        this.printRec(0);
    }

    private void printRec(int indent){
        String ind = "";
        for (int i = 0; i < indent; i ++){
            ind += "    ";
        }

        System.out.println(ind + this.name);

        for (Component cont : this.content) {
            if (cont instanceof File) {
                ((File)cont).printRec(indent + 1);
            }
            else {
                ((Folder)cont).printRec(indent + 1);
            }
        }
    }

    public void delete(String path) {
        var pths = path.split("/");
        var iterable = this;
        var size = pths.length;
        var found = false;
        Component component;

        for (int i = 0; i < size; i++) {
            found = false;
            //for (var component: iterable.content) {
            for (int j = 0; j < iterable.content.size(); j ++) {
                component = iterable.content.get(j);
                if (component.getName().equals(pths[i])) {
                    if (i == size - 1) {
                        iterable.remove(j);
                    }
                    else
                    {
                        iterable = (Folder)component;
                    }
                    found = true;
                    break;
                }
            }

            if (!found) {
                throw new IndexOutOfBoundsException();
            }
        }
    }

    public void printOne(String path) {
        getByPath(path).printContent();
    }

    public Component getByPath(String path) {
        var pths = path.split("/");
        var iterable = this;
        var size = pths.length;
        var found = false;

        for (int i = 0; i < size; i++) {
            found = false;
            for (int j = 0; j < iterable.content.size(); j++) {
                var component = iterable.content.get(j);
                if (component.getName().equals(pths[i])) {
                    if (i == size - 1) {
                        return component;
                    } else {
                        iterable = (Folder)component;
                    }
                    found = true;
                    break;
                }
            }

            if (!found) {
                throw new IndexOutOfBoundsException();
            }
        }

        return null;
    }
}

