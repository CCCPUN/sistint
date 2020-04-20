package nsgl.agents.examples.labyrinth.teseo;
import nsgl.agents.examples.labyrinth.*;

public class TeseoPercept extends LabyrinthPercept{
  public TeseoPercept( int value ) {
    super( value );
    int flag = (1<<4);
    setAttribute( LabyrinthUtil.TREASURE, (value & flag)==flag );
  }
}
