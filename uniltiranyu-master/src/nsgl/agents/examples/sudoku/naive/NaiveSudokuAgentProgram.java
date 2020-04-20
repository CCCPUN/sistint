package nsgl.agents.examples.sudoku.naive;
import nsgl.agents.*;
import nsgl.agents.examples.sudoku.*;
import nsgl.generic.array.Vector;
import nsgl.graph.ConstantCost;
import nsgl.graph.search.uninformed.DepthFirstSearch;

/**
 * <p>Title: </p>
 *
 * <p>Description: </p>
 *
 * <p>Copyright: Copyright (c) 2007</p>
 *
 * <p>Company: Universidad Nacional de Colombia</p>
 *
 * @author Jonatan Gómez
 * @version 1.0
 */
public class NaiveSudokuAgentProgram implements AgentProgram{
  Vector<Action> cmd = new Vector<Action>();
  public NaiveSudokuAgentProgram() {
  }

  public void init(){
    cmd.clear();
  }

  public Action compute( Percept percept ){
    if( cmd.size() == 0 ){
      NaiveSudokuBoardState initial_state = new NaiveSudokuBoardState((SudokuPercept)percept);
      int depth = initial_state.board.emptyPlaces();
      DepthFirstSearch<NaiveSudokuBoardState,Action> search = new DepthFirstSearch<NaiveSudokuBoardState,Action>(depth);
      cmd = search.apply( initial_state, new NaiveSudokuSearchSpace(),
                          new NaiveSudokuGoalTest(), new ConstantCost<NaiveSudokuBoardState,Action>() );
      if( cmd == null ){ cmd = new Vector<Action>(); }
    }
    if( cmd.size() > 0 ){
      try{
    	Action action = cmd.get(0);
    	cmd.remove(0);
    	return action;
      }catch(Exception e){}
    }
    return null;
  }
}
