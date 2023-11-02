package lab;

public class Score {
    private int score;
    private String name;

    public Score(int score, String name) {
        this.score = score;
        this.name = name;
    }

    public int getScore() {
        return score;
    }

    @Override
    public String toString(){
        return this.name + ": " + this.score;
    }

    public String getName() {
        return name;
    }

    @Override
    public int hashCode() {
        return name.hashCode();
    }

    @Override
    public boolean equals(Object obj) {
        if(obj instanceof Score s){
            return s.getName().equals(this.name);
        }
        return false;
    }
}
