package prog;

import java.util.ArrayList;

public class File implements Component{
    private String name;
    private String content = "";

    public File(String name, Object content ) {
        this.content = (String)content;
        this.name = name;
    }



    @Override
    public String getName() {
        var res = this.name;
        return res;
    }

    @Override
    public String getContent() {
        return content;
    }

    @Override
    public <T> void setContent(T o) {
        content = (String)o;
    }

    @Override
    public void setName(String name){
        this.name = name;
    }


    public File(String name) {
        this.name = name;
    }

    @Override
    public void add(Component c) {
        throw new UnsupportedOperationException();
    }

    @Override
    public void remove(int i) {
        throw new UnsupportedOperationException();
    }

    @Override
    public Component getChild(int i) {
        throw new UnsupportedOperationException();
    }

    public void printRec(int indent) {
        String ind = "";
        for (int i = 0; i < indent; i ++){
            ind += "    ";
        }

        System.out.println(ind + this.name);
    }

    @Override
    public void printContent(){
        System.out.println(this.content);
    }
}
