package nsgl.agents.examples.sudoku;
import nsgl.agents.*;
import nsgl.agents.examples.sudoku.naive.*;
import nsgl.agents.simulate.util.*;

public class SudokuMain {
  private static Language getLanguage(){
    return  new SudokuLanguage();
  }

  public static void main( String[] argv ){
    //    Agent agent = new Agent( new InteractiveAgentProgram( getLanguage() ) );
    Agent agent = new Agent( new NaiveSudokuAgentProgram() );
    SudokuMainFrame frame = new SudokuMainFrame( agent, getLanguage() );
    frame.setVisible(true);
  }
}
