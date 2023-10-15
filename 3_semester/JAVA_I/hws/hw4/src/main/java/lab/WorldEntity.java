package lab;

import javafx.scene.canvas.GraphicsContext;

public abstract class WorldEntity implements DrawableSimulable {
    private final World world;

    public WorldEntity(World world){
        this.world = world;
    }
    
    @Override
    public void draw(GraphicsContext gc){
        gc.save();
        drawInternal(gc);
        gc.restore();
    }

    protected World getWorld(){
        return this.world;
    }

    protected abstract void drawInternal(GraphicsContext gc);
}
